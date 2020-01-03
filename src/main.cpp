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

int main() {
    initAll();
    Position p;
    p.init();
    p.setFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    perftTest(p, 2);
}
