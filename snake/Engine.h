#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <thread> 
#include <errno.h>
#include "Board.h"

class Engine
{
private:
	static const std::string instructions;

public:
	static void PrintInstructions();
	static void StartGame();
};