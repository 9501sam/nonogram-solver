#include <stdlib.h>
#include "set.h"

set *
new_set()
{
    set *st = (set *)malloc(sizeof(set));
    st->front = 0;
    st->end = 0;
    int i;
    for (i = 1; i <= BD_SIZE; i++)
        st->flag[i] = false;
    return st;
}

int
push(set *st, int val)
{
    if (IS_FULL(st) || st->flag[val])
        return -1;
    if (st->flag[val] == false) {
        st->flag[val] = true;
        st->queue[st->end] = val;
        st->end = (st->end + 1) % Q_SIZE;
    }
    return 0;
}

int
pop(set *st)
{
    if (IS_EMPTY(st))
        return -1;
    int val = st->queue[st->front];
    st->flag[val] = false;
    st->front = (st->front + 1) % Q_SIZE;
    return val;
}

