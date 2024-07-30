// speedom_algorithm.h
#pragma once

#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>
#include <optional>
#include "skelaton/abstract_algorithm.h"
#include "sensors/battery_meter_imp.h"
#include "sensors/walls_sensor_imp.h"
#include "sensors/dirt_sensor_imp.h"
#include "logger.h"

class SpeedomAlgorithm : public AbstractAlgorithm {
private:
    class AlgorithmLocation : public LocationBase<int> {
    public:
        AlgorithmLocation();
        AlgorithmLocation(int row, int col);

        // Copy Constructor
        AlgorithmLocation(const AlgorithmLocation& other);

        // Copy Assignment Operator
        AlgorithmLocation& operator=(const AlgorithmLocation& other);

        // Move Constructor
        AlgorithmLocation(AlgorithmLocation&& other) noexcept;

        // Move Assignment Operator
        AlgorithmLocation& operator=(AlgorithmLocation&& other) noexcept;

        ~AlgorithmLocation();
    };

    class InternalHouse {
    public:
        enum LocationType {
            DOCKING,
            CURRENT,
            CHOSEN,
        };
        
    private:
    
        struct tile_stats {
            size_t dirt_level;
            bool visited;
            size_t distance_from_current;
            std::optional<AlgorithmLocation> father_from_chosen; //TODO: could be removed
            size_t distance_from_docking_station;
            std::optional<AlgorithmLocation> father_from_docking;
            std::vector<AlgorithmLocation> neighbors;

        };

        AlgorithmLocation& starting_location;
        AlgorithmLocation& current_location;

        std::unordered_map<AlgorithmLocation, tile_stats> internal_graph;

        size_t calculateTravelDistance(SpeedomAlgorithm::AlgorithmLocation loc) const;

        bool isInNeighbors(const std::vector<SpeedomAlgorithm::AlgorithmLocation>& locations, 
                            SpeedomAlgorithm::AlgorithmLocation loc) const;

        SpeedomAlgorithm::AlgorithmLocation getNextLocationToTarget(LocationType target) const;

        
    public:
       
        InternalHouse(AlgorithmLocation& start_loc, AlgorithmLocation& curr_loc)
            : starting_location(start_loc), current_location(curr_loc) {
                internal_graph.at(start_loc) = 
                {
                    0, false, 0, std::nullopt, 0, std::nullopt, std::vector<AlgorithmLocation>()
                };
            }
        
        void bfs(LocationType start, std::optional<SpeedomAlgorithm::AlgorithmLocation> chosen_location);
        size_t getDistanceToDoc(SpeedomAlgorithm::AlgorithmLocation other_location) const;

        std::pair<Step, SpeedomAlgorithm::AlgorithmLocation> calcStepToTarget(LocationType target) const;

        void updateGraph(size_t dirt_level, const std::vector<SpeedomAlgorithm::AlgorithmLocation>& possible_Locations);
        
        std::pair<size_t, SpeedomAlgorithm::AlgorithmLocation> minimalDistanceLocation() const;

                                                                   
    };

    std::size_t max_steps;

    const size_t battery_size;
    SpeedomAlgorithm::AlgorithmLocation starting_location;

    SpeedomAlgorithm::AlgorithmLocation current_location;

    const WallsSensor* walls_sensor;
    const DirtSensor* dirt_sensor;
    const BatteryMeter* battery_meter;

    InternalHouse internal_house;

    std::vector<SpeedomAlgorithm::AlgorithmLocation> getPossibleLocations() const;
    bool isFeasible(size_t travel_distance, size_t current_battery) const;

    Step updateCurrentLocAndGetNextStep(InternalHouse::LocationType target);

public:
    using AlgoLoc = SpeedomAlgorithm::AlgorithmLocation;

    SpeedomAlgorithm();

    void setMaxSteps(size_t max_steps) override;
    void setWallsSensor(const WallsSensor&) override;
    void setDirtSensor(const DirtSensor&) override;
    void setBatteryMeter(const BatteryMeter&) override;
    Step nextStep() override;

};
