#include "gtest/gtest.h"
#include "../snake/Snake.h"

class test_SnakeClass : public ::testing::Test 
{
public:
    Snake* snake;

    test_SnakeClass() {
        // initialization code here
    }

    void SetUp() {
        snake = new Snake();
    }


    void TearDown() {
        delete snake;
       // snake = nullptr;
    }

    ~test_SnakeClass() {
        // cleanup any pending stuff, but no exceptions allowed
        //delete t;
    }
};

//TEST_F(test_SnakeClass, test_SetNormalValues)
//{
//    //snake->SetStartingSnakePos(1, 1);
//    snake->SetStartingSnakePos(1, 1);
//    std::pair<int, int> snakePosition = { 1, 1 };
//    ASSERT_EQ(snakePosition, snake->GetStartingSnakePos());
//}

//TEST_F(test_SnakeClass, test_SetNegativeValues)
//{
//    snake->SetStartingSnakePos(-1, -1);
//    std::pair<int, int> snakePosition = { -1, -1 };
//    ASSERT_EQ(snakePosition, snake->GetStartingSnakePos());
//}
//
//TEST_F(test_SnakeClass, test_SetCharValues)
//{
//    snake->SetStartingSnakePos('a', 'b');
//    std::pair<int, int> snakePosition = { 0, 0 };
//    ASSERT_EQ(snakePosition, snake->GetStartingSnakePos());
//}