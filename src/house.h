// house.h
#pragma once

#include <vector>
#include <iostream>
#include <unordered_map>
#include "logger.h"
#include "location_base.h"

class House {

public:

    class Tile {
    public:
        enum Type { Open, Wall, DockingStation };

        Tile(Type type, int dirt_level);
        Tile();

        bool isWall() const;
        void setAsWall();
        bool isDockingStation() const;
        void setAsDockingStation();
        int getDirtLevel() const;
        void setDirtLevel(int new_dirt);
        void decreaseOneDirt();

    private:
        Type type;
        int dirt_level;
    };


    class Location : public LocationBase<size_t> {
    public:
        // Constructors
        Location();
        Location(size_t row, size_t col);

        // Copy Constructor
        Location(const Location& other);

        // Copy Assignment Operator
        Location& operator=(const Location& other);

        // Move Constructor
        Location(Location&& other) noexcept;

        // Move Assignment Operator
        Location& operator=(Location&& other) noexcept;

        // Destructor
        ~Location();
    };

    Tile& getTile(Location loc);
    Tile& getTile(size_t row, size_t col);
    const Tile& getTile(Location loc) const;
    const Tile& getTile(size_t row, size_t col) const;

    size_t getRowsCount() const;
    size_t getColsCount() const;

    Location getDockingStation() const;
    void setDockingStation(Location docking_loc);

    int calcTotalDirt() const;
    void print() const;

    House(size_t rows, size_t cols);

private:
    std::vector<std::vector<House::Tile>> mat;
    size_t rows;
    size_t cols;
    Location docking_station;

};
