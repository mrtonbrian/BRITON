#include "defs.h"
#include "Globals.h"

#ifndef PVTABLE_H
#define PVTABLE_H

void initPvTable(hashTable *table, const int mb);

void StorePvMove(BOARD *pos, int move, int score, int flags, int depth);

int probeTable(BOARD *pos);

void clearPvTable(hashTable *table);

int GetPvLine(int depth, BOARD *pos, Globals &g);

bool ProbeHashEntry(BOARD *pos, int *move, int *score, int alpha, int beta, int depth);
#endif