#pragma once

#include "enums.h"
#include "walls_sensor.h"
#include "logger.h"
#include "house.h"


class WallsSensorImp: public WallsSensor {
    const House& house;
    const House::Location& curr_location;

public:

    WallsSensorImp(const House& house, const House::Location& curr_location);

	bool isWall(Direction d) const;
};

