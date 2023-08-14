#include "gtest/gtest.h"
#include "../../snake/snake/Board.h"

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

	for (int wiersz = 0; wiersz < boardSize; wiersz++)
	{
		std::vector<char> vecTiles;

		for (int kolumna = 0; kolumna < boardSize; kolumna++)
		{
			// write wall
			if (wiersz == 0 || wiersz == boardSize - 1)
			{
				vecTiles.push_back('X');
			}
			// write wall
			else if (kolumna == 0 || kolumna == boardSize - 1)
			{
				vecTiles.push_back('X');
			}
			// write snake with starting position
			else if ((wiersz == snake->GetStartingSnakeXPos())
				&& (kolumna == snake->GetStartingSnakeYPos()))
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

	for (int wiersz = 0; wiersz < boardSize; wiersz++)
	{
		for (int kolumna = 0; kolumna < boardSize; kolumna++)
		{
			std::cout << expectedBoard[wiersz][kolumna];
			if (kolumna == boardSize - 1)
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
    bb.IsCorrectMove('W');
    auto output = bb.board[4][5]->GetRole();
    ASSERT_EQ(1, output);
}