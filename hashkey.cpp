#include "defs.h"
#include "Globals.h"
#include <iostream>
using namespace std;

U64 GeneratePosKey(BOARD *pos, Globals &g) {
	int sq = 0;
	U64 finalKey = 0ULL;
	int piece = EMPTY;
	// pieces
	for(sq = 0; sq < 120; ++sq) {
		piece = pos->pieces[sq];
		if(piece != NO_SQ && piece!=EMPTY && piece != OFFBOARD) {
			ASSERT(piece>=wP && piece<=bK);
			finalKey ^= g.PieceKeys[piece][sq];
		}
	}

	
	if(pos->sideToMove == WHITE) {
		finalKey ^= g.SideKey;
	}
	
	if(pos->enPass != NO_SQ) {
		ASSERT(pos->enPass>=0 && pos->enPass<120);
		finalKey ^= g.PieceKeys[EMPTY][pos->enPass];
	}
	
	ASSERT(pos->castlePerm>=0 && pos->castlePerm<=15);

	finalKey ^= g.CastleKeys[pos->castlePerm];
	return finalKey;
}