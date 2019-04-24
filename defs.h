#ifndef DEFS
#define DEFS

#include "stdlib.h"
#include <vector>

/*
#ifndef ASSERT
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed\n",#n); \
printf("On %s \n",__DATE__); \
printf("At %s \n",__TIME__); \
printf("In File %s \n",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);}
#endif
*/

#define ASSERT

// Unsigned 64bit Integer
typedef unsigned long long U64;

#define MAXDEPTH 64

#define SQUARENUM 120

#define MOVEI(f,t,ca,pro,fl) ( (f) | ((t) << 7) | ( (ca) << 14 ) | ( (pro) << 20 ) | (fl))

// Generates Random 64 Bit Integers
#define RAND_64  ((U64)rand() | \
     (U64)rand() << 15 | \
     (U64)rand() << 30 | \
     (U64)rand() << 45 | \
     ((U64)rand() & 0xf) << 60 )

// Sets Values To These (EMPTY = 0, White Pawn = 1, White Knight = 2, etc.)
enum {EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK};

enum {COL_A, COL_B, COL_C, COL_D, COL_E, COL_F, COL_G, COL_H, COL_NONE};
enum {ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8, ROW_NONE};

enum {
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD
};

enum {WHITE, BLACK, BOTH};

// Castling White Kingside, White Queenside, etc.
enum {WHITE_K_K = 1, WHITE_K_Q = 2, BLACK_K_K = 4, BLACK_K_Q = 8};

typedef struct {
    U64 position;
    int move;
} PVENTRY;

typedef struct {
    PVENTRY * pTable;
    int numEntries;
} PVTABLE;


typedef struct {
    int move;
    int score;
} MOVE;

typedef struct {
    int move;
    int castle;
    int enPass;
    int fiftyMove;
    U64 posKey;
} UNDO;

typedef struct {
    int pieces[SQUARENUM];
    // BitBoards
    U64 pawns[3];
    U64 king[2];
    
    int sideToMove;
    int enPass;
    int fiftyMove;
    
    // For Search (Depth)
    int ply;
    int hisPly;

    U64 position;

    // Ex.) If One Wants # Of Blk Bishops, Call pieceNum[9]
    int pieceNum[13];

    int nonPawn[2];
    // Rooks and Queens
    int RQ[2];
    // Knights and Bishops
    int KB[2];
    int material[2];

    int castlePerm;

    UNDO history[2048];

    // NOTE WE USE 10 BC MAX OF 10 PIECE OF SAME TYPE (2 WHITE ROOKS + 8 WHITE PAWNS = 10 POSSIBLE WHITE ROOKS)
    int pList[13][10];
    
    PVTABLE pvTable[1];
    // 64 as MaxDepth
    int PvArray[64];

    // Heuristics
    int searchHistory[13][120];
    int searchKillers[2][64];
} BOARD;

typedef struct {
    std::vector<MOVE> moves;
    int count;
} MOVES_LIST;

typedef struct {
    int starttime;
    int stoptime;
    int depth;
    int depthset;
    int timeset;
    int movesToGo;
    int infinite;

    long nodes;

    int quit; 
    int stopped;

    // https://www.chessprogramming.org/index.php?title=Fail-High&mobileaction=toggle_view_mobile
    int failHigh;
    int failHighFirst;
} SEARCHINFO;
#endif
