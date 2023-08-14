#include <windows.h>
#include <conio.h>
#include "Board.h"

int main()
{
	char move = NULL;
	COORD cur = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

	std::string instructions = "To move snake, use buttons W = UP, D = RIGHT, S = DOWN or A = LEFT. \nUse Q to quit the game.\n\n";
	std::cout << instructions;

	Board* newBoard = new Board();

	while (move != 'q')
	{
		move = _getch();
		system("cls");

		bool goodMove = newBoard->IsCorrectKeyMove(move);

		if (goodMove)
		{
			std::cout << instructions;
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
	}
	std::cout << "\n\nYou have ended the game.\n\n";
};
	
