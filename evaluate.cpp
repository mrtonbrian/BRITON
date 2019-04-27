#include "evaluate.h"
#include "defs.h"
#include "Globals.h"

// Piece Square Table https://www.chessprogramming.org/Piece-Square_Tables
const int PawnTable[64] = {
    0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,
    10	,	10	,	0	,	-10	,	-10	,	0	,	10	,	10	,
    5	,	0	,	0	,	5	,	5	,	0	,	0	,	5	,
    0	,	0	,	10	,	20	,	20	,	10	,	0	,	0	,
    5	,	5	,	5	,	10	,	10	,	5	,	5	,	5	,
    10	,	10	,	10	,	20	,	20	,	10	,	10	,	10	,
    20	,	20	,	20	,	30	,	30	,	20	,	20	,	20	,
    0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	
};

const int KnightTable[64] = {
    0	,	-10	,	0	,	0	,	0	,	0	,	-10	,	0	,
    0	,	0	,	0	,	5	,	5	,	0	,	0	,	0	,
    0	,	0	,	10	,	10	,	10	,	10	,	0	,	0	,
    0	,	0	,	10	,	20	,	20	,	10	,	0	,	0	,
    5	,	10	,	15	,	20	,	20	,	15	,	10	,	5	,
    5	,	10	,	10	,	20	,	20	,	10	,	10	,	5	,
    0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
    0	,	0	,	0	,	0	,	0	,	0	,	0	,	0		
};

const int BishopTable[64] = {
    0	,	0	,	-10	,	0	,	0	,	-10	,	0	,	0	,
    0	,	0	,	0	,	10	,	10	,	0	,	0	,	0	,
    0	,	0	,	10	,	15	,	15	,	10	,	0	,	0	,
    0	,	10	,	15	,	20	,	20	,	15	,	10	,	0	,
    0	,	10	,	15	,	20	,	20	,	15	,	10	,	0	,
    0	,	0	,	10	,	15	,	15	,	10	,	0	,	0	,
    0	,	0	,	0	,	10	,	10	,	0	,	0	,	0	,
    0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	
};

const int RookTable[64] = {
    0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
    0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
    0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
    0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
    0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
    0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
    25	,	25	,	25	,	25	,	25	,	25	,	25	,	25	,
    0	,	0	,	5	,	10	,	10	,	5	,	0	,	0		
};


// Gets Equivalent Square Index for Black (Note That Square Vals Are Built To Perspective Of White)
const int Mirror64[64] = {
    56	,	57	,	58	,	59	,	60	,	61	,	62	,	63	,
    48	,	49	,	50	,	51	,	52	,	53	,	54	,	55	,
    40	,	41	,	42	,	43	,	44	,	45	,	46	,	47	,
    32	,	33	,	34	,	35	,	36	,	37	,	38	,	39	,
    24	,	25	,	26	,	27	,	28	,	29	,	30	,	31	,
    16	,	17	,	18	,	19	,	20	,	21	,	22	,	23	,
    8	,	9	,	10	,	11	,	12	,	13	,	14	,	15	,
    0	,	1	,	2	,	3	,	4	,	5	,	6	,	7
};

static int MIRROR(int sq) {
    return Mirror64[sq];
}

int evalPosition(BOARD * pos, Globals g) {
    int pce;
	int sq;

    // Material Score
	int score = pos->material[WHITE] - pos->material[BLACK];
	
	pce = wP;	
	for(int i = 0; i < pos->pieceNum[pce]; i++) {
		sq = pos->pList[pce][i];
		ASSERT(!g.isOffBoard(sq));
		score += PawnTable[g.SQ64(sq)];
	}	

	pce = bP;	
	for(int i = 0; i < pos->pieceNum[pce]; i++) {
		sq = pos->pList[pce][i];
		ASSERT(!g.isOffBoard(sq));
		score -= PawnTable[MIRROR(g.SQ64(sq))];
	}	
	
	pce = wN;	
	for(int i = 0; i < pos->pieceNum[pce]; i++) {
		sq = pos->pList[pce][i];
		ASSERT(!g.isOffBoard(sq));
		score += KnightTable[g.SQ64(sq)];
	}	

	pce = bN;	
	for(int i = 0; i < pos->pieceNum[pce]; i++) {
		sq = pos->pList[pce][i];
		ASSERT(!g.isOffBoard(sq));
		score -= KnightTable[MIRROR(g.SQ64(sq))];
	}			
	
	pce = wB;	
	for(int i = 0; i < pos->pieceNum[pce]; i++) {
		sq = pos->pList[pce][i];
		ASSERT(!g.isOffBoard(sq));
		score += BishopTable[g.SQ64(sq)];
	}	

	pce = bB;	
	for(int i = 0; i < pos->pieceNum[pce]; i++) {
		sq = pos->pList[pce][i];
		ASSERT(!g.isOffBoard(sq));
		score -= BishopTable[MIRROR(g.SQ64(sq))];
	}	

	pce = wR;	
	for(int i = 0; i < pos->pieceNum[pce]; i++) {
		sq = pos->pList[pce][i];
		ASSERT(!g.isOffBoard(sq));
		score += RookTable[g.SQ64(sq)];
	}	

	pce = bR;	
	for(int i = 0; i < pos->pieceNum[pce]; i++) {
		sq = pos->pList[pce][i];
		ASSERT(!g.isOffBoard(sq));
		score -= RookTable[MIRROR(g.SQ64(sq))];
	}	
    
    // Note that in calculation, white has a positive score, black, has negative score
	if(pos->sideToMove == WHITE) {
		return score;
	} else {
		return -score;
	}
}