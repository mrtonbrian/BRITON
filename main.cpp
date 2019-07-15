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

int main() {
    uciLoop();
    return 0;
}
