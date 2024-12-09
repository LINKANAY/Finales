#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "position.h"
#include <assert.h>

struct _position
{
    unsigned int row;
    unsigned int column;
    unsigned int dimension;
};

void test_position_initial() {
    printf("Running test_position_initial...\n");
    unsigned int dimension = 5;
    position_t pos = position_initial(dimension);
    assert(pos != NULL);
    assert(pos->dimension == dimension);
    assert(pos->row == 0);
    assert(pos->column == 0);
    pos = position_destroy(pos);
    assert(pos == NULL);
    printf("test_position_initial passed!\n");
}

void test_position_absolute() {
    printf("Running test_position_absolute...\n");
    unsigned int dimension = 5;

    //Primer caso: posicion valida
    position_t pos = position_absolute(2, 3, dimension);
    assert(pos != NULL);
    assert(pos->dimension == dimension);
    assert(pos->row == 2);
    assert(pos->column == 3);
    pos = position_destroy(pos);
    assert(pos == NULL);

    //Segundo caso: posicion invalida
    pos = position_absolute(6, 3, dimension);
    assert(pos == NULL);
    printf("test_position_absolute passed!\n");
}

void test_position_movements() {
    printf("Running test_position_movements...\n");
    unsigned int dimension = 5;
    position_t pos = position_initial(dimension);

    pos = position_right(pos);
    assert(pos->column == 1);

    pos = position_down(pos);
    assert(pos->row == 1);

    pos = position_left(pos);
    assert(pos->column == 0);

    pos = position_up(pos);
    assert(pos->row == 0);

    pos = position_destroy(pos);
    assert(pos == NULL);
    printf("test_position_movements passed!\n");
}

void test_position_board() {
    printf("Running test_position_board...\n");
    unsigned int dimension = 5;
    position_t pos = position_initial(dimension);
    unsigned int **board = position_board(pos);

    assert(board[pos->row][pos->column] == 1);
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            if (i != pos->row || j != pos->column) {
                assert(board[i][j] == 0);
            }
        }
    }

    for (unsigned int i = 0; i < dimension; i++) {
        free(board[i]);
    }
    free(board);
    board = NULL;
    pos = position_destroy(pos);
    assert(pos == NULL && board == NULL);
    printf("test_position_board passed!\n");
}


void display_board(unsigned int **board, unsigned int dimension) {
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

void interactive_menu() {
    unsigned int dimension = 5;
    position_t pos = position_initial(dimension);
    unsigned int **board = position_board(pos);
    int choice;

    do {
        printf("\nCurrent Board:\n");
        display_board(board, dimension);
        printf("Current Position: (%d, %d)\n", pos->row, pos->column);
        printf("Menu:\n");
        printf("1. Move Right\n");
        printf("2. Move Down\n");
        printf("3. Move Left\n");
        printf("4. Move Up\n");
        printf("5. Run All Tests\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                pos = position_right(pos);
                break;
            case 2:
                pos = position_down(pos);
                break;
            case 3:
                pos = position_left(pos);
                break;
            case 4:
                pos = position_up(pos);
                break;
            case 5:
                test_position_initial();
                test_position_absolute();
                test_position_movements();
                test_position_board();
                break;
            case 0:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

        // Update board
        for (unsigned int i = 0; i < dimension; i++) {
            for (unsigned int j = 0; j < dimension; j++) {
                board[i][j] = 0;
            }
        }
        board[pos->row][pos->column] = 1;

    } while (choice != 0);

    for (unsigned int i = 0; i < dimension; i++) {
        free(board[i]);
    }
    free(board);
    pos = position_destroy(pos);
}

int main() {
    interactive_menu();
    printf("Program terminated.\n");
    return 0;
}