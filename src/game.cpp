#ifndef GAME_CPP
#define GAME_CPP
#include "coordinate.cpp"
#include "fraction.cpp"
#include "player.cpp"
#include <iostream>
#include <random>

class Game {
  public:
    Coordinate board;
    Player players[2];
    unsigned int turn;
    Fraction probability = Fraction(1, 2);

    Piece *onLocation(Coordinate location) const {
        auto it = players[0].findPiece(location);
        if (it == nullptr)
            it = players[1].findPiece(location);
        return it;
    }

    void print() const {
        std::cout << turn << std::endl;
        for (int y = 0; y < board.y; y++) {
            for (int x = 0; x < board.x; x++) {
                auto piece = onLocation(Coordinate(x, y));
                if (piece == nullptr) {
                    std::cout << "|  |";
                }
                else {
                std::cout << "|" << piece->stringAtPos(Coordinate(x, y)) << "|";
                }
            }
            std::cout << std::endl;
        }
    }

    bool validMove(Coordinate origin, Coordinate destination) const {

        // check if coords are out of bound
        if (!(origin <= board && destination <= board)) {
            return false;
        }

        // find the piece to move
        Piece *piece = players[turn % 2].findPiece(origin);
        // return if no piece was found
        if (piece == nullptr) {
            return false;
        }
        // check if move is valid
        if (!piece->validMove(origin, destination)) {
            return false;
        }

        return true;
    }
    void move(Coordinate origin, Coordinate destination) {
        // check if move is valid
        if (!validMove(origin, destination)) {
            return;
        }


        // find the piece to move
        Piece *piece = players[turn % 2].findPiece(origin);

        // check if there's a piece where we want to move to
        Piece *defender = players[turn % 2].findPiece(destination);
        bool defenderFriendly = true;
        if (defender == nullptr) {
            defender = players[(turn + 1) % 2].findPiece(destination);
            defenderFriendly = false;
        }
        // if the square we want to move to is empty move to that square
        if (defender == nullptr || defender == piece) {
            std::cout << "moved normally" << std::endl;
            piece->move(origin, destination, probability);
            turn++;
            return;
        }

        std::random_device rd; // Obtain a random seed from the operating system
        std::mt19937 gen(rd());

        // collapse the attacker
        piece->collapse(gen);
        // check if the move is still valid with the collapsed attacker
        if (!validMove(origin, destination))
        {turn++;return;};

        defender->collapse(gen);
        defender =
            players[(turn + 1 + defenderFriendly) % 2].findPiece(destination);
        if (defender == nullptr) {
            piece->move(origin, destination, Fraction(1));
            turn++;
            return;
        }
        if (defenderFriendly) {
            turn++;
            return;
        }
        if (!defenderFriendly) {
            players[(turn + 1) % 2].takePiece(defender);
            piece->move(origin, destination, Fraction(1));
            turn++;
            return;
        }
    }
};
#endif
