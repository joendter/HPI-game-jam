#ifndef PLAYER_CPP
#define PLAYER_CPP
#include "color.h"
#include "coordinate.cpp"
#include "piece.cpp"
#include <set>
class Player {
  public:
    enum Color white;
    std::set<Piece *> pieces;

    Piece *findPiece(Coordinate location) const {
        for (auto piece : pieces) {
            if (piece->probabilityOnLocation(location) > Fraction(0)) {
                return piece;
            }
        }
        return nullptr;
    }

    void takePiece(Piece *piece) {
        delete piece;
        pieces.erase(piece);
    }
};
#endif
