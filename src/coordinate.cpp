#ifndef COORDINATE_CPP
#define COORDINATE_CPP
#include <cmath>
struct Coordinate {
    int x;
    int y;

    Coordinate(int nx = 0, int ny = 0) : x(nx), y(ny){};

    bool operator==(const Coordinate &other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const Coordinate &other) const {
        return x < other.x || (x == other.x && y < other.y);
    }

    bool operator<=(const Coordinate &other) const {
        return *this < other || *this == other;
    }

    // Addition operator: adds two coordinates component-wise
    Coordinate operator+(const Coordinate &other) const {
        Coordinate result;
        result.x = this->x + other.x;
        result.y = this->y + other.y;
        return result;
    }

    // Subtraction operator: subtracts two coordinates component-wise
    Coordinate operator-(const Coordinate &other) const {
        Coordinate result;
        result.x = this->x - other.x;
        result.y = this->y - other.y;
        return result;
    }

    Coordinate normalised() const {
        int nx = std::abs(x);
        int ny = std::abs(y);
        if (nx < ny) {
            nx = ny;
            ny = std::abs(x);
        }
        return Coordinate(nx, ny);
    }
};

#endif
