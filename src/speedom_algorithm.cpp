// speedom_algorithm.cpp
#include "speedom_algorithm.h"

SpeedomAlgorithm::SpeedomAlgorithm() :
    max_steps(0),
    battery_size(0),
    starting_location(AlgoLoc()),
    current_location(starting_location),
    walls_sensor(),
    dirt_sensor(),
    battery_meter(),
    internal_house(starting_location, current_location)
    {}

void SpeedomAlgorithm::setMaxSteps(std::size_t maxSteps) {
    max_steps = maxSteps;
}

void SpeedomAlgorithm::setWallsSensor(const WallsSensor& wallsSensor) {
    walls_sensor = &wallsSensor;
}

void SpeedomAlgorithm::setDirtSensor(const DirtSensor& dirtSensor) {
    dirt_sensor = &dirtSensor;
}

void SpeedomAlgorithm::setBatteryMeter(const BatteryMeter& batteryMeter) {
    battery_meter = &batteryMeter;
}

bool SpeedomAlgorithm::isFeasible(size_t travel_distance, size_t current_battery) const {
    return travel_distance + 1 <= std::min(current_battery, max_steps);
}

Step SpeedomAlgorithm::updateCurrentLocAndGetNextStep(InternalHouse::LocationType target) {
    auto [step, next_location] = internal_house.calcStepToTarget(target);
    current_location = next_location;
    return step;
}

Step SpeedomAlgorithm::nextStep() {

    std::vector<AlgoLoc> possibleLocations = getPossibleLocations();
    size_t battery_level = battery_meter->getBatteryState();
    size_t dirt_level = dirt_sensor->dirtLevel();

    internal_house.updateGraph(dirt_level, possibleLocations);
    
    //TODO: possibility to prefer cleaning other parts rather than charging
    if (current_location == starting_location && battery_level < battery_size) {
        return Step::Stay;
    }

    internal_house.bfs(InternalHouse::DOCKING, std::nullopt);

    if (current_location == starting_location) {
        auto [travel_dist_to_chosen, chosen_location] = internal_house.minimalDistanceLocation();
        if (!isFeasible(travel_dist_to_chosen, battery_level)) {
            return Step::Finish;
        }
        internal_house.bfs(InternalHouse::CHOSEN, chosen_location);
        return updateCurrentLocAndGetNextStep(InternalHouse::CHOSEN);
    }

    if (dirt_level) {
        if (battery_level > internal_house.getDistanceToDoc(current_location)) {
            return Step::Stay;
        }

        return updateCurrentLocAndGetNextStep(InternalHouse::DOCKING);
    }

    internal_house.bfs(InternalHouse::CURRENT, std::nullopt);

    auto [travel_dist_to_chosen, chosen_location] = internal_house.minimalDistanceLocation();
    if (!isFeasible(travel_dist_to_chosen, battery_level)) {
        return updateCurrentLocAndGetNextStep(InternalHouse::DOCKING);
    }
    internal_house.bfs(InternalHouse::CHOSEN, chosen_location);
    return updateCurrentLocAndGetNextStep(InternalHouse::CHOSEN);
}



/* AlgorithmLocation */
SpeedomAlgorithm::AlgorithmLocation::AlgorithmLocation() : LocationBase() {}
SpeedomAlgorithm::AlgorithmLocation::AlgorithmLocation(int row, int col) : LocationBase(row, col) {}

// Copy Constructor
SpeedomAlgorithm::AlgorithmLocation::AlgorithmLocation(const AlgorithmLocation& other) : LocationBase(other.row, other.col) {}

// Copy Assignment Operator
SpeedomAlgorithm::AlgorithmLocation& SpeedomAlgorithm::AlgorithmLocation::operator=(const AlgorithmLocation& other) {
    if (this == &other) {
        return *this; 
    }
    row = other.row;
    col = other.col;
    return *this;
}

// Move Constructor
SpeedomAlgorithm::AlgorithmLocation::AlgorithmLocation(AlgorithmLocation&& other) noexcept : LocationBase(other.row, other.col) {
    other.row = 0;
    other.col = 0;
}

// Move Assignment Operator
SpeedomAlgorithm::AlgorithmLocation& SpeedomAlgorithm::AlgorithmLocation::operator=(AlgorithmLocation&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    row = other.row;
    col = other.col;
    other.row = 0;
    other.col = 0;
    return *this;
}

SpeedomAlgorithm::AlgorithmLocation::~AlgorithmLocation() {}

std::vector<SpeedomAlgorithm::AlgorithmLocation> SpeedomAlgorithm::getPossibleLocations() const {
    std::vector<SpeedomAlgorithm::AlgorithmLocation> possible_Locations;
    int curr_row = current_location.getRow();
    int curr_col = current_location.getCol();
    if (!walls_sensor->isWall(Direction::North)){
        possible_Locations.push_back(SpeedomAlgorithm::AlgorithmLocation(curr_row - 1, curr_col));
    }
    if (!walls_sensor->isWall(Direction::South)){
        possible_Locations.push_back(SpeedomAlgorithm::AlgorithmLocation(curr_row + 1, curr_col));
    }
    if (!walls_sensor->isWall(Direction::East)){
        possible_Locations.push_back(SpeedomAlgorithm::AlgorithmLocation(curr_row, curr_col + 1));
    }
    if (!walls_sensor->isWall(Direction::West)){
        possible_Locations.push_back(SpeedomAlgorithm::AlgorithmLocation(curr_row, curr_col - 1));
    }
    return possible_Locations;
}

void SpeedomAlgorithm::InternalHouse::bfs(LocationType start, std::optional<SpeedomAlgorithm::AlgorithmLocation> chosen_location) {
    std::queue<SpeedomAlgorithm::AlgorithmLocation> q;
    std::unordered_set<SpeedomAlgorithm::AlgorithmLocation> bfsVisited;

    if (start == DOCKING) {
        q.push(starting_location);
        bfsVisited.insert(starting_location);
        internal_graph.at(starting_location).distance_from_docking_station = 0;
        internal_graph.at(starting_location).father_from_docking = std::nullopt;
    } 
    
    else if (start == CURRENT) {
        q.push(current_location);
        bfsVisited.insert(current_location);
        internal_graph.at(current_location).distance_from_current = 0;
    }

    else {
        q.push(chosen_location.value());
        bfsVisited.insert(chosen_location.value());
    }

    while (!q.empty()) {
        SpeedomAlgorithm::AlgorithmLocation current = q.front();
        q.pop();

        for (SpeedomAlgorithm::AlgorithmLocation neighbor : internal_graph.at(current).neighbors) {
            if (bfsVisited.find(neighbor) == bfsVisited.end()) {
                if (start == DOCKING) {
                    internal_graph.at(neighbor).distance_from_docking_station = internal_graph.at(current).distance_from_docking_station + 1;
                    internal_graph.at(neighbor).father_from_docking = current;
                } 
                
                else if (start == CURRENT) {
                    internal_graph.at(neighbor).distance_from_current = internal_graph.at(current).distance_from_current + 1;
                } 

                else {
                    internal_graph.at(neighbor).father_from_chosen = current;
                }

                q.push(neighbor);
                bfsVisited.insert(neighbor);
            }
        }
    }
}


size_t SpeedomAlgorithm::InternalHouse::getDistanceToDoc(SpeedomAlgorithm::AlgorithmLocation other_location) const {
    return internal_graph.at(other_location).distance_from_docking_station;
}

SpeedomAlgorithm::AlgorithmLocation SpeedomAlgorithm::InternalHouse::getNextLocationToTarget(InternalHouse::LocationType target) const {
    return target == DOCKING ? 
        internal_graph.at(current_location).father_from_docking.value() : internal_graph.at(current_location).father_from_chosen.value();
}

std::pair<Step, SpeedomAlgorithm::AlgorithmLocation> SpeedomAlgorithm::InternalHouse::calcStepToTarget(InternalHouse::LocationType target) const {
    SpeedomAlgorithm::AlgorithmLocation next = getNextLocationToTarget(target);
    if (next.getRow() > current_location.getRow()){
        return std::make_pair(Step::South, next);
    }
    if (next.getRow() < current_location.getRow()){
        return std::make_pair(Step::North, next);
    }
    if (next.getCol() < current_location.getCol()){
        return std::make_pair(Step::West, next);
    }
    return std::make_pair(Step::East, next);

}

void SpeedomAlgorithm::InternalHouse::updateGraph(size_t dirt_level, const std::vector<SpeedomAlgorithm::AlgorithmLocation>& possible_Locations) {
    internal_graph.at(current_location).dirt_level = dirt_level;
    if(internal_graph.at(current_location).visited) {
        return;
    } 
    internal_graph.at(current_location).visited = true;
    internal_graph.at(current_location).neighbors = possible_Locations;
    for (auto& loc : possible_Locations) {
        if (!isInNeighbors(internal_graph.at(loc).neighbors, current_location)) {
            internal_graph.at(loc).neighbors.push_back(current_location);
        }
    } 
}


bool SpeedomAlgorithm::InternalHouse::isInNeighbors(const std::vector<SpeedomAlgorithm::AlgorithmLocation>& locations, 
                                                    SpeedomAlgorithm::AlgorithmLocation loc) const {
    
    return (std::find(locations.begin(), locations.end(), loc) != locations.end());
}

std::pair<size_t, SpeedomAlgorithm::AlgorithmLocation> SpeedomAlgorithm::InternalHouse::minimalDistanceLocation() const {
    
    auto min_location = (*internal_graph.begin()).first;
    size_t min_distance = calculateTravelDistance(min_location);

    for (const auto& entry : internal_graph) {
        if (entry.second.visited && entry.second.dirt_level == 0) {
            continue;
        }

        size_t current_dist = calculateTravelDistance(entry.first);
        if (current_dist < min_distance) {
            min_location = entry.first;
            min_distance = current_dist;
        }
    }
    return std::make_pair(min_distance, min_location);
    
}

size_t SpeedomAlgorithm::InternalHouse::calculateTravelDistance(SpeedomAlgorithm::AlgorithmLocation loc) const {
    
    if (current_location == starting_location) {
        return 2 * internal_graph.at(loc).distance_from_docking_station;
    }

    return internal_graph.at(loc).distance_from_docking_station + internal_graph.at(loc).distance_from_current;

    
}
