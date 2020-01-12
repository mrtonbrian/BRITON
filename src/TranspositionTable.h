//
// Created by brianton on 1/10/20.
//
#include "Types.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "Position.h"
#ifndef CHESS_ENGINE_CPP_TRANSPOSITIONTABLE_H
#define CHESS_ENGINE_CPP_TRANSPOSITIONTABLE_H
struct TranspositionTableEntry {
    uint64_t positionKey;
    int move;
    int score;
    int depth;
    int ply;
    TableFlags flags;
};

struct TranspositionTable {
    TranspositionTableEntry* entries;
    int numEntries;
    int numOverwrite;
};
extern TranspositionTable TT;

void clearTable();
bool probeHashEntry();
#endif //CHESS_ENGINE_CPP_TRANSPOSITIONTABLE_H
