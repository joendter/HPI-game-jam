#ifndef COORDINATE_H
#define COORDINATE_H
#include <cmath>

struct Coordinate {
    int x;
    int y;

    Coordinate(int nx = 0, int ny = 0);

    bool operator==(const Coordinate &other) const ;
    bool operator<(const Coordinate &other) const ;
    bool operator<=(const Coordinate &other) const ;
    // Addition operator: adds two coordinates component-wise
    Coordinate operator+(const Coordinate &other) const ;

    // Subtraction operator: subtracts two coordinates component-wise
    Coordinate operator-(const Coordinate &other) const ;
    Coordinate normalised() const ;
};

#endif
