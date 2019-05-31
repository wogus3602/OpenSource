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
#include"Size.h"
#include"ScoreAndScheme.h"
#include"initBoard.h"
#include"DrawBoard.h"
#include"Move.h"
#include"EndGame.h"


int main(int argc, char *argv[]) {
	uint8_t board[SIZE][SIZE];
	char c;
	bool success;

	if (argc == 2) {
		if(strcmp(argv[1], "blackwhite") == 0) {
			scheme = 1;
		}

		if (strcmp(argv[1], "bluered") == 0) {
			scheme = 2;
		}
	}

	printf("\033[?25l\033[2J");

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
		case 97:	// 'a' 키
		case 104:	// 'h' 키
		case 68:	// 왼쪽 방향
			success = moveUp(board);  break;
		case 100:	// 'd' 키
		case 108:	// 'l' 키
		case 67:	// 오른쪽 방향
			success = moveDown(board); break;
		case 119:	// 'w' 키
		case 107:	// 'k' 키
		case 65:	// 위 방향
			success = moveLeft(board);    break;
		case 115:	// 's' 키
		case 106:	// 'j' 키
		case 66:	// 아래쪽 방향
			success = moveRight(board);  break;
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
