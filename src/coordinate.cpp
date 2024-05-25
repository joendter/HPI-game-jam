#ifndef COORDINATE_CPP
#define COORDINATE_CPP
struct Coordinate{
    unsigned int x;
    unsigned int y;

    bool operator==(const Coordinate& other) const{
        return x == other.x && y == other.y;
    }
};

#endif
