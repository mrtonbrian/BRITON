#include "Globals.h"
#include "defs.h"
#include <string>

#ifndef VALIDATE
#define VALIDATE
int SideValid(const int side);

int FileRankValid(const int fr);

int PieceValidEmpty(const int pce);

int PieceValid(const int pce);

void MirrorTest(std::string filename, BOARD *pos, Globals& g);
#endif