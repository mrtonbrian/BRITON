#include "defs.h"

#ifndef MOVE_H
#define MOVE_H
int fromSq(int m);
int toSq(int m);
int capturePiece(int m);
int promotionPiece(int m);

bool isEnPass(int m);
bool isPawnStart(int m);
bool isCastle(int m);
bool isCapture(int m);
bool isPromotion(int m);
#endif