//
// Created by brianton on 1/5/20.
//

#include "eval.h"
#include <algorithm>

static int evalPositionMaterialPhase(Position &position, GameStates gs) {
    int total = 0;
    // Note: We Want Branchless Computation, So We Write Code Twice To Avoid
    // Side Checking Conditional
    for (PieceType p : {PAWN, KNIGHT, BISHOP, ROOK, QUEEN}) {
        total += popcnt(position.pieces(COLOR_WHITE, p)) * MaterialValues[gs][p];
    }
    std::cout << total << std::endl;
    for (PieceType p : {PAWN, KNIGHT, BISHOP, ROOK, QUEEN}) {
        total -= popcnt(position.pieces(COLOR_BLACK, p)) * MaterialValues[gs][p];
    }

    return total;
}

static int nonPawnMaterial(Position &position, Color color) {
    int total = 0;
    for (PieceType p : {KNIGHT, BISHOP, ROOK, QUEEN}) {
        total += popcnt(position.pieces(color, p)) * MaterialValues[MIDGAME][p];
    }
    return total;
}

static int nonPawnMaterial(Position &position) {
    return nonPawnMaterial(position, COLOR_WHITE) - nonPawnMaterial(position, COLOR_BLACK);
}

static int phase(Position &position) {
    int npm = nonPawnMaterial(position);
    npm = std::max(ENDGAME_LIMIT, std::min(npm, MIDGAME_LIMIT));
    return (((npm - ENDGAME_LIMIT) * 128) / (MIDGAME_LIMIT - ENDGAME_LIMIT)) << 0;
}

int scaleFactor(Position &position, int egValue) {
    Color strongSide = egValue > 0 ? COLOR_WHITE : COLOR_BLACK;
    Color weakSide = Color(strongSide ^ 1);
    int sf = 64;
    int pawnCountStrong = popcnt(position.pieces(strongSide, PAWN));
    int npmStrong = nonPawnMaterial(position, strongSide);
    int npmWeak = nonPawnMaterial(position, weakSide);

    if (pawnCountStrong == 0 && npmStrong - npmWeak <= MaterialValues[MIDGAME][BISHOP]) {
        sf = npmStrong < MaterialValues[MIDGAME][ROOK] ? 0 : npmWeak <= MaterialValues[MIDGAME][BISHOP] ? 4 : 14;
    }
    if (sf == 64) {
        bool oppositeBishops = position.oppositeBishops();
        if (oppositeBishops && npmStrong == MaterialValues[MIDGAME][BISHOP] &&
            npmWeak == MaterialValues[MIDGAME][BISHOP]) {
            sf = 22;
        } else {
            sf = std::min(sf, 36 + (oppositeBishops ? 2 : 7) * pawnCountStrong);
        }
        sf = std::max(0, sf - (((position.fiftyMoveCount() - 12) / 4) << 0));
    }
    return sf;
}

int evalPosition(Position &position) {
    // Score Material
    int midGameEvaluation = evalPositionMaterialPhase(position, MIDGAME);
    int endGameEvaluation = evalPositionMaterialPhase(position, ENDGAME);
    endGameEvaluation = endGameEvaluation * scaleFactor(position, endGameEvaluation) / 64;
    int p = phase(position);
    std::cout << "SF: " << scaleFactor(position, endGameEvaluation) << std::endl;
    return (((midGameEvaluation * p + ((endGameEvaluation * (128 - p)) << 0)) / 128) << 0);
}