//
// Created by brianton on 10/23/19.
//
#include "Types.h"
#include "misc.h"
#include "Position.h"

using namespace std;

int main() {
    Position p;
    p.init();
    p.setFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    p.printBoard();
}
