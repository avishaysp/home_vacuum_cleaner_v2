#include "dfs_algorithm.h"


void setMaxSteps(std::size_t maxSteps) {
    LOG("bbbb");
    maxSteps_ = maxSteps;
}

void setWallsSensor(const WallsSensor& wallsSensor) {
    wallsSensor_ = wallsSensor;
}

void setDirtSensor(const DirtSensor& dirtSensor) {
    dirtSensor_ = dirtSensor;
}

void setBatteryMeter(const BatteryMeter& batteryMeter) {
    batteryMeter_ = batteryMeter;
}

Step nextStep() override {
   
}

