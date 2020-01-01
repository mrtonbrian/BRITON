//
// Created by brianton on 10/23/19.
//
#include "Types.h"
#include "Bitboard.h"
#include "misc.h"
#include "Position.h"
#include "init.h"
#include <cassert>
#include "movegen.h"
#include "bitops.h"
#include <iostream>

using namespace std;

int main() {
    initAll();
    Position p;
    p.init();
    p.setFromFEN("8/6p1/1p6/8/3B4/2p1P3/8/8 w - - 0 1");
    p.printBoard();
    cout << endl;
    printBitboard(bishopAttacks(p.byColor[COLOR_WHITE] | p.byColor[COLOR_BLACK], SQ_D4) & ~p.byColor[COLOR_WHITE]);
    cout << endl;
}
