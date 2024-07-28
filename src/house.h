// house.h
#pragma once

#include <vector>
#include <iostream>
#include <unordered_map>
#include "logger.h"

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


    class Location {
        size_t row;
        size_t col;

    public:
        // Constructors
        Location();
        Location(size_t row, size_t col);

        // Copy Constructor
        Location(const Location& other) : row(other.row), col(other.col) {}

        // Copy Assignment Operator
        Location& operator=(const Location& other) {
            if (this == &other) {
                return *this; // handle self assignment
            }
            row = other.row;
            col = other.col;
            return *this;
        }

        // Move Constructor
        Location(Location&& other) noexcept : row(other.row), col(other.col) {
            other.row = 0;
            other.col = 0;
        }

        // Move Assignment Operator
        Location& operator=(Location&& other) noexcept {
            if (this == &other) {
                return *this; // handle self assignment
            }
            row = other.row;
            col = other.col;
            other.row = 0;
            other.col = 0;
            return *this;
        }

        // Destructor
        ~Location() {}

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
