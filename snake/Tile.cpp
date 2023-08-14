#include "Tile.h"


void Tile::SetRole(int role) 
{
	switch (role)
	{
	case 0:
		tileRole = TileRoles::EMPTY;
		break;
	case 1:
		tileRole = TileRoles::SNAKE;
		break;
	case 2:
		tileRole = TileRoles::WALL;
		break;
	case 3:
		tileRole = TileRoles::FOOD;
		break;
	}
}

std::pair<bool, bool> Tile::ChangeRoleToSnake()
{
	std::pair<bool, bool> result = {false, false};
	// clear Snake Ate Food Status each time
	this->SetSnakeAteFoodStatus(false);

	// check collision with WALLS and SNAKE itself
	if (this->tileRole == TileRoles::WALL || this->tileRole == TileRoles::SNAKE)
	{
		std::cout << "Unavailable action, collision detected.\n";
		result.first = false;
	}
	// check if SNAKE eat FOOD
	else if (this->tileRole == TileRoles::FOOD)
	{
		this->oldRole = this->tileRole;
		this->SetSnakeAteFoodStatus(true);
		result.second = true;
		result.first = true;
	}
	else 
	{
		this->oldRole = this->tileRole;
		result.first = true;
	}

	if (result.first)
	{
		this->tileRole = TileRoles::SNAKE;
	}
	 return result;
}

TileRoles Tile::GetRole() 
{
	return this->tileRole;
}

TileRoles Tile::GetOldRole()
{
	return this->oldRole;
}

void Tile::ClearTile() 
{
	this->SetRole(TileRoles::EMPTY);
}

void Tile::SetSnakeAteFoodStatus(bool ateOrNot)
{
	this->ateFoodStatus = ateOrNot;
}

bool Tile::GetSnakeAteFoodStatus() 
{
	return this->ateFoodStatus;
}