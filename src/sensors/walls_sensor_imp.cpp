#include "walls_sensor_imp.h"

WallsSensorImp::WallsSensorImp(const House& house, const House::Location& curr_location) : house(house), curr_location(curr_location) {}


bool WallsSensorImp::isWall(Direction d) const {
    int row = curr_location.getRow();
    int col = curr_location.getCol();
    int row_limit = house.getRowsCount();
    int col_limit = house.getColsCount();
    switch (d)
    {
    case Direction::North:
        return (row = 0) || (house.getTile(row - 1, col).isWall());
        break;
    case Direction::South:
        return (row = row_limit - 1) || (house.getTile(row + 1, col).isWall());
        break;
    case Direction::East:
        return (col = 0) || house.getTile(row, col + 1).isWall();
        break;
    case Direction::West:
        return (col = col_limit - 1) || house.getTile(row, col - 1).isWall();
        break;
    default:
        break;
    }
}