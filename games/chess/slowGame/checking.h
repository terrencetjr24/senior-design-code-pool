#ifndef CHECKING_H
#define CHECKING_H

#include "board.h"
#include "move.h"

int checkForCheckMate(Board *board, Move* currentMove);
int checkForStaleMate(Board* board, Move* currentMove);
void checkForCastlingPriveleges(Board* board);
int checkForRepetition(Move* currentMove);
int isCheck(Board *board, int checkingColor);

#endif
