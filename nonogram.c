#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "board.h"
#include "solve.h"

int
read_des(FILE *fp, description *des)
{
    int i, j, num, num_d, ret;
    char ch;

    ret = fscanf(fp, "$%d\n", &num);
    if (ret == -1)
        return -1;

    for (i = 1; i <= BD_SIZE; i++) {
        num_d = 0;
        fscanf(fp, "%d%c", &num, &ch);
        while (ch != '\n') {
            des->rows[i][++num_d] = num;
            fscanf(fp, "%d%c", &num, &ch);
        }
        des->rows[i][++num_d] = num;
        des->rows[i][0] = num_d;
    }

    for (j = 1; j <= BD_SIZE; j++) {
        num_d = 0;
        fscanf(fp, "%d%c", &num, &ch);
        while (ch != '\n') {
            des->cols[j][++num_d] = num;
            fscanf(fp, "%d%c", &num, &ch);
        }
        des->cols[j][++num_d] = num;
        des->cols[j][0] = num_d;
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    char *input = argv[1];
    FILE *fp;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s input", argv[0]);
        exit(EXIT_FAILURE);
    }
    if ((fp = fopen(input, "r")) == NULL) {
        fprintf(stderr, "%s can't be opened\n", input);
    }

    board *bd;
    description *des;
    bd = (board *)malloc(sizeof(board));
    des = (description *)malloc(sizeof(description));

    int i;
    clock_t start, end;
    float seconds;
    for (i = 1; i <= 1000; i++) {
        init_board(bd);
        read_des(fp, des);

        start = clock();
        backtracking(bd, des);
        end = clock();
        seconds = (float)(end - start) / CLOCKS_PER_SEC;
        printf("$%d: %.2lf sec\n", i, seconds);
        print_board(bd);
        sleep(1);
    }

    exit(EXIT_SUCCESS);
}

