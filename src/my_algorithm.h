#pragma once

#include "skelaton/abstract_algorithm.h"
#include "sensors/battery_meter_imp.h"
#include "sensors/walls_sensor_imp.h"
#include "sensors/dirt_sensor_imp.h"
#include "logger.h"

class MyAlgorithm : public AbstractAlgorithm {

  std::size_t max_steps;

  const size_t battery_size;
  House::Location starting_location;

  const WallsSensor* walls_sensor;
  const DirtSensor* dirt_sensor;
  const BatteryMeter* battery_meter;

public:
  MyAlgorithm();

  void setMaxSteps(size_t max_steps) override;
  void setWallsSensor(const WallsSensor&) override;
  void setDirtSensor(const DirtSensor&) override;
  void setBatteryMeter(const BatteryMeter&) override;
  Step nextStep() override;
};
