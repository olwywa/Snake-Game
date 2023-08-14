#include "Board.h"
#include "Tile.h"
#include <vector>
#include <utility>

Board::Board()
{
	int tempSize = 0;
	std::cout << "Welcome to Snake Game. Enter the board size you want to play (it must be greater or equal 5):\n\n";
	std::cin >> tempSize;
	bool correctSize = this->SetBoardSize(tempSize);

	if (correctSize)
	{
		// generate empty board
		for (int wiersz = 0; wiersz < this->boardSize; wiersz++)
		{
			std::vector<Tile*> vecTiles;

			for (int kolumna = 0; kolumna < this->boardSize; kolumna++)
			{
				// write wall
				if (wiersz == 0 || wiersz == this->boardSize - 1)
				{
					Tile* singleTile = new Tile(2);
					vecTiles.push_back(singleTile);
				}
				// write wall
				else if (kolumna == 0 || kolumna == this->boardSize - 1)
				{
					Tile* singleTile = new Tile(2);
					vecTiles.push_back(singleTile);
				}
				// write empty fields
				else
				{
					Tile* singleTile = new Tile(0);
					vecTiles.push_back(singleTile);
				}
			}
			board.push_back(vecTiles);
		}

		// generate snake and food position
		InitializeGame();
	}
}

//Board::Board() 
//{
//	InitializeGame();
//
//	for (int wiersz = 0; wiersz < boardSize; wiersz++)
//	{
//		std::vector<Tile*> vecTiles;
//
//		for (int kolumna = 0; kolumna < boardSize; kolumna++)
//		{
//			// write wall
//			if (wiersz == 0 || wiersz == boardSize - 1)
//			{
//				Tile* singleTile = new Tile(2);
//				vecTiles.push_back(singleTile);
//			}
//			// write wall
//			else if (kolumna == 0 || kolumna == boardSize - 1)
//			{
//				Tile* singleTile = new Tile(2);
//				vecTiles.push_back(singleTile);
//			}
//			// write snake with starting position
//			else if ((wiersz == snake->GetStartingSnakeXPos())
//				&& (kolumna == snake->GetStartingSnakeYPos()))
//			{
//				Tile* singleTile = new Tile(1);
//				vecTiles.push_back(singleTile);
//			}
//			// write empty fields
//			else
//			{
//				Tile* singleTile = new Tile(0);
//				vecTiles.push_back(singleTile);
//			}
//			/*if (kolumna == boardSize - 1)
//			{
//				std::cout << "\n";
//			}*/
//		}
//		board.push_back(vecTiles);
//	}
//	PrintBoard();
//}

void Board::InitializeGame() // random generate snake pos and food pos
{
	bool reqSnakeCheck = false;
	bool reqFoodCheck = false;
	int tmpX;
	int tmpY;

	// random setuj polozenie snake
	do {
		tmpX = GenerateRandomNumberInRange(0, this->boardSize-1);
		tmpY = GenerateRandomNumberInRange(0, this->boardSize-1);
		reqSnakeCheck = CheckStartingTilePosition(tmpX, tmpY); // sprawdz czy wylosowane waertosci sa okej
		if (reqSnakeCheck)
		{
			this->board[tmpX][tmpY]->SetRole(1);
			this->snake->SetStartingSnakePos(tmpX, tmpY);
			this->snake->SetPosition(tmpX, tmpY);
		}
	} while (!reqSnakeCheck);

	// random dodaj jedzenie i sprawdz polozenie jedzenia, wygeneruj plansze 

	do {
		tmpX = GenerateRandomNumberInRange(0, this->boardSize - 1);
		tmpY = GenerateRandomNumberInRange(0, this->boardSize - 1);
		reqFoodCheck = CheckStartingTilePosition(tmpX, tmpY); // sprawdz czy wylosowane waertosci sa okej
		if (reqFoodCheck)
		{
			this->board[tmpX][tmpY]->SetRole(3);
		}
	} while (!reqFoodCheck);

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
	else 
	{
		//invalid size
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

bool Board::CheckStartingTilePosition(int x, int y)
{
	//sprawdz czy pozycja plytki nie wchodzi na sciane lub jedzenie lub samego siebie
	if (this->board[x][y]->GetRole() != WALL
		&& this->board[x][y]->GetRole() != SNAKE
		&& this->board[x][y]->GetRole() != FOOD)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool Board::IsCorrectMove(char moves)
{
	//if (snake->GetCurrentXPos() == -1 || snake->GetCurrentYPos() == -1)
	//{
	//	snake->SetCurrentXPos(snake->GetStartingSnakeXPos());
	//	snake->SetCurrentYPos(snake->GetStartingSnakeYPos());

	//}
	//else if (snake->GetCurrentXPos() == NULL || snake->GetCurrentYPos() == NULL)
	//{
	//	snake->SetCurrentXPos(snake->GetStartingSnakeXPos());
	//	snake->SetCurrentYPos(snake->GetStartingSnakeYPos());
	//}
	char tmp = toupper(moves);
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
		this->isGoodMove = false;
		this->wantToPlay = false;
		return false;
	default:
		this->isGoodMove = false;
		std::cout << "This move was not correct!\nPlease enter your next move again or finish the game by entering 'Q'. \n\n";
	}
	return this->isGoodMove;
}

bool Board::Moves(char moves)
{
	if (IsCorrectMove(moves))
	{
		// check tiles
		int dir = this->snake->GetSnakeHeadDirection();
		bool tempBool = false;
		std::pair<bool, bool> result;

		switch (dir)
		{
		case HeadDirection::UP:
			try
			{
				result = board[snake->GetCurrentXPos() - 1][snake->GetCurrentYPos()]->ChangeRoleToSnake();
				tempBool = result.first;
				if (tempBool == false)
					break;
				else
					snake->SetPosition(snake->GetCurrentXPos() - 1, snake->GetCurrentYPos());
				if (result.second)
					this->snake->IncrementSnakeLenght();
				this->isGoodMove = true;
			}
			catch (const std::exception&)
			{
				std::cout << "Not possible";
			}
			break;
		case HeadDirection::RIGHT:
			try
			{
				result = board[snake->GetCurrentXPos()][snake->GetCurrentYPos() + 1]->ChangeRoleToSnake();
				tempBool = result.first;
				if (tempBool == false)
					break;
				else
					snake->SetPosition(snake->GetCurrentXPos(), snake->GetCurrentYPos() + 1);
				if (result.second)
					this->snake->IncrementSnakeLenght();
				this->isGoodMove = true;
			}
			catch (const std::exception&)
			{
				std::cout << "Not possible";
			}
			break;
		case HeadDirection::DOWN:
			try
			{
				result = board[snake->GetCurrentXPos() + 1][snake->GetCurrentYPos()]->ChangeRoleToSnake();
				tempBool = result.first;
				if (tempBool == false)
					break;
				else
					snake->SetPosition(snake->GetCurrentXPos() + 1, snake->GetCurrentYPos());
				if (result.second)
					this->snake->IncrementSnakeLenght();
				this->isGoodMove = true;
			}
			catch (const std::exception&)
			{
				std::cout << "Not possible";
			}
			break;
		case HeadDirection::LEFT:
			try
			{
				result = board[snake->GetCurrentXPos()][snake->GetCurrentYPos() - 1]->ChangeRoleToSnake();
				tempBool = result.first;
				if (tempBool == false)
					break;
				else
					snake->SetPosition(snake->GetCurrentXPos(), snake->GetCurrentYPos() - 1);
				if (result.second)
					this->snake->IncrementSnakeLenght();
				this->isGoodMove = true;
			}
			catch (const std::exception&)
			{
				std::cout << "Not possible";
			}
			break;
		}

		

		for (int wiersz = 0; wiersz < boardSize; wiersz++)
		{
			for (int kolumna = 0; kolumna < boardSize; kolumna++)
			{
				if (board[wiersz][kolumna] != nullptr)
				{
					std::pair<int, int> tempCoords = { this->snake->GetCurrentXPos(),this->snake->GetCurrentYPos() };
					std::pair<int, int> currColRow = { wiersz, kolumna };

					if (currColRow != tempCoords &&
						board[wiersz][kolumna]->GetRole() == SNAKE)
					{
						board[wiersz][kolumna]->ClearTile();
					}
				}
			}
		}
		return true;
	}
}

//void Board::Moves(char moves) 
//{
//	char tempMove = toupper(moves);
//
//	if (snake->GetCurrentXPos() == -1 || snake->GetCurrentYPos() == -1)
//	{
//		snake->SetCurrentXPos(snake->GetStartingSnakeXPos());
//		snake->SetCurrentYPos(snake->GetStartingSnakeYPos());
//
//		if (snake->GetStartingSnakeXPos() != NULL || snake->GetStartingSnakeYPos() != NULL)
//		{
//			snake->SetStartingSnakePos(NULL, NULL);
//		}
//	}
//	else if (snake->GetCurrentXPos() == NULL || snake->GetCurrentYPos() == NULL)
//	{
//		snake->SetCurrentXPos(snake->GetStartingSnakeXPos());
//		snake->SetCurrentYPos(snake->GetStartingSnakeYPos());
//	}
//
//	//if (snake->GetStartingSnakeXPos() != NULL || snake->GetStartingSnakeYPos() != NULL)
//	//{
//	//	snake->SetStartingSnakePos(NULL, NULL);
//	//}
//
//	switch (tempMove)
//	{
//	case 87: // W
//		try
//		{
//			bool succesRole = board[snake->GetCurrentXPos() - 1][snake->GetCurrentYPos()]->SetRole(1);
//			if (succesRole == false)
//				break;
//			else
//				snake->SetPosition(snake->GetCurrentXPos()-1, snake->GetCurrentYPos());
//		}
//		catch (const std::exception&)
//		{
//			std::cout << "Not possible";
//		}
//		this->isGoodMove = true;
//		break;
//	case 68: // D
//		try
//		{
//			snake->SetPosition(snake->GetCurrentXPos(), snake->GetCurrentYPos() +1);
//			int f = 0;
//		}
//		catch (const std::exception&)
//		{
//			std::cout << "Not possible";
//		}
//		this->isGoodMove = true;
//		break;
//	case 83: // S
//		try
//		{
//			snake->SetPosition(snake->GetCurrentXPos() +1, snake->GetCurrentYPos());
//			int f = 0;
//		}
//		catch (const std::exception&)
//		{
//			std::cout << "Not possible";
//		}
//		this->isGoodMove = true;
//		break;
//	case 65: // A
//		try
//		{
//			snake->SetPosition(snake->GetCurrentXPos(), snake->GetCurrentYPos() -1);
//			int f = 0;
//		}
//		catch (const std::exception&)
//		{
//			std::cout << "Not possible";
//		}
//		this->isGoodMove = true;
//		break;
//	default:
//		this->isGoodMove = false;
//		break;
//	}
//
//	std::pair<int, int> newSnakePos = snake->GetPosition();
//	bool succesRole = false;
//
//	for (int wiersz = 0; wiersz < boardSize; wiersz++)
//	{
//		for (int kolumna = 0; kolumna < boardSize; kolumna++)
//		{
//			if (board[wiersz][kolumna] != nullptr)
//			{
//				if (wiersz == newSnakePos.first && kolumna == newSnakePos.second)
//				{
//					succesRole = board[wiersz][kolumna]->SetRole(1);
//					if (succesRole == false)
//						break;
//				}
//
//				std::pair<int, int> tempCoords = { this->snake->GetCurrentXPos(),this->snake->GetCurrentYPos() };
//				std::pair<int, int> currColRow = { wiersz, kolumna };
//
//				if ( currColRow != tempCoords &&
//					board[wiersz][kolumna]->GetRole() == SNAKE && succesRole)
//				{
//					board[wiersz][kolumna]->ClearTile();
//				}
//			}
//		}
//	}
//}

void Board::PrintBoard()
{
	int o = 0;
	for (int wiersz = 0; wiersz < boardSize; wiersz++)
	{
		for (int kolumna = 0; kolumna < boardSize; kolumna++)
		{
			switch (board[wiersz][kolumna]->GetRole())
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
			if (kolumna == boardSize - 1)
			{
				std::cout << "\n";
			}
		}
	}
}

bool Board::isOver()
{
	return this->wantToPlay;
}
