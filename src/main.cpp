//
// Created by brianton on 10/23/19.
//
#include "Position.h"
#include "init.h"
#include "eval.h"
#include <cassert>
#include <iostream>

int main() {
    initAll();
    Position p;
    p.init();
    p.setFromFEN("rnb1kbnr/pppppppp/8/8/8/8/PPPPPPPP/RNB1KBNR w KQkq - 0 1");
    p.printBoard();
    std::cout << evalPosition(p) << std::endl;
}
