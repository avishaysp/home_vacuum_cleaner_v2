#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "house.h"

class LiveSimulator {
public:
    static LiveSimulator& getInstance();

    void simulate(const House& house, const House::Location& curr_location);

private:
    LiveSimulator() {}
    ~LiveSimulator();

    LiveSimulator(const LiveSimulator&) = delete;
    LiveSimulator& operator=(const LiveSimulator&) = delete;
    
    void printHouseForSimulator(const House& house, const House::Location& current_loc);
    void printWallsLine(const size_t colsOfHouse);

    std::ofstream simulatorStream;
    std::string simulatorFile;
};

extern LiveSimulator& live_simulator;

