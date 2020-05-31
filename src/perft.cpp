#include "perft.h"
#include <iostream>
#include <string>
#include "misc.h"
#include <fstream>
#include <sstream>
#include <assert.h>
#include <cassert>

long leafNodes;

static void perft(Position &position, int depth) {
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

void perftTest(Position &position, int depth) {
    position.printBoard();
    std::cout << "Starting Test To Depth" << " " << depth << std::endl;
    leafNodes = 0;

    int startTime = getTimeMs();

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

    int endTime = getTimeMs();
    printf("TEST COMPLETE: %ld nodes visited in %d ms\n", leafNodes, endTime - startTime);
    printf("That Is %.1f NPS\n", leafNodes / ((endTime - startTime) / 1000.));
}

void perftTestFile(Position &position, std::string filename="perftsuite.epd") {
    std::string line;
    std::ifstream inp(filename);

    // Make Sure We Can Read File
    assert(inp);

    // Read File Line By Line
    while (std::getline(inp, line)) {
        std::cout << std::endl << "Reading In Line: " << line << std::endl;
        // Split Line Up Into Segments (Based On ';' Character)
        std::vector<std::string> segments;
        std::stringstream inpstream(line);
        std::string token;
        while (std::getline(inpstream, token, ';')) {
            segments.push_back(token);
        }

        std::cout << "FEN: " << segments[0] << std::endl;
        // First Token is always FEN
        position.setFromFEN(segments[0]);
        position.printBoard();
        uint64_t initPosKey = position.generatePositionKey();
        std::vector<Move> moveList = position.generateAllMoves();
        for (int depth = 1; depth != segments.size(); depth++) {
            // Get Number (Second Value In Each Segment)
            std::string _;
            long expectedNodes;
            std::stringstream(segments[depth]) >> _ >> expectedNodes;
            std::cout << "Expected Nodes At Depth " << depth << ": " << expectedNodes << std::endl;

            leafNodes = 0;

            for (Move move : moveList) {
                int moveI = move.move;
                if (!position.makeMove(moveI)) {
                    continue;
                }

                perft(position, depth - 1);
                position.unmakeMove();
            }

            std::cout << "Actual: " << leafNodes << std::endl;

            assert(expectedNodes == leafNodes);
            // Just Wanna Make Sure That:
            // A: Position Key Is Correctly Updated Over Time
            // B: Position is Correctly Reset
            assert(position.getZobristHash() == position.generatePositionKey());
            assert(initPosKey == position.generatePositionKey());
        }
    }
    inp.close();
}
