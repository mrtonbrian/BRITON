#include "defs.h"
#include "pvtable.h"
#include "Globals.h"
#include "movegen.h"
#include "makemove.h"
#include <iostream>

void clearPvTable(hashTable *table) {
    hashEntry *entry;
    for (entry = table->pTable; entry < table->pTable + table->numEntries; entry++) {
        entry->position = 0ULL;
        entry->move = 0;
        entry->depth = 0;
        entry->score = 0;
        entry->flags = 0;
    }

    table->newWrite = 0;
}

void initPvTable(hashTable *table, const int mb) {
    long hashSize = 0x1000000 * mb;
    table->numEntries = hashSize / sizeof(hashEntry);
    table->numEntries -= 2;
    if (table->pTable != NULL) {
        free(table->pTable);
    }
    table->pTable = (hashEntry *) malloc(table->numEntries * sizeof(hashEntry));
    if (table->pTable == NULL) {
        printf("Hash Allocation Failed; Trying %d MB\n", mb/2);
        initPvTable(table, mb/2);
    } else {
        clearPvTable(table);
        printf("Hash Table init Complete with %d entries\n", table->numEntries);
    }
}

void StorePvMove(BOARD *pos, int move, int score, int flags, int depth) {
    int index = pos->position % pos->pvTable->numEntries;

    if (pos->pvTable->pTable[index].position == 0) {
        pos->pvTable->newWrite++;
    } else {
        pos->pvTable->overWrite++;
    }

    // Mate Score - Max Depth
    if (score > 29000 - 64) {
        score += pos->ply;
    } else if (score < (-29000 - 64)) {
        score -= pos->ply;
    }

    pos->pvTable->pTable[index].position = pos->position;
    pos->pvTable->pTable[index].move = move;
    pos->pvTable->pTable[index].flags = flags;
    pos->pvTable->pTable[index].depth = depth;
    pos->pvTable->pTable[index].score = score;
}

bool ProbeHashEntry(BOARD *pos, int *move, int *score, int alpha, int beta, int depth) {

    int index = pos->position % pos->pvTable->numEntries;

    if( pos->pvTable->pTable[index].position == pos->position ) {
        *move = pos->pvTable->pTable[index].move;
        if(pos->pvTable->pTable[index].depth >= depth){
            pos->pvTable->hit++;
            
            *score = pos->pvTable->pTable[index].score;
            if(*score > 29000 - 64) *score -= pos->ply;
            else if(*score < (-29000 - 64)) *score += pos->ply;

            switch(pos->pvTable->pTable[index].flags) {

                case ALPHA: if(*score<=alpha) {
                        *score=alpha;
                        return true;
                    }
                    break;
                case BETA: if(*score>=beta) {
                        *score=beta;
                        return true;
                    }
                    break;
                case EXACT:
                    return true;
                default: ASSERT(false);
            }
        }
    }

    return false;
}

int probeTable(BOARD *pos) {
    int index = pos->position % pos->pvTable->numEntries;
    if (pos->pvTable->pTable[index].position == pos->position) {
        return pos->pvTable->pTable[index].move;
    }
    return 0;
}

int GetPvLine(int depth, BOARD *pos, Globals &g) {

    ASSERT(depth < 64 && depth >= 1);

    int move = probeTable(pos);
    int count = 0;

    while (move != 0 && count < depth) {

        ASSERT(count < 120);

        if (MoveExists(pos, move, g)) {
            makeMove(pos, move, g);
            pos->PvArray[count++] = move;
        } else {
            break;
        }
        move = probeTable(pos);
    }
    // Reset position
    while (pos->ply > 0) {
        TakeMove(pos, g);
    }
    return count;
}