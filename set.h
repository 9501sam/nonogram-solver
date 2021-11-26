#ifndef SET_H
#define SET_H

#include <stdbool.h>
#include "board.h"

#define Q_SIZE (BD_SIZE + 1)
#define IS_EMPTY(st) (bool)((st)->end == (st)->front)
#define IS_FULL(st) (bool)(((st)->end + 1) % Q_SIZE == (st)->front)

typedef struct {
    int front;
    int end;
    int queue[Q_SIZE];
    bool flag[BD_SIZE + 1];
} set;

set *new_set();
int push(set *, int val);
int pop(set *);

#endif
