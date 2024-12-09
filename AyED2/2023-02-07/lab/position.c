#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "position.h"

struct _position
{
    unsigned int row;
    unsigned int column;
    unsigned int dimension;
};

position_t position_initial(unsigned int dimension)
{
    // COMPLETE HERE
    position_t newTabla = malloc(sizeof(struct _position));
    newTabla->dimension = dimension;
    newTabla->column = 0;
    newTabla->row = 0;
    return newTabla;
}

position_t position_absolute(unsigned int row, unsigned int column, unsigned int dimension)
{
    if (row >= dimension || column >= dimension)
    {
        return NULL;
    }    
    position_t newTabla = malloc(sizeof(struct _position));
    if (newTabla == NULL)
    {
        perror("Error reservando memoria.\n");
        exit(EXIT_FAILURE);
    }    
    newTabla->column = column;
    newTabla->dimension = dimension;
    newTabla->row = row;
    return newTabla;
}

position_t position_left(position_t pos)
{
    // COMPLETE HERE
    if (pos->column == 0)
    {
        pos->column = pos->dimension-1;
    }
    else
    {
        pos->column = pos->column - 1;
    }
    return pos;
}

position_t position_right(position_t pos)
{
    // COMPLETE HERE
    if (pos->column == pos->dimension-1)
    {
        pos->column = 0;
    }
    else
    {
        pos->column = pos->column + 1;
    }
    return pos;
}

position_t position_down(position_t pos)
{
    // COMPLETE HERE
    if (pos->row == pos->dimension-1)
    {
        pos->row = 0;
    }
    else
    {
        pos->row = pos->row + 1;
    }
    return pos;
}

position_t position_up(position_t pos)
{
    // COMPLETE HERE
    if (pos->row == 0)
    {
        pos->row = pos->dimension-1;
    }
    else
    {
        pos->row = pos->row - 1;
    }
    return pos;
}

unsigned int position_row(position_t pos)
{
    // COMPLETE HERE
    return pos->row;
}

unsigned int position_column(position_t pos)
{
    // COMPLETE HERE
    return pos->column;
}

unsigned int **position_board(position_t pos)
{
    // COMPLETE HERE
    //assert(pos != NULL);
    //assert(pos->row < pos->dimension && pos->column < pos->dimension);


    unsigned int **matriz = malloc(pos->dimension * sizeof(unsigned int *));
    for (size_t i = 0; i < pos->dimension; i++)
    {
        matriz[i] = malloc(pos->dimension * sizeof(unsigned int));
        for (size_t j = 0; j < pos->dimension; j++)
        {
            if (i == pos->row && j == pos->column)
            {
                matriz[i][j] = 1;
            }
            else
            {
                matriz[i][j] = 0;
            }
        }
    }
    return matriz;
}

// Liberar memoria
void free_position_board(unsigned int **board, unsigned int dimension) {
    for (size_t i = 0; i < dimension; i++) {
        free(board[i]);
    }
    free(board);
}

list_t position_movements(position_t pos)
{
    // COMPLETE HERE
    list_t lista = list_empty();
    if (pos->column == 0 && pos->row == 0)
    {
        return lista;
    }
    else
    {
        for (size_t i = 0; i < pos->row; i++)
        {
            lista = list_append(lista, RIGHT);
        }
        for (size_t i = 0; i < pos->column; i++)
        {
            lista = list_append(lista, DOWN);
        }
    }
    return lista;
}

position_t position_destroy(position_t pos)
{
    // COMPLETE HERE
    free(pos);
    pos = NULL;
    return pos;
}
