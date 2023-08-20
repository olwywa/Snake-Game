#include "Engine.h"

const std::string Engine::instructions = "To move snake, use buttons W = UP, D = RIGHT, S = DOWN or A = LEFT. \nUse Q to quit the game.\n\n";

void Engine::PrintInstructions()
{
	COORD cur = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
	std::cout << Engine::instructions;
}

void Engine::StartGame()
{
	Engine::PrintInstructions();

	char move = NULL;
	Board* newBoard = new Board();

	while (!newBoard->GetGameState())
	{
		while (!_kbhit())
		{
			system("cls");
			bool goodMove = newBoard->IsCorrectKeyMove(move);

			if (goodMove)
			{
				std::cout << Engine::instructions;
				bool isSuccessMove = newBoard->Move(move);
				if (isSuccessMove)
					newBoard->PrintBoard();

				std::cout << "\nSnake Counter: " << newBoard->GetSnakeLengthCounter() << std::endl;

				if (isSuccessMove == false)
				{
					std::cout << "\nGAME OVER " << std::endl;
					break;
				}
			}
			else
			{
				newBoard->PrintBoard();
			}
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		move = (char)_getche_nolock();
	}
	std::cout << "\n\nYou have ended the game.\n\n";
}