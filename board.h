#include "defs.h"
#include "Globals.h"
#include "bitboards.h"

#ifndef BOARD_H
#define BOARD_H
void resetBoard(BOARD *pos, Globals& g);
void parseFEN(const char *FEN, BOARD *pos, Globals& g);
void printBoard(BOARD *pos);
void UpdateMaterialLists(BOARD *pos, Globals& g);
bool checkBoard(BOARD *pos, Globals& g);
void mirrorBoard(BOARD *pos, Globals& g);
#endif
