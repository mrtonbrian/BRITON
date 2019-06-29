#ifdef WIN32
#include "windows.h"
#else
#include "sys/time.h"
#endif

#include "defs.h"

#ifndef MISC_H
#define MISC_H
int GetTimeMs();
void readInput(SEARCHINFO *info);
int InputWaiting();
#endif
