#include "gtest/gtest.h"
#include "../snake/Board.h"

class test_BoardClass : public ::testing::Test
{
public:
    Snake* snake;
    Board bb;

    test_BoardClass() {
        bb = Board();
        bb.SetBoardSize(10);
    }

    void SetUp() {
        snake = new Snake();
        //snake->SetStartingSnakePos(5,5);
        //snake->SetStartingSnakePos(bb.GetBoardSize());
    }


    void TearDown() {
        delete snake;
        // snake = nullptr;
    }

    ~test_BoardClass() {
        // cleanup any pending stuff, but no exceptions allowed
        //delete t;
    }
};

TEST_F(test_BoardClass, createCorrectBoard)
{
	std::stringstream buffer;
	//change the underlying buffer and save the old buffer
	auto old_buf = std::cout.rdbuf(buffer.rdbuf());

	bb.PrintBoard();
	std::string dd = buffer.str();

	std::cout.rdbuf(old_buf); //reset

    std::vector<std::vector<char>> expectedBoard = {};
	int boardSize = 10;

	for (int row = 0; row < this->bb.GetBoardSize(); row++)
	{
		std::vector<char> vecTiles;

		for (int col = 0; col < this->bb.GetBoardSize(); col++)
		{
			// write wall
			if (row == 0 || row == boardSize - 1)
			{
				vecTiles.push_back('X');
			}
			// write wall
			else if (col == 0 || col == boardSize - 1)
			{
				vecTiles.push_back('X');
			}
			// write snake with starting position
			else if ((row == snake->GetStartingSnakePos().first)
				&& (col == snake->GetStartingSnakePos().second))
			{
				vecTiles.push_back('S');
			}
			// write empty fields
			else
			{
				vecTiles.push_back(' ');
			}
		}
		expectedBoard.push_back(vecTiles);
	}

	std::stringstream buffer2;
	//change the underlying buffer and save the old buffer
	auto old_buf2 = std::cout.rdbuf(buffer2.rdbuf());

	for (int row = 0; row < this->bb.GetBoardSize(); row++)
	{
		for (int col = 0; col < this->bb.GetBoardSize(); col++)
		{
			std::cout << expectedBoard[row][col];
			if (col == boardSize - 1)
			{
				std::cout << "\n";
			}
		}
	}

	std::string dd2 = buffer2.str();

	std::cout.rdbuf(old_buf2); //reset

    ASSERT_EQ(dd, dd2);
}

TEST_F(test_BoardClass, test_Move)
{
    bb.IsCorrectKeyMove('W');
    auto output = bb.board[4][5]->GetRole();
    ASSERT_EQ(1, output);
}