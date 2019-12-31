//
// Created by brianton on 12/27/19.
//

#include "Bitboard.h"
#include "Types.h"

#ifndef CHESS_ENGINE_CPP_BITOPS_H
#define CHESS_ENGINE_CPP_BITOPS_H

int bitScanReverse(Bitboard bb);

int popBit(Bitboard& bb);

#endif //CHESS_ENGINE_CPP_BITOPS_H