#ifndef GAMEPLAY
#define GAMEPLAY

#include "board.h"
#include "move.h"

typedef enum gameState {waitingForFirst, waitingForSecond, waitingForThird, checking} gameState;


int playGame(Board* board, Move * currentMove);


//   Microcontroller speciic functions to interface between game and microcontroller
int getInput();

#endif
