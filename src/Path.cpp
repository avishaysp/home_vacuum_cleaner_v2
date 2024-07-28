// Path.cpp

#include "Path.h"

Path::Path() {}


void Path::addEntry(Step dir) {
    vec.push_back(dir);
}

size_t Path::getLength() const{
    return vec.size();
}

Step Path::popStep() {
    if (!vec.empty()) {
        Step last = vec.back();
        vec.pop_back();
        return last;
    }
    logger.log(ERROR, "Popped the first elem in the Path. Big No No.");

}

Step Path::topStep() const {
    if (!vec.empty()) {
        return vec.back();
    }
    logger.log(ERROR, "Popped the first elem in the Path. Big No No.");
}

void Path::cutPath(const size_t idx){
    vec = std::vector<Step>(vec.begin(), vec.begin() + idx + 1);
}

void Path::print() const {
    std::cout << *this;
}

std::ostream& operator<<(std::ostream& os, const Path& path) {
    for (size_t i = 0; i < path.getLength(); ++i) {
        char c;
        switch (path.vec[i])
        {
        case Step::North:
            c = 'N';
            break;
        case Step::South:
            c = 'S';
            break;
        case Step::East:
            c = 'E';
            break;
        case Step::West:
            c = 'W';
            break;
        case Step::Stay:
            c = 's';
            break;
        case Step::Finish:
            c = 'F';
            break;
        default:
            break;
        }

        os << c;
    }
    os << std::endl;
    return os;
}


