#include "Direction.h"

Direction::Direction(Value direction) : direction(direction) {}

Direction::Value Direction::getValue() const {
    return direction;
}

int Direction::getX() const {
    switch (direction) {
        case Value::North: return -1;
        case Value::South: return 1;
        case Value::East: return 0;
        case Value::West: return 0;
        case Value::Stay: return 0;
    }
    return 0;
}

int Direction::getY() const {
    switch (direction) {
        case Value::North: return 0;
        case Value::South: return 0;
        case Value::East: return 1;
        case Value::West: return -1;
        case Value::Stay: return 0;
    }
    return 0;
}

std::string Direction::toString() const {
    switch (direction) {
        case Value::Stay: return "Stay";
        case Value::North: return "North";
        case Value::South: return "South";
        case Value::East: return "East";
        case Value::West: return "West";
    }
}

bool Direction::operator==(Value other) const {
    return direction == other;
}

bool Direction::operator==(Direction other) const {
    return direction == other.getValue();
}

bool Direction::operator!=(Value other) const {
    return direction != other;
}