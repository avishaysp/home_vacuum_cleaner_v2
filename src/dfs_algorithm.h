#pragma once

#include "abstract_algorithm.h"  
#include "battery_meter_imp.h"
#include "walls_sensor_imp.h"
#include "dirt_sensor_imp.h"
#include "logger.h"

class DfsAlgorithm : public AbstractAlgorithm {
  
  std::size_t maxSteps;

  int battery_size;
  House::Location starting_location;

  WallsSensorImp wallsSensor;  
  DirtSensorImp dirtSensor;    
  BatteryMeterImp batteryMeter; 

public:
  DfsAlgorithm(const size_t battery_size,  const House::Location starting_location);

  void setMaxSteps(size_t maxSteps) override;
  void setWallsSensor(const WallsSensor&) override;
  void setDirtSensor(const DirtSensor&) override;
  void setBatteryMeter(const BatteryMeter&) override;
  Step nextStep() override;
};
