#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "move.h"

/*  Function for taking in the location selected and telling the user if there is a moveable piece there
//
//  Only checks that the current color can move that piece and that the piece is not pinning the current
//  color's king
//
// Returns: The code of the piece that is moveable, or zero if it's not moveable
*/
int validSelection(Board *board, int location){
    if ((board->color) != (COLOR(board->squares[location]))) {
        return 0;
    }
    return board->squares[location];
}

/*  Function for taking in the location selected and the piece and telling the user where it can move
//
//  Only checks that the current color can move that piece and that 
//
// Returns: The code of the piece that is moveable 
*/
int* findValidMoves(Board* board, int location, unsigned char piece){
    
}

/* Function for creating the next MoveNode before it's been executed
//
// Returns: a node that will be assigned to the next move in the linked list
*/
Move * newMoveNode(Move * currentMove, int src, int dst, int selectedPiece, int promotion){

}
/* Function for executing the move stored in the Move Node.
// 
// Essentially, used to update the board. 
// Best to keep in this file to keep with the other move functions
*/ 
void makeMove(Board *board, Move *move) {
 
}

// Shouldn't be necessary if we only create nodes and data when necessary
// (Likely redundant/useless)
void undoHalfMove(){

}

/* Function to undo the entire last move and return the previous 
// move to the tail of the move list
//
// Returns: move node of the previous move
*/

Move* undoLastMove(Board* board, Move* prevMove){

}

/*  Utility function
// Returns: 1 if is pinning, 0 if not pinning
*/
unsigned char isPinningKing(Board* board, int location){

}