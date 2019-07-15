#include <iostream>
#include "defs.h"
#include "init.h"
#include "Globals.h"
#include "movegen.h"
#include "bitboards.h"

using namespace std;

// NOTE: THIS IS IN 120 SQUARE FORMAT
int rowColToSquare(int row, int col) {
    return (21 + col) + (10 * row);
}

void initSquareArrays(Globals &a) {
    int index = 0;
    int sq64 = 0;
    for (index = 0; index < 120; ++index) {
        a.SQ120TOSQ64[index] = 65;
    }

    for (index = 0; index < 64; ++index) {
        a.SQ64TOSQ120[index] = 120;
    }

    for (int row = ROW_1; row <= ROW_8; ++row) {
        for (int col = COL_A; col <= COL_H; ++col) {
            int sq = rowColToSquare(row, col);
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
    for (index = 0; index < 13; ++index) {
        for (index2 = 0; index2 < 120; ++index2) {
            g.PieceKeys[index][index2] = RAND_64;
        }
    }

    g.SideKey = RAND_64;
    for (index = 0; index < 16; ++index) {
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
            int s = rowColToSquare(row, col);
            g.RowBoard[s] = row;
            g.ColumnBoard[s] = col;
        }
    }
}

void initEvalMasks(Globals &g) {
    for (int sq = 0; sq < 8; ++sq) {
        g.colBBMask[sq] = 0ULL;
        g.rowBBMask[sq] = 0ULL;
    }

    for (int row = ROW_8; row >= ROW_1; row--) {
        for (int col = COL_A; col <= COL_H; col++) {
            int sq = row * 8 + col;
            g.colBBMask[col] |= (1ULL << sq);
            g.rowBBMask[row] |= (1ULL << sq);
        }
    }

    for (int sq = 0; sq < 64; ++sq) {
        g.isolatedMask[sq] = 0ULL;
        g.whitePassedMask[sq] = 0ULL;
        g.blackPassedMask[sq] = 0ULL;
    }

    for (int sq = 0; sq < 64; ++sq) {
        int tsq = sq + 8;

        while (tsq < 64) {
            g.whitePassedMask[sq] |= (1ULL << tsq);
            tsq += 8;
        }

        tsq = sq - 8;
        while (tsq >= 0) {
            g.blackPassedMask[sq] |= (1ULL << tsq);
            tsq -= 8;
        }

        if (g.ColumnBoard[g.SQ120(sq)] > COL_A) {
            g.isolatedMask[sq] |= g.colBBMask[g.ColumnBoard[g.SQ120(sq)] - 1];

            tsq = sq + 7;
            while (tsq < 64) {
                g.whitePassedMask[sq] |= (1ULL << tsq);
                tsq += 8;
            }

            tsq = sq - 9;
            while (tsq >= 0) {
                g.blackPassedMask[sq] |= (1ULL << tsq);
                tsq -= 8;
            }
        }

        if (g.ColumnBoard[g.SQ120(sq)] < COL_H) {
            g.isolatedMask[sq] |= g.colBBMask[g.ColumnBoard[g.SQ120(sq)] + 1];

            tsq = sq + 9;
            while (tsq < 64) {
                g.whitePassedMask[sq] |= (1ULL << tsq);
                tsq += 8;
            }

            tsq = sq - 7;
            while (tsq >= 0) {
                g.blackPassedMask[sq] |= (1ULL << tsq);
                tsq -= 8;
            }
        }
    }
}

void init(Globals &a) {
    initSquareArrays(a);
    initMasks(a);
    InitHashKeys(a);
    initRowColArrays(a);
    initEvalMasks(a);
    initMvvLva();
}