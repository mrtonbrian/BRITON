#include "defs.h"
#include "move.h"

int fromSq(int m)
{
    return ((m)&0x7F);
}

int toSq(int m)
{
    return ((m >> 7) & 0x7F);
}

int capturePiece(int m)
{
    return ((m >> 14) & 0xF);
}

int promotionPiece(int m)
{
    return ((m >> 20) & 0xF);
}

bool isEnPass(int m)
{
    return (m & 0x40000);
}

bool isPawnStart(int m)
{
    return (m & 0x80000);
}

bool isCastle(int m)
{
    return (m & 0x1000000);
}

bool isCapture(int m)
{
    return (m & 0x7C000);
}

bool isPromotion(int m)
{
    return (m & 0xF00000);
}
