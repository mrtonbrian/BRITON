#include "defs.h"
#include "Globals.h"
#include "io.h"
#include "move.h"
#include "init.h"
#include "stdio.h"
#include "movegen.h"
#include <iostream>

using namespace std;

char *printSquare(int square, Globals g) {
    static char SqString[6];

    int col = g.ColumnBoard[square];
    int row = g.RowBoard[square];

    sprintf(SqString, "%c%c", ('a' + col), ('1' + row));

    return SqString;
}

char * printMove(int move, Globals g) {
    static char MvString[6];
    int _fRow = g.RowBoard[fromSq(move)];
    int _fCol = g.ColumnBoard[fromSq(move)];
    int tRow = g.RowBoard[toSq(move)];
    int tCol = g.ColumnBoard[toSq(move)];

    int promoted = promotionPiece(move);

    if (isPromotion(move)) {
        char piecechar = 'q';
        if (g.IsKnight(promoted)) {
            piecechar = 'n';
        } else if (g.IsRookQueen(promoted) && !g.IsBishopQueen(promoted)) {
            piecechar = 'r';
        } else if (!g.IsRookQueen(promoted) && g.IsBishopQueen(promoted)) {
            piecechar = 'b';
        }
        sprintf(MvString, "%c%c%c%c%c", ('a' + _fCol), ('1'+_fRow), ('a'+tCol), ('1' + tRow), piecechar);
    } else {
        sprintf(MvString, "%c%c%c%c", ('a' + _fCol), ('1'+_fRow), ('a'+tCol), ('1' + tRow));
    }
    return MvString;
}

int parseMove(string inp, BOARD * pos, Globals g) {
    if (inp.at(1) > '8' || inp.at(1) < '1') return 0;
    if (inp.at(3) > '8' || inp.at(3) < '1') return 0;
    if (inp.at(0) > 'h' || inp.at(0) < 'a') return 0;
    if (inp.at(2) > 'h' || inp.at(2) < 'a') return 0;

    int from = rowColToSquare(inp.at(1) - '1', inp.at(0) - 'a');
    int to   = rowColToSquare(inp.at(3) - '1', inp.at(2) - 'a');

    ASSERT(!g.isOffBoard(from) && !g.isOffBoard(to));
    MOVES_LIST list;
    generateAllMoves(pos, list, g);      
	int Move = 0;
	int PromPce = EMPTY;
	
	for(int MoveNum = 0; MoveNum < list.count; ++MoveNum) {	
		Move = list.moves[MoveNum].move;           
		if(fromSq(Move)==from && toSq(Move)==to) {
			PromPce = promotionPiece(Move);
			if(PromPce!=EMPTY) {
				if(g.IsRookQueen(PromPce) && !g.IsBishopQueen(PromPce) && inp.at(4) =='r') {
					return Move;
				} else if(!g.IsRookQueen(PromPce) && g.IsBishopQueen(PromPce) && inp.at(4)=='b') {
					return Move;
				} else if(g.IsRookQueen(PromPce) && g.IsBishopQueen(PromPce) && inp.at(4)=='q') {
					return Move;
				} else if(g.IsKnight(PromPce)&& inp.at(4)=='n') {
					return Move;
				}
				continue;
			}
			return Move;
		}
    }
	
    return 0;
}

void printMoveList(MOVES_LIST &list, Globals g) {
    printf("MOVELIST: \n");
    for (int i = 0; i < list.count; i++) {
        printf("MOVE:%d > %s (Score: %d)\n", i+1, printMove(list.moves[i].move, g), list.moves[i].score);
    }

    printf("TOTAL MOVES: %d\n\n", list.count);
}