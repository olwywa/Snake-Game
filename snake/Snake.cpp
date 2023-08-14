#include "Snake.h"

void Snake::SetStartingSnakePos(int x, int y)		// Set coordinates of Snake's starting position
{
	this->startSnakePos = { x, y };
	this->currSnakePos = startSnakePos;
}

std::pair<int, int> Snake::GetStartingSnakePos()	// Get coordinates of Snake's starting position
{
	return this->startSnakePos;
}

void Snake::SetPosition(std::pair<int, int> coords)				// Set current Snake's position
{
	this->currSnakePos = coords;
}

std::pair<int, int> Snake::GetPosition()			// Get current Snake's position
{
	return this->currSnakePos;
}

int Snake::GetCurrentXPos()
{
	return this->currSnakePos.first;
}

int Snake::GetCurrentYPos()
{
	return this->currSnakePos.second;
}

void Snake::SetCurrentXPos(int x)
{
	this->currSnakePos.first = x;
}

void Snake::SetCurrentYPos(int y)
{
	this->currSnakePos.second = y;
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

std::vector<Tile*> Snake::GetSnakeBody() 
{
	if (!this->body.empty())
		return this->body;
	else
	{
		// nothing
	}
}

void Snake::AddToSnakeBody(Tile* tile)					// Add new tile to Snake's body after eating food
{
	if (tile != nullptr)
	{
		this->snakeLength += 1;
		this->body.insert(this->body.begin(), tile);	// Add this element to the front of the vector
	}
}

void Snake::UpdateSnakeBody(Tile* tile)					// Update Snake's body after moving to new position
{
	if (tile != nullptr)
	{
		if (this->snakeLength == 1)						// if Snake is 1 tile long, just update the position of the element
		{
			this->body.at(0) = tile;
		}
		else if(this->body.back() != nullptr
			&& this->snakeLength > 1)					// clear previous tile after move, update the position of the current element
		{
			this->body.back()->SetRole(EMPTY);
			this->body.pop_back();
			this->body.insert(body.begin(), tile);
		}
	}
}

