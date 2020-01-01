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
    p.setFromFEN("4r3/8/8/8/8/6B1/8/4k3 w - - 0 1");
    p.printBoard();
}
