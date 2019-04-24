#include "defs.h"
#include "movegen.h"
#include "Globals.h"
#include "attack.h"
#include "move.h"
#include "board.h"
#include "io.h"
#include "makemove.h"
#include "validate.h"
#include <iostream>

using namespace std;

char PieceChar[] = ".PNBRQKpnbrqk";

int PceDir[13][8] = {
	// EMPTY
	{ 0, 0, 0, 0, 0, 0, 0 },
	// WHITE PAWN (Note That We Don't Use This For Pawns)
	{ 0, 0, 0, 0, 0, 0, 0 },
	// WHITE KNIGHT
	{ -8, -19,	-21, -12, 8, 19, 21, 12 },
	// WHITE BISHOP
	{ -9, -11, 11, 9, 0, 0, 0, 0 },
	// WHITE ROOK
	{ -1, -10,	1, 10, 0, 0, 0, 0 },
	// WHITE QUEEN
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	// WHITE KING
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	// BLACK PAWN
	{ 0, 0, 0, 0, 0, 0, 0 },
	// BLACK KNIGHT
	{ -8, -19,	-21, -12, 8, 19, 21, 12 },
	// BLACK BISHOP
	{ -9, -11, 11, 9, 0, 0, 0, 0 },
	// BLACK ROOK
	{ -1, -10,	1, 10, 0, 0, 0, 0},
	// BLACK QUEEN
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	// BLACK KING
	{ -1, -10,	1, 10, -9, -11, 11, 9 }
};

int NumDir[13] = {
 0, 0, 8, 4, 4, 8, 8, 0, 8, 4, 4, 8, 8
};

const int VictimScore[13] = {0, 100, 200, 300, 400, 500, 600, 100, 200, 300, 400, 500, 600};
static int mvvLVAScores[13][13];

int LoopSlidePce[8] = {
 wB, wR, wQ, 0, bB, bR, bQ, 0
};

int LoopNonSlidePce[6] = {
 wN, wK, 0, bN, bK, 0
};

int LoopSlideIndex[2] = { 0, 4 };
int LoopNonSlideIndex[2] = { 0, 3 };

void initMvvLva() {
	for (int attacker = wP; attacker <= bK; attacker++) {
		for (int Victim = wP; Victim <= bK; Victim++) {
			mvvLVAScores[Victim][attacker] = VictimScore[Victim] + 6 - (VictimScore[attacker] / 100);
		}
	}

}

static void addNonCapture(BOARD * pos, int m, MOVES_LIST &list) {
    MOVE t;
    t.move = m;
	// Optimal Noncapture
    if (pos->searchKillers[0][pos->ply] == m) {
		t.score = 900000;
	// Not-as-optimal Noncapture
	} else if (pos->searchKillers[1][pos->ply] == m) {
		t.score = 800000;
	} else {
		t.score = pos->searchHistory[pos->pieces[fromSq(m)]][toSq(m)];
	}
    list.moves.push_back(t);
    list.count++;
}


static void addCaptureMove(BOARD * pos, int m, MOVES_LIST &list) {
    MOVE t;
    t.move = m;
    t.score = mvvLVAScores[capturePiece(m)][pos->pieces[fromSq(m)]] + 1000000;
    list.moves.push_back(t);
    list.count++;
}

static void addEnPassMove(BOARD * pos, int m, MOVES_LIST &list) {
    MOVE t;
    t.move = m;
	// 1000000 + 105
    t.score = 1000105;
    list.moves.push_back(t);
    list.count++;
}

static void AddWhitePawnMove(BOARD *pos, int from, int to, MOVES_LIST &list, Globals g) {
	ASSERT(!g.isOffBoard(from));
	ASSERT(!g.isOffBoard(to));
	if (g.RowBoard[from] == ROW_7) {
		addNonCapture(pos, MOVEI(from,to,EMPTY,wQ,0), list);
		addNonCapture(pos, MOVEI(from,to,EMPTY,wR,0), list);
		addNonCapture(pos, MOVEI(from,to,EMPTY,wB,0), list);
		addNonCapture(pos, MOVEI(from,to,EMPTY,wN,0), list);
	} else {
		addNonCapture(pos, MOVEI(from,to,EMPTY,EMPTY,0), list);
	}
}

static void AddWhitePawnCapMove(BOARD *pos, const int from, const int to, const int cap, MOVES_LIST &list, Globals g) {
	ASSERT(PieceValidEmpty(cap));
	ASSERT(!g.isOffBoard(from));
	ASSERT(!g.isOffBoard(to));
	if (g.RowBoard[from] == ROW_7) {
		addCaptureMove(pos, MOVEI(from,to,cap,wQ,0), list);
		addCaptureMove(pos, MOVEI(from,to,cap,wR,0), list);
		addCaptureMove(pos, MOVEI(from,to,cap,wB,0), list);
		addCaptureMove(pos, MOVEI(from,to,cap,wN,0), list);
	} else {
		addCaptureMove(pos, MOVEI(from,to,cap,EMPTY,0), list);
	}
}

static void AddBlackPawnCapMove(BOARD *pos, const int from, const int to, const int cap, MOVES_LIST &list, Globals g) {
	ASSERT(PieceValidEmpty(cap));
	ASSERT(!g.isOffBoard(from));
	ASSERT(!g.isOffBoard(to));
	if (g.RowBoard[from] == ROW_2) {
		addCaptureMove(pos, MOVEI(from,to,cap,bQ,0), list);
		addCaptureMove(pos, MOVEI(from,to,cap,bR,0), list);
		addCaptureMove(pos, MOVEI(from,to,cap,bB,0), list);
		addCaptureMove(pos, MOVEI(from,to,cap,bN,0), list);
	} else {
		addCaptureMove(pos, MOVEI(from,to,cap,EMPTY,0), list);
	}
}

static void AddBlackPawnMove(BOARD *pos, int from, int to, MOVES_LIST &list, Globals g) {
	ASSERT(!g.isOffBoard(from));
	ASSERT(!g.isOffBoard(to));
	if (g.RowBoard[from] == ROW_2) {
		addNonCapture(pos, MOVEI(from,to,EMPTY,bQ,0), list);
		addNonCapture(pos, MOVEI(from,to,EMPTY,bR,0), list);
		addNonCapture(pos, MOVEI(from,to,EMPTY,bB,0), list);
		addNonCapture(pos, MOVEI(from,to,EMPTY,bN,0), list);
	} else {
		addNonCapture(pos, MOVEI(from,to,EMPTY,EMPTY,0), list);
	}
}

void generateAllMoves(BOARD * pos, MOVES_LIST &list, Globals g) {
    ASSERT(checkBoard(pos,g));
	list.count = 0;
	
	int pce = EMPTY;
	int side = pos->sideToMove;
	int sq = 0; int t_sq = 0;
	
	if (side == WHITE) {
        // Iterate Thru All White Pawns
		for(int i = 0; i < pos->pieceNum[wP]; i++) {
			sq = pos->pList[wP][i];
			ASSERT(!g.isOffBoard(sq));
			if (pos->pieces[sq + 10] == EMPTY) {
				AddWhitePawnMove(pos, sq, sq+10, list, g);
				if (g.RowBoard[sq] == ROW_2 && pos->pieces[sq + 20] == EMPTY) {
					addNonCapture(pos, MOVEI(sq,(sq+20),EMPTY,EMPTY,0x80000),list);
				}
			} 
			
			if (!g.isOffBoard(sq + 9) && g.PieceCol[pos->pieces[sq + 9]] == BLACK) {
				AddWhitePawnCapMove(pos, sq, sq+9, pos->pieces[sq + 9], list, g);
			}  
			if (!g.isOffBoard(sq + 11) && g.PieceCol[pos->pieces[sq + 11]] == BLACK) {
				AddWhitePawnCapMove(pos, sq, sq+11, pos->pieces[sq + 11], list, g);
			} 
			
			if (pos->enPass != NO_SQ) {
				if (sq + 9 == pos->enPass) {
					addEnPassMove(pos, MOVEI(sq,sq + 9,EMPTY,EMPTY,0x40000), list);
				} 
				if (sq + 11 == pos->enPass) {
					addEnPassMove(pos, MOVEI(sq, sq + 11,EMPTY, EMPTY, 0x40000), list);
				}
			}
		}
		// CASTLING
		if (pos->castlePerm & WHITE_K_K) {
			if (pos->pieces[F1] == EMPTY && pos->pieces[G1] == EMPTY) {
				if (!squareAttacked(E1,BLACK, g,pos) && !squareAttacked(F1, BLACK, g, pos) ) {
					addNonCapture(pos, MOVEI(E1, G1, EMPTY, EMPTY, 0x1000000), list);
				}
			}
		}
		
		if (pos->castlePerm & WHITE_K_Q) {
			if (pos->pieces[D1] == EMPTY && pos->pieces[C1] == EMPTY && pos->pieces[B1] == EMPTY) {
				if (!squareAttacked(E1,BLACK,g, pos) && !squareAttacked(D1,BLACK, g,pos) ) {
					addNonCapture(pos, MOVEI(E1, C1, EMPTY, EMPTY, 0x1000000), list);
				}
			}
		}
	} else {
        // Iterate Through All Black Pawns
		for(int i = 0; i < pos->pieceNum[bP]; i++) {
			sq = pos->pList[bP][i];
			ASSERT(!g.isOffBoard(sq));
            if (pos->pieces[sq - 10] == EMPTY) {
				AddBlackPawnMove(pos, sq, sq-10, list, g);
				if (g.RowBoard[sq] == ROW_7 && pos->pieces[sq - 20] == EMPTY) {
					addNonCapture(pos, MOVEI(sq,(sq-20),EMPTY,EMPTY,0x80000),list);
				}
			} 

            if (!g.isOffBoard(sq - 9) && g.PieceCol[pos->pieces[sq - 9]] == WHITE) {
				AddBlackPawnCapMove(pos, sq, sq-9, pos->pieces[sq - 9], list, g);
			}  
			if (!g.isOffBoard(sq - 11) && g.PieceCol[pos->pieces[sq - 11]] == WHITE) {
				AddBlackPawnCapMove(pos, sq, sq-11, pos->pieces[sq - 11], list, g);
			} 
			
			if (pos->enPass != NO_SQ) {
				if (sq - 9 == pos->enPass) {
					addEnPassMove(pos, MOVEI(sq,sq - 9,EMPTY,EMPTY,0x40000), list);
				} 
				if (sq - 11 == pos->enPass) {
					addEnPassMove(pos, MOVEI(sq,sq - 11,EMPTY,EMPTY,0x40000), list);
				}
			}
        }
		if (pos->castlePerm & BLACK_K_K) {
			if (pos->pieces[F8] == EMPTY && pos->pieces[G8] == EMPTY) {
				if (!squareAttacked(E8,WHITE, g,pos) && !squareAttacked(F8, WHITE, g, pos) ) {
					addNonCapture(pos, MOVEI(E8, G8, EMPTY, EMPTY, 0x1000000), list);
				}
			}
		}
		
		if (pos->castlePerm & BLACK_K_Q) {
			if (pos->pieces[D8] == EMPTY && pos->pieces[C8] == EMPTY && pos->pieces[B8] == EMPTY) {
				if (!squareAttacked(E8,WHITE, g,pos) && !squareAttacked(D8,WHITE, g,pos) ) {
					addNonCapture(pos, MOVEI(E8, C8, EMPTY, EMPTY, 0x1000000), list);
				}
			}
		}
	}

	// Non Sliders
	int pceIndex = LoopNonSlideIndex[side];
	pce = LoopNonSlidePce[pceIndex++];
	
	while( pce != 0) {
		ASSERT(PieceValid(pce));
		for(int pceNum = 0; pceNum < pos->pieceNum[pce]; ++pceNum) {
			sq = pos->pList[pce][pceNum];
			ASSERT(!g.isOffBoard(sq));
			for(int index = 0; index < NumDir[pce]; ++index) {
				int dir = PceDir[pce][index];
				t_sq = sq + dir;
				
				if (g.isOffBoard(t_sq)) {				    
					continue;
				}
				
				// BLACK ^ 1 == WHITE       WHITE ^ 1 == BLACK
				if (pos->pieces[t_sq] != EMPTY) {
					if ( g.PieceCol[pos->pieces[t_sq]] == (side ^ 1)) {
						addCaptureMove(pos, MOVEI(sq, t_sq, pos-> pieces[t_sq], EMPTY, 0), list);
					}
					continue;
				}	
				addNonCapture(pos, MOVEI(sq, t_sq, EMPTY, EMPTY, 0), list);
			}
		}
				
		pce = LoopNonSlidePce[pceIndex++];
	}
	
	// SLIDERS
	pceIndex = LoopSlideIndex[side];
	pce = LoopSlidePce[pceIndex++];
	while( pce != 0) {
		ASSERT(PieceValid(pce));
		for(int pceNum = 0; pceNum < pos->pieceNum[pce]; ++pceNum) {
			sq = pos->pList[pce][pceNum];			
			ASSERT(!g.isOffBoard(sq));
			for(int index = 0; index < NumDir[pce]; ++index) {
				int dir = PceDir[pce][index];
				t_sq = sq + dir;
				
				while(!g.isOffBoard(t_sq)) {				
					// BLACK ^ 1 == WHITE       WHITE ^ 1 == BLACK
					if (pos->pieces[t_sq] != EMPTY) {
						if ( g.PieceCol[pos->pieces[t_sq]] == (side ^ 1)) {
							addCaptureMove(pos, MOVEI(sq, t_sq, pos-> pieces[t_sq], EMPTY, 0), list);
						}
						break;
					}	
					addNonCapture(pos, MOVEI(sq, t_sq, EMPTY, EMPTY, 0), list);
					t_sq += dir;
				}
			}
		}
		
		pce = LoopSlidePce[pceIndex++];
	}	
}

bool MoveExists(BOARD * pos, int move, Globals g) {
	MOVES_LIST list;
    generateAllMoves(pos,list, g);
	for(int i = 0; i < list.count; i++) {	
        if (!makeMove(pos,list.moves[i].move, g))  {
            continue;
        }        
        TakeMove(pos, g);
		if (list.moves[i].move == move) {
			return true;
		}
    }
	return false;
}

void generateAllCaps(BOARD * pos, MOVES_LIST &list, Globals g) {
    ASSERT(checkBoard(pos,g));
	list.count = 0;
	
	int pce = EMPTY;
	int side = pos->sideToMove;
	int sq = 0; int t_sq = 0;
	
	if (side == WHITE) {
        // Iterate Thru All White Pawns
		for(int i = 0; i < pos->pieceNum[wP]; i++) {
			sq = pos->pList[wP][i];
			ASSERT(!g.isOffBoard(sq));
			
			if (!g.isOffBoard(sq + 9) && g.PieceCol[pos->pieces[sq + 9]] == BLACK) {
				AddWhitePawnCapMove(pos, sq, sq+9, pos->pieces[sq + 9], list, g);
			}  
			if (!g.isOffBoard(sq + 11) && g.PieceCol[pos->pieces[sq + 11]] == BLACK) {
				AddWhitePawnCapMove(pos, sq, sq+11, pos->pieces[sq + 11], list, g);
			} 
			
			if (pos->enPass != NO_SQ) {
				if (sq + 9 == pos->enPass) {
					addEnPassMove(pos, MOVEI(sq,sq + 9,EMPTY,EMPTY,0x40000), list);
				} 
				if (sq + 11 == pos->enPass) {
					addEnPassMove(pos, MOVEI(sq, sq + 11,EMPTY, EMPTY, 0x40000), list);
				}
			}
		}
	} else {
        // Iterate Through All Black Pawns
		for(int i = 0; i < pos->pieceNum[bP]; i++) {
			sq = pos->pList[bP][i];
			ASSERT(!g.isOffBoard(sq));
            if (!g.isOffBoard(sq - 9) && g.PieceCol[pos->pieces[sq - 9]] == WHITE) {
				AddBlackPawnCapMove(pos, sq, sq-9, pos->pieces[sq - 9], list, g);
			}  
			if (!g.isOffBoard(sq - 11) && g.PieceCol[pos->pieces[sq - 11]] == WHITE) {
				AddBlackPawnCapMove(pos, sq, sq-11, pos->pieces[sq - 11], list, g);
			} 
			
			if (pos->enPass != NO_SQ) {
				if (sq - 9 == pos->enPass) {
					addEnPassMove(pos, MOVEI(sq,sq - 9,EMPTY,EMPTY,0x40000), list);
				} 
				if (sq - 11 == pos->enPass) {
					addEnPassMove(pos, MOVEI(sq,sq - 11,EMPTY,EMPTY,0x40000), list);
				}
			}
        }
	}

	// Non Sliders
	int pceIndex = LoopNonSlideIndex[side];
	pce = LoopNonSlidePce[pceIndex++];
	
	while( pce != 0) {
		ASSERT(PieceValid(pce));
		for(int pceNum = 0; pceNum < pos->pieceNum[pce]; ++pceNum) {
			sq = pos->pList[pce][pceNum];
			ASSERT(!g.isOffBoard(sq));
			for(int index = 0; index < NumDir[pce]; ++index) {
				int dir = PceDir[pce][index];
				t_sq = sq + dir;
				if (g.isOffBoard(t_sq)) {				    
					continue;
				}
				// BLACK ^ 1 == WHITE       WHITE ^ 1 == BLACK
				if (pos->pieces[t_sq] != EMPTY) {
					if ( g.PieceCol[pos->pieces[t_sq]] == (side ^ 1)) {
						addCaptureMove(pos, MOVEI(sq, t_sq, pos-> pieces[t_sq], EMPTY, 0), list);
					}
					continue;
				}	
			}
		}
				
		pce = LoopNonSlidePce[pceIndex++];
	}
	
	// SLIDERS
	pceIndex = LoopSlideIndex[side];
	pce = LoopSlidePce[pceIndex++];
	while( pce != 0) {
		ASSERT(PieceValid(pce));
		for(int pceNum = 0; pceNum < pos->pieceNum[pce]; ++pceNum) {
			sq = pos->pList[pce][pceNum];			
			ASSERT(!g.isOffBoard(sq));
			for(int index = 0; index < NumDir[pce]; ++index) {
				int dir = PceDir[pce][index];
				t_sq = sq + dir;
				
				while(!g.isOffBoard(t_sq)) {				
					// BLACK ^ 1 == WHITE       WHITE ^ 1 == BLACK
					if (pos->pieces[t_sq] != EMPTY) {
						if ( g.PieceCol[pos->pieces[t_sq]] == (side ^ 1)) {
							addCaptureMove(pos, MOVEI(sq, t_sq, pos-> pieces[t_sq], EMPTY, 0), list);
						}
						break;
					}	
					t_sq += dir;
				}
			}
		}
		
		pce = LoopSlidePce[pceIndex++];
	}	
}