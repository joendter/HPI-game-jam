#ifndef PLAYER_H
#define PLAYER_H
#include "color.h"
#include "coordinate.h"
#include "piece.h"
#include <set>
class Player {
  public:
    enum Color color;
    std::set<Piece *> pieces;

    Piece *findPiece(Coordinate location) const;
    void takePiece(Piece *piece);
    bool colorCorrect() const;
    bool piecesCorrect() const;
    unsigned numberPiecesOnSquare(Coordinate location) const;
    void spawnPiece(enum Piecetype type, Coordinate location);
    bool hasKing() const;
};
#endif
