#pragma once
#include <utility>
#include <iostream>

enum HeadDirection {
	UP = 0,
	RIGHT,
	DOWN,
	LEFT
};

class Snake
{
private:
	std::pair<int, int> startSnakePos = std::make_pair(NULL, NULL);
	std::pair<int, int> snakePos = {-1,-1};
	int snakeLength = 0;
	HeadDirection snakeHeadDir = RIGHT; // default

public:
	// starting position setters/getters
	std::pair<int, int> GetStartingSnakePos();
	void SetStartingSnakePos(int x, int y);

	int GetStartingSnakeXPos();
	int GetStartingSnakeYPos();

	int GetCurrentXPos();
	int GetCurrentYPos();

	void SetCurrentXPos(int x);
	void SetCurrentYPos(int y);

	void SetPosition(int x, int y);
	std::pair<int, int> GetPosition();

	void IncrementSnakeLenght();

	int GetSnakeLength();

	void SetSnakeHeadDirection(HeadDirection dir);

	int GetSnakeHeadDirection();
	//utworz snake
	// idz w ktoras strone
	// 
};

