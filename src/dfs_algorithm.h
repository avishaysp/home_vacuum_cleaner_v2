#ifndef DFSALGORITHM_H
#define DFSALGORITHM_H

#include "abstract_algorithm.h"  
#include "battery_meter.h"
#include "wall_sensor.h"
#include "dirt_sensor.h"
#include "logger.h"

class DfsAlgorithm : public AbstractAlgorithm {
public:
  void setMaxSteps(size_t maxSteps) override;
  void setWallsSensor(const WallsSensor&) override;
  void setDirtSensor(const DirtSensor&) override;
  void setBatteryMeter(const BatteryMeter&) override;
  Step nextStep() override;

private:
  
  std::size_t maxSteps;  
  WallsSensorImp wallsSensor;  
  DirtSensorImp dirtSensor;    
  BatteryMeterImp batteryMeter; 
};

#endif  
