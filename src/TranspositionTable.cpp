//
// Created by brianton on 1/10/20.
//

#include "TranspositionTable.h"
#include <cassert>

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
        printf("hashtable alloc failed; trying %d Mb". mb / 2);
        initTable(mb / 2);
    }

    printf("init hashtable with %d entries\n", TT.numEntries);
}

void storeMove(Position& position, int move, int score, TableFlags flags, int depth, int ply) {
    int tableIndex = position.getZobristHash() % TT.numEntries;

    TranspositionTableEntry* prevEntry = &TT.entries[tableIndex];

    // Entry Exists
    if (prevEntry->positionKey != 0) {
        int putScore = depth - prevEntry->depth;
        putScore += (ply - prevEntry->ply);

        // Prioritize Exact Evals Over Beta-Cutoffs
        if (flags == EXACT) putScore += 2;
        else if (flags == BETA) putScore += 1;

        TableFlags prevFlag = prevEntry->flags;
        if (prevFlag == EXACT) putScore -= 2;
        else if (prevFlag == BETA) putScore -= 1;

        // Add If Desired
        if (putScore > 0) {
            TT.entries[tableIndex].positionKey = position.getZobristHash();
            TT.entries[tableIndex].move = move;
            TT.entries[tableIndex].score = score;
            TT.entries[tableIndex].depth = depth;
            TT.entries[tableIndex].ply = ply;
            TT.entries[tableIndex].flags = flags;
            TT.numOverwrite++;
        }
    }
}

bool probeHashEntry(Position& position, int* move, int* score, int alpha, int beta, int depth) {
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

TranspositionTableEntry* getHashEntry(uint64_t key) {
    int i = key % TT.numEntries;
    if (TT.entries[i].positionKey == key) {
        return &TT.entries[i];
    }
    return NULL;
}

std::vector<int> getPVLine(Position pos, int depth) {
    std::vector<int> out;
    out.push_back(pos.principalVariation[0]);

    assert(pos.makeMoveIfExists(out[0]));
    TranspositionTableEntry* entry;
    while (out.size() < depth && (entry = getHashEntry(pos.getZobristHash()))!= NULL) {
        if (pos.makeMoveIfExists(entry->move)) {
            out.push_back(entry->move);
        } else {
            break;
        }
    }

    for (int i = 0; i <= out.size(); i++) {
        pos.unmakeMove();
    }

    return out;
}