#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>

#define BD_SIZE 25
#define ZERO    (uint64_t)0x4000000000000000 // 01
#define ONE     (uint64_t)0x8000000000000000 // 10
#define U       (uint64_t)0xC000000000000000 // 11
#define MASK    (uint64_t)0xC000000000000000 // 11

#define GET_BD(ptr_bd, i, j) (((ptr_bd)->rows[i] >> (62 - (j) * 2)) << 62)
#define SET_BD(ptr_bd, i, j, val)                   \
    do {                                            \
        ptr_bd->rows[i] &= ~(MASK >> ((j) * 2));    \
        ptr_bd->rows[i] |= (val) >> ((j) * 2);      \
        ptr_bd->cols[j] &= ~(MASK >> ((i) * 2));    \
        ptr_bd->cols[j] |= (val) >> ((i) * 2);      \
    } while (0)

#define GET_S(s, i) (((s) >> (62 - (i) * 2)) << 62)
#define SET_S(ptr_s, i, val)                \
    do {                                    \
        *ptr_s &= ~(MASK >> ((i) * 2));     \
        *ptr_s |= (val) >> ((i) * 2);       \
    } while (0)

typedef struct {
    int rows[BD_SIZE + 1][BD_SIZE / 2 + 2];
    int cols[BD_SIZE + 1][BD_SIZE / 2 + 2];
} description;

typedef struct {
    uint64_t rows[BD_SIZE + 1];
    uint64_t cols[BD_SIZE + 1];
} board;

void init_board(board *);
void print_board(board *);

#endif

