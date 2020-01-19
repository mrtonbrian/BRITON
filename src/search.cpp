//
// Created by brianton on 1/13/20.
//

#include "search.h"
#include "eval.h"
#include "TranspositionTable.h"
#include "Types.h"
#include <algorithm>

static void checkUpTime() {
    if (SEARCH_SETTINGS.timeSet && getTimeMs() >= SEARCH_SETTINGS.stoptime) {
        SEARCH_SETTINGS.stopped = true;
    }
}

static bool isRepetition(Position& position) {
    for (int i = position.getHisPly() - 2; i >= position.getHisPly() - position.fiftyMoveCount(); i--) {
        if (position.getPrevBoard(i).positionKey == position.getZobristHash()) {
            return true;
        }
    }

    return false;
}

static int quiescence(int alpha, int beta, Position& position) {
    position.nodesSearched++;
    if ((position.nodesSearched & 4095) == 0) {
        checkUpTime();
    }

    if (position.getSearchPly() && (isRepetition(position) || position.fiftyMoveCount() >= 100)) {
        return 0;
    }

    if (position.getSearchPly() > MAX_DEPTH - 1) {
        return evalPosition(position);
    }

    int score = evalPosition(position);

    if (score >= beta) {
        return beta;
    }

    if (score > alpha) {
        alpha = score;
    }
    std::vector<Move> captures = position.generateAllCaps();
    std::sort(captures.begin(), captures.end(), [](Move a, Move b) {
        return a.score > b.score;
    });
    for (Move capture : captures) {
        if (!position.makeMove(capture.move)) {
            continue;
        }
        score = -quiescence(-beta, -alpha, position);
        position.unmakeMove();
        if (SEARCH_SETTINGS.stopped) {
            return MIN_VAL;
        }

        if (score > alpha) {
            if (score >= beta) {
                return beta;
            }
            alpha = score;
        }
    }

    return alpha;
}

static int alphaBeta(int alpha, int beta, int depth, Position& position) {
    position.nodesSearched++;
    if (depth == 0) {
        return quiescence(alpha, beta, position);
    }

    if ((position.nodesSearched & 4095) == 0) {
        checkUpTime();
    }

    int oldAlpha = alpha;

    if (position.getSearchPly() && (isRepetition(position) || position.fiftyMoveCount() >= 100)) {
        return 0;
    }

    if (position.getSearchPly() >= MAX_DEPTH) {
        return evalPosition(position);
    }

    bool inCheck = position.squareAttacked(position.pieces(position.getTurn(), KING),
                                           static_cast<Color>(position.getTurn() ^ 1));
    if (inCheck) {
        depth++;
    }

    std::vector<Move> moves = position.generateAllMoves();
    std::sort(moves.begin(), moves.end(), [](Move a, Move b) {
        return a.score > b.score;
    });
    int bestScore = MIN_VAL;
    int bestMove = -1;
    bool legalMoves = false;
    for (Move move : moves) {
        if (!position.makeMove(move.move)) {
            continue;
        }
        legalMoves = true;
        int score = -alphaBeta(-beta, -alpha, depth - 1, position);
        position.unmakeMove();
        if (SEARCH_SETTINGS.stopped) {
            return MIN_VAL;
        }

        if (score >= bestScore) {
            bestScore = score;
            bestMove = move.move;

            if (score > alpha) {
                if (score >= beta) {
                    storeMove(position, bestMove, beta, BETA, depth);
                    return beta;
                }
            }
            alpha = score;
        }
    }

    if (!legalMoves) {
        if (inCheck) {
            return -MATE_SCORE + position.getSearchPly();
        } else {
            return 0;
        }
    }

    if (alpha != oldAlpha) {
        storeMove(position, bestMove, bestScore, EXACT, depth);
        position.principalVariation[position.getSearchPly()] = bestMove;
    } else {
        storeMove(position, bestMove, alpha, ALPHA, depth);
    }
    return alpha;
}

void searchPosition(Position& position) {
    position.clearForSearch();

    int bestMove = 0;
    int bestScore;

    for (int currentDepth = 1; currentDepth <= SEARCH_SETTINGS.depth; currentDepth++) {
        bestScore = alphaBeta(MIN_VAL, MAX_VAL, currentDepth, position);

        if (SEARCH_SETTINGS.stopped) {
            break;
        }

        std::vector<int> pvMoves = getPVLine(position, currentDepth);
        bestMove = pvMoves[0];
        printf("info score cp %d depth %d nodes %ld time %ld ", bestScore, currentDepth, position.nodesSearched,
               getTimeMs() - SEARCH_SETTINGS.starttime);
        std::cout << "pv";
        for (int move : pvMoves) {
            std::cout << " " << printMove(move);
        }
        std::cout << std::endl;
    }
    std::cout << "bestmove " << printMove(bestMove) << std::endl;
}