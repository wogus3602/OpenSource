/*
============================================================================
영어로 써져 있는 부분은 원래 작성되어 있던 주석입니다.
============================================================================
*/
/*
 ============================================================================
 Name        : 2048.c
 Author      : Maurits van der Schee
 Description : Console version of the game "2048" for GNU/Linux
 ============================================================================
 */

#define _XOPEN_SOURCE 500
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<termios.h>
#include<stdbool.h>
#include<stdint.h>
#include<time.h>
#include<signal.h>
#include"2048Color.h"

/*15012971 정민영*/
/*-----------------------------------------------------------------findTarget-----------------------------------------------------------------*/
/*배열을 열로 순회하다가 타겟(합치고자 하는 숫자)이 합칠 숫자가 생기면 타겟의 위치를 반환하기 위함입니다.*/
/*4x4 행렬을 한라인씩 순회 하다가 같은 숫자가 나오면 그 즉시 합치고자 하는 숫자의 위치를 알려주는 역할입니다.*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
uint8_t findTarget(uint8_t array[SIZE], uint8_t x, uint8_t stop) {
	uint8_t t;
	//** if the position is already on the first, don't evaluate
	if (x == 0) {
		return x;
	}

	for (t = x - 1;; t--) { // 방향키 입력 방향으로 타겟을 이동시키다가 타겟의 숫자와 타일의 숫자가 같으면 합치기 위함. ex) 2+2 = 4로 만들기 위함입니다.
		if (array[t] != 0) {
			if (array[t] != array[x]) {
				//** merge is not possible, take next position
				return t + 1; // 합칠 숫자를 발견하지 못하면 인덱스를 다음으로 넘깁니다.
			}
			return t; // 합칠 숫자를 발견하면 타겟의 인덱스를 반환합니다.
		}
		else {
			//** we should not slide further, return this one
			// 중복 합침을 방지하기 위해서 합친 위치의 인덱스를 저장해놓고 그 인덱스에 도착할 때 아무것도 안하고 멈추기 위함입니다.
			if (t == stop) {
				return t;
			}
		}
	}
	//** we did not find a
	return x;
}

/*15012971 정민영*/
/*-----------------------------------------------------------------slideArray-----------------------------------------------------------------*/
/*4x4 행렬을 순회 하다가 같은 숫자가 나오면 합쳐주는 역할입니다.*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
bool slideArray(uint8_t array[SIZE]) {
	bool success = false;
	uint8_t x, t, stop = 0;

	for (x = 0; x < SIZE; x++) {
		if (array[x] != 0) {
			t = findTarget(array, x, stop);
			// if target is not original position, then move or merge
			if (t != x) {
				// if target is zero, this is a move
				if (array[t] == 0) {
					array[t] = array[x];
				}
				else if (array[t] == array[x]) {
					// merge (increase power of two)
					array[t]++;
					// increase score
					score += (uint32_t)1 << array[t];
					// set stop to avoid double merge
					stop = t + 1;
				}
				array[x] = 0; // 2를 합치고나서 합친 2의 자리를 0으로 초기화
				success = true;
			}
		}
	}
	return success;
}

/*-----------------------------------------------------------------rotateBoard-----------------------------------------------------------------*/
/*4x4 행렬을 시계방향으로 90도 돌려줍니다*/
/*함수내에 여러가지 로직을 구현할 때 호출됩니다.(가로,세로를 바꿔 연산하기위해)   16013083 이주형 */
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
void rotateBoard(uint8_t board[SIZE][SIZE]) {
	uint8_t i, j, n = SIZE;
	uint8_t tmp;
	for (i = 0; i < n / 2; i++) {
		for (j = i; j < n - i - 1; j++) {
			tmp = board[i][j];
			board[i][j] = board[j][n - i - 1];
			board[j][n - i - 1] = board[n - i - 1][n - j - 1];
			board[n - i - 1][n - j - 1] = board[n - j - 1][i];
			board[n - j - 1][i] = tmp;
		}
	}
}

/*15012971 정민영*/
/*-----------------------------------------------------------------moveUp-----------------------------------------------------------------*/
/*방향키 위를 입력했을 때 보드판 맨 위에서 아래까지 순회하면서 똑같은 숫자끼리 합해주고 합한 숫자 둘중에 하나를 지웁니다.*/
/*4x4 행렬을 위에서 아래로 이동하면서 같은 숫자가 나오면 합쳐주는 함수들 입니다.*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
bool moveUp(uint8_t board[SIZE][SIZE]) {
	bool success = false;
	uint8_t x;
	for (x = 0; x < SIZE; x++) {
		success |= slideArray(board[x]); // |=의 사용은 같은 숫자끼리 한번이라도 합치면 true를 출력해서 합침 성공을 알리기 위함입니다.
	}
	return success;
}

/*15012971 정민영*/
/*-----------------------------------------------------------------moveLeft-----------------------------------------------------------------*/
/* 왼쪽으로 이동할 경우 rotateBoard함수를 1번 이용하여 보드를 90도를 돌린뒤
위로 밀고난 후 다시 270도를 돌려서 원상태로 만들어준다. */
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
bool moveLeft(uint8_t board[SIZE][SIZE]) {
	bool success;
	rotateBoard(board);
	success = moveUp(board);
	rotateBoard(board);
	rotateBoard(board);
	rotateBoard(board);
	return success;
}

/*15012971 정민영*/
/*-----------------------------------------------------------------moveDown-----------------------------------------------------------------*/
/* 아래쪽으로 이동할 경우 rotateBoard함수를 2번 이용하여 보드를 180도를 돌린뒤
위로 밀고난 후 다시 180도를 돌려서 원상태로 만들어준다. */
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
bool moveDown(uint8_t board[SIZE][SIZE]) {
	bool success;
	rotateBoard(board);
	rotateBoard(board);
	success = moveUp(board);
	rotateBoard(board);
	rotateBoard(board);
	return success;
}

/*15012971 정민영*/
/*-----------------------------------------------------------------moveRight-----------------------------------------------------------------*/
/* 오른쪽으로 이동할 경우 rotateBoard함수를 3번 이용하여 보드를 270도를 돌린뒤
위로 밀고난 후 다시 90도를 돌려서 원상태로 만들어준다. */
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
bool moveRight(uint8_t board[SIZE][SIZE]) {
	bool success;
	rotateBoard(board);
	rotateBoard(board);
	rotateBoard(board);
	success = moveUp(board);
	rotateBoard(board);
	return success;
}

/*-----------------------------------------------------------------findPairDown-----------------------------------------------------------------*/
/* findPairDown함수는 가로의 인접한 배열값들이 같은것이 있는지 확인하여
   gameEnded 함수내에서 게임을 끝내는 조건을 확인할때 쓰인다. 16013083 이주형 */
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


/*-----------------------------------------------------------------countEmpty-----------------------------------------------------------------*/
/* countEmpty함수는 보드내에 있는 0의 갯수를 세어주는 함수이며 gameEnded()함수에서 쓰인다. 16013083 이주형 */
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
uint8_t countEmpty(uint8_t board[SIZE][SIZE]) {
	/*보드에 0이 몇개 있는지 세줌*/
	uint8_t x, y;
	uint8_t count = 0;
	for (x = 0; x < SIZE; x++) {
		for (y = 0; y < SIZE; y++) {
			if (board[x][y] == 0) {
				count++;
			}
		}
	}
	return count;
}

/*-----------------------------------------------------------------gameEnded-----------------------------------------------------------------*/
/* gameEnded함수는 게임이 끝나는 조건이 되는지 확인하는 함수이며 그 조건을 확인하기 위해
   board내에 0이 있는지 확인하며 인접한 값들끼리 같은것이 있는지 확인한다.  16013083 이주형 */
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


void setBufferedInput(bool enable) {
	static bool enabled = true;
	static struct termios old;
	struct termios new;

	if (enable && !enabled) {
		// restore the former settings
		tcsetattr(STDIN_FILENO, TCSANOW, &old);
		// set the new state
		enabled = true;
	}
	else if (!enable && enabled) {
		// get the terminal settings for standard input
		tcgetattr(STDIN_FILENO, &new);
		// we want to keep the old setting to restore them at the end
		old = new;
		// disable canonical mode (buffered i/o) and local echo
		new.c_lflag &= (~ICANON & ~ECHO);
		// set the new settings immediately
		tcsetattr(STDIN_FILENO, TCSANOW, &new);
		// set the new state
		enabled = false;
	}
}


/*15012971 정민영*/
/*-----------------------------------------------------------------signal_callback_handler-----------------------------------------------------------------*/
/*리눅스에서 Ctrl + C를 눌렀을 때 종료되는 메세지와 프로그램을 종료하는 작업입니다.*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
void signal_callback_handler(int signum) {
	printf("         TERMINATED         \n");
	setBufferedInput(true);
	printf("\033[?25h\033[m");
	exit(signum);
}

int main(int argc, char *argv[]) {
	uint8_t board[SIZE][SIZE];
	char c;
	bool success;

	if (argc == 2 && strcmp(argv[1], "blackwhite") == 0) {
		scheme = 1;
	}
	if (argc == 2 && strcmp(argv[1], "bluered") == 0) {
		scheme = 2;
	}

	printf("\033[?25l\033[2J");

	// register signal handler for when ctrl-c is pressed
	signal(SIGINT, signal_callback_handler);//SIGINT는 리눅스에서 Ctrl+C를 눌렀을 때 프로세스를 종료시키는 역할을 한다.

	initBoard(board);
	setBufferedInput(false);
	while (true) {
		c = getchar();
		if (c == -1) { //TODO: maybe replace this -1 with a pre-defined constant(if it's in one of header files)
			puts("\nError! Cannot read keyboard input!");
			break;
		}
		switch (c) {
		case 97:	// 'a' key
		case 104:	// 'h' key
		case 68:	// left arrow
			success = moveLeft(board);  break;
		case 100:	// 'd' key
		case 108:	// 'l' key
		case 67:	// right arrow
			success = moveRight(board); break;
		case 119:	// 'w' key
		case 107:	// 'k' key
		case 65:	// up arrow
			success = moveUp(board);    break;
		case 115:	// 's' key
		case 106:	// 'j' key
		case 66:	// down arrow
			success = moveDown(board);  break;
		default: success = false;
		}
		if (success) {
			drawBoard(board);
			usleep(150000);
			addRandom(board);
			drawBoard(board);
			if (gameEnded(board)) {
				printf("         GAME OVER          \n");
				break;
			}
		}
		if (c == 'q') {
			printf("        QUIT? (y/n)         \n");
			c = getchar();
			if (c == 'y') {
				break;
			}
			drawBoard(board);
		}
		if (c == 'r') {
			printf("       RESTART? (y/n)       \n");
			c = getchar();
			if (c == 'y') {
				initBoard(board);
			}
			drawBoard(board);
		}
	}
	setBufferedInput(true);

	printf("\033[?25h\033[m");

	return EXIT_SUCCESS;
}
