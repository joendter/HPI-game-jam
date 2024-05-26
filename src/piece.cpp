#include "piece.h"

bool validPieceMove(enum Piecetype piecetype, Coordinate diff) {
    if (piecetype == PAWN) {
        return (diff.y == 1) && (-1 <= diff.x) && (diff.x <= 1);
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

Superposition::Superposition(enum Piecetype type, Fraction probability)
    : type(type), probability(probability) {}

Superposition *Piece::onLocation(Coordinate location) const {
    auto it = superpositions.find(location);
    if (it == superpositions.end()) {
        return nullptr;
    }
    return (it->second);
}

Fraction Piece::probabilityOnLocation(Coordinate location) const {
    auto it = onLocation(location);
    if (it == nullptr)
        return Fraction(0);
    return (it->probability);
}

bool Piece::validMove(Coordinate origin, Coordinate destination) const {
    auto it = onLocation(origin);
    if (it == nullptr)
        return false;
    return validPieceMove(it->type,
            color ? 
            destination - origin :
            origin - destination
            );
}

void Piece::collapse(std::mt19937 gen) {
    unsigned smallest_common_denominator = 1;
    for (auto pair : superpositions) {
        smallest_common_denominator =
            std::lcm(smallest_common_denominator,
                     pair.second->probability.getDenominator());
    }

    std::uniform_int_distribution<> dis(1, smallest_common_denominator);
    DEBUGOUT << "lcm: " << smallest_common_denominator << std::endl;
    unsigned randomNumber = dis(gen);
    DEBUGOUT << "generated value" << randomNumber << std::endl;
    unsigned accumulator = 0;
    bool found = false;
    Coordinate collapsedPosition;
    enum Piecetype collapsedPiecetype;
    for (auto pair : superpositions) {
        accumulator +=
            (pair.second->probability * Fraction(smallest_common_denominator))
                .getNumerator();
        if ((accumulator >= randomNumber) && (!found)) {
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

void Piece::move(Coordinate origin, Coordinate destination,
                 Fraction probability) {
    auto it = onLocation(origin);
    Fraction yoinkedProbability = it->probability * probability;
    it->probability = it->probability - yoinkedProbability;
    auto other = onLocation(destination);
    if (other != nullptr) {
        other->probability = other->probability + yoinkedProbability;
        DEBUGOUT << "superpositions after move" << superpositions.size()
                 << std::endl;
        return;
    }
    enum Piecetype newSuperType = it->type;
    if (it->type == PAWN && (destination.y == 0 + 7*color)){
        newSuperType = QUEEN;
    }
    superpositions[destination] =
        new Superposition(newSuperType, yoinkedProbability);
    DEBUGOUT << "superpositions after move" << superpositions.size()
             << std::endl;
    DEBUGOUT << "superposition at origin: "
             << superpositions.find(origin)->second->probability << std::endl;
}

Piece::~Piece() {
    for (auto i : superpositions) {
        delete i.second;
    }
}

// assume there exists a superposition at position
std::string Piece::stringAtPos(Coordinate position) const {
    auto it = superpositions.find(position)->second;
    return foregroundColor(
        std::string() + (char)(it->type) + it->probability.asHex(),
        getColor());
}

bool Piece::isCorrect() const {
    Fraction accumulator = Fraction(0);
    for (auto super : superpositions) {
        accumulator = accumulator + super.second->probability;
    }
    return accumulator == Fraction(1);
}

RGBColor Piece::getColor() const {
    return RGBColor(255 * color, 255 * color, 255 * color);
}
