#include "player.h"

    Piece *Player::findPiece(Coordinate location) const {
        for (auto piece : pieces) {
            if (piece->probabilityOnLocation(location) > Fraction(0)) {
                return piece;
            }
        }
        return nullptr;
    }

    void Player::takePiece(Piece *piece) {
        delete piece;
        pieces.erase(piece);
    }
