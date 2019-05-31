#ifndef _MOVE_H
/*포함 되어있는 함수: findTarget, slideArray, rotateBoard, moveUp, moveLeft, moveDown, moveRight*/
/*방향키 조작을 위한 헤더 파일이다.*/
#define _MOVE_H

#include <stdbool.h>
#include "ScoreAndScheme.h"
#include "Size.h"
#include "EndGame.h"

uint8_t findTarget(uint8_t array[SIZE], uint8_t x, uint8_t stop);
bool slideArray(uint8_t array[SIZE]);
void rotateBoard(uint8_t board[SIZE][SIZE]);
bool moveUp(uint8_t board[SIZE][SIZE]);
bool moveLeft(uint8_t board[SIZE][SIZE]);
bool moveDown(uint8_t board[SIZE][SIZE]);
bool moveRight(uint8_t board[SIZE][SIZE]);
#endif
