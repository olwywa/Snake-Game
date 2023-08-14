#pragma once
#include <vector>
#include "Tile.h"
#include "Snake.h"

class Board
{
private:
	int boardSize = 0;

public:
	std::vector <std::vector<Tile*>> board;
	bool isGoodMove = true;
	bool wantToPlay = true;

	// constructor
	Board();

	Snake* snake = new Snake();

	bool SetBoardSize(int x);
	int GetBoardSize();

	void InitializeGame();

	int GenerateRandomNumberInRange(int min, int max);

	bool CheckStartingTilePosition(int x, int y);

	bool Moves(char moves);
	void PrintBoard();
	bool IsCorrectMove(char moves);
	bool isOver();
	// utworz plansze
	// clear plansze
	// check ruch usera z rodzajem tile
};

