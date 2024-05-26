#ifndef PIECE_H
#define PIECE_H
#include "color.h"
#include "coordinate.h"
#include "fraction.h"
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <stdexcept>

enum Piecetype {
    PAWN = 'p',
    ROOK = 'r',
    BISHOP = 'b',
    KNIGHT = 'n',
    QUEEN = 'q',
    KING = 'k'
};

bool validPieceMove(enum Piecetype piecetype, Coordinate diff);
struct Superposition {
    enum Piecetype type;
    Fraction probability;

    Superposition(enum Piecetype type, Fraction probability);
};

class Piece {
  public:
    enum Color color;
    std::map<Coordinate, Superposition *> superpositions;

    Superposition *onLocation(Coordinate location) const ;
    Fraction probabilityOnLocation(Coordinate location) const ;
    bool validMove(Coordinate origin, Coordinate destination) const ;
    void collapse(std::mt19937 gen);
    void move(Coordinate origin, Coordinate destination, Fraction probability) ;
    ~Piece() ;

    // assume there exists a superposition at position
    std::string stringAtPos(Coordinate position) const ;

};

#endif
