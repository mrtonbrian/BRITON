#include "defs.h"
#include "Globals.h"
#include "perft.h"
#include "movegen.h"
#include "makemove.h"
#include "board.h"
#include "io.h"
#include "misc.h"
#include <chrono>

long leafNodes;

void Perft(int depth, BOARD *pos, Globals g)
{
    if (depth == 0)
    {
        leafNodes++;
        return;
    }

    MOVES_LIST list;
    generateAllMoves(pos, list, g);

    int MoveNum = 0;
    for (MoveNum = 0; MoveNum < list.count; ++MoveNum)
    {

        if (!makeMove(pos, list.moves[MoveNum].move, g))
        {
            continue;
        }
        Perft(depth - 1, pos, g);
        TakeMove(pos, g);
    }

    return;
}

void PerftTest(int depth, BOARD *pos, Globals g)
{
    printBoard(pos);
    printf("\nStarting Test To Depth:%d\n", depth);
    leafNodes = 0;
    double start = GetTimeMs();

    MOVES_LIST list;
    generateAllMoves(pos, list, g);

    int move;
    int MoveNum = 0;
    for (MoveNum = 0; MoveNum < list.count; ++MoveNum)
    {
        move = list.moves[MoveNum].move;
        if (!makeMove(pos, move, g))
        {
            continue;
        }
        long cumnodes = leafNodes;
        Perft(depth - 1, pos, g);
        TakeMove(pos, g);
        long oldnodes = leafNodes - cumnodes;
        printf("move %d : %s : %ld\n", MoveNum + 1, printMove(move, g), oldnodes);
    }

    double end = GetTimeMs();
    printf("TEST COMPLETE: %ld nodes visited in %f ms\n", leafNodes, end - start);
    return;
}