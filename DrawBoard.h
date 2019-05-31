#ifndef _DRAWBOARD_H
/*보드판에 색과 랜덤한 위치에 2와 4를 넣고 여러 색을 입히기 위한 헤더 파일이다.*/
#define _DRAWBOARD_H

#include <stdint.h>
#include <time.h>
#include "Size.h"
#include "ScoreAndScheme.h"

void addRandom(uint8_t board[SIZE][SIZE]);
void getColor(uint8_t value, char *color, size_t length);
void drawBoard(uint8_t board[SIZE][SIZE]);

#endif
