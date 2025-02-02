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
      delta_battery(0),
      enable_live_visualization(false),
      input_file("")
      {}

void Simulator::readHouseFile(const std::string input_file_path) {
    input_file = input_file_path;
    FileReader fr(input_file_path);
    FileReader::file_reader_output args = fr.readFile();
    setProperties(args.max_num_of_steps, args.max_battery_steps, args.house_map);
}

void Simulator::writeToOutputFile(Status status, std::string output_file) {
    FileWriter fw(output_file);
    fw.writeNumberOfSteps(history_path);
    fw.writeDirt(house->calcTotalDirt());
    fw.writeStatus(status);
    fw.writePath(history_path);
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

void Simulator::enableVisualization() {
    enable_live_visualization = true;
}

void Simulator::setAlgorithm(std::shared_ptr<SpeedomAlgorithm> alg) {
    alg->setWallsSensor(walls_sensor);
    alg->setDirtSensor(dirt_sensor);
    alg->setBatteryMeter(battery_meter);
    alg->setMaxSteps(max_steps);
    alg->setBatterySize(battery_size / 100);
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

std::string Simulator::addOutputPrefixToFilename(const std::string& path) const {
    std::size_t lastSlashPos = path.find_last_of('/');

    std::string directory = (lastSlashPos == std::string::npos) ? "" : path.substr(0, lastSlashPos + 1);
    std::string filename = (lastSlashPos == std::string::npos) ? path : path.substr(lastSlashPos + 1);

    std::string newFilename = "output_" + filename;

    return directory + newFilename;
}

void Simulator::run() {
    Step step;
    Status final_status = Status::WORKING;
    logger.log(INFO, "Simulator | Start cleaning house");
    for (size_t i = 0; i < max_steps; ++i) {

        if ((current_location != house->getDockingStation()) && current_battery <= 0) {
            logger.log(WARNING, "Simulator | Battery level is empty, Can not continue cleaning");
            final_status = Status::DEAD;
            addToHistory(step);
            break;
        }

        step = algo->nextStep();

        if ((step == Step::Stay) && (current_location == house->getDockingStation())) {
            if (current_battery == battery_size) {
                logger.log(WARNING, "Simulator | Stayed in docking station even though battary is full. Inappropriate behavior.");
            }
            current_battery = std::min(current_battery + delta_battery, battery_size);
            logger.log(INFO, std::format("Simulator | New battery after charging {}", current_battery / 100));
        }

        else if (step == Step::Stay) {
            logger.log(INFO, "Simulator | Stay and clean");
            updateDirtLevel();
            current_battery -= 100;
        }

        else if (step != Step::Finish) {
            move(step);
            house->getTile(current_location).setVisited();
            current_battery -= 100;
        }

        else {
            logger.log(INFO, "Simulator | Simulator successfully finished running ");
            if (enable_live_visualization) {
                live_simulator.simulate(*house, current_location, step, false, (max_steps - 1) - i, current_battery / 100);
            }
            final_status = Status::FINISH;
            addToHistory(step);
            break;
        }

        addToHistory(step);
        if (enable_live_visualization) {
            live_simulator.simulate(*house, current_location, step, current_location == house->getDockingStation(), (max_steps - 1) - i, current_battery / 100);
        }
    }

    if (final_status != Status::FINISH && current_location == house->getDockingStation() && algo->nextStep() == Step::Finish) {
        final_status = Status::FINISH;
        addToHistory(Step::Finish);
    }

    logger.log(INFO, "Simulator | Prepering output file");
    std::string output_file = addOutputPrefixToFilename(input_file);
    logger.log(INFO, std::format("Simulator | input file: {}, output file: {}", input_file, output_file));
    writeToOutputFile(final_status, output_file);
}

void Simulator::updateDirtLevel() {
    if (house->getTile(current_location).getDirtLevel() == 0) {
        logger.log(FATAL, "Stayed in a floor tile that is already clean. Inappropriate behavior.");
    }
    (house->getTile(current_location)).decreaseOneDirt();
}

void Simulator::move(Step step) {
    size_t rows = house->getRowsCount();
    size_t cols = house->getColsCount();
    size_t curr_row = current_location.getRow();
    size_t curr_col = current_location.getCol();
    Location next_loc;
    int next_row = 0;
    int next_col = 0;
    switch (step) {
        case Step::North:
            next_row = curr_row - 1;
            if (next_row < 0) {
                logger.log(FATAL, "Tried to move North from northest row");
            }
            next_loc = Location(next_row, curr_col);
            break;
        case Step::South:
            next_row = curr_row + 1;
            if (next_row >= (int)rows) {
                logger.log(FATAL, "Tried to move South from southest row");
            }
            next_loc = Location(next_row, curr_col);
            break;
        case Step::East:
            next_col = curr_col + 1;
            if (next_col >= (int)cols) {
                logger.log(FATAL, "Tried to move East from most east col");
            }
            next_loc = Location(curr_row, next_col);
            break;
        case Step::West:
            next_col = curr_col - 1;
            if (next_col < 0) {
                logger.log(FATAL, "Tried to move West from most west col");
            }
            next_loc = Location(curr_row, next_col);
            break;
        default:
            break;
    }
    if (house->getTile(next_loc).isWall()) {
        logger.log(FATAL, "Tried to move into a wall");
    }
    logger.log(INFO, std::format("Simulator | Move to location {}", next_loc.toString()));
    current_location = next_loc;
}






