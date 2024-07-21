#include "walls_sensor_imp.h"

WallsSensorImp::WallsSensorImp(const House& house, const House::Location& curr_location) : house(house), curr_location(curr_location) {}


bool WallsSensorImp::isWall(Direction d) const {
    switch (d)
    {
    case Direction::North:
        return house.getTile(curr_location.getRow() - 1, curr_location.getCol()).isWall();
        break;
    case Direction::South:
        return house.getTile(curr_location.getRow() + 1, curr_location.getCol()).isWall();
        break;
    case Direction::East:
        return house.getTile(curr_location.getRow(), curr_location.getCol() + 1).isWall();
        break;
    case Direction::West:
        return house.getTile(curr_location.getRow(), curr_location.getCol() - 1).isWall();
        break;
    default:
        break;
    }
}