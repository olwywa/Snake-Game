#include "Board.h"

Board::Board()
{
	int tempSize = 0;
	std::cout << "Welcome to Snake Game. Enter the board size you want to play (it must be greater or equal 5):\n\n";
	std::cin >> tempSize;
	bool correctSize = this->SetBoardSize(tempSize);

	if (correctSize)
	{
		for (int row = 0; row < this->boardSize; row++)			// generate empty board to initialize it later
		{
			std::vector<Tile*> vecTiles;

			for (int col = 0; col < this->boardSize; col++)
			{
				if (row == 0 || row == this->boardSize - 1)			// write wall
				{
					Tile* singleTile = new Tile(2);
					vecTiles.push_back(singleTile);
				}
				else if (col == 0 || col == this->boardSize - 1)	// write wall
				{
					Tile* singleTile = new Tile(2);
					vecTiles.push_back(singleTile);
				}
				else														// write empty fields
				{
					Tile* singleTile = new Tile(0);
					vecTiles.push_back(singleTile);
				}
			}
			this->board.push_back(vecTiles);
		}
		InitializeGame();													// generate snake and food position
	}
}

void Board::InitializeGame()												// randomly generate snake pos and food pos
{
	bool reqSnakeCheck = false;
	int tmpX;
	int tmpY;

	do {
		tmpX = GenerateRandomNumberInRange(0, this->boardSize-1);
		tmpY = GenerateRandomNumberInRange(0, this->boardSize-1);
		reqSnakeCheck = CheckTileRoleAtPosition(tmpX, tmpY);	
		if (reqSnakeCheck)													// check if random values are correct
		{
			this->board[tmpX][tmpY]->SetRole(1);
			this->snake->SetStartingSnakePos(tmpX, tmpY);
			this->snake->AddToSnakeBody(this->board[tmpX][tmpY]);
		}
	} while (!reqSnakeCheck);

	GenerateFood();

	std::cout << "\nThis is your starting board and position:\n\n";
	PrintBoard();
}

bool Board::SetBoardSize(int x) 
{
	if (x >= 5) 
	{
		this->boardSize = x;
		return true;
	}
	else  //invalid size
	{
		std::cout << "This board size is incorrect, it must be a value equal or greater than 5 to play." << std::endl;
		return false;
	}
}

int Board::GetBoardSize() 
{
	return this->boardSize;
}

int Board::GenerateRandomNumberInRange(int min, int max) 
{
	return (min + (rand() % static_cast<int>(max - min + 1)));
}

void Board::GenerateFood() 
{
	int tmpX;
	int tmpY;	
	bool reqFoodCheck = false;

	do {
		tmpX = GenerateRandomNumberInRange(0, this->boardSize - 1);
		tmpY = GenerateRandomNumberInRange(0, this->boardSize - 1);
		reqFoodCheck = CheckTileRoleAtPosition(tmpX, tmpY);				// check if random values are correct
		if (reqFoodCheck)
		{
			this->board[tmpX][tmpY]->SetRole(3);
		}
	} while (!reqFoodCheck);
}

bool Board::CheckTileRoleAtPosition(int x, int y)
{
	if (this->board[x][y]->GetRole() == EMPTY)							// check if tile role at position is ok (is empty)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

int Board::GetSnakeLengthCounter() 
{
	return this->snake->GetSnakeLength();
}

bool Board::IsCorrectKeyMove(char move)
{
	char tmp = toupper(move);

	switch (tmp)
	{
	case 87: // W
		this->snake->SetSnakeHeadDirection(UP);
		return true;
	case 68: // D
		this->snake->SetSnakeHeadDirection(RIGHT);
		return true;
	case 83: // S
		this->snake->SetSnakeHeadDirection(DOWN);
		return true;
	case 65: // A
		this->snake->SetSnakeHeadDirection(LEFT);
		return true;
	case 81: // Q - quit game
		return false;
	default:
		std::cout << "This move was not correct!\nPlease enter your next move again or finish the game by entering 'Q'. \n\n";
		return false;
	}
}

bool Board::Move(char move)
{
	if (IsCorrectKeyMove(move))							// check if the key was correct
	{
		int dir = this->snake->GetSnakeHeadDirection();
		std::pair<bool, bool> result;
		std::pair<int, int> tmpSnakeCoords;

		switch (dir) 									// check next tile's role
		{
		case HeadDirection::UP:
			try
			{
				tmpSnakeCoords = { this->snake->GetCurrentXPos() - 1, this->snake->GetCurrentYPos() };
				result = this->board[tmpSnakeCoords.first][tmpSnakeCoords.second]->ChangeRoleToSnake();

				if (result.first == false)				// check if move is possible
				{
					this->isGoodMove = false;
					this->isGameOver = true;
					break;
				}
				else									// check is Snake ate food
				{
					if (result.second)					// Snake ate food - add new tile to Snake's body
					{
						this->snake->AddToSnakeBody(board[tmpSnakeCoords.first][tmpSnakeCoords.second]);
						this->snake->SetPosition(tmpSnakeCoords);
						GenerateFood();
					}
					else								// did not eat - just update Snake's body
					{
						this->snake->UpdateSnakeBody(board[tmpSnakeCoords.first][tmpSnakeCoords.second]);
						this->snake->SetPosition(tmpSnakeCoords);
					}
					this->isGoodMove = true;
				}
			}
			catch (const std::exception&)
			{
				std::cout << "Not possible";
			}
			break;
		case HeadDirection::RIGHT:
			try
			{
				tmpSnakeCoords = { this->snake->GetCurrentXPos(), this->snake->GetCurrentYPos() + 1 };
				result = this->board[tmpSnakeCoords.first][tmpSnakeCoords.second]->ChangeRoleToSnake();

				if (result.first == false)				// check if move is possible
				{
					this->isGoodMove = false;
					this->isGameOver = true;
					break;
				}
				else									// check is Snake ate food
				{
					if (result.second) 
					{
						this->snake->AddToSnakeBody(board[tmpSnakeCoords.first][tmpSnakeCoords.second]);
						this->snake->SetPosition(tmpSnakeCoords);
						GenerateFood();
					}
					else
					{
						this->snake->UpdateSnakeBody(board[tmpSnakeCoords.first][tmpSnakeCoords.second]);
						this->snake->SetPosition(tmpSnakeCoords);
					}
					this->isGoodMove = true;
				}
			}
			catch (const std::exception&)
			{
				std::cout << "Not possible";
			}
			break;
		case HeadDirection::DOWN:
			try
			{
				tmpSnakeCoords = { this->snake->GetCurrentXPos() + 1, this->snake->GetCurrentYPos() };
				result = this->board[tmpSnakeCoords.first][tmpSnakeCoords.second]->ChangeRoleToSnake();

				if (result.first == false)				// check if move is possible
				{
					this->isGoodMove = false;
					this->isGameOver = true;
					break;
				}
				else									// check is Snake ate food
				{
					if (result.second)
					{
						this->snake->AddToSnakeBody(board[tmpSnakeCoords.first][tmpSnakeCoords.second]);
						this->snake->SetPosition(tmpSnakeCoords);
						GenerateFood();
					}
					else
					{
						this->snake->UpdateSnakeBody(board[tmpSnakeCoords.first][tmpSnakeCoords.second]);
						this->snake->SetPosition(tmpSnakeCoords);
					}
					this->isGoodMove = true;
				}
			}
			catch (const std::exception&)
			{
				std::cout << "Not possible";
			}
			break;
		case HeadDirection::LEFT:
			try
			{
				tmpSnakeCoords = { this->snake->GetCurrentXPos(), this->snake->GetCurrentYPos() - 1 };
				result = this->board[tmpSnakeCoords.first][tmpSnakeCoords.second]->ChangeRoleToSnake();

				if (result.first == false)				// check if move is possible
				{
					this->isGoodMove = false;
					this->isGameOver = true;
					break;
				}
				else									// check is Snake ate food
				{
					if (result.second) 
					{
						this->snake->AddToSnakeBody(board[tmpSnakeCoords.first][tmpSnakeCoords.second]);
						this->snake->SetPosition(tmpSnakeCoords);
						GenerateFood();
					}
					else 
					{
						this->snake->UpdateSnakeBody(board[tmpSnakeCoords.first][tmpSnakeCoords.second]);
						this->snake->SetPosition(tmpSnakeCoords);
					}
					this->isGoodMove = true;
				}
			}
			catch (const std::exception&)
			{
				std::cout << "Not possible";
			}
			break;
		}

		
		if (this->isGoodMove)							// if the move was successful, clear previous tiles
		{
			for (int row = 0; row < this->boardSize; row++)
			{
				for (int col = 0; col < this->boardSize; col++)
				{
					if (board[row][col] != nullptr)
					{
						std::pair<int, int> tempCoords = { this->snake->GetCurrentXPos(),this->snake->GetCurrentYPos() };
						std::pair<int, int> currColRow = { row, col };

						if (this->snake->GetSnakeLength() >= 2
							&& this->board[row][col]->GetRole() == SNAKE
							&& (this->board[row][col]->GetOldRole() == FOOD
								|| this->board[row][col]->GetOldRole() == EMPTY))
						{
							// dont clear
						}
						else
						{
							if (currColRow != tempCoords &&
								board[row][col]->GetRole() == SNAKE)
							{
								board[row][col]->ClearTile();
							}
						}
					}
				}
			}
		}
	}
	return this->isGoodMove;
}

void Board::PrintBoard()
{
	for (int row = 0; row < this->boardSize; row++)
	{
		for (int col = 0; col < this->boardSize; col++)
		{
			switch (this->board[row][col]->GetRole())
			{
			case TileRoles::EMPTY:
				std::cout << " ";
				break;
			case TileRoles::SNAKE:
				std::cout << "S";
				break;
			case TileRoles::WALL:
				std::cout << "X";
				break;
			case TileRoles::FOOD:
				std::cout << "o";
				break;
			}
			if (col == this->boardSize - 1)
			{
				std::cout << "\n";
			}
		}
	}
}

bool Board::GetGameState()
{
	return this->isGameOver;
}

Board::~Board() 
{
	//delete this->snake;
}