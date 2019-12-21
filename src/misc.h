#include "Types.h"

#ifndef CHESS_ENGINE_CPP_MISC_H
#define CHESS_ENGINE_CPP_MISC_H

constexpr Color getColorFromPiece(Piece p) {
    return Color(p >> 3);
}

constexpr PieceType getTypeFromPiece(Piece p) {
    return PieceType(p & 7);
}

constexpr Square makeSquare(Rank r, File f) {
    return Square((r << 3) | f);
}

uint64_t random64BitInteger();

#endif //CHESS_ENGINE_CPP_MISC_H
