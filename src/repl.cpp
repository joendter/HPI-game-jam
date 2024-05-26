#include "repl.h"
void repl(Game game) {
    std::string input;
    unsigned turn = game.turn;
    while (1) {
        game.print();
        if (turn == game.turn) {
            std::cout << "nothing moved" << std::endl;
        }
        turn = game.turn;
        std::getline(std::cin, input);
        if (!checkInput(input)) {
            std::cout << "invalid input" << std::endl;
        }
        game.move(getOrigin(input), getDestination(input));
        if (game.winner() != -1) {
            std::cout << "player " << game.winner() << " won" << std::endl;
        }
    }
}

bool checkInput(std::string input) {

    if (input.length() != 4) {
        return false;
    }

    if (input[0] < 'a' || input[0] > 'h') {
        return false;
    }

    if (input[2] < 'a' || input[2] > 'h') {
        return false;
    }

    if (input[1] < '1' || input[1] > '8') {
        return false;
    }

    if (input[1] < '1' || input[1] > '8') {
        return false;
    }

    return true;
}

Coordinate getOrigin(std::string input) {
    return Coordinate(input[0] - 'a', input[1] - '1');
}

Coordinate getDestination(std::string input) {
    return Coordinate(input[2] - 'a', input[3] - '1');
}
