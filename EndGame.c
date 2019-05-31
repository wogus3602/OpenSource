/*-----------------------------------------------------------------머릿주석-----------------------------------------------------------------*/
/*Game over가 되었거나 게임을 종료할 때 사용한다.*/
/*countEmpty, gameEnded, setBufferedInput, signal_callback_handler, findPairDown 함수 사용.*/
/*----------------------------------------------------------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<termios.h>
#include"EndGame.h"

/*-----------------------------------------------------------------countEmpty-----------------------------------------------------------------*/
/* countEmpty함수는 보드내에 있는 0의 갯수를 세어주는 함수이며 gameEnded()함수에서 쓰인다.
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
uint8_t countEmpty(uint8_t board[SIZE][SIZE]) {
	/*보드에 0이 몇개 있는지 세줌*/
	uint8_t x, y;
	uint8_t count = 0; // 0의 갯수를 하나씩 카운트 하기 위해서 0으로 초기화
	for (x = 0; x < SIZE; x++) {
		for (y = 0; y < SIZE; y++) {
			/*보드판이 4x4여서 4x4 행렬을 만들기 위해 2중 중첩문 활용.*/
			if (board[x][y] == 0) {
				count++;
			}
		}
	}
	return count;
}

/*-----------------------------------------------------------------gameEnded-----------------------------------------------------------------*/
/* gameEnded함수는 게임이 끝나는 조건이 되는지 확인하는 함수이며 그 조건을 확인하기 위해
   board내에 0이 있는지 확인하며 인접한 값들끼리 같은것이 있는지 확인한다.*/
   /*--------------------------------------------------------------------------------------------------------------------------------------------*/
bool gameEnded(uint8_t board[SIZE][SIZE]) {
	bool ended = true; // ended가 true이면 게임을 끝내는데 countempty에서 0이 하나라도 있으면 게임을 끝내지 않음
	if (countEmpty(board) > 0) return false;
	if (findPairDown(board)) return false; // 게임을 끝내기 전에 board 배열에 마주하는 양옆의 값이 같으면 게임을 끝내면 안되므로 게임을 끝내지 않는다.
	rotateBoard(board);
	if (findPairDown(board)) ended = false;
	rotateBoard(board);
	rotateBoard(board);
	rotateBoard(board);
	return ended;
}

/*-----------------------------------------------------------------setBufferedInput-----------------------------------------------------------------*/
/* 이전 설정을 복원하거나 새로운 설정 환경을 만들기 위해 이 함수를 활용한다.*/
   /*--------------------------------------------------------------------------------------------------------------------------------------------*/
void setBufferedInput(bool enable) {
	static bool enabled = true;
	static struct termios old;
	struct termios new;

	if (enable && !enabled) {
		// 이전 설정을 복원한다.
		tcsetattr(STDIN_FILENO, TCSANOW, &old);
		// 새로운 상태를 설정한다.
		enabled = true;
	}
	else if (!enable && enabled) {
		// 표준 입력 단자 설정을 가져온다.
		tcgetattr(STDIN_FILENO, &new);
		// 오래된 설정을 유지해서 게임을 플레이를 마지막에 복원하기 위해.
		old = new;
		// 캐논ical 모드(버퍼링된 I/O) 및 로컬 에코 사용 안 함.
		new.c_lflag &= (~ICANON & ~ECHO);
		// 새 설정을 즉시 설정한다.
		tcsetattr(STDIN_FILENO, TCSANOW, &new);
		// 새로운 상태를 설정한다.
		enabled = false;
	}
}



/*-----------------------------------------------------------------signal_callback_handler-----------------------------------------------------------------*/
/*리눅스에서 Ctrl + C를 눌렀을 때 종료되는 메세지와 프로그램을 종료하는 작업입니다.*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
void signal_callback_handler(int signum) {
	printf("         TERMINATED         \n");
	setBufferedInput(true);
	printf("\033[?25h\033[m");
	exit(signum);
}
/*-----------------------------------------------------------------findPairDown-----------------------------------------------------------------*/
/* findPairDown함수는 가로의 인접한 배열값들이 같은것이 있는지 확인하여 gameEnded 함수내에서 게임을 끝내는 조건을 확인할때 쓰인다.*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
bool findPairDown(uint8_t board[SIZE][SIZE]) {
	bool success = false;
	uint8_t x, y;
	for (x = 0; x < SIZE; x++) {
		for (y = 0; y < SIZE - 1; y++) {
			if (board[x][y] == board[x][y + 1]) return true;
		}
	}
	return success;
}
