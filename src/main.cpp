#include "Types.h"
#include "search.h"
#include "Position.h"
// #include "eval.h"
#include "init.h"
#include "perft.h"
SearchInfo SEARCH_SETTINGS;

int main() {
    initAll();
    Position p;
    p.init();

    p.setFromFEN("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10 ");

    perftTest(p, 5);
//    perftTestFile(p, "perftsuite.epd", 1, 6);
}
