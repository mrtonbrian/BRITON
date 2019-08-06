#include "defs.h"
#include "Globals.h"

#ifndef MAKEMOVE
#define MAKEMOVE

bool makeMove(BOARD *pos, int move, Globals &g);

void TakeMove(BOARD *pos, Globals &g);

void makeNullMove(BOARD *pos, Globals &g);

void takeNullMove(BOARD *pos, Globals &g);

#endif