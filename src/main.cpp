#include "main.h"

int main() {
    Game game;
    game = Game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    std::cout << "first char of each square is the piece, second one is the probability in hex in 1/16ths" <<std::endl;
    std::cout << "move pieces by entering origin and destination square, like this: `d2d3` or `b1c3`" << std::endl;
   repl(game);

    return 0;
}
