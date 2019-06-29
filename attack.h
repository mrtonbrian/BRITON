#include "defs.h"
#include "bitboards.h"
#include "Globals.h"

#ifndef ATTACK
#define ATTACK

bool squareAttacked(int sq, int side, Globals& g, BOARD *pos);

#endif