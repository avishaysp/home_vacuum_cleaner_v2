// Path.h
#pragma once

#include <vector>
#include "house.h"
#include "skelaton/enums.h"

class Path {
public:
    Path();

    void addEntry(Step dir);

    size_t getLength() const;

    Step popStep();

    Step topStep() const;

    void cutPath(const size_t idx);

    void print() const;
    friend std::ostream& operator<<(std::ostream& os, const Path& path);

private:

    std::vector<Step> vec;

};
