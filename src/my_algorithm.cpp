#include "my_algorithm.h"

MyAlgorithm::MyAlgorithm() : 
    battery_size(0),
    starting_location(House::Location()),
    max_steps(0),
    walls_sensor(nullptr),
    dirt_sensor(nullptr),
    battery_meter(nullptr)
    {}

MyAlgorithm::~MyAlgorithm() {
    walls_sensor.release();
    dirt_sensor.release();
    battery_meter.release();
}


void MyAlgorithm::setMaxSteps(std::size_t maxSteps) {
    max_steps = maxSteps;
}

void MyAlgorithm::setWallsSensor(const WallsSensor& wallsSensor) {
    walls_sensor = std::make_unique<const WallsSensor>(wallsSensor);
}

void MyAlgorithm::setDirtSensor(const DirtSensor& dirtSensor) {
    dirt_sensor = std::make_unique<const DirtSensor>(dirtSensor);
}

void MyAlgorithm::setBatteryMeter(const BatteryMeter& batteryMeter) {
    battery_meter = std::make_unique<const BatteryMeter>(batteryMeter);
}

Step MyAlgorithm::nextStep() override {
   
}

