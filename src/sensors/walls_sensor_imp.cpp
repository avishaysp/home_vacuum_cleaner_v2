#include "walls_sensor_imp.h"

WallsSensorImp::WallsSensorImp(const Location& curr_location) : house(nullptr), curr_location(curr_location) {}

WallsSensorImp::WallsSensorImp(const std::shared_ptr<House> house, const Location& curr_location) : house(house), curr_location(curr_location) {}

void WallsSensorImp::setHouse(const std::shared_ptr<House> house) {
    this->house = house;
}

bool WallsSensorImp::isWall(Direction d) const {
    logger.log(INFO, "WallsSensorImp | isWall");
    int row = curr_location.getRow();
    int col = curr_location.getCol();
    int row_limit = house->getRowsCount();
    int col_limit = house->getColsCount();
    switch (d)
    {
    case Direction::North:
        logger.log(INFO, "WallsSensorImp | isWall 1");
        return (row == 0) || (house->getTile(row - 1, col).isWall());
        break;
    case Direction::South:
        logger.log(INFO, "WallsSensorImp | isWall 2");
        return (row == row_limit - 1) || (house->getTile(row + 1, col).isWall());
        break;
    case Direction::East:
        logger.log(INFO, "WallsSensorImp | isWall 3");
        return (col == 0) || (house->getTile(row, col + 1).isWall());
        break;
    case Direction::West:
        logger.log(INFO, "WallsSensorImp | isWall 4");
        return (col == col_limit - 1) || (house->getTile(row, col - 1).isWall());
        break;
    default:
        break;
    }
}