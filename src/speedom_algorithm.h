#pragma once

#include <unordered_map>
#include "skelaton/abstract_algorithm.h"
#include "sensors/battery_meter_imp.h"
#include "sensors/walls_sensor_imp.h"
#include "sensors/dirt_sensor_imp.h"
#include "logger.h"

class SpeedomAlgorithm : public AbstractAlgorithm {

    class InternalHouse {
        struct tile_stats {
            size_t dirt_level;
            bool visited;
            bool rechable;
            std::vector<House::Location> neighbors;
        };
        std::unordered_map<House::Location, tile_stats> internal_graph;
    public:
        
    };


    std::size_t max_steps;

    const size_t battery_size;
    House::Location starting_location;

    const WallsSensor* walls_sensor;
    const DirtSensor* dirt_sensor;
    const BatteryMeter* battery_meter;

public:
    SpeedomAlgorithm();

    void setMaxSteps(size_t max_steps) override;
    void setWallsSensor(const WallsSensor&) override;
    void setDirtSensor(const DirtSensor&) override;
    void setBatteryMeter(const BatteryMeter&) override;
    Step nextStep() override;
};
