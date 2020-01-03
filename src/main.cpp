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
// a2a3 f7f6 a1a2
int main() {
    initAll();
    Position p;
    p.init();
    p.setFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
//    p.makeMove(gen_move(SQ_A2, SQ_A3, W_PAWN, false, false, false, false));

    perftTest(p, 4);
}
