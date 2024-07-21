// house.h
#pragma once

#include <vector>
#include <iostream>
#include <unordered_map>

class House {

public:

    class Tile {
    public:
        enum Type { Open, Wall, DockingStation };

        Tile(Type type = Open, int dirtLevel = 0);

        bool isWall() const;
        bool isDockingStation() const;
        int getDirtLevel() const;
        void decreaseOneDirt();

    private:
        Type type;
        int dirtLevel;
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

    Tile& getTile(Location loc);
    Tile& getTile(size_t row, size_t col);
    const Tile& getTile(Location loc) const;
    const Tile& getTile(size_t row, size_t col) const;

    size_t getRowsCount() const;
    size_t getColsCount() const;

    int calcTotalDirt() const;

    House(size_t rows, size_t cols);

private:
    std::vector<std::vector<House::Tile>> mat;
    size_t rows;
    size_t cols;
};
