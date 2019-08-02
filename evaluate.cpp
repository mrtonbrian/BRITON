#include "evaluate.h"
#include "defs.h"
#include "Globals.h"
#include "io.h"

// Piece Square Table https://www.chessprogramming.org/Piece-Square_Tables
const int PawnTable[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        10, 10, 0, -10, -10, 0, 10, 10,
        5, 0, 0, 5, 5, 0, 0, 5,
        0, 0, 10, 20, 20, 10, 0, 0,
        5, 5, 5, 10, 10, 5, 5, 5,
        10, 10, 10, 20, 20, 10, 10, 10,
        20, 20, 20, 30, 30, 20, 20, 20,
        0, 0, 0, 0, 0, 0, 0, 0};

const int KnightTable[64] = {
        0, -10, 0, 0, 0, 0, -10, 0,
        0, 0, 0, 5, 5, 0, 0, 0,
        0, 0, 10, 10, 10, 10, 0, 0,
        0, 0, 10, 20, 20, 10, 0, 0,
        5, 10, 15, 20, 20, 15, 10, 5,
        5, 10, 10, 20, 20, 10, 10, 5,
        0, 0, 5, 10, 10, 5, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0};

const int BishopTable[64] = {
        0, 0, -10, 0, 0, -10, 0, 0,
        0, 0, 0, 10, 10, 0, 0, 0,
        0, 0, 10, 15, 15, 10, 0, 0,
        0, 10, 15, 20, 20, 15, 10, 0,
        0, 10, 15, 20, 20, 15, 10, 0,
        0, 0, 10, 15, 15, 10, 0, 0,
        0, 0, 0, 10, 10, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0};

const int RookTable[64] = {
        0, 0, 5, 10, 10, 5, 0, 0,
        0, 0, 5, 10, 10, 5, 0, 0,
        0, 0, 5, 10, 10, 5, 0, 0,
        0, 0, 5, 10, 10, 5, 0, 0,
        0, 0, 5, 10, 10, 5, 0, 0,
        0, 0, 5, 10, 10, 5, 0, 0,
        25, 25, 25, 25, 25, 25, 25, 25,
        0, 0, 5, 10, 10, 5, 0, 0};
/*
const int KingE[64] = {
        -50, -10, 0, 0, 0, 0, -10, -50,
        -10, 0, 10, 10, 10, 10, 0, -10,
        0, 10, 15, 15, 15, 15, 10, 0,
        0, 10, 15, 20, 20, 15, 10, 0,
        0, 10, 15, 20, 20, 15, 10, 0,
        0, 10, 15, 15, 15, 15, 10, 0,
        -10, 0, 10, 10, 10, 10, 0, -10,
        -50, -10, 0, 0, 0, 0, -10, -50
};

const int KingO[64] = {
        0, 10, 10, -10, -10, 10, 20, 5,
        -5, -5, -5, -5, -5, -5, -5, -5,
        -10, -10, -10, -10, -10, -10, -10, -10,
        -70, -70, -70, -70, -70, -70, -70, -70,
        -70, -70, -70, -70, -70, -70, -70, -70,
        -70, -70, -70, -70, -70, -70, -70, -70,
        -70, -70, -70, -70, -70, -70, -70, -70,
        -70, -70, -70, -70, -70, -70, -70, -70
};
 */

const int pawnPassed[8] = {0, 5, 10, 20, 40, 80, 160, 200};
const int isolatedPawn = -20;
const int rookOpenCol = 30;
const int rookSemiOpenCol = 10;
const int queenOpenCol = 5;
const int queenSemiOpenCol = 3;
const int bishopPair = 30;

//int PieceVal[13] = {0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000};
//const int endgameMaterialMax = (1 * PieceVal[wR] + 2 * PieceVal[wN] + 2 * PieceVal[wP]);

// https://en.wikipedia.org/wiki/Draw_(chess)
/*
Impossibility of checkmate – if a position arises in which neither player could possibly give checkmate by a series of legal moves, the game is a draw ("dead position"). This is usually because there is insufficient material left, but it is possible in other positions too. Combinations with insufficient material to checkmate are:
king versus king
king and bishop versus king
king and knight versus king
king and bishop versus king and bishop with the bishops on the same color.
*/

bool materialDraw(const BOARD *pos) {
    if (!pos->pieceNum[wR] && !pos->pieceNum[bR] && !pos->pieceNum[wQ] && !pos->pieceNum[bQ]) {
        if (!pos->pieceNum[bB] && !pos->pieceNum[wB]) {
            if (pos->pieceNum[wN] < 3 && pos->pieceNum[bN] < 3)
                return true;
        } else if (!pos->pieceNum[wN] && !pos->pieceNum[bN]) {
            if (abs(pos->pieceNum[wB] - pos->pieceNum[bB]) < 2)
                return true;
        } else if ((pos->pieceNum[wN] < 3 && !pos->pieceNum[wB]) || (pos->pieceNum[wB] == 1 && !pos->pieceNum[wN])) {
            if ((pos->pieceNum[bN] < 3 && !pos->pieceNum[bB]) || (pos->pieceNum[bB] == 1 && !pos->pieceNum[bN]))
                return true;
        }
    } else if (!pos->pieceNum[wQ] && !pos->pieceNum[bQ]) {
        if (pos->pieceNum[wR] == 1 && pos->pieceNum[bR] == 1) {
            if ((pos->pieceNum[wN] + pos->pieceNum[wB]) < 2 && (pos->pieceNum[bN] + pos->pieceNum[bB]) < 2)
                return true;
        } else if (pos->pieceNum[wR] == 1 && !pos->pieceNum[bR]) {
            if ((pos->pieceNum[wN] + pos->pieceNum[wB] == 0) &&
                (((pos->pieceNum[bN] + pos->pieceNum[bB]) == 1) || ((pos->pieceNum[bN] + pos->pieceNum[bB]) == 2)))
                return true;
        } else if (pos->pieceNum[bR] == 1 && !pos->pieceNum[wR]) {
            if ((pos->pieceNum[bN] + pos->pieceNum[bB] == 0) &&
                (((pos->pieceNum[wN] + pos->pieceNum[wB]) == 1) || ((pos->pieceNum[wN] + pos->pieceNum[wB]) == 2)))
                return true;
        }
    }
    return false;
}


int evalPosition(BOARD *pos, Globals &g) {
    int pce;
    int sq;

    // Material Score
    int score = pos->material[WHITE] - pos->material[BLACK];

    if (!pos->pieceNum[wP] && !pos->pieceNum[bP] && materialDraw(pos)) {
        return 0;
    }

    pce = wP;
    for (int i = 0; i < pos->pieceNum[pce]; i++) {
        sq = pos->pList[pce][i];
        ASSERT(!g.isOffBoard(sq));
        score += PawnTable[g.SQ64(sq)];

        if ((g.isolatedMask[g.SQ64(sq)] & pos->pawns[WHITE]) == 0) {
            score += isolatedPawn;
        }

        if ((g.whitePassedMask[g.SQ64(sq)] & pos->pawns[BLACK]) == 0) {
            score += pawnPassed[g.RowBoard[sq]];
        }
    }

    pce = bP;
    for (int i = 0; i < pos->pieceNum[pce]; i++) {
        sq = pos->pList[pce][i];
        ASSERT(!g.isOffBoard(sq));
        score -= PawnTable[g.MIRROR(g.SQ64(sq))];

        if ((g.isolatedMask[g.SQ64(sq)] & pos->pawns[BLACK]) == 0) {
            score -= isolatedPawn;
        }

        if ((g.blackPassedMask[g.SQ64(sq)] & pos->pawns[WHITE]) == 0) {
            score -= pawnPassed[7 - g.RowBoard[sq]];
        }
    }

    pce = wN;
    for (int i = 0; i < pos->pieceNum[pce]; i++) {
        sq = pos->pList[pce][i];
        ASSERT(!g.isOffBoard(sq));
        score += KnightTable[g.SQ64(sq)];
    }

    pce = bN;
    for (int i = 0; i < pos->pieceNum[pce]; i++) {
        sq = pos->pList[pce][i];
        ASSERT(!g.isOffBoard(sq));
        score -= KnightTable[g.MIRROR(g.SQ64(sq))];
    }

    pce = wB;
    for (int i = 0; i < pos->pieceNum[pce]; i++) {
        sq = pos->pList[pce][i];
        ASSERT(!g.isOffBoard(sq));
        score += BishopTable[g.SQ64(sq)];
    }

    pce = bB;
    for (int i = 0; i < pos->pieceNum[pce]; i++) {
        sq = pos->pList[pce][i];
        ASSERT(!g.isOffBoard(sq));
        score -= BishopTable[g.MIRROR(g.SQ64(sq))];
    }

    pce = wR;
    for (int i = 0; i < pos->pieceNum[pce]; i++) {
        sq = pos->pList[pce][i];
        ASSERT(!g.isOffBoard(sq));
        score += RookTable[g.SQ64(sq)];

        if (!(pos->pawns[BOTH] & g.colBBMask[g.ColumnBoard[sq]])) {
            score += rookOpenCol;
        } else if (!(pos->pawns[WHITE] & g.colBBMask[g.ColumnBoard[sq]])) {
            score += rookSemiOpenCol;
        }
    }

    pce = bR;
    for (int i = 0; i < pos->pieceNum[pce]; i++) {
        sq = pos->pList[pce][i];
        ASSERT(!g.isOffBoard(sq));
        score -= RookTable[g.MIRROR(g.SQ64(sq))];

        if (!(pos->pawns[BOTH] & g.colBBMask[g.ColumnBoard[sq]])) {
            score -= rookOpenCol;
        } else if (!(pos->pawns[BLACK] & g.colBBMask[g.ColumnBoard[sq]])) {
            score -= rookSemiOpenCol;
        }
    }

    pce = wQ;
    for (int i = 0; i < pos->pieceNum[pce]; i++) {
        sq = pos->pList[pce][i];
        ASSERT(!g.isOffBoard(sq));

        if (!(pos->pawns[BOTH] & g.colBBMask[g.ColumnBoard[sq]])) {
            score += queenOpenCol;
        } else if (!(pos->pawns[WHITE] & g.colBBMask[g.ColumnBoard[sq]])) {
            score += queenSemiOpenCol;
        }
    }

    pce = bQ;
    for (int i = 0; i < pos->pieceNum[pce]; i++) {
        sq = pos->pList[pce][i];
        ASSERT(!g.isOffBoard(sq));

        if (!(pos->pawns[BOTH] & g.colBBMask[g.ColumnBoard[sq]])) {
            score -= queenOpenCol;
        } else if (!(pos->pawns[BLACK] & g.colBBMask[g.ColumnBoard[sq]])) {
            score -= queenSemiOpenCol;
        }
    }

    /*
    pce = wK;
    sq = pos->pList[pce][WHITE];
    if (pos->material[BLACK] <= endgameMaterialMax) {
        score += KingE[g.SQ64(sq)];
    } else {
        score += KingO[g.SQ64(sq)];
    }


    pce = bK;
    sq = pos->pList[pce][0];
    if (pos->material[WHITE] <= endgameMaterialMax) {
        score -= KingE[g.MIRROR(g.SQ64(sq))];
    } else {
        score -= KingO[g.MIRROR(g.SQ64(sq))];
    }
     */

    if (pos->pieceNum[wB] >= 2) score += bishopPair;
    if (pos->pieceNum[bB] >= 2) score -= bishopPair;

    // Note that in calculation, white has a positive score, black, has negative score
    if (pos->sideToMove == WHITE) {
        return score;
    } else {
        return -score;
    }
}