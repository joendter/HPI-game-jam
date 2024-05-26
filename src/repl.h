#ifndef REPL_H
#define REPL_H
#include "ansicolor.h"
#include "coordinate.h"
#include "debugprint.h"
#include "game.h"
#include <iostream>
#include <string>
void repl(Game game);
bool checkInput(std::string input);
Coordinate getOrigin(std::string input);
Coordinate getDestination(std::string input);
#endif
