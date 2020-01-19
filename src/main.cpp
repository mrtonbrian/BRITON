//
// Created by brianton on 10/23/19.
//
#include "Types.h"
#include "search.h"
#include "Position.h"
#include "init.h"

SearchInfo SEARCH_SETTINGS;

int main() {
    initAll();
    Position p;
    p.init();
    p.setFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    p.printBoard();
    SEARCH_SETTINGS.starttime = getTimeMs();
    SEARCH_SETTINGS.stoptime = SEARCH_SETTINGS.starttime + 1000;
    SEARCH_SETTINGS.stopped = false;
    SEARCH_SETTINGS.depth = 64;
    SEARCH_SETTINGS.timeSet = true;
    searchPosition(p);
}
