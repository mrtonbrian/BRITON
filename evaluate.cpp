#include "evaluate.h"
#include "defs.h"
#include "Globals.h"

// Piece Square Table https://www.chessprogramming.org/Piece-Square_Tables
const int PawnTable[64] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	10, 10, 0, -10, -10, 0, 10, 10,
	5, 0, 0, 5, 5, 0, 0, 5,
	0, 0, 10, 20, 20, 10, 0, 0,
	5, 5, 5, 10, 10, 5, 5, 5,
	10, 10, 10, 20, 20, 10, 10, 10,
	20, 20, 20, 30, 30, 20, 20, 20,
	0, 0, 0, 0, 0, 0, 0, 0};

const int KnightTable[64] = {
	0, -10, 0, 0, 0, 0, -10, 0,
	0, 0, 0, 5, 5, 0, 0, 0,
	0, 0, 10, 10, 10, 10, 0, 0,
	0, 0, 10, 20, 20, 10, 0, 0,
	5, 10, 15, 20, 20, 15, 10, 5,
	5, 10, 10, 20, 20, 10, 10, 5,
	0, 0, 5, 10, 10, 5, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0};

const int BishopTable[64] = {
	0, 0, -10, 0, 0, -10, 0, 0,
	0, 0, 0, 10, 10, 0, 0, 0,
	0, 0, 10, 15, 15, 10, 0, 0,
	0, 10, 15, 20, 20, 15, 10, 0,
	0, 10, 15, 20, 20, 15, 10, 0,
	0, 0, 10, 15, 15, 10, 0, 0,
	0, 0, 0, 10, 10, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0};

const int RookTable[64] = {
	0, 0, 5, 10, 10, 5, 0, 0,
	0, 0, 5, 10, 10, 5, 0, 0,
	0, 0, 5, 10, 10, 5, 0, 0,
	0, 0, 5, 10, 10, 5, 0, 0,
	0, 0, 5, 10, 10, 5, 0, 0,
	0, 0, 5, 10, 10, 5, 0, 0,
	25, 25, 25, 25, 25, 25, 25, 25,
	0, 0, 5, 10, 10, 5, 0, 0};

int evalPosition(BOARD *pos, Globals& g)
{
	int pce;
	int sq;

	// Material Score
	int score = pos->material[WHITE] - pos->material[BLACK];

	pce = wP;
	for (int i = 0; i < pos->pieceNum[pce]; i++)
	{
		sq = pos->pList[pce][i];
		ASSERT(!g.isOffBoard(sq));
		score += PawnTable[g.SQ64(sq)];
	}

	pce = bP;
	for (int i = 0; i < pos->pieceNum[pce]; i++)
	{
		sq = pos->pList[pce][i];
		ASSERT(!g.isOffBoard(sq));
		score -= PawnTable[g.MIRROR(g.SQ64(sq))];
	}

	pce = wN;
	for (int i = 0; i < pos->pieceNum[pce]; i++)
	{
		sq = pos->pList[pce][i];
		ASSERT(!g.isOffBoard(sq));
		score += KnightTable[g.SQ64(sq)];
	}

	pce = bN;
	for (int i = 0; i < pos->pieceNum[pce]; i++)
	{
		sq = pos->pList[pce][i];
		ASSERT(!g.isOffBoard(sq));
		score -= KnightTable[g.MIRROR(g.SQ64(sq))];
	}

	pce = wB;
	for (int i = 0; i < pos->pieceNum[pce]; i++)
	{
		sq = pos->pList[pce][i];
		ASSERT(!g.isOffBoard(sq));
		score += BishopTable[g.SQ64(sq)];
	}

	pce = bB;
	for (int i = 0; i < pos->pieceNum[pce]; i++)
	{
		sq = pos->pList[pce][i];
		ASSERT(!g.isOffBoard(sq));
		score -= BishopTable[g.MIRROR(g.SQ64(sq))];
	}

	pce = wR;
	for (int i = 0; i < pos->pieceNum[pce]; i++)
	{
		sq = pos->pList[pce][i];
		ASSERT(!g.isOffBoard(sq));
		score += RookTable[g.SQ64(sq)];
	}

	pce = bR;
	for (int i = 0; i < pos->pieceNum[pce]; i++)
	{
		sq = pos->pList[pce][i];
		ASSERT(!g.isOffBoard(sq));
		score -= RookTable[g.MIRROR(g.SQ64(sq))];
	}

	// Note that in calculation, white has a positive score, black, has negative score
	if (pos->sideToMove == WHITE)
	{
		return score;
	}
	else
	{
		return -score;
	}
}