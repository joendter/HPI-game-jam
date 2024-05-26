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

bool Player::colorCorrect() const {
    for (auto piece : pieces) {
        if (piece->color != color)
            return false;
    }
    return true;
}

bool Player::piecesCorrect() const {
    for (auto piece : pieces) {
        if (!piece->isCorrect())
            return false;
    }
    return true;
}

unsigned Player::numberPiecesOnSquare(Coordinate location) const {
    unsigned accumulator = 0;
    for (auto piece : pieces) {
        accumulator += piece->onLocation(location) != nullptr;
    }
    return accumulator;
}

void Player::spawnPiece(enum Piecetype type, Coordinate location) {
    Piece *piece = new Piece();
    Superposition *super = new Superposition(type, Fraction(1));
    piece->superpositions[location] = super;
    piece->color = color;
    pieces.insert(piece);
}

bool Player::hasKing() const{
    for (auto piece: pieces){
        for (auto super : piece->superpositions){
            if (super.second->type == KING) return true;
        }
    }
    return false;
}
