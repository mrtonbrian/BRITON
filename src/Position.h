#include "misc.h"
#include "Types.h"
#include <string>
#include <vector>

#ifndef CHESS_ENGINE_CPP_POSITION_H
#define CHESS_ENGINE_CPP_POSITION_H

#define gen_move(f, t, p, c, pr, ep, ca) ((f) | (t<<6) | (p<<12) | (c<<16) | (pr<<20) | (ep<<25) | (ca<<26))
#define mv_from(m) ((m) & (0b111111))
#define mv_to(m) ((m >> 6) & (0b111111))
#define mv_piece(m) ((m >> 12) & (0b1111))
#define mv_cap(m) ((m >> 16) & (0b1111))
#define mv_prom(m) ((m >> 20) & (0b1111))
#define mv_ep(m) ((m >> 25) & (0b1))
#define mv_castle(m) ((m >> 26) & (0b1))


const char pieceToChar[15] = {
        '-',
        'P',
        'N',
        'B',
        'R',
        'Q',
        'K',
        '\0',
        '\0',
        'p',
        'n',
        'b',
        'r',
        'q',
        'k'
};

const char colorToChar[2] = {
        'W',
        'B'
};

const uint8_t castle_update[64] = {
        13, 15, 15, 15, 12, 15, 15, 14,
        15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15,
        7,  15, 15, 15, 3, 15, 15, 11
};

struct PrevBoard {
    int move;
    int castlePerms;
    int enPassSquare;
    int fiftyMove;
    uint64_t positionKey;
};

class Position {
public:
    void init();
    uint64_t generatePositionKey();
    bool setFromFEN(std::string fen);
    void resetPosition();
    void printBoard();
    std::vector<Move> generateAllMoves();
    bool squareAttacked(Square sq, Color color);
    bool squareAttacked(Bitboard bitmap, Color color);
    void flipTurn();
    bool makeMove(int move);
    void unmakeMove();
private:
    Bitboard byType[PIECE_TYPE_NB];
    Bitboard byColor[COLOR_NB];
    Piece board[SQUARE_NUM];
    int pieceCount[PIECE_NB];
    uint64_t zobristHash;
    Color turn;
    int castlePerms;
    int enPassSquare;
    int fiftyMove;
    int searchPly;

    uint64_t pieceKeys[15][SQUARE_NUM];
    uint64_t sideKey;
    uint64_t castleKeys[16];
    std::vector<PrevBoard> prevBoards;

    void generateWhitePawnMoves(std::vector<Move> moves);
    void generateBlackPawnMoves(std::vector<Move> moves);
    void generateWhiteKnightMoves(std::vector<Move> moves);
    void generateBlackKnightMoves(std::vector<Move> moves);
    void generateWhiteBishopMoves(std::vector<Move> moves);
    void generateBlackBishopMoves(std::vector<Move> moves);
    void generateWhiteRookMoves(std::vector<Move> moves);
    void generateBlackRookMoves(std::vector<Move> moves);
    void generateWhiteQueenMoves(std::vector<Move> moves);
    void generateBlackQueenMoves(std::vector<Move> moves);
    void generateWhiteKingMoves(std::vector<Move> moves);
    void generateBlackKingMoves(std::vector<Move> moves);

    void hashPiece(Piece piece, Square sq);
    void hashCastle();
    void hashSide();
    void hashEnPass();

    void clearPiece(Square square);
    void addPiece(Piece piece, Square square);
};

#endif //CHESS_ENGINE_CPP_POSITION_H
