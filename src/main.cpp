#include "game.cpp"
int main() { 
    Game game;

    game.board = Coordinate(8,8);
    game.turn = 0;
    game.players[0] = Player();
    game.players[1] = Player();
    game.players[0].white = WHITE;
    game.players[1].white = BLACK;
    Piece* piece = new Piece();
    Superposition* super = new Superposition(QUEEN, Fraction(1));
    piece->superpositions[Coordinate(1,1)] = super;
    game.players[0].pieces.insert(piece);
    game.print();
    piece = new Piece();
    super = new Superposition(QUEEN, Fraction(1));
    piece->superpositions[Coordinate(2,3)] = super;
    game.players[1].pieces.insert(piece);
    game.print();
    game.move(Coordinate(1,1), Coordinate(1,2));
    game.print();
    game.move(Coordinate(2,3), Coordinate(3,3));
    game.print();




    return 0; 

}
