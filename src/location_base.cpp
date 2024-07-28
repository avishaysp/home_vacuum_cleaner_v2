#include "location_base.h"

template <typename T>
LocationBase<T>::LocationBase() : row(0), col(0) {}

template <typename T>
LocationBase<T>::LocationBase(T row, T col) : row(row), col(col) {}

template <typename T>
T LocationBase<T>::getRow() const { return row; }

template <typename T>
T LocationBase<T>::getCol() const { return col; }

template <typename T>
void LocationBase<T>::setRow(T row) { this->row = row; }

template <typename T>
void LocationBase<T>::setCol(T col) { this->col = col; }

template <typename T>
void LocationBase<T>::setBoth(T row, T col) {
    this->row = row;
    this->col = col;
}

template <typename T>
bool LocationBase<T>::operator==(const LocationBase& other) const {
    return row == other.row && col == other.col;
}

template <typename T>
bool LocationBase<T>::operator!=(const LocationBase& other) const {
    return !(*this == other);
}

template <typename T>
std::string LocationBase<T>::toString() const {
    return "Location(" + std::to_string(row) + ", " + std::to_string(col) + ")";
}

template <typename T>
void LocationBase<T>::print() const {
    std::cout << toString() << std::endl;
}

// Explicit template instantiation
template class LocationBase<size_t>;
template class LocationBase<int>;
