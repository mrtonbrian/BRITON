#include <iostream>
#include "defs.h"
#include "init.h"
#include "Globals.h"
#include "movegen.h"

using namespace std;

// NOTE: THIS IS IN 120 SQUARE FORMAT
int rowColToSquare(int row, int col) {
    return (21 + col) + (10 * row);
}

void initSquareArrays(Globals &a) {
    int index = 0;
	int file = COL_A;
	int rank = ROW_1;
	int sq = A1;
	int sq64 = 0;
	for(index = 0; index < 120; ++index) {
		a.SQ120TOSQ64[index] = 65;
	}
	
	for(index = 0; index < 64; ++index) {
		a.SQ64TOSQ120[index] = 120;
	}
	
	for(rank = ROW_1; rank <= ROW_8; ++rank) {
		for(file = COL_A; file <= COL_H; ++file) {
			sq = rowColToSquare(rank,file);
			a.SQ64TOSQ120[sq64] = sq;
			a.SQ120TOSQ64[sq] = sq64;
			sq64++;
		}
	}
}

void initMasks(Globals &g) {
    //Initialize Both Arrays To ALL Zeros Before Ops
    for (int i = 0; i < 64; i++) {
        g.SETMASK[i] = 0ULL;
        g.CLEARMASK[i] = 0ULL; 
    }
    for (int i = 0; i < 64; i++) {
        g.SETMASK[i] |= (1ULL << i);
        g.CLEARMASK[i] = ~g.SETMASK[i];
    }
}
void InitHashKeys(Globals &g) {
	int index = 0;
	int index2 = 0;
	for(index = 0; index < 13; ++index) {
		for(index2 = 0; index2 < 120; ++index2) {
			g.PieceKeys[index][index2] = RAND_64;
		}
	}

	g.SideKey = RAND_64;
	for(index = 0; index < 16; ++index) {
		g.CastleKeys[index] = RAND_64;
	}
}

void initRowColArrays(Globals &g) {
	// Default State Of Square is Offboard
	for (int i = 0; i < 120; i++) {
		g.RowBoard[i] = OFFBOARD;
		g.ColumnBoard[i] = OFFBOARD;
	}

	for (int row = ROW_1; row <= ROW_8; row++) {
		for (int col = COL_A; col <= COL_H; col++) {
			int s = rowColToSquare(row,col);
			g.RowBoard[s] = row;
			g.ColumnBoard[s] = col;
		}
	}
}

void init(Globals &a) {
    initSquareArrays(a);
    initMasks(a);
    InitHashKeys(a);
	initRowColArrays(a);
	initMvvLva();
}