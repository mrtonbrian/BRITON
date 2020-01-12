#include "misc.h"
#include "Types.h"
#include <string>
#include <vector>

#ifndef CHESS_ENGINE_CPP_POSITION_H
#define CHESS_ENGINE_CPP_POSITION_H


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
    bool makeMoveIfExists(int move);
    void unmakeMove();

    Bitboard pieces();
    Bitboard pieces(PieceType pieceType);
    Bitboard pieces(Color c);
    Bitboard pieces(Color c, PieceType pieceType);
    uint64_t getZobristHash();

    int principalVariation[512];
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
    int hisPly;

    uint64_t pieceKeys[15][SQUARE_NUM];
    uint64_t sideKey;
    uint64_t castleKeys[16];
    PrevBoard prevBoards[2048];

    void generateWhitePawnMoves(std::vector<Move>& moves);
    void generateBlackPawnMoves(std::vector<Move>& moves);
    void generateWhiteKnightMoves(std::vector<Move>& moves);
    void generateBlackKnightMoves(std::vector<Move>& moves);
    void generateWhiteBishopMoves(std::vector<Move>& moves);
    void generateBlackBishopMoves(std::vector<Move>& moves);
    void generateWhiteRookMoves(std::vector<Move>& moves);
    void generateBlackRookMoves(std::vector<Move>& moves);
    void generateWhiteQueenMoves(std::vector<Move>& moves);
    void generateBlackQueenMoves(std::vector<Move>& moves);
    void generateWhiteKingMoves(std::vector<Move>& moves);
    void generateBlackKingMoves(std::vector<Move>& moves);

    void hashPiece(Piece piece, Square sq);
    void hashCastle();
    void hashSide();
    void hashEnPass();

    void clearPiece(Square square);
    void addPiece(Piece piece, Square square);
};

inline Bitboard Position::pieces() {
    return byColor[COLOR_WHITE] | byColor[COLOR_BLACK];
}

inline Bitboard Position::pieces(PieceType pieceType) {
    return byType[pieceType];
}

inline Bitboard Position::pieces(Color color) {
    return byColor[color];
}

inline Bitboard Position::pieces(Color color, PieceType pieceType) {
    return byColor[color] & byType[pieceType];
}

inline uint64_t Position::getZobristHash() {
    return zobristHash;
}
#endif //CHESS_ENGINE_CPP_POSITION_H
