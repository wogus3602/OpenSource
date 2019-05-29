#ifndef _COLOR_H

#define _COLOR_H

#include <stdint.h>
#include <time.h>

#define SIZE 4
extern uint32_t score;	//unsigned는 부호비트를 제거해서 양수 범위를 2배로 늘리기 위해 사용
extern uint8_t scheme;
extern uint8_t board[SIZE][SIZE];

void addRandom(uint8_t board[SIZE][SIZE]);
void initBoard(uint8_t board[SIZE][SIZE]);
void getColor(uint8_t value, char *color, size_t length);
void drawBoard(uint8_t board[SIZE][SIZE]);



#endif






