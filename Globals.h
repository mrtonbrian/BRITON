#include "defs.h"
#include "stdio.h"
#include <vector>

#ifndef GLOBALS
#define GLOBALS

class Globals {
    public:
    int SQ120TOSQ64[120];
    int SQ64TOSQ120[64];
    U64 SETMASK[64];
    U64 CLEARMASK[64];
    U64 PieceKeys[13][120];
    U64 SideKey;
    U64 CastleKeys[16];
    int ColumnBoard[120];
    int RowBoard[120];

    // Is Rook or Queen?
    bool isHorizontalSlide[13] = { false, false, false, false, true, true, false, false, false, false, true, true, false };
    // Is Bishop Or Queen?
    bool isDiagonalSlide[13] = { false, false, false, true, false, true, false, false, false, true, false, true, false };
    bool isKing[13] = {false, false, false, false, false, false, true, false, false, false, false, false, true};
    bool isKnight[13] = {false, false, true, false, false, false, false, false, true, false, false, false, false};

    // Used As True / False Answer Lookups
    int NonPawn[13] = { false, false, true, true, true, true, true, false, true, true, true, true, true };
    int RookQueen[13] = { false, false, false, false, true, true, true, false, false, false, true, true, true };
    int BishopKnight[13] = { false, false, true, true, false, false, false, false, true, true, false, false, false };

    // Centipawn Values http://chess.wikia.com/wiki/Centipawn
    int PieceVal[13]= { 0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000  };
    int PieceCol[13] = { BOTH, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK };


    int SQ64(int x) {
        return SQ120TOSQ64[x];
    }

    int SQ120(int x) {
        return SQ64TOSQ120[x];
    }

    bool IsKing(int p) {
        return isKing[p];
    }

    bool IsRookQueen(int p) {
        return isHorizontalSlide[p];
    }

    bool IsKnight(int p) {
        return isKnight[p];
    }

    bool IsBishopQueen(int p) {
        return isDiagonalSlide[p];
    }

    bool isOffBoard(int sq) {
        return (ColumnBoard[sq] == OFFBOARD);
    }
};
#endif