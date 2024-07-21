#pragma once

#include "dirt_sensor.h"
#include "logger.h"


class DirtSensorImp: public DirtSensor {

	const House& house;
    House::Location& curr_location;

public:
    DirtSensorImp(const House& house, House::Location& curr_location);
    int dirtLevel() const;
};

