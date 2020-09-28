#ifndef GAMEPLAY
#define GAMEPLAY

#include "board.h"
#include "move.h"

<<<<<<< HEAD
typedef enum gameState {waitingForFirst, waitingForSecond, waitingForThird, checking} gameState;


int playGame(Board* board, Move * currentMove);
=======
typedef enum gameState {waitingForFirst, waitingForSecond, waitingForThird} gameState;

int playGame(Board* board, Move * currentMove);
int isCheckmate(Board * board);


void nextMove(Board* board);
void undoLastMove();
>>>>>>> 87321697d9800e1d6e00a9a884d44fdb9195cc0a


//   Microcontroller speciic functions to interface between game and microcontroller
int getInput();

#endif