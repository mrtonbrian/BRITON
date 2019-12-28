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

constexpr Rank getRank(Square s) {
    return Rank(int(s) >> 3);
}

constexpr File getFile(Square s) {
    return File(int(s) & 7);
}

constexpr bool is_ok(Square s) {
    return s >= SQ_A1 && s <= SQ_H8;
}

constexpr bool fileRankOk(File f, Rank r) {
    return (FILE_A <= f && f <= FILE_H) && (RANK_1 <= r && r <= RANK_8);
}

uint64_t random64BitInteger();

#endif //CHESS_ENGINE_CPP_MISC_H
