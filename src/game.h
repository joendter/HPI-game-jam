#ifndef GAME_H
#define GAME_H
#include "ansicolor.h"
#include "coordinate.h"
#include "debugprint.h"
#include "dirtyrandom.h"
#include "fraction.h"
#include "player.h"
#include <iostream>
#include <random>

class Game {
  public:
    Coordinate board;
    Player players[2];
    unsigned int turn;
    Fraction probability = Fraction(1, 2);

    Piece *onLocation(Coordinate location) const;
    void print() const;
    bool validMove(Coordinate origin, Coordinate destination) const;
    void move(Coordinate origin, Coordinate destination);
    bool isValid() const;
    RGBColor getSquareColor(Coordinate location) const;
    Game(std::string fen = "8/8/8/8/8/8/8/8");
    bool raycastFree(Coordinate origin, Coordinate destination) const;
};
#endif
