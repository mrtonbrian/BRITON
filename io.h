#include "defs.h"
#include "Globals.h"
#include "stdio.h"
#include <string>

#ifndef IO
#define IO
char *printSquare(int square, Globals g);
char *printMove(int square, Globals g);
int parseMove(std::string inp, BOARD * pos, Globals g);
void printMoveList(MOVES_LIST &list, Globals g);
#endif
