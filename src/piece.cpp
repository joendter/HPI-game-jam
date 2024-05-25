#ifndef PIECE_CPP
#define PIECE_CPP
#include "color.h"
#include "coordinate.cpp"
#include "fraction.cpp"
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

bool validPieceMove(enum Piecetype piecetype, Coordinate diff) {
    if (piecetype == PAWN) {
        return diff == Coordinate(1, 0);
    }

    diff = diff.normalised();
    switch (piecetype) {
    case ROOK:
        return diff.y == 0;
    case BISHOP:
        return diff.x == diff.y;
    case KNIGHT:
        return diff.x == 2 && diff.y == 1;
    case QUEEN:
        return diff.y == 0 || diff.x == diff.y;
    case KING:
        return diff <= Coordinate(1, 1);
    default:
        throw std::invalid_argument(
            ((std::string) "invalid piece type: " + (char)piecetype).c_str());
    }
}

struct Superposition {
    enum Piecetype type;
    Fraction probability;

    Superposition(enum Piecetype type, Fraction probability)
        : type(type), probability(probability) {}
};

class Piece {
  public:
    enum Color color;
    std::map<Coordinate, Superposition *> superpositions;

    Superposition *onLocation(Coordinate location) const {
        auto it = superpositions.find(location);
        if (it == superpositions.end()) {
            return nullptr;
        }
        return (it->second);
    }

    Fraction probabilityOnLocation(Coordinate location) const {
        auto it = onLocation(location);
        if (it == nullptr)
            return Fraction(0);
        return (it->probability);
    }

    bool validMove(Coordinate origin, Coordinate destination) const {
        auto it = onLocation(origin);
        if (it == nullptr)
            return false;
        return validPieceMove(it->type, destination - origin);
    }

    template <typename Generator> void collapse(Generator gen) {
        unsigned smallest_common_denominator = 1;
        for (auto pair : superpositions) {
            smallest_common_denominator =
                std::lcm(smallest_common_denominator,
                         pair.second->probability.getDenominator());
        }

        std::uniform_int_distribution<> dis(1, smallest_common_denominator);
        unsigned randomNumber = dis(gen);
        unsigned accumulator = 0;
        bool found = false;
        Coordinate collapsedPosition;
        enum Piecetype collapsedPiecetype;
        for (auto pair : superpositions) {
            accumulator += (pair.second->probability *
                            Fraction(smallest_common_denominator))
                               .getNumerator();
            if (accumulator <= randomNumber && !found) {
                collapsedPosition = pair.first;
                collapsedPiecetype = pair.second->type;
                found = true;
            }
            delete pair.second;
        }
        superpositions.clear();
        superpositions[collapsedPosition] =
            new Superposition(collapsedPiecetype, Fraction(1));
    }

    void move(Coordinate origin, Coordinate destination, Fraction probability) {
        auto it = onLocation(origin);
        Fraction yoinkedProbability = it->probability * probability;
        it->probability -= yoinkedProbability;
        auto other = onLocation(destination);
        if (other != nullptr) {
            other->probability += yoinkedProbability;
            return;
        }
        superpositions[destination] =
            new Superposition(it->type, yoinkedProbability);
    }

    ~Piece() {
        for (auto i : superpositions) {
            delete i.second;
        }
    }

    // assume there exists a superposition at position
    std::string stringAtPos(Coordinate position) const {
        auto it = superpositions.find(position)->second;
        return std::string() + (char)(it->type) +
               std::to_string((float)it->probability)[2];
    }
};

#endif
