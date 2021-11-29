#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solve.h"

bool
fix(int i, int j, uint64_t s, int *d)
{
    if (i <= 0 && j == 0)
        return true;
    if ((i == 0 || i == -1) && j >= 1)
        return false;
    return (fix0(i, j, s, d) || fix1(i, j, s, d));
}

bool
fix0(int i, int j, uint64_t s, int *d)
{
    if ((GET_S(s, i) == ZERO) || (GET_S(s, i) == U))
        return fix(i - 1, j, s, d);
    return false;
}

bool
fix1(int i, int j, uint64_t s, int *d)
{
    if ((j >= 1) && (i >= (*(d + j))) && (match(i, *(d + j), s)))
        return fix(i - *(d + j) - 1, j - 1, s, d);
    return false;
}

bool
match(int i, int dj, uint64_t s)
{
    if (i < dj)
        return false;
    int k;
    for (k = i; k > i - dj; k--)
        if (GET_S(s, k) == ZERO)
            return false;
    if (GET_S(s, i - dj) == ONE)
        return false;
    return true;
}

uint64_t
paint(int i, int j, uint64_t s, int *d)
{
    if (i == 0 || i == -1)
        return s;
    return _paint(i, j, s, d);
}

uint64_t
_paint(int i, int j, uint64_t s, int *d)
{
    if (fix0(i, j, s, d) && !fix1(i, j, s, d))
        return paint0(i, j, s, d);
    if (!fix0(i, j, s, d) && fix1(i, j, s, d))
        return paint1(i, j, s, d);
    return MERGE(paint0(i, j, s, d), paint1(i, j, s, d));
}

uint64_t
paint0(int i, int j, uint64_t s, int *d)
{
    SET_S(&s, i, ZERO);
    return paint(i - 1, j, s, d);
}

uint64_t
paint1(int i, int j, uint64_t s, int *d)
{
    int k;
    int dj = *(d + j);
    for (k = i; k > i - dj; k--)
        SET_S(&s, k, ONE);
    SET_S(&s, i - dj, ZERO);
    return paint(i - dj - 1, j - 1, s, d);
}

int
propagate(board *bd, description *des)
{
    uint64_t new, old;
    int i, j, II_G = 0;
    set *row_set = new_set();
    set *col_set = new_set();
    for (i = 0; i <= BD_SIZE; i++)
        push(row_set, i);
    for (j = 0; j <= BD_SIZE; j++)
        push(col_set, j);

    while (!IS_EMPTY(row_set) || !IS_EMPTY(col_set)) {
        while (!IS_EMPTY(row_set)) {
            i = pop(row_set);
            if (!fix(BD_SIZE, des->rows[i][0], bd->rows[i], des->rows[i])) {
                bd->status = CONFLICT;
                return 0;
            }
            bd->rows[i] = paint(BD_SIZE, des->rows[i][0], bd->rows[i], des->rows[i]);
            for (j = 1; j <= BD_SIZE; j++) {
                new = GET_S(bd->rows[i], j);
                old = GET_S(bd->cols[j], i);
                if (new != old) {
                    SET_BD(bd, i, j, new);
                    push(col_set, j);
                    II_G++;
                }
            }
        }
        while (!IS_EMPTY(col_set)) {
            j = pop(col_set);
            if (!fix(BD_SIZE, des->cols[j][0], bd->cols[j], des->cols[j])) {
                bd->status = CONFLICT;
                return 0;
            }
            bd->cols[j] = paint(BD_SIZE, des->cols[j][0], bd->cols[j], des->cols[j]);
            for (i = 1; i <= BD_SIZE; i++) {
                new = GET_S(bd->cols[j], i);
                old = GET_S(bd->rows[i], j);
                if (new != old) {
                    SET_BD(bd, i, j, new);
                    push(row_set, i);
                    II_G++;
                }
            }
        }
    }
    if (is_solved(bd))
        bd->status = SOLVED;
    else
        bd->status = INCOMPLETE;
    free(row_set);
    free(col_set);
    print_board(bd);
    return II_G;
}

void
fp1(board *bd, description *des)
{
    int i, j;
    bool flag;
    do {
        propagate(bd, des);
        if (bd->status == CONFLICT || bd->status == SOLVED)
            return;
        flag = false;
        for (i = 1; i <= BD_SIZE; i++)
            for (j = 1; j <= BD_SIZE; j++) {
                if (GET_BD(bd, i, j) != U)
                    continue;
                probe(bd, des, i, j);
                if (bd->status == CONFLICT || bd->status == SOLVED)
                    return;
                if (bd->status == PAINTED)
                    flag = true;
            }
    } while (flag);
}

int m[2][BD_SIZE + 1][BD_SIZE + 1] = {0};

void
probe(board *bd, description *des, int pi, int pj)
{
    int bd0_new_paint, bd1_new_paint, bd_new_paint = 0;
    board *bd0 = (board *)malloc(sizeof(board));
    board *bd1 = (board *)malloc(sizeof(board));
    memcpy(bd0, bd, sizeof(board));
    memcpy(bd1, bd, sizeof(board));
    SET_BD(bd0, pi, pj, ZERO);
    SET_BD(bd1, pi, pj, ONE);
    bd0_new_paint = propagate(bd0, des);
    bd1_new_paint = propagate(bd1, des);
    m[0][pi][pj] = bd0_new_paint;
    m[1][pi][pj] = bd1_new_paint;
    if (bd0->status == CONFLICT && bd1->status == CONFLICT) {
        bd->status = CONFLICT;
        free(bd0);
        free(bd1);
        return;
    } else if (bd0->status == CONFLICT) {
        memcpy(bd, bd1, sizeof(board));
        bd_new_paint = bd1_new_paint;
    } else if (bd1->status == CONFLICT) {
        memcpy(bd, bd0, sizeof(board));
        bd_new_paint = bd0_new_paint;
    } else {
        bd_new_paint = merge_bd(bd, bd0, bd1);
    }
    free(bd0);
    free(bd1);

    if (bd_new_paint != 0)
        bd->status = PAINTED;
    else
        bd->status = INCOMPLETE;
}

int
merge_bd(board *bd, board *bd0, board *bd1)
{
    int i, j, bd_new_paint = 0;
    for (i = 1; i <= BD_SIZE; i++)
        if (bd->rows[i] != MERGE(bd0->rows[i], bd1->rows[i])) {
            bd_new_paint = 1;
            break;
        }
    for (i = 1; i <= BD_SIZE; i++)
        bd->rows[i] = MERGE(bd0->rows[i], bd1->rows[i]);
    for (j = 1; j <= BD_SIZE; j++)
        bd->cols[j] = MERGE(bd0->cols[j], bd1->cols[j]);
    return bd_new_paint;
}

void
backtracking(board *bd, description *des)
{
    fp1(bd, des);
    if (bd->status == CONFLICT)
        return;
    if (bd->status == SOLVED)
        return;

    int pi = 0, pj = 0;
    int i, j, max = 0;
    for (i = 1; i <= BD_SIZE; i++)
        for (j = 1; j <= BD_SIZE; j++)
            if (GET_BD(bd, i, j) == U && (m[0][i][j] + 1) * (m[1][i][j] + 1) > max) {
                pi = i;
                pj = j;
            }
    board *bd0 = (board *)malloc(sizeof(board));
    board *bd1 = (board *)malloc(sizeof(board));
    memcpy(bd0, bd, sizeof(board));
    memcpy(bd1, bd, sizeof(board));
    SET_BD(bd0, pi, pj, ZERO);
    SET_BD(bd1, pi, pj, ONE);
    backtracking(bd0, des);
    if (bd0->status == SOLVED) {
        memcpy(bd, bd0, sizeof(board));
        return;
    }
    backtracking(bd1, des);
    if (bd1->status == SOLVED) {
        memcpy(bd, bd1, sizeof(board));
        return;
    }
    free(bd0);
    free(bd1);
}

