#ifndef CHESS_ENGINE_CPP_BITBOARD_H
#define CHESS_ENGINE_CPP_BITBOARD_H

#include <iostream>
#include "Types.h"
#include "misc.h"

inline int popcnt(Bitboard b) {
    return __builtin_popcountll(b);
}

inline int lsb(Bitboard b) {
    return __builtin_ctzll(b);
}

inline int msb1(Bitboard b) {
    return (63 ^ __builtin_ctzll(b));
}

inline void setBit(Bitboard &b, int bit) {
    b |= (1ULL << bit);
}

inline void clearBit(Bitboard &b, int bit) {
    b &= ~(1ULL << bit);
}

void printBitboard(Bitboard b);

#endif //CHESS_ENGINE_CPP_BITBOARD_H
