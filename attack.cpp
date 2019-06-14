#include "attack.h"
#include "Globals.h"
#include "defs.h"
#include "board.h"
#include "validate.h"
#include <string>

const int KnDir[8] = {-8, -19, -21, -12, 8, 19, 21, 12};
const int RkDir[4] = {-1, -10, 1, 10};
const int BiDir[4] = {-9, -11, 11, 9};
const int KiDir[8] = {-1, -10, 1, 10, -9, -11, 11, 9};

bool squareAttacked(int sq, int side, Globals g, BOARD *pos)
{
	ASSERT(!g.isOffBoard(sq));
	ASSERT(SideValid(side));
	ASSERT(checkBoard(pos, g));

	if (side == WHITE)
	{
		if (pos->pieces[sq - 11] == wP || pos->pieces[sq - 9] == wP)
		{
			return true;
		}
	}
	else
	{
		if (pos->pieces[sq + 11] == bP || pos->pieces[sq + 9] == bP)
		{
			return true;
		}
	}

	// Knight Checking
	for (int i = 0; i < 8; i++)
	{
		int piece = pos->pieces[sq + KnDir[i]];

		if (g.IsKnight(piece) && g.PieceCol[piece] == side && piece != OFFBOARD)
		{
			return true;
		}
	}

	// rooks, queens
	for (int i = 0; i < 4; i++)
	{
		int dir = RkDir[i];
		int test_sq = sq + dir;
		int piece = pos->pieces[test_sq];
		while (piece != OFFBOARD)
		{
			if (piece != EMPTY)
			{
				if (g.IsRookQueen(piece) && g.PieceCol[piece] == side)
				{
					return true;
				}
				break;
			}
			test_sq += dir;
			piece = pos->pieces[test_sq];
		}
	}

	// bishops, queens
	for (int i = 0; i < 4; i++)
	{
		int dir = BiDir[i];
		int test_sq = sq + dir;
		int piece = pos->pieces[test_sq];
		while (piece != OFFBOARD)
		{
			if (piece != EMPTY)
			{
				if (g.IsBishopQueen(piece) && g.PieceCol[piece] == side)
				{
					return true;
				}
				break;
			}
			test_sq += dir;
			piece = pos->pieces[test_sq];
		}
	}

	// kings
	for (int i = 0; i < 8; i++)
	{
		int piece = pos->pieces[sq + KiDir[i]];
		if (g.IsKing(piece) && g.PieceCol[piece] == side)
		{
			return true;
		}
	}

	return false;
}