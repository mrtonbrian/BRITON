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
    p.setFromFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
    perftTest(p, 4);
    /*
    p.printBoard();
    SEARCH_SETTINGS.starttime = getTimeMs();
    SEARCH_SETTINGS.stoptime = SEARCH_SETTINGS.starttime + 5000;
    SEARCH_SETTINGS.stopped = false;
    SEARCH_SETTINGS.depth = 7;
    SEARCH_SETTINGS.timeSet = true;
    // searchPosition(p);
    */
}
