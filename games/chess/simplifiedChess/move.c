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
/*  Utility function
// Returns: 1 if is pinning, 0 if not pinning
*/
unsigned char isPinningKing(Board* board, int location){
    return 0;
}

/*  Function for taking in the location selected and the piece and telling the user where it can move
//
//  Only checks that the current color can move that piece and that 
//
// Returns: The code of the piece that is moveable 
*/
int* findValidMoves(Board* board, int location, unsigned char piece){
    return 0;
}

void make_move(Board *board, Move *move) {
    //Undo undo; // throw-away
    //do_move(board, move, &undo);
}