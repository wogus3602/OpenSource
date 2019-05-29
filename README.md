2048.c
======
slack 주소 https://opensourcechat-group.slack.com/messages/DK41QTEG6/
======
![screenshot](screenshot.png)

Console version of the game "2048" for GNU/Linux

### Gameplay

You can move the tiles in four directions using the arrow keys: up, down, left, and right. All numbers on the board will slide into that direction until they hit the wall and if they bump into each other then two numbers will be combined into one if they have the same value. Each number will only be combined once per move. Every move a new number 2 or 4 appears. If you have a 2048 on the board you have won, but you lose once the board is full and you cannot make a move. 

### Requirements

- C compiler

Tested on: GNU/Linux, FreeBSD, OpenBSD

### Installation

```
git clone https://github.com/wogus3602/OpenSource.git
gcc -o 2048 2048.c
./2048
```

### Running

The game supports different color schemes. This depends on ANSI support for 88 or 256 colors. If there are not enough colors supported the game will fallback to black and white (still very much playable). For the original color scheme run:

```
./2048
```
For the black-to-white color scheme (requires 256 colors):

```
./2048 blackwhite
```

For the blue-to-red color scheme (requires 256 colors):

```
./2048 bluered
```

### Contributing

Contributions are very welcome. Always run the tests before committing using:

```
$ ./2048 test
All 13 tests executed successfully
```
----------------------------------------------------------------------------------------
readme (한국어)

2048.c
======
slack 주소 https://opensourcechat-group. slack.com/messages/DK41QTEG6/


======

![스크린샷](스크린샷.png)

GNU/Linux용 게임 콘솔 버전

### 게임플레이

위쪽, 아래쪽, 왼쪽, 오른쪽 화살표 키를 사용하여 타일을 네 방향으로 이동할 수 있다. 보드의 모든 숫자는 벽에 부딪힐 때까지 그 방향으로 미끄러져 들어갈 것이고 만약 그들이 서로 부딪친다면, 두 개의 숫자가 같은 값을 가지고 있다면 하나로 합쳐질 것이다. 각각의 숫자는 한 번에 한 번만 결합될 것이다. 움직일 때마다 2번이나 4번이 나타난다. 만약 당신이 판 위에 2048점을 가지고 있다면, 당신은 이겼지만, 일단 판이 꽉 차서 움직일 수 없게 되면 진다. 

### 요구사항

- C 컴파일러

테스트 대상: GNU/리눅스, FreeBSD, OpenBSD

### 설치

```
Git 클론 https://github.com/wogus3602/OpenSource.git
gcc -o 2048 2048.c
./2048
```

### 러닝

그 게임은 다양한 색채 배열을 지원한다. 이것은 88색이나 256색에 대한 ANSI 지원에 따라 달라진다. 지원되는 색상이 충분하지 않으면 게임은 흑백으로 되돌아갈 것이다. 원래 색상표 실행의 경우:

```
./2048
```
흑백 색상표(256색 필요):

```
./2048년 흑백
```

파란색에서 빨간색까지의 색상표(색상 256개 필요):

```
./2048년 청색
```

### 기여

공헌은 매우 환영한다. 다음을 사용하기 전에 항상 테스트를 실행하십시오.

```
$ ./2048 테스트
모든 13개의 테스트가 성공적으로 실행됨
```
