//
// Created by brianton on 12/25/19.
//

#include "Bitboard.h"
#include "Types.h"
#include "TranspositionTable.h"

SMasks masks[SQUARE_NUM][4];

Bitboard KNIGHT_ATTACKS[SQUARE_NUM];

Bitboard KING_ATTACKS[SQUARE_NUM];

Bitboard PAWN_SINGLE_MOVES[COLOR_NB][SQUARE_NUM];
Bitboard PAWN_DOUBLE_MOVES[COLOR_NB][SQUARE_NUM];
Bitboard PAWN_ATTACKS[COLOR_NB][SQUARE_NUM];

Bitboard OO_MASK[COLOR_NB];
Bitboard OOO_MASK[COLOR_NB];

Bitboard OO_ATTACK_MASK[COLOR_NB];
Bitboard OOO_ATTACK_MASK[COLOR_NB];

int MaterialValues[NUM_GAME_STATES][PIECE_TYPE_NB];

using namespace std;

static void initODMasks() {
    // Loop over all squares
    for (int sq = SQ_A1; sq <= SQ_H8; sq++) {
        int testSq;
        // Create FileMask
        Bitboard fileUpperMask = 0ULL;
        for (testSq = sq; testSq <= SQ_H8; testSq += 8) {
            setBit(fileUpperMask, testSq);
        }
        clearBit(fileUpperMask, sq);

        Bitboard fileLowerMask = 0ULL;
        for (testSq = sq; testSq >= SQ_A1; testSq -= 8) {
            setBit(fileLowerMask, testSq);
        }
        clearBit(fileLowerMask, sq);

        SMasks fileMask;
        fileMask.lower = fileLowerMask;
        fileMask.upper = fileUpperMask;
        fileMask.line = fileLowerMask | fileUpperMask;
        masks[sq][0] = fileMask;

        // Create RankMask
        testSq = sq;
        Bitboard rankLowerMask = 0ULL;
        while (testSq % 8 != 0) {
            testSq--;
            setBit(rankLowerMask, testSq);
        }
        clearBit(rankLowerMask, sq);
        Bitboard rankUpperMask = 0ULL;
        testSq = sq;
        while (testSq % 8 != 7) {
            testSq++;
            setBit(rankUpperMask, testSq);
        }
        SMasks rankMask;
        rankMask.lower = rankLowerMask;
        rankMask.upper = rankUpperMask;
        rankMask.line = rankLowerMask | rankUpperMask;
        masks[sq][1] = rankMask;

        // BottomLeft -> TopRight Mask
        Bitboard rightDiagonalMaskLower = 0ULL;
        testSq = sq;
        while (getFile(Square(testSq)) > FILE_A && getRank(Square(testSq)) > RANK_1) {
            testSq -= 9;
            setBit(rightDiagonalMaskLower, testSq);
        }

        Bitboard rightDiagonalMaskUpper = 0ULL;
        testSq = sq;
        while (getFile(Square(testSq)) >= getFile(Square(sq)) && getFile(Square(testSq)) < FILE_H &&
               getRank(Square(testSq)) < RANK_8) {
            testSq += 9;
            setBit(rightDiagonalMaskUpper, testSq);
        }
        SMasks rightDiagonalMask;
        rightDiagonalMask.lower = rightDiagonalMaskLower;
        rightDiagonalMask.upper = rightDiagonalMaskUpper;
        rightDiagonalMask.line = rightDiagonalMaskLower | rightDiagonalMaskUpper;
        masks[sq][2] = rightDiagonalMask;

        // TopLeft -> BottomRight Mask
        Bitboard leftDiagonalMaskLower = 0ULL;
        testSq = sq;
        while (getFile(Square(testSq)) < FILE_H && getRank(Square(testSq)) > RANK_1) {
            testSq -= 7;
            setBit(leftDiagonalMaskLower, testSq);
        }

        Bitboard leftDiagonalMaskUpper = 0ULL;
        testSq = sq;
        while (getFile(Square(testSq)) <= getFile(Square(sq)) && getFile(Square(testSq)) > FILE_A &&
               getRank(Square(testSq)) < RANK_8) {
            testSq += 7;
            setBit(leftDiagonalMaskUpper, testSq);
        }
        SMasks leftDiagonalMask;
        leftDiagonalMask.lower = leftDiagonalMaskLower;
        leftDiagonalMask.upper = leftDiagonalMaskUpper;
        leftDiagonalMask.line = leftDiagonalMaskLower | leftDiagonalMaskUpper;
        masks[sq][3] = leftDiagonalMask;
    }
}

static void initNonSlidingMasks() {
    //Knight attacks
    for (int sq = SQ_A1; sq <= SQ_H8; sq++) {
        File file = getFile(static_cast<Square>(sq));
        Rank rank = getRank(static_cast<Square>(sq));

        int testFile = file + 2;
        int testRank = rank + 1;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            KNIGHT_ATTACKS[sq] |= (1ULL << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        testFile = file + 2;
        testRank = rank - 1;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            KNIGHT_ATTACKS[sq] |= (1ULL << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        testFile = file - 2;
        testRank = rank + 1;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            KNIGHT_ATTACKS[sq] |= (1ULL << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        testFile = file - 2;
        testRank = rank - 1;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            KNIGHT_ATTACKS[sq] |= (1ULL << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        testFile = file + 1;
        testRank = rank + 2;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            KNIGHT_ATTACKS[sq] |= (1ULL << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        testFile = file + 1;
        testRank = rank - 2;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            KNIGHT_ATTACKS[sq] |= (1ULL << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        testFile = file - 1;
        testRank = rank + 2;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            KNIGHT_ATTACKS[sq] |= (1ULL << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        testFile = file - 1;
        testRank = rank - 2;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            KNIGHT_ATTACKS[sq] |= (1ULL << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }
    }

    //King attacks
    for (int sq = SQ_A1; sq <= SQ_H8; sq++) {
        File file = getFile(static_cast<Square>(sq));
        Rank rank = getRank(static_cast<Square>(sq));

        int testFile = file;
        int testRank = rank + 1;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            KING_ATTACKS[sq] |= (1ULL << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        testFile = file;
        testRank = rank - 1;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            KING_ATTACKS[sq] |= (1ULL << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        testFile = file + 1;
        testRank = rank;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            KING_ATTACKS[sq] |= (1ULL << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        testFile = file - 1;
        testRank = rank;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            KING_ATTACKS[sq] |= (1ULL << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        testFile = file + 1;
        testRank = rank + 1;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            KING_ATTACKS[sq] |= (1ULL << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        testFile = file + 1;
        testRank = rank - 1;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            KING_ATTACKS[sq] |= (1ULL << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        testFile = file - 1;
        testRank = rank + 1;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            KING_ATTACKS[sq] |= (1ULL << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        testFile = file - 1;
        testRank = rank - 1;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            KING_ATTACKS[sq] |= (1ULL << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }
    }
}

static void initPawnMoveMasks() {
    //COLOR_WHITE pawn moves
    for (int sq = SQ_A1; sq <= SQ_H8; sq++) {
        int file = getFile(static_cast<Square>(sq));
        int rank = getRank(static_cast<Square>(sq));

        int testFile = file;
        int testRank = rank + 1;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            PAWN_SINGLE_MOVES[COLOR_WHITE][sq] |= (1ULL
                    << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        if (rank == RANK_2) {
            testFile = file;
            testRank = rank + 2;
            if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
                PAWN_DOUBLE_MOVES[COLOR_WHITE][sq] |= (1ULL
                        << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
            }
        }

        testFile = file - 1;
        testRank = rank + 1;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            PAWN_ATTACKS[COLOR_WHITE][sq] |= (1ULL
                    << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        testFile = file + 1;
        testRank = rank + 1;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            PAWN_ATTACKS[COLOR_WHITE][sq] |= (1ULL
                    << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        testFile = file;
        testRank = rank - 1;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            PAWN_SINGLE_MOVES[COLOR_BLACK][sq] |= (1ULL
                    << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        if (rank == RANK_7) {
            testFile = file;
            testRank = rank - 2;
            if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
                PAWN_DOUBLE_MOVES[COLOR_BLACK][sq] |= (1ULL
                        << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
            }
        }

        testFile = file - 1;
        testRank = rank - 1;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            PAWN_ATTACKS[COLOR_BLACK][sq] |= (1ULL
                    << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }

        testFile = file + 1;
        testRank = rank - 1;
        if (fileRankOk(static_cast<File>(testFile), static_cast<Rank>(testRank))) {
            PAWN_ATTACKS[COLOR_BLACK][sq] |= (1ULL
                    << makeSquare(static_cast<Rank>(testRank), static_cast<File>(testFile)));
        }
    }
}

static void initCastleMasks() {
    OO_MASK[COLOR_WHITE] = (1LL << SQ_F1) | (1LL << SQ_G1);
    OO_MASK[COLOR_BLACK] = (1LL << SQ_F8) | (1LL << SQ_G8);
    OOO_MASK[COLOR_WHITE] = (1LL << SQ_B1) | (1LL << SQ_C1) | (1LL << SQ_D1);
    OOO_MASK[COLOR_BLACK] = (1LL << SQ_B8) | (1LL << SQ_C8) | (1LL << SQ_D8);

    OO_ATTACK_MASK[COLOR_WHITE] = (1LL << SQ_E1) | (1LL << SQ_F1);
    OO_ATTACK_MASK[COLOR_BLACK] = (1LL << SQ_E8) | (1LL << SQ_F8);
    OOO_ATTACK_MASK[COLOR_WHITE] = (1LL << SQ_E1) | (1LL << SQ_D1);
    OOO_ATTACK_MASK[COLOR_BLACK] = (1LL << SQ_E8) | (1LL << SQ_D8);
}

/*
 *  Could be made shorter by initializing at declaring
 *  But I don't really care :|
 *  Values From: https://github.com/official-stockfish/Stockfish/blob/master/src/types.h
*/
static void initEvalValues() {
    MaterialValues[MIDGAME][PAWN] = 128;
    MaterialValues[ENDGAME][PAWN] = 213;
    MaterialValues[MIDGAME][KNIGHT] = 782;
    MaterialValues[ENDGAME][KNIGHT] = 865;
    MaterialValues[MIDGAME][BISHOP] = 830;
    MaterialValues[ENDGAME][BISHOP] = 918;
    MaterialValues[MIDGAME][ROOK] = 1289;
    MaterialValues[ENDGAME][ROOK] = 1378;
    MaterialValues[MIDGAME][QUEEN] = 2529;
    MaterialValues[ENDGAME][QUEEN] = 2687;
}

void initAll() {
    initODMasks();
    initNonSlidingMasks();
    initPawnMoveMasks();
    initCastleMasks();
    initEvalValues();
    initTable(5);
}
