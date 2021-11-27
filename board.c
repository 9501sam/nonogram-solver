#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void
init_board(board *bd)
{
    int i, j;
    for (i = 0; i <= BD_SIZE; i++)
        SET_BD(bd, i, 0, ZERO);
    for (j = 0; j <= BD_SIZE; j++)
        SET_BD(bd, 0, j, ZERO);
    for (i = 1; i <= BD_SIZE; i++)
        for (j = 1; j <= BD_SIZE; j++)
            SET_BD(bd, i, j, U);
    bd->status = INCOMPLETE;
}

void
print_board(board *bd)
{
    int i, j;
    for (i = 1; i <= BD_SIZE; i++) {
        for (j = 1; j <= BD_SIZE; j++)
            if (GET_BD(bd, i, j) == ZERO) {
                printf("%c", '0');
            } else if (GET_BD(bd, i, j) == ONE) {
                printf("%c", '1');
            } else if (GET_BD(bd, i, j) == U) {
                printf("%c", 'u');
            } else {
                printf("%c", 'x');
            }
        printf("\n");
    }
    printf("\n");
}

bool
is_solved(board *bd)
{
    int i, j;
    for (i = 1; i <= BD_SIZE; i++)
        for (j = 1; j < BD_SIZE; j++)
            if (GET_BD(bd, i, j) == U)
                return false;
    return true;
}
