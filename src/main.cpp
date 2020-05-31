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
    /*
    p.printBoard();
    SEARCH_SETTINGS.starttime = getTimeMs();
    SEARCH_SETTINGS.stoptime = SEARCH_SETTINGS.starttime + 5000;
    SEARCH_SETTINGS.stopped = false;
    SEARCH_SETTINGS.depth = 7;
    SEARCH_SETTINGS.timeSet = true;
    // searchPosition(p);
    */
    perftTestFile(p, "perftsuite.epd");
}
