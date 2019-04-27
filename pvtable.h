#include "defs.h"
#include "Globals.h"

#ifndef PVTABLE_H
#define PVTABLE_H

void initPvTable(PVTABLE * table);
void StorePvMove(BOARD * pos, int move);
int probeTable(BOARD * pos);
void clearPvTable(PVTABLE * table);
int GetPvLine(int depth, BOARD *pos, Globals g);

#endif