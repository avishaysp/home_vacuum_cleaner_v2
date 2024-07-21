// house.cpp
#include <format>
#include "house.h"

/* House */

House::House(size_t rows, size_t cols) : mat(rows, std::vector<House::Tile>(cols, House::Tile())), rows(rows), cols(cols) {}

size_t House::getDirt(House::Location loc) const {
   return House::getDirt(loc.getRow(), loc.getCol());
}

size_t House::getDirt(size_t row, size_t col) const {
    if (row < rows && col < cols) {
        return mat[row][col].getDirt();
    }
    return -99;
}

void House::setDirt(House::Location loc, size_t value) {
    return House::setDirt(loc.getRow(), loc.getCol(), value);
}

void House::setDirt(size_t row, size_t col, size_t value) {
    if (row < rows && col < cols) {
        mat[row][col].setDirt(value);
    }
}

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

size_t House::calcTotalDirt() const {
    size_t sum = 0;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (mat[i][j].getDirt() > 0) {
                sum += mat[i][j].getDirt();
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

House::Tile::Tile()
    : dirt_level(0), wall_on_north(false), wall_on_south(false), wall_on_east(false), wall_on_west(false) {}

House::Tile::Tile(size_t dirt_level, bool wall_on_north, bool wall_on_south, bool wall_on_east, bool wall_on_west)
    : dirt_level(dirt_level), wall_on_north(wall_on_north), wall_on_south(wall_on_south), wall_on_east(wall_on_east), wall_on_west(wall_on_west) {}

// Getter implementations
size_t House::Tile::getDirt() const {
    return dirt_level;
}

bool House::Tile::getNorthWall() const {
    return wall_on_north;
}

bool House::Tile::getSouthWall() const {
    return wall_on_south;
}

bool House::Tile::getEastWall() const {
    return wall_on_east;
}

bool House::Tile::getWestWall() const {
    return wall_on_west;
}

// Setter implementations
void House::Tile::setDirt(size_t dirt) {
    dirt_level = dirt;
}

void House::Tile::setNorthWall(bool val) {
    wall_on_north = val;
}

void House::Tile::setSouthWall(bool val) {
    wall_on_south = val;
}

void House::Tile::setEastWall(bool val) {
    wall_on_east = val;
}

void House::Tile::setWestWall(bool val) {
    wall_on_west = val;
}

void House::Tile::removeOneDirt() {
    dirt_level = dirt_level > 0 ? (dirt_level - 1) : 0;
}
