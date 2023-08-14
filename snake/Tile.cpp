#include "Tile.h"

void Tile::SetRole(int role) 
{
	switch (role)
	{
	case 0:
		this->currTileRole = TileRoles::EMPTY;
		break;
	case 1:
		this->currTileRole = TileRoles::SNAKE;
		break;
	case 2:
		this->currTileRole = TileRoles::WALL;
		break;
	case 3:
		this->currTileRole = TileRoles::FOOD;
		break;
	}
}

TileRoles Tile::GetRole()
{
	return this->currTileRole;
}

TileRoles Tile::GetOldRole()
{
	return this->oldRole;
}

std::pair<bool, bool> Tile::ChangeRoleToSnake()
{
	std::pair<bool, bool> result = {true, false};				// {move was successful, Snake ate food status}
	
	if (this->currTileRole == TileRoles::WALL 
		|| this->currTileRole == TileRoles::SNAKE)				// check collision with WALLS and SNAKE itself
	{
		std::cout << "Collision detected!!!\n\n";
		result.first = false;
	}
	else if (this->currTileRole == TileRoles::FOOD)				// check if Snake ate FOOD
	{
		this->oldRole = this->currTileRole;
		result.second = true;
	}
	else 
	{
		this->oldRole = this->currTileRole;
	}

	if (result.first)											// if Snake's move was successful, update current tile role
	{
		this->currTileRole = TileRoles::SNAKE;
	}
	 return result;
}

void Tile::ClearTile() 
{
	this->SetRole(TileRoles::EMPTY);
}