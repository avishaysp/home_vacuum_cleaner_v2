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

/* Location */

House::Location::Location(size_t row, size_t col) : row(row), col(col) {}
House::Location::Location() : row(0), col(0) {}


// Getters for Location
size_t House::Location::getRow() const {
    return row;
}

size_t House::Location::getCol() const {
    return col;
}

// Setters for Location
void House::Location::setRow(size_t row) {
    this->row = row;
}

void House::Location::setCol(size_t col) {
    this->col = col;
}

void House::Location::setBoth(size_t row, size_t col) {
    this->row = row;
    this->col = col;
}

// Overloaded operators for Location
bool House::Location::operator==(const House::Location& other) const {
    return (row == other.row) && (col == other.col);
}

bool House::Location::operator!=(const House::Location& other) const {
    return !(*this == other);
}

std::string House::Location::toString() const {
    return std::format("({}|{})",this->row, this->col);
}

std::ostream& operator<<(std::ostream& os, const House::Location& loc) {
    return os << std::format("({}|{})", loc.row, loc.col);
}

void House::Location::print() const {
    std::cout << "(" << (this->row) << "|" << (this->col) << ")" << std::endl;
}

/* Tile */

// Tile implementation
House::Tile::Tile(Type type, int dirtLevel) : type(type), dirtLevel(dirtLevel) {}

bool House::Tile::isWall() const {
    return type == Wall;
}

bool House::Tile::isDockingStation() const {
    return type == DockingStation;
}

int House::Tile::getDirtLevel() const {
    if (type != Open) {
        // TODO: log an error
    }
    return dirtLevel;
}

void House::Tile::decreaseOneDirt() {
    if (type != Open) {
        // TODO: log an error
        return;
    }
    if (dirtLevel > 0) {
        --dirtLevel;
    }
}