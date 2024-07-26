#pragma once
#include <string>
#include <iostream>
#include "house.h"
#include "io_handling.h"
#include "sensors/walls_sensor_imp.h"
#include "sensors/dirt_sensor_imp.h"
#include "sensors/battery_meter_imp.h"
#include "Path.h"
#include "my_algorithm.h"



class MySimulator {
    size_t battery_size;
    size_t current_battery;
    size_t max_steps;
    std::shared_ptr<House> house;
    House::Location current_location;
    Path history_path; // verify if needed
    WallsSensorImp walls_sensor;
    const BatteryMeterImp battery_meter;
    DirtSensorImp dirt_sensor;
    std::shared_ptr<MyAlgorithm> algo;
    size_t delta_battery;

    void setBatterySize(const size_t battery_size);
    void setCurrestBattery();
    void setMaxSteps(const size_t max_steps);
    void setHouse(const std::shared_ptr<House> house);
    void setCurrentLocation();
    void setWallsSensor();
    void setDirtSensor();
    void setProperties(const size_t max_num_of_steps, const size_t max_battery_steps, 
                        const std::shared_ptr<House> house_map);





    void move(Step step);
    void addToHistory(Step step);
    void decreaseTotalDirt();
    void updateDirtLevel();


    public:
        MySimulator();

        void readHouseFile(const std::string input_file_path);

        void setAlgorithm(std::shared_ptr<MyAlgorithm> alg);

        void run();

        const Path& getPath() const;
        size_t getHistoryLength() const;
};
