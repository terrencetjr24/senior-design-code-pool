#ifndef GAMEPLAY
#define GAMEPLAY

#include "board.h"
#include "move.h"

typedef enum gameState {waitingForFirst, waitingForSecond, waitingForThird} gameState;

int playGame(Board* board, Move * currentMove);
int isCheckmate(Board * board);


void nextMove(Board* board);
void undoLastMove();


//   Microcontroller speciic functions to interface between game and microcontroller
int getInput();

#endif