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

}

/* Function for looking for stalemates
//
// -1 = no stalemate
// 2 = stalemate
//
// Returnn: winner value
*/
int checkForStaleMate(Board* board, Move* currentMove){

}

// Looking for castling priveleges
/* Function for looking for castle priveleges
//
// Updates the board directly
// (Values to update by are in board.h)
// Returns: None
*/
void checkForCastlingPriveleges(Board* board){

}