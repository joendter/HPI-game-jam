#ifndef PLAYER_H
#define PLAYER_H
#include "color.h"
#include "coordinate.h"
#include "piece.h"
#include <set>
class Player {
  public:
    enum Color white;
    std::set<Piece *> pieces;

    Piece *findPiece(Coordinate location) const ;
    void takePiece(Piece *piece);
};
#endif
