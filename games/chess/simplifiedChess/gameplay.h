#ifndef GAMEPLAY
#define GAMEPLAY

#include "board.h"
#include "move.h"

typedef enum gameState {waitingForFirst, waitingForSecond} gameState;

int playGame(Board* board, Move * currentMove);



void nextMove(Board* board, );
void undoLastMove();


//   Microcontroller speciic functions to interface between game and microcontroller
int getInput();

#endif GAMEPLAY