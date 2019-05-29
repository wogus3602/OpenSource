#include"initBoard.h"

/*16013076 박재현*/
/* 게임판을 초기화 시켜주는 함수*/
void initBoard(uint8_t board[SIZE][SIZE]) {
	uint8_t x, y;
	for (x = 0; x < SIZE; x++) {
		for (y = 0; y < SIZE; y++) {
			board[x][y] = 0;         // 0을 대입한다는건 빈칸이라는 뜻이다.
		}
	}
	addRandom(board);               // 1(2진수), 2(2진수) 값중 하나를 board에서의 랜덤 위치에 저장
	addRandom(board);
	drawBoard(board);               // 게임판을 명령프롬프트 창에 출력
	score = 0;
}