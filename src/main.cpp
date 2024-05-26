#include "main.h"

int main() {
    Game game;
    game = Game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

    game.print();
    game.move(Coordinate(1, 1), Coordinate(1, 2));
    game.print();
    game.move(Coordinate(2, 3), Coordinate(3, 3));
    game.print();
    game.move(Coordinate(1, 2), Coordinate(2, 3));
    game.print();
    game.move(Coordinate(3, 3), Coordinate(1, 1));
    game.print();
    
    repl(game);

    return 0;
}
