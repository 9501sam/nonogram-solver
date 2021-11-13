#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "board.h"
#include "solve.h"

int des[51][16] = {
    {0, },
    {6, 1, 3,  7,  2,  2,  1},
    {8, 3, 1,  2,  1,  1,  1,  1,  1},
    {6, 1, 1,  1,  2,  2,  2, },
    {6, 2, 1,  1,  4,  1,  3, },
    {7, 5, 4,  1,  2,  1,  1,  1, },
    {8, 1, 1,  1,  2,  1,  1,  1,  1},
    {7, 4, 1,  2,  1,  2,  2,  1, },
    {6, 1, 2,  1,  5,  1,  2, },
    {8, 2, 1,  2,  3,  1,  1,  1,  2},
    {6, 4, 1,  3,  1,  2,  2, },
    {9, 2, 2,  1,  1,  1,  1,  1,  1,  1},
    {6, 1, 1,  2,  1,  2,  7, },
    {7, 2, 2,  1,  2,  1,  1,  2, },
    {8, 2, 1,  1,  1,  1,  1,  2,  2, },
    {10, 1, 1,  2,  1,  1,  2,  1,  1,  1,  1},
    {7, 1, 2,  1,  1,  2,  5,  1, },
    {7, 1, 1,  1,  3,  4,  1,  1, },
    {5, 1, 5,  4,  5,  1, },
    {8, 5, 1,  1,  1,  2,  1,  1,  2, },
    {7, 1, 3,  1,  1,  4,  1,  1, },
    {6, 4, 2,  2,  2,  2,  2, },
    {9, 1, 1,  1,  2,  1,  2,  1,  2,  1, },
    {6, 1, 2,  3,  1,  1,  4, },
    {10, 1, 1,  1,  1,  2,  2,  1,  1,  1,  1, },
    {6, 1, 2,  3,  4,  1,  2, },
    {6, 1, 3,  2,  2,  1,  4, },
    {7, 5, 1,  6,  1,  1,  1,  2, },
    {6, 1, 4,  2,  1,  1,  2, },
    {4, 1, 1,  7,  7, },
    {7, 1, 2,  1,  1,  1,  3,  3, },
    {5, 5, 1,  5,  1,  1, },
    {6, 2, 3,  1,  1,  1,  1, },
    {6, 3, 1,  1,  1,  1,  4, },
    {6, 2, 2,  3,  1,  1,  3, },
    {7, 2, 2,  6,  1,  2,  1,  1, },
    {7, 1, 3,  1,  2,  1,  3,  2, },
    {6, 1, 2,  3,  2,  4,  2, },
    {7, 4, 3,  1,  1,  1,  2,  2, },
    {6, 1, 1,  1,  3,  1,  4, },
    {7, 1, 1,  4,  1,  3,  1,  1, },
    {7, 1, 1,  3,  1,  1,  3,  2, },
    {7, 1, 2,  1,  2,  2,  1,  4, },
    {6, 1, 1,  1,  1,  4,  1, },
    {5, 2, 1,  2,  3,  2, },
    {7, 2, 5,  1,  2,  2,  1,  1, },
    {7, 4, 1,  3,  1,  1,  2,  1, },
    {7, 1, 1,  1,  1,  1,  3,  3, },
    {7, 3, 1,  1,  2,  2,  1,  4, },
    {8, 1, 1,  2,  2,  1,  3,  1,  1, },
    {5, 1, 1,  1,  4,  4, },
};

void
test_GET_S()
{
    assert(GET_S((uint64_t)0xC000000000000000,  0) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x3000000000000000,  1) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x0C00000000000000,  2) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x0300000000000000,  3) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x00C0000000000000,  4) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x0030000000000000,  5) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x000C000000000000,  6) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x0003000000000000,  7) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x0000C00000000000,  8) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x0000300000000000,  9) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x00000C0000000000, 10) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x0000030000000000, 11) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x000000C000000000, 12) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x0000003000000000, 13) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x0000000C00000000, 14) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x0000000300000000, 15) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x00000000C0000000, 16) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x0000000030000000, 17) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x000000000C000000, 18) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x0000000003000000, 19) == (uint64_t)0xC000000000000000);
    assert(GET_S((uint64_t)0x0000000000100000, 21) == (uint64_t)0x4000000000000000);
}

void
test_init_board()
{
    int i, j;
    uint64_t s;
    board *bd = (board *)malloc(sizeof(board));
    init_board(bd);

    for (i = 1; i <= BD_SIZE; i++) {
        s = bd->rows[i];
        assert(GET_S(s, i) == U);
        assert(GET_S(s, 0) == ZERO);
    }
    for (j = 1; j <= BD_SIZE; j++) {
        s = bd->cols[j];
        assert(GET_S(s, j) == U);
        assert(GET_S(s, 0) == ZERO);
    }
}

void
test_fix()
{
    uint64_t s;
    s = 0x3fffffffffffffff;

    int i;
    for (i = 1; i <= BD_SIZE; i++) {
        printf("i = %d\n", i);
        assert(fix(BD_SIZE, des[i][0], s, des[i]) == true);
    }
}

void
test_fix0()
{
}

void
test_fix1()
{
    uint64_t s;
    s = 0x3fffffffffffffff;
    int d[2] = {0, 25};
    assert(fix1(BD_SIZE, 1, s, d) == true);
}


void
test_match()
{
    uint64_t s;
    s = 0x3fffffffffffffff;
    assert(match(0, 3, s) == false);
    s = 0x2A8fffffffffffff;
    assert(match(2, 2, s) == true);
    assert(match(3, 3, s) == true);
    assert(match(4, 4, s) == true);
    assert(match(4, 5, s) == false);
    s = 0x3fffffffffffffff;
    assert(match(0, 3, s) == false);

    int i;
    for (i = 1; i <= BD_SIZE; i++) {
        printf("i = %d\n", i);
        assert(match(BD_SIZE, des[i][0], s) == true);
    }
}

void
test_paint()
{
    uint64_t s;
    s = 0x3fffffffffffffff;
    int d[2] = {0, 25};
    s = paint(BD_SIZE, 1, s, d);
    assert(((s >> 12) << 12) == (uint64_t)0x6aaaaaaaaaaaa000);
}

int
main()
{
    test_GET_S();
    test_init_board();
    test_match();
    test_fix();
    test_fix1();
    test_paint();

    exit(EXIT_SUCCESS);
}
