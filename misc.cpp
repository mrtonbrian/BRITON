#include "misc.h"
#include "defs.h"
#include <cstdio>
#include <iostream>
#include <string>

int GetTimeMs() {
    #ifdef WIN32
        return GetTickCount();
    #else
        struct timeval t;
        gettimeofday(&t, 0);
        return t.tv_sec*1000 + t.tv_usec/1000;
    #endif
}
int InputWaiting() {
#ifndef WIN32
  fd_set readfds;
  struct timeval tv;
  FD_ZERO (&readfds);
  FD_SET (fileno(stdin), &readfds);
  tv.tv_sec=0; tv.tv_usec=0;
  select(16, &readfds, 0, 0, &tv);

  return (FD_ISSET(fileno(stdin), &readfds));
#else
   static int init = 0, pipe;
   static HANDLE inh;
   DWORD dw;

   if (!init) {
     init = 1;
     inh = GetStdHandle(STD_INPUT_HANDLE);
     pipe = !GetConsoleMode(inh, &dw);
     if (!pipe) {
        SetConsoleMode(inh, dw & ~(ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT));
        FlushConsoleInputBuffer(inh);
      }
    }
    if (pipe) {
      if (!PeekNamedPipe(inh, NULL, 0, NULL, &dw, NULL)) return 1;
      return dw;
    } else {
      GetNumberOfConsoleInputEvents(inh, &dw);
      return dw <= 1 ? 0 : dw;
	}
#endif
}

void readInput(SEARCHINFO * info) {
    int bytes;
    std::string s;

    if (InputWaiting()) {    
		std::getline(std::cin, s);
        if (s == "quit") {
            info->quit = true;
        }
    }
}