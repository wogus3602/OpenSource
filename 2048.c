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
			success = moveUp(board);  break;
		case 100:	// 'd' key
		case 108:	// 'l' key
		case 67:	// right arrow
			success = moveDown(board); break;
		case 119:	// 'w' key
		case 107:	// 'k' key
		case 65:	// up arrow
			success = moveLeft(board);    break;
		case 115:	// 's' key
		case 106:	// 'j' key
		case 66:	// down arrow
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
