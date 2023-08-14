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
private:
	TileRoles currTileRole;					// current Tile role
	TileRoles oldRole;						// previous Tile role

public:
	Tile(int role)
	{
		SetRole(role);
		this->oldRole = static_cast<TileRoles>(role);
	};

	~Tile();

	void SetRole(int role);

	TileRoles GetRole();

	TileRoles GetOldRole();

	std::pair<bool, bool> ChangeRoleToSnake();	// first bool - if succeed changing role, second - if ate food

	void ClearTile();
};

