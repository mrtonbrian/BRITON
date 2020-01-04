//
// Created by brianton on 10/23/19.
//
#include "Types.h"
#include "Bitboard.h"
#include "misc.h"
#include "Position.h"
#include "init.h"
#include "perft.h"
#include <cassert>
#include "movegen.h"
#include "bitops.h"
#include <iostream>

using namespace std;
// e2e3 d7e6 e3e4
int main() {
    initAll();
    Position p;
    p.init();
    p.setFromFEN("R6r/8/8/2K5/5k2/8/8/r6R b - - 0 1");

    perftTest(p, 6);
}
