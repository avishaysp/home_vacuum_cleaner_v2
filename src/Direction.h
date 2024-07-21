#pragma once

#include <string>


class Direction {
public:
    enum class Value {
        Stay,   // (0, 0)
        North,  // (1, 0)
        South,  // (-1, 0)
        East,   // (0, 1)
        West   // (0, -1)
    };

    Direction(Value direction);

    // Getter for the value
    Value getValue() const;

    // Methods to get the row and col components of the direction
    int getX() const;
    int getY() const;
    std::string toString() const;

    bool operator==(Value other) const;
    bool operator==(Direction other) const;

    bool operator!=(Value other) const;

private:
    Value direction;
};

