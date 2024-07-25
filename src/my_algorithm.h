#pragma once

#include "abstract_algorithm.h"  
#include "battery_meter_imp.h"
#include "walls_sensor_imp.h"
#include "dirt_sensor_imp.h"
#include "logger.h"

class MyAlgorithm : public AbstractAlgorithm {
  
  std::size_t max_steps;

  const size_t battery_size;
  House::Location starting_location;

  std::unique_ptr<const WallsSensor> walls_sensor;  
  std::unique_ptr<const DirtSensor>  dirt_sensor;    
  std::unique_ptr<const BatteryMeter> battery_meter; 

public:
  MyAlgorithm();

  ~MyAlgorithm();

  void setMaxSteps(size_t max_steps) override;
  void setWallsSensor(const WallsSensor&) override;
  void setDirtSensor(const DirtSensor&) override;
  void setBatteryMeter(const BatteryMeter&) override;
  Step nextStep() override;
};
