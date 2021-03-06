#include "unity.h"
#include "Board.h"

void printBoard(Board * board);

void test_empty_board(void) {
    Board board = Board_newBlankBoard();
    for (int i = 0; i < 4; i ++)
        for (int j = 0; j < 4; j++) 
            TEST_ASSERT_EQUAL_INT(0,board.grid[i][j].value);
}

void test_board_constructor(void) {
    uint16_t boardGrid[4][4] = {{0,2,0,0},{0,0,7,0},{0,0,0,0},{69,0,0,69}};
    Board board = Board_newBoard(boardGrid);
    TEST_ASSERT_EQUAL_INT(2,board.grid[0][1].value);
    TEST_ASSERT_EQUAL_INT(7,board.grid[1][2].value);
    TEST_ASSERT_EQUAL_INT(0,board.grid[2][0].value);
    TEST_ASSERT_EQUAL_INT(69,board.grid[3][0].value);
    TEST_ASSERT_EQUAL_INT(69,board.grid[3][3].value);
}

void test_board_equal_blank(void) {
    uint16_t boardGrid[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    Board board1 = Board_newBoard(boardGrid);
    Board board2 = Board_newBlankBoard();
    TEST_ASSERT_TRUE(Board_equal(&board1, &board2));
}

void test_board_update_value(void) {
    Board board = Board_newBlankBoard();
    board.grid[1][2].value = 7;
    for (int i = 0; i < 4; i ++)
        for (int j = 0; j < 4; j++){
            if (i == 1 & j == 2)
                TEST_ASSERT_EQUAL_INT(7,board.grid[i][j].value);
            else
                TEST_ASSERT_EQUAL_INT(0,board.grid[i][j].value);
        }
}

void test_board_shift_left_zeroes(void) {
    Board board = Board_newBlankBoard();
    Board_shift(LEFT, &board);
    printBoard(&board);
    for (int i = 0; i < 4; i ++)
        for (int j = 0; j < 4; j++) 
            TEST_ASSERT_EQUAL_INT(0,board.grid[i][j].value);
}

void test_board_shift_left_twos(void) {
    uint16_t startingGrid[4][4] = {
        {0,2,0,0},
        {0,0,0,2},
        {0,0,0,0},
        {0,0,0,0}
    };
    Board board = Board_newBoard(startingGrid);
    uint16_t expectedGrid[4][4] = {
        {2,0,0,0},
        {2,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    }; 
    Board expectedBoard = Board_newBoard(expectedGrid);
    Board_shift(LEFT, &board);
    printBoard(&board);
    TEST_ASSERT_TRUE(Board_equal(&board,&expectedBoard));
}

void test_board_shift_left_twos_merge(void) {
    uint16_t startingGrid[4][4] = {
        {2,2,0,0},
        {0,2,0,2},
        {2,2,2,0},
        {2,2,2,2}
    };
    Board board = Board_newBoard(startingGrid);
    uint16_t expectedGrid[4][4] = {
        {4,0,0,0},
        {4,0,0,0},
        {4,2,0,0},
        {4,4,0,0}
    }; 
    Board expectedBoard = Board_newBoard(expectedGrid);
    Board_shift(LEFT, &board);
    printBoard(&board);
    TEST_ASSERT_TRUE(Board_equal(&board, &expectedBoard));
}

void test_board_shift_left_different(void) {
    uint16_t startingGrid[4][4] = {
        {2,4,8,16},
        {0,2,4,8},
        {2,0,4,8},
        {2,0,0,4}
    };
    Board board = Board_newBoard(startingGrid);
    uint16_t expectedGrid[4][4] = {
        {2,4,8,16},
        {2,4,8,0},
        {2,4,8,0},
        {2,4,0,0}
    }; 
    Board expectedBoard = Board_newBoard(expectedGrid);
    Board_shift(LEFT, &board);
    printBoard(&board);
    TEST_ASSERT_TRUE(Board_equal(&board, &expectedBoard));
}

void test_board_shift_right_zeroes(void) {
    Board board = Board_newBlankBoard();
    Board_shift(RIGHT, &board);
    printBoard(&board);
    for (int i = 0; i < 4; i ++)
        for (int j = 0; j < 4; j++) 
            TEST_ASSERT_EQUAL_INT(0,board.grid[i][j].value);
}

void test_board_shift_right_twos(void) {
    uint16_t startingGrid[4][4] = {
        {0,2,0,0},
        {0,0,0,2},
        {0,0,0,0},
        {0,0,0,0}
    };
    Board board = Board_newBoard(startingGrid);
    uint16_t expectedGrid[4][4] = {
        {0,0,0,2},
        {0,0,0,2},
        {0,0,0,0},
        {0,0,0,0}
    }; 
    Board expectedBoard = Board_newBoard(expectedGrid);
    Board_shift(RIGHT, &board);
    printBoard(&board);
    TEST_ASSERT_TRUE(Board_equal(&board,&expectedBoard));
}

void test_board_shift_right_twos_merge(void) {
    uint16_t startingGrid[4][4] = {
        {2,2,0,0},
        {0,2,0,2},
        {2,2,2,0},
        {2,2,2,2}
    };
    Board board = Board_newBoard(startingGrid);
    uint16_t expectedGrid[4][4] = {
        {0,0,0,4},
        {0,0,0,4},
        {0,0,2,4},
        {0,0,4,4}
    }; 
    Board expectedBoard = Board_newBoard(expectedGrid);
    Board_shift(RIGHT, &board);
    printBoard(&board);
    TEST_ASSERT_TRUE(Board_equal(&board, &expectedBoard));
}

void test_board_shift_right_different(void) {
    uint16_t startingGrid[4][4] = {
        {2,4,8,16},
        {0,2,4,8},
        {2,0,4,8},
        {2,0,0,4}
    };
    Board board = Board_newBoard(startingGrid);
    uint16_t expectedGrid[4][4] = {
        {2,4,8,16},
        {0,2,4,8},
        {0,2,4,8},
        {0,0,2,4}
    }; 
    Board expectedBoard = Board_newBoard(expectedGrid);
    Board_shift(RIGHT, &board);
    printBoard(&board);
    TEST_ASSERT_TRUE(Board_equal(&board, &expectedBoard));
}

void test_board_shift_down_zeroes(void) {
    Board board = Board_newBlankBoard();
    Board_shift(DOWN, &board);
    printBoard(&board);
    for (int i = 0; i < 4; i ++)
        for (int j = 0; j < 4; j++) 
            TEST_ASSERT_EQUAL_INT(0,board.grid[i][j].value);
}

void test_board_shift_down_twos(void) {
    uint16_t startingGrid[4][4] = {
        {0,2,0,0},
        {0,0,0,2},
        {0,0,0,0},
        {0,0,0,0}
    };
    Board board = Board_newBoard(startingGrid);
    uint16_t expectedGrid[4][4] = {
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,2,0,2}
    }; 
    Board expectedBoard = Board_newBoard(expectedGrid);
    Board_shift(DOWN, &board);
    printBoard(&board);
    TEST_ASSERT_TRUE(Board_equal(&board,&expectedBoard));
}

void test_board_shift_down_twos_merge(void) {
    uint16_t startingGrid[4][4] = {
        {2,2,0,0},
        {0,2,0,2},
        {2,2,2,0},
        {2,2,2,2}
    };
    Board board = Board_newBoard(startingGrid);
    uint16_t expectedGrid[4][4] = {
        {0,0,0,0},
        {0,0,0,0},
        {2,4,0,0},
        {4,4,4,4}
    }; 
    Board expectedBoard = Board_newBoard(expectedGrid);
    Board_shift(DOWN, &board);
    printBoard(&board);
    TEST_ASSERT_TRUE(Board_equal(&board, &expectedBoard));
}

void test_board_shift_down_different(void) {
    uint16_t startingGrid[4][4] = {
        {2,4,2,4},
        {4,2,4,0},
        {8,0,8,8},
        {16,0,0,4}
    };
    Board board = Board_newBoard(startingGrid);
    uint16_t expectedGrid[4][4] = {
        {2,0,0,0},
        {4,0,2,4},
        {8,4,4,8},
        {16,2,8,4}
    }; 
    Board expectedBoard = Board_newBoard(expectedGrid);
    Board_shift(DOWN, &board);
    printBoard(&board);
    TEST_ASSERT_TRUE(Board_equal(&board, &expectedBoard));
}

void test_board_shift_up_zeroes(void) {
    Board board = Board_newBlankBoard();
    Board_shift(UP, &board);
    printBoard(&board);
    for (int i = 0; i < 4; i ++)
        for (int j = 0; j < 4; j++) 
            TEST_ASSERT_EQUAL_INT(0,board.grid[i][j].value);
}

void test_board_shift_up_twos(void) {
    uint16_t startingGrid[4][4] = {
        {0,2,0,0},
        {0,0,0,2},
        {0,0,0,0},
        {0,0,0,0}
    };
    Board board = Board_newBoard(startingGrid);
    uint16_t expectedGrid[4][4] = {
        {0,2,0,2},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    }; 
    Board expectedBoard = Board_newBoard(expectedGrid);
    Board_shift(UP, &board);
    printBoard(&board);
    TEST_ASSERT_TRUE(Board_equal(&board,&expectedBoard));
}

void test_board_shift_up_twos_merge(void) {
    uint16_t startingGrid[4][4] = {
        {2,2,0,0},
        {0,2,0,2},
        {2,2,2,0},
        {2,2,2,2}
    };
    Board board = Board_newBoard(startingGrid);
    uint16_t expectedGrid[4][4] = {
        {4,4,4,4},
        {2,4,0,0},
        {0,0,0,0},
        {0,0,0,0}
    }; 
    Board expectedBoard = Board_newBoard(expectedGrid);
    Board_shift(UP, &board);
    printBoard(&board);
    TEST_ASSERT_TRUE(Board_equal(&board, &expectedBoard));
}

void test_board_shift_up_different(void) {
    uint16_t startingGrid[4][4] = {
        {2,4,2,4},
        {4,0,4,0},
        {8,0,8,8},
        {16,2,0,4}
    };
    Board board = Board_newBoard(startingGrid);
    uint16_t expectedGrid[4][4] = {
        {2,4,2,4},
        {4,2,4,8},
        {8,0,8,4},
        {16,0,0,0}
    }; 
    Board expectedBoard = Board_newBoard(expectedGrid);
    Board_shift(UP, &board);
    printBoard(&board);
    TEST_ASSERT_TRUE(Board_equal(&board, &expectedBoard));
}

void test_board_shift_combo_twos(void) {
    uint16_t startingGrid[4][4] = {
        {2,2,0,2},
        {0,0,2,0},
        {2,0,0,0},
        {0,2,0,0}
    };
    Board board = Board_newBoard(startingGrid);
    uint16_t expectedGrid[4][4] = {
        {0,0,8,4},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    }; 
    Board expectedBoard = Board_newBoard(expectedGrid);
    Board_shift(UP, &board);
    Board_shift(UP, &board);
    Board_shift(RIGHT, &board);
    Board_shift(RIGHT, &board);
    printBoard(&board);
    TEST_ASSERT_TRUE(Board_equal(&board, &expectedBoard));
    TEST_ASSERT_FALSE(Board_gameOver(&board));
}

void test_board_shift_combo_different(void) {
    uint16_t startingGrid[4][4] = {
        {0,2,0,2},
        {16,0,4,0},
        {0,8,0,0},
        {0,0,0,0}
    };
    Board board = Board_newBoard(startingGrid);
    uint16_t expectedGrid[4][4] = {
        {32,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    }; 
    Board expectedBoard = Board_newBoard(expectedGrid);
    Board_shift(RIGHT, &board);
    Board_shift(RIGHT, &board);
    Board_shift(DOWN, &board);
    Board_shift(DOWN, &board);
    Board_shift(UP, &board);
    Boolean moved = Board_shift(LEFT, &board);
    printBoard(&board);
    TEST_ASSERT_TRUE(Board_equal(&board, &expectedBoard));
    TEST_ASSERT_TRUE(moved); 
}

void test_board_no_moves(void) {
    uint16_t startingGrid[4][4] = {
        {2,4,6,8},
        {8,6,4,2},
        {2,4,6,8},
        {8,6,4,2}
    };
    Board board = Board_newBoard(startingGrid);
    uint16_t expectedGrid[4][4] = {
        {2,4,6,8},
        {8,6,4,2},
        {2,4,6,8},
        {8,6,4,2}
    }; 
    Board expectedBoard = Board_newBoard(expectedGrid);
    Board_shift(UP, &board);
    Board_shift(DOWN, &board);
    Board_shift(RIGHT, &board);
    Boolean moved = Board_shift(LEFT, &board);
    printBoard(&board);
    TEST_ASSERT_TRUE(Board_equal(&board, &expectedBoard));
    TEST_ASSERT_FALSE(moved); 
    TEST_ASSERT_TRUE(Board_gameOver(&board));
}

void test_board_gameOver(void) {
    uint16_t startingGrid[4][4] = {
        {0,0,0,0},
        {0,0,0,0},
        {2,0,0,0},
        {2,8,2,0}
    };
    Board board = Board_newBoard(startingGrid);
    TEST_ASSERT_FALSE(Board_gameOver(&board));
}

void test_board_put_random(void) {
    uint16_t startingGrid[4][4] = {
        {2,0,0,8},
        {2,2,2,2},
        {0,0,0,0},
        {2,0,2,0}
    };
    Board board = Board_newBoard(startingGrid);
    uint16_t expectedGrid[4][4] = {
        {2,2,0,8},
        {2,2,2,2},
        {0,0,2,0},
        {2,4,2,0}
    }; 
    Board expectedBoard = Board_newBoard(expectedGrid);
    Board_putRandom(&board, 8, TRUE);
    Board_putRandom(&board, 12, FALSE);
    Board_putRandom(&board, 57, TRUE);
    printBoard(&board);
    TEST_ASSERT_TRUE(Board_equal(&board,&expectedBoard));
}

void test_board_gameWon(void) {
    uint16_t wonGrid[4][4] = {
        {2,0,0,8},
        {2,2,2,2},
        {2048,0,0,0},
        {2,0,2,0}
    };
    Board boardWon = Board_newBoard(wonGrid);
    uint16_t notWonGrid[4][4] = {
        {2,2,0,8},
        {2,2,2,2},
        {0,0,2,0},
        {2,4,2,0}
    }; 
    Board boardNotWon = Board_newBoard(notWonGrid);
    TEST_ASSERT_TRUE(Board_gameWon(&boardWon));
    TEST_ASSERT_FALSE(Board_gameWon(&boardNotWon));
};

void printBoard(Board * board) {
    for (int row = 0; row < 4; row++){
        printf("{");
        for (int col = 0; col < 4; col++) {
            printf(" %u ", board -> grid[row][col].value); 
        }
        printf("}\n\r");
    }
}

int main(void)
{
UNITY_BEGIN();
RUN_TEST(test_empty_board);
RUN_TEST(test_board_constructor);
RUN_TEST(test_board_equal_blank);
RUN_TEST(test_board_update_value);

RUN_TEST(test_board_shift_left_zeroes);
RUN_TEST(test_board_shift_left_twos);
RUN_TEST(test_board_shift_left_twos_merge);
RUN_TEST(test_board_shift_left_different);

RUN_TEST(test_board_shift_right_zeroes);
RUN_TEST(test_board_shift_right_twos);
RUN_TEST(test_board_shift_right_twos_merge);
RUN_TEST(test_board_shift_right_different);

RUN_TEST(test_board_shift_down_zeroes);
RUN_TEST(test_board_shift_down_twos);
RUN_TEST(test_board_shift_down_twos_merge);
RUN_TEST(test_board_shift_down_different);

RUN_TEST(test_board_shift_up_zeroes);
RUN_TEST(test_board_shift_up_twos);
RUN_TEST(test_board_shift_up_twos_merge);
RUN_TEST(test_board_shift_up_different);

RUN_TEST(test_board_shift_combo_twos);
RUN_TEST(test_board_shift_combo_different);

RUN_TEST(test_board_no_moves);
RUN_TEST(test_board_gameOver);

RUN_TEST(test_board_put_random);

RUN_TEST(test_board_gameWon);

return UNITY_END();
}
