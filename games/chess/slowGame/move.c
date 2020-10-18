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
//
// Returns: The code of the piece that is moveable 
*/
int* findValidMoves(Board* board, Move* lastMove, int location, unsigned char piece, int * lengthOfValidMoves){
    int* moveList;
    switch(PIECE(piece)){
        case PAWN:
            moveList = validPawnMoves(board, lastMove, location, lengthOfValidMoves);
            break;
        case KNIGHT:
            moveList = validKnightMoves(board, lastMove, location, lengthOfValidMoves);
            break;
        case BISHOP:
            moveList = validBishopMoves(board, lastMove, location, lengthOfValidMoves);
            break;
        case ROOK:
            moveList = validRookMoves(board, lastMove, location, lengthOfValidMoves);
            break;
        case QUEEN:
            moveList = validQueenMoves(board, lastMove, location, lengthOfValidMoves);
            break;
        case KING:
            moveList = validKingMoves(board, lastMove, location, lengthOfValidMoves);
            break;
    }

    return moveList;
}

/* Function for finding the valid moves for the pawn at the given location
//
//
// Returns: a list of locations that the pawn can move to
*/ 
int* validPawnMoves(Board* board, Move* lastMove, int location, int * numOfMoves){
    // Holder array
    int moves[4] = {-1};
    int *retMoves;
    *numOfMoves = 0;

    // If the current player is white
    if(COLOR(board->color) == WHITE){
        // if the pawn is on the home row
        if(location / 8 == 1){
            if(board->squares[location + 8] == EMPTY && board->squares[location + 16] == EMPTY){
                moves[(*numOfMoves)++] = location + 16;
            }
        }
        // Checking for en passant capture
        else if(location / 8 == 4 && lastMove->piece == PAWN && lastMove->src / 8 == 6 && lastMove->dst / 8 == 4) {
            if(lastMove->dst == location + 1){
                moves[(*numOfMoves)++] = location + 9;
            }
            if(lastMove->dst == location - 1){
                moves[(*numOfMoves)++] = location + 7;
            }
        }
        // ALWAYS, checking directly in front of the pawn
        if(board->squares[location + 8] == EMPTY)  {
            moves[(*numOfMoves)++] = location + 8;
        }

        // Checking the forward diagonals for capturable pieces
        if(location % 8 != 7 && COLOR(board->squares[location + 9]) != WHITE && board->squares[location + 9] != EMPTY){
            moves[(*numOfMoves)++] = location + 9;
        }
        if(location % 8 != 0 && COLOR(board->squares[location + 7]) != WHITE && board->squares[location + 7] != EMPTY){
            moves[(*numOfMoves)++] = location + 7;
        }
    }
    // If the current player is black
    else{
        // If the pawn is on teh home row
        if(location / 8 == 6){
            if(board->squares[location - 8] == EMPTY && board->squares[location - 16] == EMPTY){
                moves[(*numOfMoves)++] = location - 16;
            }
        }
        // Checking for en passant capture
        else if(location / 8 == 3 && lastMove->piece == PAWN && lastMove->src / 8 == 1 && lastMove->dst / 8 == 3) {
            if(lastMove->dst == location + 1){
                moves[(*numOfMoves)++] = location - 7;
            }
            if(lastMove->dst == location - 1){
                moves[(*numOfMoves)++] = location - 9;
            }
        }
        // ALWAYS, checking directly in front of the pawn
        if(board->squares[location - 8] == EMPTY)  {
            moves[(*numOfMoves)++] = location - 8;
        }
        // Checking the forward diagonals for capturable pieces
        if(location % 8 != 7 && COLOR(board->squares[location - 7]) != BLACK && board->squares[location - 7] != EMPTY){
            moves[(*numOfMoves)++] = location - 7;
        }
        if(location % 8 != 0 && COLOR(board->squares[location - 9]) != BLACK && board->squares[location - 9] != EMPTY){
            moves[(*numOfMoves)++] = location - 9;
        }
    }

    // Copy from holder array to the array being returned
    retMoves = malloc((*numOfMoves) * sizeof(int));
    for(int i = 0; i < *numOfMoves; i++){
        retMoves[i] = moves[i];
    }
    return retMoves;
}

/* Function for finding the valid moves for the Knight at the given location
//
//
// Returns: a list of locations that the pawn can move to
*/ 
int* validKnightMoves(Board* board, Move* lastMove, int location, int * numOfMoves){
    return NULL;
}

/* Function for finding the valid moves for the Bishop at the given location
//
//
// Returns: a list of locations that the pawn can move to
*/ 
int* validBishopMoves(Board* board, Move* lastMove, int location, int * numOfMoves){
    return NULL;
}

/* Function for finding the valid moves for the Rook at the given location
//
//
// Returns: a list of locations that the pawn can move to
*/ 
int* validRookMoves(Board* board, Move* lastMove, int location, int * numOfMoves){
    return NULL;
}

/* Function for finding the valid moves for the Queen at the given location
//
//
// Returns: a list of locations that the pawn can move to
*/ 
int* validQueenMoves(Board* board, Move* lastMove, int location, int * numOfMoves){
    return NULL;
}

/* Function for finding the valid moves for the King at the given location
//
//
// Returns: a list of locations that the pawn can move to
*/ 
int* validKingMoves(Board* board, Move* lastMove, int location, int * numOfMoves){
    return NULL;
}

/* Function for executing the move stored in the move Node.
// 
// Creates a new move Node and links it to the end of the current node
// then calls board_set to update the board
// 
// (Remember to check for a promotion)
//
// Returns: the new tail of the doubly linked list
*/ 
Move* makeMove(Board* board, Move* prevMove, int source, int destination, int selectedPiece, int promotion){
    Move* newTailMove;

    // calling newMoveNode
        // Creates a new node and puts it at the end of the list and returns that pointer
        // Linking the newMoveNode to the end of lastMove
    newTailMove = newMoveNode(prevMove, source, destination, selectedPiece, promotion);
    
    // calling board set to place a piece in the destination
    board_set(board, destination, selectedPiece);
    // calling board set to make the source location empty
    board_set(board, source, EMPTY);

    // Maniupulate board as necessarry
        // Change color of the board (whichever user's turn it is)
        // Updating the move number (increment with each move)
        // If the king moved, make sure to update this in the board

    return newTailMove;
}

/* Function for creating the next MoveNode before it's been executed
//
// (Remember to check for a promotion)
//
// Returns: a node that will be assigned to the next move in the linked list
*/
Move * newMoveNode(Move * prevMove, int src, int dst, int selectedPiece, int promotion){
    return NULL;
}

/* Function to undo the entire last move and return the previous 
// move to the tail of the move list
//
//
// Returns: move node of the previous move
*/

Move* undoLastMove(Board* board, Move* prevMove){

    // Maniupulate board as necessarry
        // Change color of the board (whichever user's turn it is)
        // Updating the move number (decrement with each undo)


    return NULL;
}