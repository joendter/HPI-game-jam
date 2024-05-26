# HPI-game-jam
18th HPI Game Jam: Architects of Disaster.  
Credits to [ChatGPT](https://chatgpt.com/share/ea195cec-ca03-48bd-abb5-0740f3a8628f).  

# build-instructions
To build this project you will need [cmake](https://cmake.org/) and a C++ compiler (ideally [g++](https://gcc.gnu.org/)).  
Run
```sh
cd src
make
```
The finished executable will be located in `/out/main`.  
Run it in a terminal emulator that supports ANSI escape sequences for colors.  
# Quantum-Chess: The Game
Have you ever though chess was too deterministic? Too much skill involved? It's unfun because you always loose?  
This version of chess tries to address this:  
Pieces aren't guaranteed to move if you tell them to. They only transfer into a superposition between the board state if they moved and if they didn't move.  
These superpositions only resolve once one piece tries to move ontop of another.  
The attacker is resolved first, then if he can still attack the defender is resolved.  
It is possible to attack your own pieces, if you do and both pieces collapse into the positions where they collide, the attacker doesn't move.  
Other notable differences to normal chess:
- no castling
- no 2 space pawn move
	- no en passant
- pawns can always move diagonally
- pawns always promote to a queen
- no more check/checkmate -> You win if you take the enemy king