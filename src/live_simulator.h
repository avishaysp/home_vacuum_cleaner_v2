#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "house.h"
#include "skelaton/enums.h"

class LiveSimulator {
public:
    static LiveSimulator& getInstance();

    void simulate(const House& house, const Location& curr_location, Step step);

private:
    LiveSimulator() {}
    ~LiveSimulator();

    LiveSimulator(const LiveSimulator&) = delete;
    LiveSimulator& operator=(const LiveSimulator&) = delete;

    void printHouseForSimulator(const House& house, const Location& current_loc, Step step);
    void printWallsLine(const size_t colsOfHouse);

    std::ofstream simulatorStream;
    std::string simulatorFile;
};

extern LiveSimulator& live_simulator;

