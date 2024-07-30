#include "live_simulator.h"
#include <ctime>
#include <iomanip>
#include <format>
#include <thread>


LiveSimulator& LiveSimulator::getInstance() {
    static LiveSimulator instance;
    return instance;
}

LiveSimulator::~LiveSimulator() {}

void LiveSimulator::simulate(const House& house, const Location& curr_location) {
    logger.log(INFO, "Start waiting for 0.5 second");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    logger.log(INFO, "Printing house");
    printHouseForSimulator(house, curr_location);
}


void LiveSimulator::printHouseForSimulator(const House& house, const Location& current_loc) {
    std::cout << "\033[2J\033[1;1H";

    size_t house_rows = house.getRowsCount();
    size_t house_cols = house.getColsCount();
    size_t colsOfHouse = house.getColsCount() * 2 + 3;
    size_t curr_row = current_loc.getRow();
    size_t curr_col = current_loc.getCol();
    printWallsLine(colsOfHouse);

    for (size_t i = 0; i < house_rows; i++) {
        if ((i == curr_row) && (curr_col == 0)) {
            std::cout << "W[";
        } else {
            std::cout << "W ";
        }
        for (size_t j = 0; j < house_cols; j++) {
            House::Tile tile = house.getTile(i, j);
            if (tile.isDockingStation()) {
                std::cout << 'D';
            } else if (tile.isWall()) {
                std::cout << 'W';
            } else {
                std::cout << tile.getDirtLevel();
            }
            if ((i == curr_row) && (j == curr_col - 1)) {
                std::cout << "[";
            }
            else if ((i == curr_row) && (j == curr_col)) {
                std::cout << "]";
            } else {
                std::cout << ' ';
            }
        }
        std::cout << 'W';
        std::cout << std::endl;
    }
    printWallsLine(colsOfHouse);
}

void LiveSimulator::printWallsLine(const size_t colsOfHouse) {
    for (size_t i = 0; i < colsOfHouse; i++) {
        std::cout << 'W';
    }
    std::cout << std::endl;
}


LiveSimulator& live_simulator = LiveSimulator::getInstance();

