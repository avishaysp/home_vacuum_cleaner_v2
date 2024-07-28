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
            updateDirtLevel();
            current_battery += delta_battery;
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
    (house->getTile(current_location)).decreaseOneDirt();
}

void Simulator::move(Step step) {
    switch (step)
        {
        case Step::North:
            current_location.setBoth(current_location.getRow() - 1, current_location.getCol());
            break;
        case Step::South:
            current_location.setBoth(current_location.getRow() + 1, current_location.getCol());
            break;
        case Step::East:
            current_location.setBoth(current_location.getRow(), current_location.getCol() + 1);
            break;
        case Step::West:
            current_location.setBoth(current_location.getRow(), current_location.getCol() - 1);
            break;
        default:
            break;
        }
}






