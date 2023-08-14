#pragma once
#include <iostream>

enum TileRoles 
{
	EMPTY = 0,
	SNAKE,
	WALL,
	FOOD
};

class Tile
{
	TileRoles tileRole;
	TileRoles oldRole;
	int tileCharacter;
	bool ateFoodStatus = false;

public:
	Tile(int role)
	{
		SetRole(role);
		this->oldRole = static_cast<TileRoles>(role);
	};

	void SetRole(int role);

	std::pair<bool, bool> ChangeRoleToSnake();// first - if success, second - if ate food

	TileRoles GetRole();

	TileRoles GetOldRole();

	void ClearTile();

	void SetSnakeAteFoodStatus(bool ateOrNot);

	bool GetSnakeAteFoodStatus();
	//void DrawTile(TileRoles role) {};
};

