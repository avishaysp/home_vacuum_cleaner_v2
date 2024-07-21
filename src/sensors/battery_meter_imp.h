#pragma once

#include "battery_meter.h"
#include "logger.h"



class BatteryMeterImp : public BatteryMeter {

public:
	std::size_t getBatteryState() const override;
};

