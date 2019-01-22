#include "defs.h"
#include "Globals.h"

#ifndef MOVEGEN
#define MOVEGEN
void generateAllMoves(BOARD * pos, MOVES_LIST & list, Globals g);
bool MoveExists(BOARD * pos, const int move, Globals g);
void initMvvLva();
void generateAllCaps(BOARD * pos, MOVES_LIST & list, Globals g);
#endif
