// guwno.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Board.h"

int main()
{

	//std::cout << "Welcome to Snake Game. This is your starting board and position: \n\n";
	//Board* newBoard = new Board();
	//std::cout << "\n\nTo move snake, use buttons W = UP, D = RIGHT, S = DOWN or A = LEFT. Do your turn:\n";
	char move = NULL;

	/*do {
		std::cin >> move;
		bool goodMove = newBoard->IsCorrectMove(move);
		if (goodMove)
		{
			newBoard->Moves(move);
			newBoard->PrintBoard();
			std::cout << "\nYour next move:\n";
		}
	} while (newBoard->isOver());*/


	COORD cur = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

	std::string instructions = "To move snake, use buttons W = UP, D = RIGHT, S = DOWN or A = LEFT. \nUse Q to quit the game.\n\n";
	std::cout << instructions;

	Board* newBoard = new Board();

	while (move != 'q')
	{
		move = _getch();
		system("cls");

		bool goodMove = newBoard->IsCorrectMove(move);

		if (goodMove)
		{
			std::cout << instructions;
			newBoard->Moves(move);
			newBoard->PrintBoard();
		}
		else
		{
			newBoard->PrintBoard();
		}
	}

	std::cout << "\n\nYou have ended the game.\n\n";


	//do {
	//	std::cin >> move;
	//	newBoard->Moves(move);
	//	newBoard->PrintBoard();
	//	while (newBoard->isOver())
	//	{
	//		std::cout << "\nYour next move:\n";
	//		break;
	//	}
	//} while (newBoard->IsCorrectMove(move));
};
	
