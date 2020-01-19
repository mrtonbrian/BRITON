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
    TableFlags flags;
};

struct TranspositionTable {
    TranspositionTableEntry* entries;
    int numEntries;
    int numOverwrite;
};
extern TranspositionTable TT;

std::vector<int> getPVLine(Position& pos, int depth);
TranspositionTableEntry* getHashEntry(uint64_t key);
bool probeHashEntry(Position& position, int* move, int* score, int alpha, int beta, int depth);
void storeMove(Position& position, int move, int score, TableFlags flags, int depth);
void initTable(int mb);
void clearTable();
#endif //CHESS_ENGINE_CPP_TRANSPOSITIONTABLE_H
