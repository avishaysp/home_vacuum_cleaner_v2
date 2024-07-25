#include "my_algorithm.h"

MyAlgorithm::MyAlgorithm() :
    max_steps(0),
    battery_size(0),
    starting_location(House::Location()),
    walls_sensor(),
    dirt_sensor(),
    battery_meter()
    {}


void MyAlgorithm::setMaxSteps(std::size_t maxSteps) {
    max_steps = maxSteps;
}

void MyAlgorithm::setWallsSensor(const WallsSensor& wallsSensor) {
    walls_sensor = &wallsSensor;
}

void MyAlgorithm::setDirtSensor(const DirtSensor& dirtSensor) {
    dirt_sensor = &dirtSensor;
}

void MyAlgorithm::setBatteryMeter(const BatteryMeter& batteryMeter) {
    battery_meter = &batteryMeter;
}

Step MyAlgorithm::nextStep() {
    
    return Step::Stay;
}

