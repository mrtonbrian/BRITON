//
// Created by brianton on 1/10/20.
//

#include "TranspositionTable.h"
#include <cassert>

TranspositionTable TT;

void clearTable() {
    TT.numOverwrite = 0;

    memset(TT.entries, 0, TT.numEntries * sizeof(TranspositionTableEntry));
}

void initTable(int mb) {
    if (mb == 0) {
        // Initialize Some Small Amount Of Memory
        // If no size specified
        mb = 25;
    }

    uint64_t hashSize = 1000000ULL * mb;
    TT.numEntries = hashSize / sizeof(TranspositionTableEntry);
    // Just So We Don't Segfault
    TT.numEntries -= 2;
    if (TT.entries != NULL) {
        free(TT.entries);
    }

    TT.entries = (TranspositionTableEntry *) calloc(TT.numEntries, sizeof(TranspositionTableEntry));
    if (TT.entries == NULL) {
        printf("hashtable alloc failed; trying %d Mb", mb / 2);
        initTable(mb / 2);
    }

    printf("init hashtable with %d entries\n", TT.numEntries);
}

void storeMove(Position &position, int move, int score, TableFlags flags, int depth) {
    int tableIndex = position.getZobristHash() % TT.numEntries;

    TT.entries[tableIndex].positionKey = position.getZobristHash();
    TT.entries[tableIndex].move = move;
    TT.entries[tableIndex].score = score;
    TT.entries[tableIndex].depth = depth;
    TT.entries[tableIndex].flags = flags;
}

bool probeHashEntry(Position &position, int *move, int *score, int alpha, int beta, int depth) {
    int tableIndex = position.getZobristHash() % TT.numEntries;

    if (TT.entries[tableIndex].positionKey == position.getZobristHash()) {
        *move = TT.entries[tableIndex].move;
        if (TT.entries[tableIndex].depth >= depth) {
            *score = TT.entries[tableIndex].score;
            switch (TT.entries[tableIndex].flags) {
                case ALPHA:
                    if (*score <= alpha) {
                        *score = alpha;
                        return true;
                    }
                    break;
                case BETA:
                    if (*score >= beta) {
                        *score = beta;
                        return true;
                    }
                    break;
                case EXACT:
                    return true;
                default:
                    assert(false);
            }
        }
    }
    return false;
}

TranspositionTableEntry *getHashEntry(uint64_t key) {
    int i = key % TT.numEntries;
    if (TT.entries[i].positionKey == key) {
        return &TT.entries[i];
    }
    return NULL;
}

std::vector<int> getPVLine(Position &pos, int depth) {
    std::vector<int> out;
    out.push_back(pos.principalVariation[0]);
    pos.makeMove(out[0]);
    TranspositionTableEntry *entry = getHashEntry(pos.getZobristHash());
    int i = 0;
    while (i < depth && entry) {
        if (pos.makeMoveIfExists(entry->move)) {
            out.push_back(entry->move);
        } else {
            break;
        }
        entry = getHashEntry(pos.getZobristHash());
        i++;
    }

    for (int j = 0; j <= i; j++) {
        pos.unmakeMove();
    }

    return out;
}