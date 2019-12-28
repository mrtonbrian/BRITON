//
// Created by brianton on 10/23/19.
//
#include "Types.h"
#include "Bitboard.h"
#include "misc.h"
#include "Position.h"
#include "init.h"
#include "movegen.h"
#include <iostream>

using namespace std;

int main() {
    initAll();
    Position p;
    p.init();
    p.setFromFEN("8/8/8/8/8/1p6/3N4/5P2 w - - 0 1");
    p.printBoard();
    cout << endl;
    printBitboard(knightMoves(p.byColor[COLOR_WHITE], SQ_D2));
    cout << endl;
}
