#pragma once
#include <string>
#include <iostream>

template <typename T>
class LocationBase {
protected:
    T row;
    T col;

public:
    LocationBase();
    LocationBase(T row, T col);

    virtual ~LocationBase() {}

    T getRow() const;
    T getCol() const;

    void setRow(T row);
    void setCol(T col);
    void setBoth(T row, T col);

    bool operator==(const LocationBase& other) const;
    bool operator!=(const LocationBase& other) const;

    std::string toString() const;
    void print() const;

    friend std::ostream& operator<<(std::ostream& os, const LocationBase& loc) {
        os << loc.toString();
        return os;
    }
};
