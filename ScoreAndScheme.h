#ifndef _SIZE_H
/*보드판 사이즈를 선언 해주기 위한 헤더 파일이다.*/
#define _SIZE_H

#include <stdint.h>

#define SIZE 4 // 보드판 사이즈가 4x4이기 때문에 4로 사이즈 정의

extern uint8_t board[SIZE][SIZE]; // 보드판 2차원 배열 선언

#endif
