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