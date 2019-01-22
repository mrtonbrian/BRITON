#include "defs.h"
#include "pvtable.h"
#include "Globals.h"
#include "movegen.h"
#include "makemove.h"
#include <iostream>
using namespace std;

const long PvSize = 0x1000000 * 2;

void clearPvTable(PVTABLE * table) {
    PVENTRY * entry;
    for (entry = table->pTable; entry < table->pTable + table->numEntries; entry++) {
        entry->position = 0ULL;
        entry->move     = 0;
    }
}

void initPvTable(PVTABLE * table) {
    table->numEntries = PvSize / sizeof(PVENTRY);
    table->numEntries -= 2;
    if(table != NULL) { free(table->pTable); }
    else {table->pTable = 0; free(table->pTable);}
    table->pTable = new PVENTRY[table->numEntries];
    clearPvTable(table);
}

void StorePvMove(BOARD * pos, int move) {
    int index = pos->position % pos->pvTable->numEntries;
    pos->pvTable->pTable[index].move = move;
    pos->pvTable->pTable[index].position = pos->position;
}

int probeTable(BOARD * pos) {
    int index = pos-> position % pos->pvTable->numEntries;
    if (pos->pvTable->pTable[index].position == pos->position) {
        return pos->pvTable->pTable[index].move;
    }
    return 0;
}

int GetPvLine(int depth, BOARD *pos, Globals g) {

	ASSERT(depth < 64);

	int move = probeTable(pos);
	int count = 0;
	
	while(move != 0 && count < depth) {
	
		ASSERT(count < 120);
	
		if(MoveExists(pos, move, g) ) {
			makeMove(pos, move, g);
			pos->PvArray[count++] = move;
		} else {
			break;
		}		
		move = probeTable(pos);	
	}
    // Reset position
	while(pos->ply > 0) {
		TakeMove(pos, g);
	}
	return count;
}