#include "defs.h"
#include "board.h"
#include "evaluate.h"
#include "validate.h"
#include <string>
#include <iostream>
#include <fstream>

int SideValid(const int side)
{
	return (side == WHITE || side == BLACK) ? 1 : 0;
}

int FileRankValid(const int fr)
{
	return (fr >= 0 && fr <= 7) ? 1 : 0;
}

int PieceValidEmpty(const int pce)
{
	return (pce >= EMPTY && pce <= bK) ? 1 : 0;
}

int PieceValid(const int pce)
{
	return (pce >= wP && pce <= bK) ? 1 : 0;
}

void MirrorTest(std::string filename, BOARD *pos, Globals g)
{
	std::ifstream epdFile(filename);
	std::string line;
	int ev1 = 0;
	int ev2 = 0;
	int positions = 0;
	if (epdFile.is_open())
	{
		while (getline(epdFile, line))
		{
			parseFEN(line.c_str(), pos, g);
			positions++;
			//std::cout << positions << std::endl;
			ev1 = evalPosition(pos, g);
			mirrorBoard(pos, g);
			ev2 = evalPosition(pos, g);

			if (ev1 != ev2)
			{
				std::cout << std::endl
						  << std::endl
						  << std::endl;
				parseFEN(line.c_str(), pos, g);
				printBoard(pos);
				mirrorBoard(pos, g);
				printBoard(pos);
				std::cout << std::endl
						  << std::endl
						  << "Mirror Fail: " << line << std::endl;
				return;
			}
			if (positions % 100 == 0)
			{
				std::cout << "Positions " << positions << std::endl;
			}
		}
	}
	else
	{
		std::cerr << "Unable to Open File" << std::endl;
	}
}
