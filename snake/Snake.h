#pragma once
#include <utility>
#include <iostream>
#include <vector>
#include "Tile.h"

enum HeadDirection {
	UP = 0,
	RIGHT,
	DOWN,
	LEFT
};

class Snake
{
private:
	std::pair<int, int> startSnakePos = std::make_pair(NULL, NULL);		// starting Snake position
	std::pair<int, int> currSnakePos = {NULL, NULL};					// current Snake position
	int snakeLength = 1;
	HeadDirection snakeHeadDir = RIGHT;									// default Snake's head direction
	std::vector<Tile*> body;											// Snake's body

public:
	Snake() {}															// Constructor

	//~Snake();															// Destructor

	void SetStartingSnakePos(int x, int y);

	std::pair<int, int> GetStartingSnakePos();

	void SetPosition(std::pair<int,int> coords);

	std::pair<int, int> GetPosition();

	void SetCurrentXPos(int x);
	void SetCurrentYPos(int y);

	int GetCurrentXPos();
	int GetCurrentYPos();

	void IncrementSnakeLength();

	int GetSnakeLength();

	void SetSnakeHeadDirection(HeadDirection dir);

	int GetSnakeHeadDirection();

	std::vector<Tile*> GetSnakeBody();

	void AddToSnakeBody(Tile* tile);

	void UpdateSnakeBody(Tile* tile);
};

