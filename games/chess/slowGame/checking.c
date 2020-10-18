#include "board.h"
#include "move.h"


//looking for checkmate
//lookgng for stalemate
//looking for castling privileges


/* Function for checking if the game has reached a check
// 
// -1 = there's been no checkmate
// 0 = white wins
// 1 = black wins 
//
// Returns: winner value
*/
int checkForCheckMate(Board *board, Move* currentMove){
    return -1;
}

/* Function for checking if there is a check
// 
// 0 = no check
// 1 = there is a check on the input color
//
// Returns: check value
*/
int isCheck(Board *board, int checkingColor){
    return 0;
}

/* Function for looking for stalemates
//
// -1 = no stalemate
// 2 = stalemate
//
// Returnn: winner value
*/
int checkForStaleMate(Board* board, Move* currentMove){
    return -1;
}

/* Function for looking for castle priveleges
//
// Updates the board directly
// (Values to update by are in board.h)
// Returns: None
*/
void checkForCastlingPriveleges(Board* board){
    return;
}

/* Function for checking for 3 fold repition
// -1 = no stalemate
// 2 = draw
// 
// Return: winner value
*/
int checkForRepetition(Move* currentMove){
    return -1;
}
