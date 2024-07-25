// Path.cpp

#include "Path.h"

Path::Path() {}

Path::Path(const House::Location start_loc) {
    vec.push_back(start_loc);
}


void Path::addEntry(const House::Location loc) {
    vec.push_back(loc);
}

size_t Path::getLength() const{
    return vec.size();
}

House::Location Path::popStep() {
    if (!vec.empty()) {
        House::Location last = vec.back();
        vec.pop_back();
        return last;
    }
    std::cerr << "Popped the first elem in the Path. Big No No." << std::endl;
    std::exit(EXIT_FAILURE);
}

House::Location Path::topStep() const {
    if (!vec.empty()) {
        return vec.back();
    }
    std::cerr << "Popped the first elem in the Path. Big No No." << std::endl;
    std::exit(EXIT_FAILURE);
}

void Path::cutPath(const size_t idx){
    vec = std::vector<House::Location>(vec.begin(), vec.begin() + idx + 1);
}

House::Location Path::getPrev() const {
    return vec.end()[-2];
}

House::Location Path::getLocation(const int idx) const {
    return vec[idx];
}

int Path::getIndexOfLocation(const House::Location& loc) const {
    for (int i = 0; i < static_cast<int>(getLength()); i++)
    {
        if (vec[i] == loc) return i;
    }
    return -1;
}

void Path::print() const {
    std::cout << *this;
}

std::ostream& operator<<(std::ostream& os, const Path& path) {
    os << path.vec[0];
    for (size_t i = 1; i < path.vec.size(); ++i) {
        os << " --> " << path.vec[i];
    }
    os << std::endl;
    return os;
}


