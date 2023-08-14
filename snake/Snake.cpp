#include "Snake.h"

void Snake::SetPosition(int x, int y) 
{
	snakePos = std::make_pair(x,y);
}

std::pair<int, int> Snake::GetPosition()
{
	return snakePos;
}

std::pair<int, int> Snake::GetStartingSnakePos()
{
	return startSnakePos;
}

void Snake::SetStartingSnakePos(int x, int y)
{
	this->startSnakePos = { x, y };
}

int Snake::GetStartingSnakeXPos()
{
	if (this->startSnakePos.first != NULL)
		return startSnakePos.first;
}

int Snake::GetStartingSnakeYPos()
{
	//return startSnakePos.second;
	if (this->startSnakePos.first != NULL)
		return startSnakePos.second;
}

int Snake::GetCurrentXPos()
{
	return snakePos.first;
}

int Snake::GetCurrentYPos()
{
	return snakePos.second;
}

void Snake::SetCurrentXPos(int x)
{
	snakePos.first = x;
}

void Snake::SetCurrentYPos(int y)
{
	snakePos.second = y;
}

void Snake::IncrementSnakeLenght() 
{
	this->snakeLength += 1;
}

int Snake::GetSnakeLength() 
{
	return this->snakeLength;
}

void Snake::SetSnakeHeadDirection(HeadDirection dir)
{
	this->snakeHeadDir = dir;
}

int Snake::GetSnakeHeadDirection()
{
	return int(this->snakeHeadDir);
}