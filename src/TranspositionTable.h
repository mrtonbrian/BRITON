//
// Created by brianton on 5/31/20.
//

#include <cstdint>

#ifndef CHESS_ENGINE_CPP_TRANSPOSITIONTABLE_H
#define CHESS_ENGINE_CPP_TRANSPOSITIONTABLE_H
typedef struct {
    uint64_t positionKey;
    int move;
    int eval;
    int flag;
    int depth;
} HashEntry;

struct HashTable {
    HashEntry *entries;
    int numEntries;
    void initHashTable(int sizeMB);
    void clearHashTable();
    void storePvMove(uint64_t position, int move);
    int probeTable(uint64_t position);
};


#endif //CHESS_ENGINE_CPP_TRANSPOSITIONTABLE_H
