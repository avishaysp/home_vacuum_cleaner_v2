#include "live_simulator.h"
#include <ctime>
#include <iomanip>
#include <format>
#include <thread>

#define RESET   "\033[0m"
#define RED     "\033[31m"


LiveSimulator& LiveSimulator::getInstance() {
    static LiveSimulator instance;
    return instance;
}

LiveSimulator::~LiveSimulator() {}

void LiveSimulator::simulate(const House& house, const Location& curr_location, Step step, bool is_docking, size_t remaining_steps, size_t current_battery) const{
    if (remaining_steps > 10){
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    logger.log(INFO, "LiveSimulator | Printing house");
    printHouseForSimulator(house, curr_location, step, is_docking, remaining_steps, current_battery);
    if (step == Step::Finish) {
        std::cout << "Cleaning has Finished, Exiting Live Simulation" << std::endl;
    }
}


void LiveSimulator::printHouseForSimulator(const House& house, const Location& current_loc, Step step, bool is_docking, size_t remaining_steps, size_t current_battery) const{
    std::cout << "\033[2J\033[1;1H";

    size_t house_rows = house.getRowsCount();
    size_t house_cols = house.getColsCount();
    size_t colsOfHouse = house.getColsCount() * 2 + 3;
    size_t curr_row = current_loc.getRow();
    size_t curr_col = current_loc.getCol();
    printWallsLine(colsOfHouse);

    for (size_t i = 0; i < house_rows; i++) {
        if ((i == curr_row) && (curr_col == 0)) {
            if (step == Step::Stay){
                if (is_docking) {
                        std::cout << "\033[31m" << "W" << "\033[0m" << "{";
                    } else {
                        std::cout << "\033[31m" << "W" << "\033[0m" << "<";
                    }
            } else {
                std::cout << "\033[31m" << "W" << "\033[0m" << "[";
            }
        } else {
            std::cout << "\033[31m" << "W" << "\033[0m" << " ";
        }
        for (size_t j = 0; j < house_cols; j++) {
            House::Tile tile = house.getTile(i, j);
            if (tile.isDockingStation()) {
                std::cout << "\033[32m" << 'D' << "\033[0m";
            } else if (tile.isWall()) {
                std::cout << "\033[31m" << "W" << "\033[0m";
            } else {
                if (tile.getVisited()){
                    std::cout << "\033[34m" << tile.getDirtLevel() << "\033[0m";
                } else {
                    std::cout << tile.getDirtLevel();
                }
            }
            if ((i == curr_row) && (j == curr_col - 1)) {
                if (step == Step::Stay){
                    if (is_docking) {
                        std::cout << "{";
                    } else {
                        std::cout << "<";
                    }
                } else {
                    std::cout << "[";
                }
            }
            else if ((i == curr_row) && (j == curr_col)) {
                if (step == Step::Stay){
                    if (is_docking) {
                        std::cout << "}";
                    } else {
                        std::cout << ">";
                    }
                } else {
                    std::cout << "]";
                }
            } else {
                std::cout << ' ';
            }
        }
        std::cout << "\033[31m" << "W" << "\033[0m";
        std::cout << std::endl;
    }
    printWallsLine(colsOfHouse);
    printRemainingStepsAndCurrentBattery(remaining_steps, current_battery);

}

void LiveSimulator::printWallsLine(const size_t colsOfHouse) const{
    std::cout << "\033[31m";
    for (size_t i = 0; i < colsOfHouse; i++) {
        std::cout << 'W';
    }
    std::cout << "\033[0m";
    std::cout << std::endl;
}

void LiveSimulator::printRemainingStepsAndCurrentBattery(size_t remaining_steps, size_t current_battery) const {
    std::cout << std::endl;
    std::cout << "Remaining Steps: " << remaining_steps << std::endl;
    std::cout << "Current Battery: " << current_battery << std::endl;
}


LiveSimulator& live_simulator = LiveSimulator::getInstance();

