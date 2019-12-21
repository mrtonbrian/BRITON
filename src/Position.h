#include "misc.h"
#include "Types.h"
#include <string>

#ifndef CHESS_ENGINE_CPP_POSITION_H
#define CHESS_ENGINE_CPP_POSITION_H

class Position {
public:
    void init();
    uint64_t generatePositionKey();
    bool movePiece(Piece piece, Square from, Square to);
    bool setFromFEN(std::string fen);
    void resetPosition();
    void printBoard();

    Bitboard byType[PIECE_TYPE_NB];
    Bitboard byColor[COLOR_NB];
    Piece board[SQUARE_NUM];
    int pieceCount[PIECE_NB];
    uint64_t zobristHash;
    Color turn;
    int castlePerms;
    int enPassSquare;

    uint64_t pieceKeys[15][SQUARE_NUM];
    uint64_t sideKey;
    uint64_t castleKeys[16];
};

#endif //CHESS_ENGINE_CPP_POSITION_H
