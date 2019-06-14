#include "Globals.h"
#include "defs.h"

#ifndef BB
#define BB
void printBB(U64 bb, Globals &a);
const int BitTable[64] = {
    63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
    51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
    26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
    58, 20, 37, 17, 36, 8};
int popBit(U64 *);
int countBits(U64 b);
void clearBit(U64 &b, int sq, Globals g);
void setBit(U64 &b, int sq, Globals g);
#endif