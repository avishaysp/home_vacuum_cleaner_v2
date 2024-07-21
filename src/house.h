// house.h
#pragma once

#include <vector>
#include <iostream>
#include <unordered_map>
#include "Direction.h"

class House {

public:
    House(size_t rows, size_t cols);

    class Tile {
        size_t dirt_level;
        bool wall_on_north;
        bool wall_on_south;
        bool wall_on_east;
        bool wall_on_west;

    public:
        Tile();
        Tile(size_t dirt_level, bool wall_on_north, bool wall_on_south, bool wall_on_east, bool wall_on_west);

        // Getters
        size_t getDirt() const;
        bool getNorthWall() const;
        bool getSouthWall() const;
        bool getEastWall() const;
        bool getWestWall() const;

        // Setters
        void setDirt(size_t dirt);
        void setNorthWall(bool val);
        void setSouthWall(bool val);
        void setEastWall(bool val);
        void setWestWall(bool val);

        void removeOneDirt();
    };


    class Location {
        size_t row;
        size_t col;

    public:
        // Constructors
        Location();
        Location(size_t row, size_t col);

        // Getters
        size_t getRow() const;
        size_t getCol() const;

        // Setters
        void setRow(size_t row);
        void setCol(size_t col);
        void setBoth(size_t row, size_t col);

        bool operator==(const Location& other) const;
        bool operator!=(const Location& other) const;

        std::string toString() const;
        friend std::ostream& operator<<(std::ostream& os, const Location& loc);
        void print() const;
    };


    size_t getDirt(Location loc) const;
    size_t getDirt(size_t row, size_t col) const;
    void setDirt(Location loc, size_t value);
    void setDirt(size_t row, size_t col, size_t value);

    Tile& getTile(Location loc);
    Tile& getTile(size_t row, size_t col);
    const Tile& getTile(Location loc) const;
    const Tile& getTile(size_t row, size_t col) const;

    size_t getRowsCount() const;
    size_t getColsCount() const;

    size_t calcTotalDirt() const;

private:
    std::vector<std::vector<House::Tile>> mat;
    size_t rows;
    size_t cols;
};
