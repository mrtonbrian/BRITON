#ifndef CHESS_ENGINE_CPP_PERFT_H
#define CHESS_ENGINE_CPP_PERFT_H
#include "Position.h"

void perftTest(Position& position, int depth);

void perftTestFile(Position& position, const std::string& filename="perftsuite.epd", unsigned int verbosity=0, unsigned int max_depth=10);
#endif