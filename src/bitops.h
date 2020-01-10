//
// Created by brianton on 12/27/19.
//

#include "Bitboard.h"
#include "Types.h"

#ifndef CHESS_ENGINE_CPP_BITOPS_H
#define CHESS_ENGINE_CPP_BITOPS_H

#ifdef __GNUC__
#define bsr(x) (63-__builtin_clzll(x))
#define popcnt(x) (__builtin_popcountll(x))
#else
#define bsr(x) (bitScanReverse(x))
#define popcnt(x) (populationCount(x))
#endif

int bitScanReverse(Bitboard bb);

int popBit(Bitboard& bb);

int populationCount(Bitboard bb);

#endif //CHESS_ENGINE_CPP_BITOPS_H