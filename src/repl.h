#ifndef REPL_H
#define REPL_H
#include "game.h"
#include "debugprint.h"
#include "ansicolor.h"
#include "coordinate.h"
#include <string>
#include <iostream>
void repl(Game game);
bool checkInput(std::string input);
Coordinate getOrigin(std::string input);
Coordinate getDestination(std::string input);
#endif
