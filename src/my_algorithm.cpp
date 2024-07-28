#include "my_algorithm.h"

SpeedomAlgorithm::SpeedomAlgorithm() :
    max_steps(0),
    battery_size(0),
    starting_location(House::Location()),
    walls_sensor(),
    dirt_sensor(),
    battery_meter()
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

Step SpeedomAlgorithm::nextStep() {
    std::cout << battery_size << std::endl;
    return Step::East;
}

