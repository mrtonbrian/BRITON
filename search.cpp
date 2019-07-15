#include "defs.h"
#include "Globals.h"
#include "search.h"
#include "misc.h"
#include "evaluate.h"
#include "io.h"
#include "move.h"
#include "board.h"
#include "pvtable.h"
#include "attack.h"
#include "movegen.h"
#include "makemove.h"
#include "limits.h"
#include <cstdio>
#include <iostream>

const int MATE = 29000;

static void checkUp(SEARCHINFO *info) {
    if (info->timeset && GetTimeMs() >= info->stoptime) {
        info->stopped = true;
    }

    readInput(info);
}

static void PickNextMove(int moveNum, MOVES_LIST &list) {
    MOVE temp;
    int bestScore = 0;
    int bestNum = moveNum;

    for (int index = moveNum; index < list.count; ++index) {
        if (list.moves[index].score > bestScore) {
            bestScore = list.moves[index].score;
            bestNum = index;
        }
    }
    temp = list.moves[moveNum];
    list.moves[moveNum] = list.moves[bestNum];
    list.moves[bestNum] = temp;
}

// Checks if Position Hash is Same As Previous Hash
static int isRepetition(BOARD *pos) {
    // int count = 0;
    for (int index = pos->hisPly - pos->fiftyMove; index < pos->hisPly - 1; index++) {
        if (pos->position == pos->history[index].posKey) {
            return true;
        }
    }
    return false;
}

static void clearForSearch(BOARD *pos, SEARCHINFO *info) {
    for (int index = 0; index < 13; ++index) {
        for (int index2 = 0; index2 < 120; ++index2) {
            pos->searchHistory[index][index2] = 0;
        }
    }

    for (int index = 0; index < 2; ++index) {
        for (int index2 = 0; index2 < 64; ++index2) {
            pos->searchKillers[index][index2] = 0;
        }
    }

    clearPvTable(pos->pvTable);
    pos->ply = 0;

    //info->starttime = GetTimeMs();
    info->stopped = 0;
    info->nodes = 0;
    info->failHigh = 0;
    info->failHighFirst = 0;
}

// https://www.chessprogramming.org/Quiescence_Search
static int quiescence(int alpha, int beta, BOARD *pos, SEARCHINFO *info, Globals &g) {
    ASSERT(checkBoard(pos, g));

    // 2048 Nodes
    if (info->nodes % 2047 == 0) {
        checkUp(info);
    }
    info->nodes++;

    if ((isRepetition(pos) || pos->fiftyMove >= 100) && pos->ply) {
        return 0;
    }
    if (pos->ply > MAXDEPTH - 1) {
        return evalPosition(pos, g);
    }

    int score = evalPosition(pos, g);

    if (score >= beta) {
        return beta;
    }

    if (score > alpha) {
        alpha = score;
    }
    MOVES_LIST list;
    generateAllCaps(pos, list, g);
    int legalMoves = 0;
    int oldAlpha = alpha;
    int bestMove = 0;
    score = INT_MIN;
    int pvMove = probeTable(pos);

    if (pvMove != 0) {
        for (int moveNum = 0; moveNum < list.count; ++moveNum) {
            if (list.moves[moveNum].move == pvMove) {
                list.moves[moveNum].score = 2000000;
                break;
            }
        }
    }

    for (int moveNum = 0; moveNum < list.count; moveNum++) {

        // Optimization
        PickNextMove(moveNum, list);

        // Illegal Move (puts king in check)
        if (!makeMove(pos, list.moves[moveNum].move, g)) {
            continue;
        }

        legalMoves++;
        // Negamax
        score = -quiescence(-beta, -alpha, pos, info, g);
        // Undo
        TakeMove(pos, g);

        if (info->stopped) {
            return -INT_MAX;
        }

        if (score > alpha) {
            if (score >= beta) {
                if (legalMoves == 1) {
                    info->failHighFirst++;
                }
                info->failHigh++;
                return beta;
            }
            alpha = score;
            bestMove = list.moves[moveNum].move;
        }
    }
    if (alpha != oldAlpha) {
        StorePvMove(pos, bestMove);
    }
    return alpha;
}

static int alphaBeta(int alpha, int beta, int depth, BOARD *pos, SEARCHINFO *info, int doNull, Globals &g) {
    ASSERT(checkBoard(pos, g));
    if (depth == 0) {
        info->nodes++;
        return quiescence(alpha, beta, pos, info, g);
    }

    if (info->nodes % 2047 == 0) {
        checkUp(info);
    }

    info->nodes++;
    // Note that 50 move is in Full moves (50 moves each side) and fiftyMove variable is in half-moves
    if ((isRepetition(pos) || pos->fiftyMove >= 100) && pos->ply) {
        return 0;
    }

    // Going Too Deep
    if (pos->ply > MAXDEPTH - 1) {
        return evalPosition(pos, g);
    }

    // In-Check Extension
    bool inCheck = squareAttacked(pos->king[pos->sideToMove], pos->sideToMove ^ 1, g, pos);
    if (inCheck) {
        depth++;
    }

    MOVES_LIST list;
    generateAllMoves(pos, list, g);

    int legalMoves = 0;
    int oldAlpha = alpha;
    int bestMove = 0;
    int score = INT_MIN;
    int pvMove = probeTable(pos);

    if (pvMove != 0) {
        for (int m = 0; m < list.count; m++) {
            if (list.moves[m].move == pvMove) {
                list.moves[m].score = 2000000;
                break;
            }
        }
    }

    for (int moveNum = 0; moveNum < list.count; moveNum++) {
        // Optimization
        PickNextMove(moveNum, list);

        // Illegal Move (puts king in check)
        if (!makeMove(pos, list.moves[moveNum].move, g)) {
            continue;
        }

        legalMoves++;
        // Negamax
        score = -alphaBeta(-beta, -alpha, depth - 1, pos, info, true, g);
        // Undo
        TakeMove(pos, g);
        if (info->stopped) {
            return -INT_MAX;
        }

        if (score > alpha) {
            if (score >= beta) {
                if (legalMoves == 1) {
                    info->failHighFirst++;
                }
                info->failHigh++;
                if (!(isCapture(list.moves[moveNum].move))) {
                    // Shuffle
                    pos->searchKillers[1][pos->ply] = pos->searchKillers[0][pos->ply];
                    pos->searchKillers[0][pos->ply] = list.moves[moveNum].move;
                }
                return beta;
            }
            alpha = score;
            bestMove = list.moves[moveNum].move;
            if (!isCapture(list.moves[moveNum].move)) {
                pos->searchHistory[pos->pieces[fromSq(bestMove)]][toSq(bestMove)] += depth;
            }
        }
    }
    if (!legalMoves) {
        // Inverts Side
        if (inCheck) {
            return -MATE + pos->ply;
        } else {
            return 0;
        }
    }

    // If New Best Score
    if (alpha != oldAlpha) {
        StorePvMove(pos, bestMove);
    }
    return alpha;
}

void searchPosition(BOARD *pos, SEARCHINFO *info, Globals &g) {
    int bestMove = 0;
    int bestScore;

    int currentDepth = 0;
    int pvMoves = 0;

    clearForSearch(pos, info);
    for (currentDepth = 1; currentDepth <= info->depth; currentDepth++) {
        bestScore = alphaBeta(-INT_MAX, INT_MAX, currentDepth, pos, info, true, g);
        if (info->stopped) {
            break;
        }

        /*
        Case White Winning, Engine White: +
        Case White Losing, Engine White: -
        Case Black Winning, Engine Black: +
        Case Black Losing, Engine Black: -
        */

        //pvMoves = GetPvLine(currentDepth, pos, g);
        bestMove = pos->PvArray[0];
        printf("info score cp %d depth %d nodes %ld time %d ", bestScore, currentDepth, info->nodes,
               GetTimeMs() - info->starttime);

        printf("pv");
        std::cout.flush();
        pvMoves = GetPvLine(currentDepth, pos, g);
        for (int i = 0; i < pvMoves; i++) {
            printf(" %s", printMove(pos->PvArray[i], g));
        }
        printf("\n");
    }
    std::cout << "bestmove " << printMove(bestMove, g) << std::endl;
}
