#ifndef _DRAWBOARD_H

#define _DRAWBOARD_H

#include <stdint.h>
#include <time.h>
#include "Size.h"
#include "ScoreAndScheme.h"

void addRandom(uint8_t board[SIZE][SIZE]);
void getColor(uint8_t value, char *color, size_t length);
void drawBoard(uint8_t board[SIZE][SIZE]);

#endif
