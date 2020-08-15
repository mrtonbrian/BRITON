#ifndef CHESS_ENGINE_CPP_PERFT_H
#define CHESS_ENGINE_CPP_PERFT_H
#include "Position.h"

void perftTest(Position& position, int depth);

void perftTestFile(Position& position, std::string filename="perftsuite.epd", int verbosity=0);
#endif