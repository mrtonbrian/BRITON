#include <cstdint>
#include "TranspositionTable.h"

#ifndef TYPES
#define TYPES
typedef uint64_t Bitboard;

const int SQUARE_NUM = 64;

enum File {
    FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE
};

enum Rank {
    RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE
};

enum Square {
    SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1,
    SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2,
    SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3,
    SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4,
    SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5,
    SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6,
    SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7,
    SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8,
    SQ_NONE,
};

enum Color {
    COLOR_WHITE, COLOR_BLACK,
    COLOR_NB = 2
};

const int MAX_DEPTH = 128;
const int MATE_SCORE = 100000;
const int MIN_VAL = -1000001;
const int MAX_VAL = 1000001;

/*
 * Values Come From Stockfish
 * https://github.com/official-stockfish/Stockfish/tree/master
 */

enum GameStates {
    MIDGAME,
    ENDGAME,
    NUM_GAME_STATES = 2
};

// Castling White Kingside, White Queenside, etc.
enum CastlingPerms {
    WHITE_K_K = 1,
    WHITE_K_Q = 2,
    BLACK_K_K = 4,
    BLACK_K_Q = 8
};

enum Piece {
    PIECE_NONE,
    W_PAWN = 1, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
    B_PAWN = 9, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING,
    PIECE_NB = 16
};

enum PieceType {
    NO_PIECE_TYPE, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, ALL_PIECE_TYPES,
    PIECE_TYPE_NB = 8
};

struct SMasks {
    Bitboard lower;
    Bitboard upper;
    Bitboard line; // Lower | Upper
};

struct Move {
    int move;
    int score;
};

struct SearchInfo {
    long starttime;
    long stoptime;

    int depth;
    int depthset;

    bool stopped;
    bool timeSet;
};

const int MIDGAME_LIMIT = 15258;
const int ENDGAME_LIMIT = 3915;

extern SMasks masks[SQUARE_NUM][4];

extern Bitboard KNIGHT_ATTACKS[SQUARE_NUM];

extern Bitboard KING_ATTACKS[SQUARE_NUM];

extern Bitboard PAWN_SINGLE_MOVES[COLOR_NB][SQUARE_NUM];
extern Bitboard PAWN_DOUBLE_MOVES[COLOR_NB][SQUARE_NUM];
extern Bitboard PAWN_ATTACKS[COLOR_NB][SQUARE_NUM];

extern Bitboard OO_MASK[COLOR_NB];
extern Bitboard OOO_MASK[COLOR_NB];

extern Bitboard OO_ATTACK_MASK[COLOR_NB];
extern Bitboard OOO_ATTACK_MASK[COLOR_NB];

extern int MaterialValues[NUM_GAME_STATES][PIECE_TYPE_NB];

extern HashTable globalHashTable;

#define gen_move(f, t, p, c, pr, ep, ca) ((f) | (t<<6) | (p<<12) | (c<<16) | (pr<<20) | (ep<<25) | (ca<<26))
#define mv_from(m) ((m) & (0b111111))
#define mv_to(m) ((m >> 6) & (0b111111))
#define mv_piece(m) ((m >> 12) & (0b1111))
#define mv_cap(m) ((m >> 16) & (0b1111))
#define mv_prom(m) ((m >> 20) & (0b1111))
#define mv_ep(m) ((m >> 25) & (0b1))
#define mv_castle(m) ((m >> 26) & (0b1))
#endif
