// speedom_algorithm.cpp
#include "speedom_algorithm.h"

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

void SpeedomAlgorithm::setDockingLocation(House::Location loc) {
    starting_location = loc;
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
    if ( battery_meter->getBatteryState() < )

    return Step::East;
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