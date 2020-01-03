#include "perft.h"
#include <iostream>
#include "misc.h"

long leafNodes;

static void perft(Position position, int depth) {
    if (depth == 0) {
        leafNodes++;
        return;
    }

    std::vector<Move> moveList = position.generateAllMoves();
    for (Move move : moveList) {
        int moveI = move.move;
        if (!position.makeMove(moveI)) {
            continue;
        }

        perft(position, depth - 1);
        position.unmakeMove();
    }
}

void perftTest(Position position, int depth) {
    position.printBoard();
    std::cout << "Starting Test To Depth" << " " << depth << std::endl;
    leafNodes = 0;

    double startTime = getTimeMs();

    int moveNum = 0;
    std::vector<Move> moveList = position.generateAllMoves();
    for (Move move : moveList) {
        int moveI = move.move;
        if (!position.makeMove(moveI)) {
            continue;
        }

        long cumnodes = leafNodes;
        perft(position, depth - 1);
        position.unmakeMove();
        long changeNodes = leafNodes - cumnodes;
        printf("move %d : %s : %ld\n", ++moveNum, printMove(moveI).c_str(), changeNodes);
    }

    double endTime = getTimeMs();
    printf("TEST COMPLETE: %ld nodes visited in %f ms\n", leafNodes, endTime - startTime);
    printf("That Is %.1f NPS\n", (endTime - startTime) / leafNodes);
}
