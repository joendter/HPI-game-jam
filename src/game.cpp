#include "game.h"

Piece *Game::onLocation(Coordinate location) const {
    auto it = players[0].findPiece(location);
    if (it == nullptr)
        it = players[1].findPiece(location);
    return it;
}

void Game::print() const {
    std::cout << "turn: " << turn << std::endl << " ";
    for (int x = 0; x < board.x; x++) {
        std::cout << "" << (char)('a' + x) << " ";
    }
    std::cout << std::endl;
    for (int y = 0; y < board.y; y++) {
        std::cout << y + 1;
        for (int x = 0; x < board.x; x++) {
            Coordinate currentLocation = Coordinate(x, y);
            auto piece = onLocation(currentLocation);
            if (piece == nullptr) {
                std::cout << backgroundColor("  ",
                                             getSquareColor(currentLocation));
            } else {
                std::cout << backgroundColor(
                    piece->stringAtPos(currentLocation),
                    getSquareColor(currentLocation));
            }
        }
        std::cout << std::endl;
    }
}

bool Game::validMove(Coordinate origin, Coordinate destination) const {

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
    auto pieceType = piece->onLocation(origin)->type;
    if (pieceType == ROOK || pieceType == BISHOP || pieceType == QUEEN){
        if (!raycastFree(origin, destination)){return false;}
    }

    return true;
}
void Game::move(Coordinate origin, Coordinate destination) {
    std::mt19937 gen(dirtyrandom());
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
         //DEBUGOUT<< "moved normally" << std::endl;
        piece->move(origin, destination, probability);
        goto success;
    }


    // collapse the attacker
    piece->collapse(gen);
    // check if the move is still valid with the collapsed attacker
    if (!validMove(origin, destination)) {
        goto success;
    };

    defender->collapse(gen);
    defender =
        players[(turn + 1 + defenderFriendly) % 2].findPiece(destination);
    if (defender == nullptr) {
        piece->move(origin, destination, Fraction(1));
        goto success;
    }
    if (defenderFriendly) {
        goto success;
    }
    if (!defenderFriendly) {
        players[(turn + 1) % 2].takePiece(defender);
        piece->move(origin, destination, Fraction(1));
        goto success;
    }

success:
    prevOrigin = origin;
    prevDestination = destination;
    turn++;
    return;
}

bool Game::isValid() const {
    // all colors are correct
    if (!(players[0].color == WHITE && players[1].color == BLACK))
        return false;
    if (!(players[0].colorCorrect() && players[1].colorCorrect()))
        return false;

    // all pieces are correct
    if (!(players[0].piecesCorrect() && players[1].piecesCorrect()))
        return false;

    // there are no 2 pieces on 1 square
    for (auto x = 0; x < board.x; x++) {
        for (auto y = 0; y < board.y; y++) {
            if (!(players[0].numberPiecesOnSquare(Coordinate(x, y)) +
                      players[1].numberPiecesOnSquare(Coordinate(x, y)) <=
                  1))
                return false;
        }
    }
    return true;
}

RGBColor Game::getSquareColor(Coordinate location) const {
    bool even = (location.x + location.y) % 2;
    bool touched =  ((location == prevOrigin) + (location == prevDestination));
    return RGBColor(255 - 64*touched, 
            128 * (1 - even) , 
            128 * (1 - even));
}

Game::Game(std::string fen) {
    board = Coordinate(8, 8);
    turn = 0;
    players[0] = Player();
    players[1] = Player();
    players[0].color = WHITE;
    players[1].color = BLACK;
    unsigned x = 0;
    unsigned y = 7;
    for (char c : fen) {
        if (c == '/') {
            y--;
            x = 0;
        };
        if ('1' <= c && c <= '9')
            x += c - '0';
        if ('a' <= c && c <= 'z')
            players[1].spawnPiece((enum Piecetype)c, Coordinate(x++, y));
        if ('A' <= c && c <= 'Z')
            players[0].spawnPiece((enum Piecetype)(c - 'A' + 'a'), Coordinate(x++, y));
        if (c == ' ')
            break;
    }
}

bool Game::raycastFree(Coordinate origin, Coordinate destination) const{
    Piece* it = onLocation(origin);
    Piece* other;
    Coordinate direction = (destination - origin).direction();
    for (Coordinate tmp = origin ; tmp != destination; tmp = tmp + direction){
        other = onLocation(tmp);
        if (other != nullptr && other != it) return false;
    }
    return true;
}
