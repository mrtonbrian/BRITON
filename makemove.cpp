#include "makemove.h"
#include "defs.h"
#include "Globals.h"
#include "attack.h"
#include "bitboards.h"
#include "board.h"
#include "move.h"
#include "validate.h"
#include "Globals.h"
#include <iostream>

using namespace std;
const int CastlePerm[120] = {
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 13, 15, 15, 15, 12, 15, 15, 14, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 7, 15, 15, 15, 3, 15, 15, 11, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15};

#define HASH_PCE(pce, sq) (pos->position ^= (g.PieceKeys[(pce)][(sq)]))
#define HASH_CA (pos->position ^= (g.CastleKeys[(pos->castlePerm)]))
#define HASH_SIDE (pos->position ^= (g.SideKey))
#define HASH_EP (pos->position ^= (g.PieceKeys[EMPTY][(pos->enPass)]))

static void ClearPiece(const int sq, BOARD *pos, Globals &g) {

    ASSERT(!g.isOffBoard(sq));

    int pce = pos->pieces[sq];

    ASSERT(PieceValid(pce));

    int col = g.PieceCol[pce];
    int index = 0;
    int t_pieceNum = -1;

    HASH_PCE(pce, sq);

    pos->pieces[sq] = EMPTY;
    pos->material[col] -= g.PieceVal[pce];

    if (g.NonPawn[pce]) {
        pos->nonPawn[col]--;
        if (g.RookQueen[pce]) {
            pos->RQ[col]--;
        } else {
            pos->KB[col]--;
        }
    } else {
        clearBit(pos->pawns[col], g.SQ64(sq), g);
        clearBit(pos->pawns[BOTH], g.SQ64(sq), g);
    }

    for (index = 0; index < pos->pieceNum[pce]; ++index) {
        if (pos->pList[pce][index] == sq) {
            t_pieceNum = index;
            break;
        }
    }

    ASSERT(t_pieceNum != -1);

    pos->pieceNum[pce]--;

    pos->pList[pce][t_pieceNum] = pos->pList[pce][pos->pieceNum[pce]];
}

static void AddPiece(const int sq, BOARD *pos, const int pce, Globals &g) {

    ASSERT(PieceValid(pce));
    ASSERT(!g.isOffBoard(sq));

    int col = g.PieceCol[pce];

    HASH_PCE(pce, sq);

    pos->pieces[sq] = pce;

    if (g.NonPawn[pce]) {
        pos->nonPawn[col]++;
        if (g.RookQueen[pce]) {
            pos->RQ[col]++;
        } else {
            pos->KB[col]++;
        }
    } else {
        setBit(pos->pawns[col], g.SQ64(sq), g);
        setBit(pos->pawns[BOTH], g.SQ64(sq), g);
    }

    pos->material[col] += g.PieceVal[pce];
    pos->pList[pce][pos->pieceNum[pce]++] = sq;
}

static void MovePiece(const int from, const int to, BOARD *pos, Globals &g) {

    ASSERT(!g.isOffBoard(from));
    ASSERT(!g.isOffBoard(to));

    int index = 0;
    int pce = pos->pieces[from];
    int col = g.PieceCol[pce];

    int t_PieceNum = false;

    HASH_PCE(pce, from);
    pos->pieces[from] = EMPTY;

    HASH_PCE(pce, to);
    pos->pieces[to] = pce;

    if (!g.NonPawn[pce]) {
        clearBit(pos->pawns[col], g.SQ64(from), g);
        clearBit(pos->pawns[BOTH], g.SQ64(from), g);
        setBit(pos->pawns[col], g.SQ64(to), g);
        setBit(pos->pawns[BOTH], g.SQ64(to), g);
    }

    for (index = 0; index < pos->pieceNum[pce]; ++index) {
        if (pos->pList[pce][index] == from) {
            pos->pList[pce][index] = to;
            t_PieceNum = true;
            break;
        }
    }
    ASSERT(t_PieceNum);
}

bool makeMove(BOARD *pos, int move, Globals &g) {

    ASSERT(checkBoard(pos, g));

    int from = fromSq(move);
    int to = toSq(move);
    int sideToMove = pos->sideToMove;

    ASSERT(!g.isOffBoard(from));
    ASSERT(!g.isOffBoard(to));
    ASSERT(SideValid(sideToMove));
    ASSERT(PieceValid(pos->pieces[from]));

    pos->history[pos->hisPly].posKey = pos->position;

    if (move & 0x40000) {
        if (sideToMove == WHITE) {
            ClearPiece(to - 10, pos, g);
        } else {
            ClearPiece(to + 10, pos, g);
        }
    } else if (move & 0x1000000) {
        switch (to) {
            case C1:
                MovePiece(A1, D1, pos, g);
                break;
            case C8:
                MovePiece(A8, D8, pos, g);
                break;
            case G1:
                MovePiece(H1, F1, pos, g);
                break;
            case G8:
                MovePiece(H8, F8, pos, g);
                break;
            default:
                ASSERT(false);
                break;
        }
    }

    if (pos->enPass != NO_SQ)
        HASH_EP;
    HASH_CA;

    pos->history[pos->hisPly].move = move;
    pos->history[pos->hisPly].fiftyMove = pos->fiftyMove;
    pos->history[pos->hisPly].enPass = pos->enPass;
    pos->history[pos->hisPly].castle = pos->castlePerm;

    pos->castlePerm &= CastlePerm[from];
    pos->castlePerm &= CastlePerm[to];
    pos->enPass = NO_SQ;

    HASH_CA;

    int captured = capturePiece(move);
    pos->fiftyMove++;

    if (captured != EMPTY) {
        ASSERT(PieceValid(captured));
        ClearPiece(to, pos, g);
        pos->fiftyMove = 0;
    }

    pos->hisPly++;
    pos->ply++;

    if (!g.NonPawn[pos->pieces[from]]) {
        pos->fiftyMove = 0;
        if (move & 0x80000) {
            if (sideToMove == WHITE) {
                pos->enPass = from + 10;
                ASSERT(g.RowBoard[pos->enPass] == ROW_3);
            } else {
                pos->enPass = from - 10;
                ASSERT(g.RowBoard[pos->enPass] == ROW_6);
            }
            HASH_EP;
        }
    }

    MovePiece(from, to, pos, g);

    int prPce = promotionPiece(move);
    if (prPce != EMPTY) {
        ASSERT(PieceValid(prPce) && g.NonPawn[prPce]);
        ClearPiece(to, pos, g);
        AddPiece(to, pos, prPce, g);
    }

    if (g.isKing[pos->pieces[to]]) {
        pos->king[pos->sideToMove] = to;
    }

    pos->sideToMove ^= 1;
    HASH_SIDE;

    ASSERT(checkBoard(pos, g));

    if (squareAttacked(pos->king[sideToMove], pos->sideToMove, g, pos)) {
        TakeMove(pos, g);
        return false;
    }

    return true;
}

void TakeMove(BOARD *pos, Globals &g) {

    ASSERT(checkBoard(pos, g));

    pos->hisPly--;
    pos->ply--;

    int move = pos->history[pos->hisPly].move;
    int from = fromSq(move);
    int to = toSq(move);

    ASSERT(!g.isOffBoard(from));
    ASSERT(!g.isOffBoard(to));

    if (pos->enPass != NO_SQ)
        HASH_EP;
    HASH_CA;

    pos->castlePerm = pos->history[pos->hisPly].castle;
    pos->fiftyMove = pos->history[pos->hisPly].fiftyMove;
    pos->enPass = pos->history[pos->hisPly].enPass;

    if (pos->enPass != NO_SQ)
        HASH_EP;
    HASH_CA;

    pos->sideToMove ^= 1;
    HASH_SIDE;

    if (0x40000 & move) {
        if (pos->sideToMove == WHITE) {
            AddPiece(to - 10, pos, bP, g);
        } else {
            AddPiece(to + 10, pos, wP, g);
        }
    } else if (0x1000000 & move) {
        switch (to) {
            case C1:
                MovePiece(D1, A1, pos, g);
                break;
            case C8:
                MovePiece(D8, A8, pos, g);
                break;
            case G1:
                MovePiece(F1, H1, pos, g);
                break;
            case G8:
                MovePiece(F8, H8, pos, g);
                break;
            default:
                ASSERT(false);
                break;
        }
    }

    MovePiece(to, from, pos, g);

    if (g.isKing[pos->pieces[from]]) {
        pos->king[pos->sideToMove] = from;
    }

    int captured = capturePiece(move);
    if (captured != EMPTY) {
        ASSERT(PieceValid(captured));
        AddPiece(to, pos, captured, g);
    }

    if (promotionPiece(move) != EMPTY) {
        ASSERT(PieceValid(promotionPiece(move)) && g.NonPawn[promotionPiece(move)]);
        ClearPiece(from, pos, g);
        AddPiece(from, pos, (g.PieceCol[promotionPiece(move)] == WHITE ? wP : bP), g);
    }

    ASSERT(checkBoard(pos, g));
}

void makeNullMove(BOARD *pos, Globals &g) {
    ASSERT(checkBoard(pos, g));

    pos->ply++;
    pos->history[pos->hisPly].posKey = pos->position;

    if (pos->enPass != NO_SQ) {
        HASH_EP;
    }

    pos->history[pos->hisPly].move = 0;
    pos->history[pos->hisPly].fiftyMove = pos->fiftyMove;
    pos->history[pos->hisPly].enPass = pos->enPass;
    pos->history[pos->hisPly].castle = pos->castlePerm;
    pos->enPass = NO_SQ;

    pos->sideToMove ^= 1;
    pos->hisPly++;
    HASH_SIDE;

    ASSERT(checkBoard(pos, g));
}

void takeNullMove(BOARD *pos, Globals &g) {
    ASSERT(checkBoard(pos, g));

    pos->hisPly--;
    pos->ply--;

    if (pos->enPass != NO_SQ) {
        HASH_EP;
    }

    pos->castlePerm = pos->history[pos->hisPly].castle;
    pos->fiftyMove = pos->history[pos->hisPly].fiftyMove;
    pos->enPass = pos->history[pos->hisPly].enPass;
    if (pos->enPass != NO_SQ) {
        HASH_EP;
    }

    pos->sideToMove ^= 1;
    HASH_SIDE;

    ASSERT(checkBoard(pos, g));
}