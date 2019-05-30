#ifndef _ENDGAME_H

#define _ENDGAME_H

#include "Size.h"
#include "ScoreAndScheme.h"
#include "Move.h"

uint8_t countEmpty(uint8_t board[SIZE][SIZE]);
bool gameEnded(uint8_t board[SIZE][SIZE]);
void setBufferedInput(bool enable);
void signal_callback_handler(int signum);
bool findPairDown(uint8_t board[SIZE][SIZE]);
#endif
