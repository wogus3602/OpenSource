#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"DrawBoard.h"

uint32_t score = 0;
uint8_t scheme = 0;

/*16013076 박재현*/
/* board[][]에 '1(2진수)'or '2(2진수)' 를 랜덤한 위치에 넣어주는 함수 */
void addRandom(uint8_t board[SIZE][SIZE]) {
	static bool initialized = false;
	uint8_t x, y;
	uint8_t r, len = 0;  //len은 빈칸의 갯수
	uint8_t n, list[SIZE*SIZE][2];

	if (!initialized) { // initBoard()에서 addRandom()를 2번 호출 하는데 시드값을 변경해서 다른 난수를 생성하기 위해서
		srand(time(NULL));
		initialized = true;
	}

	for (x = 0; x < SIZE; x++) {
		for (y = 0; y < SIZE; y++) {
			if (board[x][y] == 0) { //0을 제외한 숫자가 저장된 위치를 list[][]에 저장
				list[len][0] = x;
				list[len][1] = y;
				len++;
			}
		}
	}

	if (len > 0) { //만약 모든곳에 숫자가 채워지면 len=0 이고 if문이 돌아가지 않는다.
		r = rand() % len;      // 0~len(빈칸의 갯수) 까지 랜덤 값 저장
		x = list[r][0];         // board의 빈칸 위치 저장 
		y = list[r][1];
		n = (rand() % 10) / 9 + 1; // n은 1(2진수),2(2진수) 둘중 하나의 값이고 1(2진수)은 8/9 확률로  2(2진수)는 1/9 확률로 값이 정해진다.
		board[x][y] = n; //(x,y) 에 n을 저장
	}
}
/*16013076 박재현*/
/* 숫자 타일 및 숫자 자체 색을 정해주는 함수 */
void getColor(uint8_t value, char *color, size_t length) {
	// original[],blackwhite[],bluered[] 의 값 순서 {빈타일색깔,·의 색깔,'2'숫자타일색깔,'2'숫자색깔,'4'숫자타일색깔,'4'숫자색깔,....,'16384'숫자타일색깔,'16384'숫자색깔}
	// 88 또는 256 색상에 대한 ANSI 지원에 따라 달라진다. 지원되는 색상이 충분하지 않으면 blackwhite,bluered 로 바뀔것이다.
	uint8_t original[] = { 8,255,1,255,2,255,3,255,4,255,5,255,6,255,7,255,9,0,10,0,11,0,12,0,13,0,14,0,255,0,255,0 };
	uint8_t blackwhite[] = { 232,255,234,255,236,255,238,255,240,255,242,255,244,255,246,0,248,0,249,0,250,0,251,0,252,0,253,0,254,0,255,0 };
	uint8_t bluered[] = { 235,255,63,255,57,255,93,255,129,255,165,255,201,255,200,255,199,255,198,255,197,255,196,255,196,255,196,255,196,255,196,255 };
	uint8_t *schemes[] = { original,blackwhite,bluered };
	uint8_t *background = schemes[scheme] + 0; // background = 숫자타일색깔
	uint8_t *foreground = schemes[scheme] + 1; // foreground = 숫자 색깔

	//value(borad[][]에 저장된 값)
	if (value > 0) {
		while (value--) {
			if (background + 2 < schemes[scheme] + sizeof(original)) { //original[]가 총 32개 인데 background가 배열을 초과하면 false 이다.
				background += 2;
				foreground += 2;
			}
		}
	}
	snprintf(color, length, "\033[38;5;%d;48;5;%dm", *foreground, *background); // 버퍼에 잠시 값(color)을 저장해둔다.
}

/*16013076 박재현*/
/* 명령 프롬프트창에 게임 판을 그려주는 함수*/
void drawBoard(uint8_t board[SIZE][SIZE]) {
	uint8_t x, y;
	char color[40], reset[] = "\033[m"; //reset[] = 모든 속성을 off 시킴 (초기화)
	printf("\033[H"); //커서를 왼쪽 상단 모서리로 이동

	printf("2048.c %17d pts\n\n", score);

	for (x = 0; x < SIZE; x++) {
		for (y = 0; y < SIZE; y++) {
			getColor(board[x][y], color, 40);   // 버퍼안 color의 값을 "\033[38;5;%d;48;5;%dm"로 저장
			printf("%s", color);            // color를 출력하면 그 다음 타일색이 출력됨
			printf("       ");
			printf("%s", reset);            // 색을 초기화 시킴
		}
		printf("\n");
		for (y = 0; y < SIZE; y++) {
			getColor(board[x][y], color, 40);
			printf("%s", color);
			if (board[x][y] != 0) { // board[][]의 값이 0 이면 숫자를 표현할 필요가 없으니깐
				char s[8];
				snprintf(s, 8, "%u", (uint32_t)1 << board[x][y]);   //버퍼 안 s에 비트연산 적용된 값(10진수로 생각하면 *2로 생각)이 저장
				uint8_t t = 7 - strlen(s);                     //한 타일에서 숫자칸을 제외한 숫자 양 옆 공백을 나타내기 위한 변수
				printf("%*s%s%*s", t - t / 2, "", s, t / 2, ""); //위에서 계산한 t로 앞뒤 공백을 만들고 그 사이에 숫자(변수 s)를 넣는다.
			}
			else {
				printf("   ·   ");// 빈칸을 · 으로 표기
			}

			printf("%s", reset);
		}
		printf("\n");
		for (y = 0; y < SIZE; y++) {  //위에서 반복
			getColor(board[x][y], color, 40);
			printf("%s", color);
			printf("       ");
			printf("%s", reset);
		}
		printf("\n");
	}
	printf("\n");
	printf("        ←,↑,→,↓ or q        \n");
	printf("\033[A"); // one line up
}
