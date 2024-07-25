#include "simulator.h"


MySimulator::MySimulator()
    : battery_size(0),
      current_battery(0),
      max_steps(0),
      house(nullptr),
      docking_loc(),
      current_location(),
      history_path(),
      walls_sensor(current_location),
      battery_meter(current_battery),
      dirt_sensor(current_location),
      algo(nullptr) {}

void MySimulator::readHouseFile(const std::string input_file_path) {
    FileReader fr(input_file_path);
    FileReader::file_reader_output args = fr.readFile();
    setProperties(args.max_num_of_steps, args.max_battery_steps, args.house_map, args.docking_loc);
}

//setters

void MySimulator::setBatterySize(const size_t battery_size) {
    this->battery_size = battery_size;
}

void MySimulator::setCurrestBattery() {
    current_battery = battery_size;
}

void MySimulator::setMaxSteps(const size_t max_steps) {
    this->max_steps = max_steps;
}

void MySimulator::setHouse(const std::shared_ptr<House> house) {
    this->house = house;
}

void MySimulator::setDockingStation(const House::Location docking_loc) {
    this->docking_loc = docking_loc;
}

void MySimulator::setCurrentLocation() {
    this->current_location = docking_loc;
}

void MySimulator::setWallsSensor() {
    walls_sensor.setHouse(house);
}

void MySimulator::setDirtSensor() {
    dirt_sensor.setHouse(house);
}

void MySimulator::setAlgorithm(std::shared_ptr<MyAlgorithm> alg) {
    alg->setWallsSensor(walls_sensor);
    alg->setDirtSensor(dirt_sensor);
    alg->setBatteryMeter(battery_meter);
    alg->setMaxSteps(max_steps);
    algo = alg;
}

void MySimulator::setProperties(const size_t max_num_of_steps, const size_t max_battery_steps, 
                        const std::shared_ptr<House> house_map, const House::Location docking_loc) {
    
    setBatterySize(max_battery_steps);
    setCurrestBattery();
    setMaxSteps(max_num_of_steps);
    setHouse(house_map);
    setDockingStation(docking_loc);
    setCurrentLocation();
    addToHistory();
    setWallsSensor();
    setDirtSensor();

}

void MySimulator::addToHistory() {
    history_path.addEntry(current_location);
}

const Path& MySimulator::getPath() const {
    return history_path;
}

size_t MySimulator::getHistoryLength() const {
    return history_path.getLength();
}




/*
VacuumCleaner::vacuum_cleaner_output VacuumCleaner::cleanHouse() {
    Algorithm algo(wall_sensor, battery_sensor, dirt_sensor, battery_size, current_location);
    for (size_t i = 0; i < max_steps; ++i) {
        if ((current_total_dirt <= 0) && (current_location == docking_loc)) {
            break;
        }
        Direction step = algo.nextStep();

        //Stay in docking station
        if ((step.getValue() == Direction::Value::Stay) && (current_location == docking_loc)) {
            size_t updated_battery = current_battery + battery_size / 20;
            current_battery = (updated_battery > battery_size) ? battery_size : updated_battery;
        }

        //Stay and clean
        else if (step.getValue() == Direction::Value::Stay) {
            decreaseTotalDirt();
            updateHouse();
            current_battery -= 1;
        }

        //Move to another location
        else {
            move(step);
            current_battery -= 1;
        }

        addToHistory();
    }
    return {current_battery, current_total_dirt, current_location == docking_loc};
}



void VacuumCleaner::move(const Direction direction) {
    current_location.setBoth(current_location.getRow() + direction.getX(), current_location.getCol() + direction.getY());
}

void VacuumCleaner::decreaseTotalDirt() {
    current_total_dirt -= 1;
}

void VacuumCleaner::updateHouse() {
    house.getTile(current_location).removeOneDirt();
}

*/


