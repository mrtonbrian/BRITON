#include "defs.h"
#include "stdio.h"
#include <vector>

#ifndef GLOBALS
#define GLOBALS

class Globals
{
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
    bool isHorizontalSlide[13] = {false, false, false, false, true, true, false, false, false, false, true, true, false};
    // Is Bishop Or Queen?
    bool isDiagonalSlide[13] = {false, false, false, true, false, true, false, false, false, true, false, true, false};
    bool isKing[13] = {false, false, false, false, false, false, true, false, false, false, false, false, true};
    bool isKnight[13] = {false, false, true, false, false, false, false, false, true, false, false, false, false};

    // Used As True / False Answer Lookups
    int NonPawn[13] = {false, false, true, true, true, true, true, false, true, true, true, true, true};
    int RookQueen[13] = {false, false, false, false, true, true, true, false, false, false, true, true, true};
    int BishopKnight[13] = {false, false, true, true, false, false, false, false, true, true, false, false, false};

    // Centipawn Values http://chess.wikia.com/wiki/Centipawn
    int PieceVal[13] = {0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000};
    int PieceCol[13] = {BOTH, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK};

    // Mirror Board
    // Gets Equivalent Square Index for Black (Note That Square Vals Are Built To Perspective Of White)
    const int Mirror64[64] = {
        56, 57, 58, 59, 60, 61, 62, 63,
        48, 49, 50, 51, 52, 53, 54, 55,
        40, 41, 42, 43, 44, 45, 46, 47,
        32, 33, 34, 35, 36, 37, 38, 39,
        24, 25, 26, 27, 28, 29, 30, 31,
        16, 17, 18, 19, 20, 21, 22, 23,
        8, 9, 10, 11, 12, 13, 14, 15,
        0, 1, 2, 3, 4, 5, 6, 7};

    int MIRROR(int sq)
    {
        return Mirror64[sq];
    }

    // Pawn Bitmasks
    U64 colBBMask[8];
    U64 rowBBMask[8];
    U64 blackPassedMask[64];
    U64 whitePassedMask[64];
    U64 isolatedMask[64];

    int SQ64(int x)
    {
        return SQ120TOSQ64[x];
    }

    int SQ120(int x)
    {
        return SQ64TOSQ120[x];
    }

    bool IsKing(int p)
    {
        return isKing[p];
    }

    bool IsRookQueen(int p)
    {
        return isHorizontalSlide[p];
    }

    bool IsKnight(int p)
    {
        return isKnight[p];
    }

    bool IsBishopQueen(int p)
    {
        return isDiagonalSlide[p];
    }

    bool isOffBoard(int sq)
    {
        return (ColumnBoard[sq] == OFFBOARD);
    }
};
#endif