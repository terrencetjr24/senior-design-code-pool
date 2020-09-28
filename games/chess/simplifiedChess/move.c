#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "move.h"

void freeMoves(Move * move) {
    Move * next = move->next;
    free(move);
    while(next != NULL){
        move = next->next;
        free(next);
        next = move;
    }
}

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
<<<<<<< HEAD
=======
/*  Utility function
// Returns: 1 if is pinning, 0 if not pinning
*/
unsigned char isPinningKing(Board* board, int location){
    return 0;
}
>>>>>>> 87321697d9800e1d6e00a9a884d44fdb9195cc0a

/*  Function for taking in the location selected and the piece and telling the user where it can move
//
//
// Returns: The code of the piece that is moveable 
*/
<<<<<<< HEAD
int* findValidMoves(Board* board, Move* lastMove, int location, unsigned char piece){
    int* moveList;
    switch(PIECE(piece)){
        case PAWN:
            moveList = validPawnMoves(board, lastMove, location);
            break;
        case KNIGHT:
            moveList = validKnightMoves(board, lastMove, location);
            break;
        case BISHOP:
            moveList = validBishopMoves(board, lastMove, location);
            break;
        case ROOK:
            moveList = validRookMoves(board, lastMove, location);
            break;
        case QUEEN:
            moveList = validQueenMoves(board, lastMove, location);
            break;
        case KING:
            moveList = validKingMoves(board, lastMove, location);
            break;
    }

    return moveList;
}

/* Function for finding the valid moves for the pawn at the given location
//
//
// Returns: a list of locations that the pawn can move to
*/ 
int* validPawnMoves(Board* board, Move* lastMove, int location){

}

/* Function for finding the valid moves for the Knight at the given location
//
//
// Returns: a list of locations that the pawn can move to
*/ 
int* validKnightMoves(Board* board, Move* lastMove, int location){

}

/* Function for finding the valid moves for the Bishop at the given location
//
//
// Returns: a list of locations that the pawn can move to
*/ 
int* validBishopMoves(Board* board, Move* lastMove, int location){

}

/* Function for finding the valid moves for the Rook at the given location
//
//
// Returns: a list of locations that the pawn can move to
*/ 
int* validRookMoves(Board* board, Move* lastMove, int location){

}

/* Function for finding the valid moves for the Queen at the given location
//
//
// Returns: a list of locations that the pawn can move to
*/ 
int* validQueenMoves(Board* board, Move* lastMove, int location){

}

/* Function for finding the valid moves for the King at the given location
//
//
// Returns: a list of locations that the pawn can move to
*/ 
int* validKingMoves(Board* board, Move* lastMove, int location){

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
    
    // calling board_set with the correct parameters 
    board_set(board, source, destination, selectedPiece);

    return newTailMove;
}

/* Function for creating the next MoveNode before it's been executed
//
// (Remember to check for a promotion)
//
// Returns: a node that will be assigned to the next move in the linked list
*/
Move * newMoveNode(Move * prevMove, int src, int dst, int selectedPiece, int promotion){

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
=======
int* findValidMoves(Board* board, int location, unsigned char piece){
    return 0;
}

void make_move(Board *board, Move *move) {
    do_move(board, move);
}

void do_move(Board *board, Move *move/*, Undo *undo*/) {
    board_set(board, move->src, EMPTY);
    if (move->promotion) {
        board_set(board, move->dst, move->promotion | board->color);
    }
    else {
        board_set(board, move->dst, move->piece);
    }
    /*board->ep = 0L;
    if (undo->piece == WHITE_PAWN) {
        bb src = BIT(move->src);
        bb dst = BIT(move->dst);
        if ((src & 0x000000000000ff00L) && (dst & 0x00000000ff000000L)) {
            board->ep = BIT(move->src + 8);
        }
        if (dst == undo->ep) {
            board_set(board, move->dst - 8, EMPTY);
        }
    }
    else if (undo->piece == BLACK_PAWN) {
        bb src = BIT(move->src);
        bb dst = BIT(move->dst);
        if ((src & 0x00ff000000000000L) && (dst & 0x000000ff00000000L)) {
            board->ep = BIT(move->src - 8);
        }
        if (dst == undo->ep) {
            board_set(board, move->dst + 8, EMPTY);
        }
    }
    else if (undo->piece == WHITE_KING) {
        board->castle &= ~CASTLE_WHITE;
        if (move->src == 4 && move->dst == 6) {
            board_set(board, 7, EMPTY);
            board_set(board, 5, WHITE_ROOK);
        }
        else if (move->src == 4 && move->dst == 2) {
            board_set(board, 0, EMPTY);
            board_set(board, 3, WHITE_ROOK);
        }
    }
    else if (undo->piece == BLACK_KING) {
        board->castle &= ~CASTLE_BLACK;
        if (move->src == 60 && move->dst == 62) {
            board_set(board, 63, EMPTY);
            board_set(board, 61, BLACK_ROOK);
        }
        else if (move->src == 60 && move->dst == 58) {
            board_set(board, 56, EMPTY);
            board_set(board, 59, BLACK_ROOK);
        }
    }*/
    if (move->src == 0 || move->dst == 0) {
        board->castle &= ~CASTLE_WHITE_QUEEN;
    }
    if (move->src == 7 || move->dst == 7) {
        board->castle &= ~CASTLE_WHITE_KING;
    }
    if (move->src == 56 || move->dst == 56) {
        board->castle &= ~CASTLE_BLACK_QUEEN;
    }
    if (move->src == 63 || move->dst == 63) {
        board->castle &= ~CASTLE_BLACK_KING;
    }
    board->color ^= BLACK;
}
>>>>>>> 87321697d9800e1d6e00a9a884d44fdb9195cc0a
