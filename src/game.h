#ifndef GAME_H
#define GAME_H
#include "coordinate.h"
#include "fraction.h"
#include "player.h"
#include <iostream>
#include <random>
#include "dirtyrandom.h"

class Game {
  public:
    Coordinate board;
    Player players[2];
    unsigned int turn;
    Fraction probability = Fraction(1,2);


    Piece *onLocation(Coordinate location) const ;
    void print() const;
    bool validMove(Coordinate origin, Coordinate destination) const;
    void move(Coordinate origin, Coordinate destination);

};
#endif
