
#include "dirt_sensor_imp.h"

DirtSensorImp::DirtSensorImp(const House& house, House::Location& curr_location) :  house(house), curr_location(curr_location) { }

int DirtSensorImp::dirtLevel() const {
    return this->house.getDirt(this->curr_location);
}