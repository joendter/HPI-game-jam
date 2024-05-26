#include <cmath>
#include "coordinate.h"

Coordinate::Coordinate(int nx , int ny ) : x(nx), y(ny){};

bool Coordinate::operator==(const Coordinate &other) const {
    return x == other.x && y == other.y;
}

bool Coordinate::operator<(const Coordinate &other) const {
    return x < other.x || (x == other.x && y < other.y);
}

bool Coordinate::operator<=(const Coordinate &other) const {
    return *this < other || *this == other;
}

// Addition operator: adds two coordinates component-wise
Coordinate Coordinate::operator+(const Coordinate &other) const {
    Coordinate result;
    result.x = this->x + other.x;
    result.y = this->y + other.y;
    return result;
}

// Subtraction operator: subtracts two coordinates component-wise
Coordinate Coordinate::operator-(const Coordinate &other) const {
    Coordinate result;
    result.x = this->x - other.x;
    result.y = this->y - other.y;
    return result;
}

Coordinate Coordinate::normalised() const {
    int nx = std::abs(x);
    int ny = std::abs(y);
    if (nx < ny) {
        nx = ny;
        ny = std::abs(x);
    }
    return Coordinate(nx, ny);
}

