#include "simulator.h"
#include "live_simulator.h"


Simulator::Simulator()
    : battery_size(0),
      current_battery(0),
      max_steps(0),
      house(nullptr),
      current_location(),
      history_path(),
      walls_sensor(current_location),
      battery_meter(current_battery),
      dirt_sensor(current_location),
      algo(nullptr),
      delta_battery(0) {}

void Simulator::readHouseFile(const std::string input_file_path) {
    FileReader fr(input_file_path);
    FileReader::file_reader_output args = fr.readFile();
    setProperties(args.max_num_of_steps, args.max_battery_steps, args.house_map);
}

//setters

void Simulator::setBatterySize(const size_t battery_size) {
    this->battery_size = battery_size * 100;
}

void Simulator::setCurrestBattery() {
    current_battery = battery_size;
}

void Simulator::setMaxSteps(const size_t max_steps) {
    this->max_steps = max_steps;
}

void Simulator::setHouse(const std::shared_ptr<House> house) {
    this->house = house;
}

//Todo
void Simulator::setCurrentLocation() {
    this->current_location = house->getDockingStation();
}

void Simulator::setWallsSensor() {
    walls_sensor.setHouse(house);
}

void Simulator::setDirtSensor() {
    dirt_sensor.setHouse(house);
}

void Simulator::setAlgorithm(std::shared_ptr<SpeedomAlgorithm> alg) {
    alg->setWallsSensor(walls_sensor);
    alg->setDirtSensor(dirt_sensor);
    alg->setBatteryMeter(battery_meter);
    alg->setMaxSteps(max_steps);
    algo = alg;
}

void Simulator::setProperties(const size_t max_num_of_steps, const size_t max_battery_steps,
                        const std::shared_ptr<House> house_map) {

    setBatterySize(max_battery_steps);
    setCurrestBattery();
    setMaxSteps(max_num_of_steps);
    setHouse(house_map);
    setCurrentLocation();
    setWallsSensor();
    setDirtSensor();
    delta_battery = battery_size / 20;

}

void Simulator::addToHistory(Step step) {
    history_path.addEntry(step);
}

const Path& Simulator::getPath() const {
    return history_path;
}

size_t Simulator::getHistoryLength() const {
    return history_path.getLength();
}


void Simulator::run() {
    for (size_t i = 0; i < max_steps; ++i) {
        Step step = algo->nextStep();

        //Stay in docking station
        if ((step == Step::Stay) && (current_location == house->getDockingStation())) {
            if (current_battery == battery_size) {
                logger.log(ERROR, "Stayed in docking station even though battary is full. Inappropriate behavior.");
            }

            current_battery = std::max(current_battery + delta_battery, battery_size);
        }

        //Stay and clean
        else if (step == Step::Stay) {
            updateDirtLevel();
            current_battery -= 100;
        }

        //Move to another location
        else if (step != Step::Finish) {
            move(step);
            current_battery -= 100;
        }

        //finish running
        else {
            
        }
        addToHistory(step);
        live_simulator.simulate(*house, current_location);

    }
}

void Simulator::updateDirtLevel() {
    if (house->getTile(current_location).getDirtLevel() == 0) {
        logger.log(ERROR, "Stayed in a floor tile that is already clean. Inappropriate behavior.");
    }
    (house->getTile(current_location)).decreaseOneDirt();
}

void Simulator::move(Step step) {
    size_t rows = house->getRowsCount();
    size_t cols = house->getColsCount();
    size_t curr_row = current_location.getRow();
    size_t curr_col = current_location.getCol();
    House::Location next_loc;
    switch (step) {
        case Step::North:
            int next_row = curr_row - 1;
            if (next_row < 0) {
                logger.log(ERROR, "Tried to move North from northest row");
            }
            next_loc = House::Location(next_row, curr_col);
            break;
        case Step::South:
            int next_row = curr_row + 1;
            if (next_row >= rows) {
                logger.log(ERROR, "Tried to move South from southest row");
            }
            next_loc = House::Location(next_row, curr_col);
            break;
        case Step::East:
            int next_col = curr_col + 1;
            if (next_col >= cols) {
                logger.log(ERROR, "Tried to move East from most east col");
            }
            next_loc = House::Location(curr_row, next_col);
            break;
        case Step::West:
            int next_col = curr_col - 1;
            if (next_col < 0) {
                logger.log(ERROR, "Tried to move West from most west col");
            }
            next_loc = House::Location(curr_row, next_col);
            break;
        default:
            break;
    }
    if (house->getTile(next_loc).isWall()) {
        logger.log(ERROR, "Tried to move West from most west col");
    }
    current_location = next_loc;
}






