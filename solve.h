#ifndef SOLVE_H
#define SOLVE_H

#include <stdbool.h>
#include "board.h"

#define MERGE(s, t) (s | t)

bool fix(int i, int j, uint64_t s, int *d);
bool fix0(int i, int j, uint64_t s, int *d);
bool fix1(int i, int j, uint64_t s, int *d);

uint64_t paint(int i, int j, uint64_t s, int *d);
uint64_t _paint(int i, int j, uint64_t s, int *d);
uint64_t paint0(int i, int j, uint64_t s, int *d);
uint64_t paint1(int i, int j, uint64_t s, int *d);

bool match(int i, int dj, uint64_t s);

void propagate(board *bd, description *des);

#endif

