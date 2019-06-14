#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include "board.h"
#include "pvtable.h"
#include "defs.h"
#include "Globals.h"
#include "hashkey.h"
#include "init.h"
#include "bitboards.h"

using namespace std;

char PceChar[] = ".PNBRQKpnbrqk";
char SideChar[] = "wb-";

void resetBoard(BOARD *pos, Globals g)
{
	int index = 0;

	for (index = 0; index < 120; ++index)
	{
		pos->pieces[index] = OFFBOARD;
	}

	for (index = 0; index < 64; ++index)
	{
		pos->pieces[g.SQ120(index)] = EMPTY;
	}

	for (index = 0; index < 2; ++index)
	{
		pos->nonPawn[index] = 0;
		pos->RQ[index] = 0;
		pos->KB[index] = 0;
		pos->material[index] = 0;
	}

	for (index = 0; index < 3; index++)
	{
		pos->pawns[index] = 0ULL;
	}

	for (index = 0; index < 13; ++index)
	{
		pos->pieceNum[index] = 0;
	}

	pos->king[WHITE] = pos->king[BLACK] = NO_SQ;

	pos->sideToMove = BOTH;
	pos->enPass = NO_SQ;
	pos->fiftyMove = 0;

	pos->ply = 0;
	pos->hisPly = 0;

	pos->castlePerm = 0;

	pos->position = 0ULL;
}

void parseFEN(const char *FEN, BOARD *pos, Globals g)
{
	resetBoard(pos, g);
	int row = ROW_8;
	int col = COL_A;

	int piece = 0;
	int count;

	int sq64 = 0;
	int sq120 = 0;
	// Iterate Thru Last Row, Check If Still Stuff to Iterate Thru
	while ((row >= ROW_1) && *FEN)
	{
		// Defaults to 1 Piece
		count = 1;
		switch (*FEN)
		{
		case 'p':
			piece = bP;
			break;
		case 'r':
			piece = bR;
			break;
		case 'n':
			piece = bN;
			break;
		case 'b':
			piece = bB;
			break;
		case 'k':
			piece = bK;
			break;
		case 'q':
			piece = bQ;
			break;
		case 'P':
			piece = wP;
			break;
		case 'R':
			piece = wR;
			break;
		case 'N':
			piece = wN;
			break;
		case 'B':
			piece = wB;
			break;
		case 'K':
			piece = wK;
			break;
		case 'Q':
			piece = wQ;
			break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
			piece = EMPTY;
			// http://cs.smu.ca/~porter/csc/ref/asciifull.gif
			count = *FEN - '0';
			break;

		case '/':
		case ' ':
			// Move Array Indexes
			row--;
			col = COL_A;
			// Increment pointer
			FEN++;
			continue;
		default:
			cerr << "ERROR IN PARSING FEN" << endl;
			return;
		}
		for (int i = 0; i < count; i++)
		{
			sq64 = row * 8 + col;
			sq120 = g.SQ120(sq64);
			if (piece != EMPTY)
			{
				pos->pieces[sq120] = piece;
			}
			col++;
		}
		FEN++;
	}

	// Pointer Should Now Be At Side To Move Letter
	// Look Ma! I'm Using a Ternary Operator!
	// http://www.cplusplus.com/articles/1AUq5Di1/
	pos->sideToMove = (*FEN == 'w') ? WHITE : BLACK;
	FEN += 2;

	// Pointer Should Now Be At Castling Perms
	for (int i = 0; i < 4; i++)
	{
		if (*FEN == ' ')
		{
			break;
		}
		switch (*FEN)
		{
		case 'K':
			pos->castlePerm |= WHITE_K_K;
			break;
		case 'Q':
			pos->castlePerm |= WHITE_K_Q;
			break;
		case 'k':
			pos->castlePerm |= BLACK_K_K;
			break;
		case 'q':
			pos->castlePerm |= BLACK_K_Q;
			break;
		default:
			break;
		}
		FEN++;
	}
	FEN++;

	if (*FEN != '-')
	{
		col = FEN[0] - 'a';
		row = FEN[1] - '1';
		pos->enPass = rowColToSquare(row, col);
	}
	pos->position = GeneratePosKey(pos, g);
	UpdateMaterialLists(pos, g);
}

// Used for debugging and stuff
void printBoard(BOARD *pos)
{
	int sq, file, rank, piece;

	printf("\nGame Board:\n\n");

	for (rank = ROW_8; rank >= ROW_1; rank--)
	{
		printf("%d  ", rank + 1);
		for (file = COL_A; file <= COL_H; file++)
		{
			sq = rowColToSquare(rank, file);
			piece = pos->pieces[sq];
			printf("%3c", PceChar[piece]);
		}
		printf("\n");
	}

	printf("\n   ");
	for (file = COL_A; file <= COL_H; file++)
	{
		printf("%3c", 'a' + file);
	}
	printf("\n");
	printf("side:%c\n", SideChar[pos->sideToMove]);
	printf("enPas:%d\n", pos->enPass);
	printf("castle:%c%c%c%c\n",
		   pos->castlePerm & WHITE_K_K ? 'K' : '-',
		   pos->castlePerm & WHITE_K_Q ? 'Q' : '-',
		   pos->castlePerm & BLACK_K_K ? 'k' : '-',
		   pos->castlePerm & BLACK_K_Q ? 'q' : '-');
	printf("PosKey:%llX\n", pos->position);
}

void UpdateMaterialLists(BOARD *pos, Globals g)
{
	for (int i = 0; i < 120; i++)
	{
		int piece = pos->pieces[i];
		if (piece != OFFBOARD && piece != EMPTY)
		{
			int color = g.PieceCol[piece];

			if (g.NonPawn[piece])
				pos->nonPawn[color]++;
			if (g.RookQueen[piece])
				pos->RQ[color]++;
			if (g.BishopKnight[piece])
				pos->KB[color]++;

			pos->material[color] += g.PieceVal[piece];
			pos->pList[piece][pos->pieceNum[piece]] = i;
			pos->pieceNum[piece]++;

			if (piece == wK)
				pos->king[WHITE] = i;
			if (piece == bK)
				pos->king[BLACK] = i;

			if (piece == wP)
			{
				setBit(pos->pawns[WHITE], g.SQ64(i), g);
				setBit(pos->pawns[BOTH], g.SQ64(i), g);
			}
			else if (piece == bP)
			{
				setBit(pos->pawns[BLACK], g.SQ64(i), g);
				setBit(pos->pawns[BOTH], g.SQ64(i), g);
			}
		}
	}
}

bool checkBoard(BOARD *pos, Globals g)
{

	int _pceNum[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int _notPawn[2] = {0, 0};
	int _rookQueen[2] = {0, 0};
	int _knightBishop[2] = {0, 0};
	int _material[2] = {0, 0};

	int sq64, t_piece, t_pce_num, sq120, colour, pcount;

	U64 t_pawns[3] = {0ULL, 0ULL, 0ULL};

	t_pawns[WHITE] = pos->pawns[WHITE];
	t_pawns[BLACK] = pos->pawns[BLACK];
	t_pawns[BOTH] = pos->pawns[BOTH];

	// check pList
	for (t_piece = wP; t_piece <= bK; ++t_piece)
	{
		for (t_pce_num = 0; t_pce_num < pos->pieceNum[t_piece]; ++t_pce_num)
		{
			sq120 = pos->pList[t_piece][t_pce_num];
		}
	}

	// check piece count and other counters
	for (sq64 = 0; sq64 < 64; ++sq64)
	{
		sq120 = g.SQ120(sq64);
		t_piece = pos->pieces[sq120];
		_pceNum[t_piece]++;
		colour = g.PieceCol[t_piece];
		if (g.NonPawn[t_piece] == true)
			_notPawn[colour]++;
		if (g.BishopKnight[t_piece] == true)
			_knightBishop[colour]++;
		if (g.RookQueen[t_piece] == true)
			_rookQueen[colour]++;

		_material[colour] += g.PieceVal[t_piece];
	}

	// check bitboards count
	pcount = countBits(t_pawns[WHITE]);
	pcount = countBits(t_pawns[BLACK]);
	pcount = countBits(t_pawns[BOTH]);

	// check bitboards squares
	while (t_pawns[WHITE])
	{
		sq64 = popBit(&t_pawns[WHITE]);
	}

	while (t_pawns[BLACK])
	{
		sq64 = popBit(&t_pawns[BLACK]);
	}

	while (t_pawns[BOTH])
	{
		sq64 = popBit(&t_pawns[BOTH]);
	}

	// Check The Lists
	ASSERT(_material[WHITE] == pos->material[WHITE] && _material[BLACK] == pos->material[BLACK]);
	ASSERT(_knightBishop[WHITE] == pos->KB[WHITE] && _knightBishop[BLACK] == pos->KB[BLACK]);
	ASSERT(_rookQueen[WHITE] == pos->RQ[WHITE] && _rookQueen[BLACK] == pos->RQ[BLACK]);
	ASSERT(_notPawn[WHITE] == pos->nonPawn[WHITE] && _notPawn[BLACK] == pos->nonPawn[BLACK]);

	ASSERT(pos->sideToMove == WHITE || pos->sideToMove == BLACK);
	ASSERT(GeneratePosKey(pos, g) == pos->position);

	ASSERT(pos->enPass == NO_SQ || (g.RowBoard[pos->enPass] == ROW_6 && pos->sideToMove == WHITE) || (g.RowBoard[pos->enPass] == ROW_3 && pos->sideToMove == BLACK));

	ASSERT(pos->pieces[pos->king[WHITE]] == wK);
	ASSERT(pos->pieces[pos->king[BLACK]] == bK);

	return true;
}

void mirrorBoard(BOARD *pos, Globals g)
{
	int mirrorArray[64];
	int side = pos->sideToMove ^ 1;
	int swapPiece[13]{EMPTY, bP, bN, bB, bR, bQ, bK, wP, wN, wB, wR, wQ, wK};
	int castlePerm = 0;
	int enPas = NO_SQ;

	if (pos->castlePerm & WHITE_K_K)
	{
		castlePerm |= BLACK_K_K;
	}
	if (pos->castlePerm & BLACK_K_K)
	{
		castlePerm |= WHITE_K_K;
	}
	if (pos->castlePerm & WHITE_K_Q)
	{
		castlePerm |= BLACK_K_Q;
	}
	if (pos->castlePerm & BLACK_K_Q)
	{
		castlePerm |= WHITE_K_Q;
	}

	if (pos->enPass != NO_SQ)
	{
		enPas = g.SQ120(g.MIRROR(g.SQ64(pos->enPass)));
	}

	for (int sq = 0; sq < 64; sq++)
	{
		mirrorArray[sq] = pos->pieces[g.SQ120(g.MIRROR(sq))];
	}

	resetBoard(pos, g);

	for (int sq = 0; sq < 64; sq++)
	{
		pos->pieces[g.SQ120(sq)] = swapPiece[mirrorArray[sq]];
	}

	pos->sideToMove = side;
	pos->castlePerm = castlePerm;
	pos->enPass = enPas;
	pos->position = GeneratePosKey(pos, g);
	UpdateMaterialLists(pos, g);
	ASSERT(checkBoard(pos, g));
}