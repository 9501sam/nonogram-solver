#include <stdio.h>
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

void
propagate(board *bd, description *des)
{
    uint64_t val;
    int i, j;
    bool change = true;
    while (change) {
        change = false;
        for (i = 1; i <= BD_SIZE; i++) {
            bd->rows[i] = paint(BD_SIZE, des->rows[i][0], bd->rows[i], des->rows[i]);
        }
        for (i = 1; i <= BD_SIZE; i++)
            for (j = 1; j <= BD_SIZE; j++)
                if (GET_S(bd->rows[i], j) != GET_S(bd->cols[j], i)) {
                    val = GET_S(bd->rows[i], j);
                    SET_BD(bd, i, j, val);
                    change = true;
                }
        for (j = 1; j <= BD_SIZE; j++) {
            bd->cols[j] = paint(BD_SIZE, des->cols[j][0], bd->cols[j], des->cols[j]);
        }
        for (i = 1; i <= BD_SIZE; i++)
            for (j = 1; j <= BD_SIZE; j++)
                if (GET_S(bd->rows[i], j) != GET_S(bd->cols[j], i)) {
                    val = GET_S(bd->cols[j], i);
                    SET_BD(bd, i, j, val);
                    change = true;
                }
        print_board(bd);
    }
}

