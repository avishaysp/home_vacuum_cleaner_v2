// house.cpp
#include <format>
#include "house.h"

/* House */

House::House(size_t rows, size_t cols) : mat(rows, std::vector<House::Tile>(cols, House::Tile())), rows(rows), cols(cols) {}

House::Tile& House::getTile(House::Location loc) {
    size_t row = loc.getRow();
    size_t col = loc.getCol();
    return getTile(row, col);
}

House::Tile& House::getTile(size_t row, size_t col) {
    return mat[row][col];
}

const House::Tile& House::getTile(House::Location loc) const {
    size_t row = loc.getRow();
    size_t col = loc.getCol();
    return getTile(row, col);
}

const House::Tile& House::getTile(size_t row, size_t col) const {
    return mat[row][col];
}

size_t House::getRowsCount() const {
    return rows;
}

size_t House::getColsCount() const {
    return cols;
}

House::Location House::getDockingStation() const {
    return docking_station;
}

void House::setDockingStation(House::Location docking_loc) {
    docking_station = docking_loc;
}

int House::calcTotalDirt() const {
    int sum = 0;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (mat[i][j].getDirtLevel() > 0) {
                sum += mat[i][j].getDirtLevel();
            }
        }
    }
    return sum;
}

void House::print() const {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            Tile tile = mat[i][j];
            if (tile.isDockingStation()) {
                std::cout << 'D';
            } else if (tile.isWall()) {
                std::cout << 'W';
            } else {
                std::cout << tile.getDirtLevel();
            }
        }
        std::cout << std::endl;
    }
}


/* Location */

House::Location::Location() : LocationBase() {}
House::Location::Location(size_t row, size_t col) : LocationBase(row, col) {}

// Copy Constructor
House::Location::Location(const Location& other) : LocationBase(other.row, other.col) {}

// Copy Assignment Operator
House::Location& House::Location::operator=(const Location& other) {
    if (this == &other) {
        return *this; // handle self assignment
    }
    row = other.row;
    col = other.col;
    return *this;
}

// Move Constructor
House::Location::Location(Location&& other) noexcept : LocationBase(other.row, other.col) {
    other.row = 0;
    other.col = 0;
}

// Move Assignment Operator
House::Location& House::Location::operator=(Location&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    row = other.row;
    col = other.col;
    other.row = 0;
    other.col = 0;
    return *this;
}

House::Location::~Location() {}

/* Tile */

House::Tile::Tile(Type type, int dirt_level) : type(type), dirt_level(dirt_level) {}
House::Tile::Tile() : type(Open), dirt_level(0) {}

bool House::Tile::isWall() const {
    return type == Wall;
}

void House::Tile::setAsWall() {
    type = Wall;
}

bool House::Tile::isDockingStation() const {
    return type == DockingStation;
}

void House::Tile::setAsDockingStation() {
    type = DockingStation;
}

int House::Tile::getDirtLevel() const {
    if (type != Open) {
        logger.log(ERROR, "Tried to get the dirt level of a Wall/Docking tile");
    }
    return dirt_level;
}

void House::Tile::setDirtLevel(int new_dirt) {
    if (type != Open) {
        logger.log(WARNING, "Set the dirt level of a Wall/Docking tile");
    }
    dirt_level = new_dirt;
}

void House::Tile::decreaseOneDirt() {
    if (type != Open) {
        logger.log(WARNING, "Tried todecrease the dirt level of a Wall/Docking tile");
        return;
    }
    if (dirt_level > 0) {
        --dirt_level;
    }
}