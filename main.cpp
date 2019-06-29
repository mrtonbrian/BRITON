#include "Globals.h"
#include "defs.h"
#include "init.h"
#include "board.h"
#include "move.h"
#include "io.h"
#include "perft.h"
#include "makemove.h"
#include "pvtable.h"
#include "misc.h"
#include "uci.h"
#include "movegen.h"
#include "search.h"
#include "hashkey.h"
#include "bitboards.h"
#include "attack.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    /*
    BOARD b[1];
    initPvTable(b->pvTable);
    // Note that argv[0] is just filename
    const char * fen = argv[1];
    int msAllowed = atoi(argv[2]);
    parseFEN(fen, b, g);

    SEARCHINFO info[1];
    info->starttime = GetTimeMs();
    info->stoptime  = GetTimeMs() + msAllowed;
    info->depth = 64;
    info->timeset = true;
    searchPosition(b, info, g);
    */

    uciLoop();

    /*
    BOARD b[1];
    Globals g;
    initPvTable(b->pvTable);
    init(g);
    parseFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", b, g);
    PerftTest(6, b, g);
    */

    return 0;
}
