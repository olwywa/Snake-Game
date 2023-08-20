#pragma once
#include "Snake.h"

class Board
{
private:
	int boardSize = 0;
	bool isGoodMove = false;
	bool isGameOver = false;
	Snake* snake = new Snake();

public:
	std::vector <std::vector<Tile*>> board;

	// constructor
	Board();
	// destructor
	~Board();

	bool SetBoardSize(int x);

	int GetBoardSize();

	void InitializeGame();

	int GenerateRandomNumberInRange(int min, int max);

	void GenerateTileRole(TileRoles role);

	bool CheckTileRoleAtPosition(int x, int y);

	int GetSnakeLengthCounter();

	bool IsCorrectKeyMove(char move);

	bool Move(char move);

	void MakeMoveWithDirection(int x, int y);

	void PrintBoard();

	bool GetGameState();
};

