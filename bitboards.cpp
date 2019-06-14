#include "init.h"
#include "Globals.h"
#include "bitboards.h"
#include "defs.h"
#include <cstdio>
#include <iostream>
using namespace std;

int popBit(U64 *bb)
{
    U64 b = *bb ^ (*bb - 1);
    unsigned int fold = (unsigned)((b & 0xffffffff) ^ (b >> 32));
    *bb &= (*bb - 1);
    return BitTable[(fold * 0x783a9b23) >> 26];
}

int countBits(U64 b)
{
    int r;
    for (r = 0; b; r++, b &= b - 1)
        ;
    return r;
}

void printBB(U64 bb, Globals &a)
{
    U64 shift = 1ULL;
    int sq = 0;
    int sq64 = 0;
    printf("\n");

    for (int r = ROW_8; r >= ROW_1; r--)
    {
        for (int c = COL_A; c <= COL_H; c++)
        {
            sq = rowColToSquare(r, c);
            sq64 = a.SQ64(sq);

            if ((shift << sq64) & bb)
            {
                printf("X");
            }
            else
            {
                printf("-");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

// Speed Optimization
void clearBit(U64 &b, int sq, Globals g)
{
    b &= g.CLEARMASK[sq];
}
void setBit(U64 &b, int sq, Globals g)
{
    b |= g.SETMASK[sq];
}