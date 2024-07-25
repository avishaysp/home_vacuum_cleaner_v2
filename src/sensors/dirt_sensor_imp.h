#pragma once

#include "../skelaton/dirt_sensor.h"
#include "../logger.h"
#include "../house.h"


class DirtSensorImp: public DirtSensor {

	std::shared_ptr<House> house;
    House::Location& curr_location;

public:

    DirtSensorImp(House::Location& curr_location);
    DirtSensorImp(const std::shared_ptr<House> house, House::Location& curr_location);
    void setHouse(const std::shared_ptr<House> house);
    int dirtLevel() const override;
};

