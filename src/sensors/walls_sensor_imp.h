#pragma once

#include "enums.h"
#include "walls_sensor.h"
#include "logger.h"
#include "house.h"


class WallsSensorImp: public WallsSensor {
    std::shared_ptr<House> house;
    const House::Location& curr_location;

public:
    WallsSensorImp(const House::Location& curr_location);

    WallsSensorImp(const std::shared_ptr<House> house, const House::Location& curr_location);

    void setHouse(const std::shared_ptr<House> house);

	bool isWall(Direction d) const;
};

