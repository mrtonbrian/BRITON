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

int main (int argc, char *argv[]) {
	Globals g;
	init(g);

	BOARD b[1];
	initPvTable(b->pvTable);
	// Note that argv[0] is just filename
	const char * fen = argv[1];
	int msAllowed = atoi(argv[2]);
	//const char * fen = "2B1K3/2p5/4Np2/1Q3P2/2p2r2/1p1bkP2/1p1n4/n7 w - - 0 1";
	parseFEN(fen, b, g);

	SEARCHINFO info[1];
	info->starttime = GetTimeMs();
	info->stoptime  = GetTimeMs() + msAllowed;
	info->depth = 64;
	info->timeset = true;
	searchPosition(b, info, g);
	return 0;
}
