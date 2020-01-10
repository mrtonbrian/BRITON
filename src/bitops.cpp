//
// Created by brianton on 12/27/19.
//

#include <cassert>
#include "bitops.h"

const int index64[64] = {
        0, 47, 1, 56, 48, 27, 2, 60,
        57, 49, 41, 37, 28, 16, 3, 61,
        54, 58, 35, 52, 50, 42, 21, 44,
        38, 32, 29, 23, 17, 11, 4, 62,
        46, 55, 26, 59, 40, 36, 15, 53,
        34, 51, 20, 43, 31, 22, 10, 45,
        25, 39, 14, 33, 19, 30, 9, 24,
        13, 18, 8, 12, 7, 6, 5, 63
};

/**
 * bitScanReverse
 * @authors Kim Walisch, Mark Dickinson
 * @param bb bitboard to scan
 * @precondition bb != 0
 * @return index (0..63) of most significant one bit
 */
int bitScanReverse(Bitboard bb) {
    const uint64_t debruijn64 = 0x03f79d71b4cb0a89ULL;
    bb |= bb >> 1;
    bb |= bb >> 2;
    bb |= bb >> 4;
    bb |= bb >> 8;
    bb |= bb >> 16;
    bb |= bb >> 32;
    return index64[(bb * debruijn64) >> 58];
}

int popBit(Bitboard &bb) {
    int out = bsr(bb);
    bb ^= (1ULL << out);
    return out;
}

// https://www.chessprogramming.org/Population_Count#The_PopCount_routine
const uint64_t k1 = 0x5555555555555555ULL; /*  -1/3   */
const uint64_t k2 = 0x3333333333333333ULL; /*  -1/5   */
const uint64_t k4 = 0x0f0f0f0f0f0f0f0fULL; /*  -1/17  */
const uint64_t kf = 0x0101010101010101ULL; /*  -1/255 */
int populationCount(Bitboard bb) {
    bb = bb - ((bb >> 1) & k1); /* put count of each 2 bits into those 2 bits */
    bb = (bb & k2) + ((bb >> 2) & k2); /* put count of each 4 bits into those 4 bits */
    bb = (bb + (bb >> 4)) & k4; /* put count of each 8 bits into those 8 bits */
    bb = (bb * kf) >> 56; /* returns 8 most significant bits of x + (x<<8) + (x<<16) + (x<<24) + ...  */
    return (int) bb;
}