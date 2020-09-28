#include <stdio.h>
#include <string.h>
#include "board.h"

#define NO_SRC -1

void board_clear(Board *board) {
    memset(board, 0, sizeof(Board));
}

void board_reset(Board *board) {
    board_clear(board);
    for (int file = 0; file < 8; file++) {
        board_set(board, RF(1, file), NO_SRC, WHITE_PAWN);
        board_set(board, RF(6, file), NO_SRC, BLACK_PAWN);
    }
    board_set(board, RF(0, 0), NO_SRC, WHITE_ROOK);
    board_set(board, RF(0, 1), NO_SRC, WHITE_KNIGHT);
    board_set(board, RF(0, 2), NO_SRC, WHITE_BISHOP);
    board_set(board, RF(0, 3), NO_SRC, WHITE_QUEEN);
    board_set(board, RF(0, 4), NO_SRC, WHITE_KING);
    board_set(board, RF(0, 5), NO_SRC, WHITE_BISHOP);
    board_set(board, RF(0, 6), NO_SRC, WHITE_KNIGHT);
    board_set(board, RF(0, 7), NO_SRC, WHITE_ROOK);
    board_set(board, RF(7, 0), NO_SRC, BLACK_ROOK);
    board_set(board, RF(7, 1), NO_SRC, BLACK_KNIGHT);
    board_set(board, RF(7, 2), NO_SRC, BLACK_BISHOP);
    board_set(board, RF(7, 3), NO_SRC, BLACK_QUEEN);
    board_set(board, RF(7, 4), NO_SRC, BLACK_KING);
    board_set(board, RF(7, 5), NO_SRC, BLACK_BISHOP);
    board_set(board, RF(7, 6), NO_SRC, BLACK_KNIGHT);
    board_set(board, RF(7, 7), NO_SRC, BLACK_ROOK);
}

void board_set(Board *board, int src_sq, int dest_sq, int piece) {
    //Save the previous piece and move current piece there
    int previousPiece = board->squares[dest_sq];
    board->squares[dest_sq] = piece;


    if (src_sq != -1)
        board->squares[src_sq] = EMPTY;

    //If there was a piece
    if (previousPiece){
        //If the previous piece was black
        if (COLOR(previousPiece)) {
            switch (PIECE(previousPiece)) {
                case PAWN:
                    board->lostPawns_black++;
                    break;
                case KNIGHT:
                    board->lostKnights_black++;
                    break;
                case BISHOP:
                    board->lostBishops_black++;
                    break;
                case ROOK:
                    board->lostRooks_black++;
                    break;
                case QUEEN:
                    board->lostQueens_black++;
                    break;
                case KING:
                    //Shouldn't occur normally
                    board->lostKings_black++;
                    break;
            }
        }
        //If the previous pice was white
        else{
            switch (PIECE(previousPiece)) {
                case PAWN:
                    board->lostPawns_white++;
                    break;
                case KNIGHT:
                    board->lostKnights_white++;
                    break;
                case BISHOP:
                    board->lostBishops_white++;
                    break;
                case ROOK:
                    board->lostRooks_white++;
                    break;
                case QUEEN:
                    board->lostQueens_white++;
                    break;
                case KING:
                    //Shouldn't occur normally
                    board->lostKings_white++;
                    break;
            }
        }
    }

}

void board_print(Board *board) {
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            char c;
            int piece = board->squares[RF(rank, file)];
            switch (PIECE(piece)) {
                case EMPTY:  c = '.'; break;
                case PAWN:   c = 'P'; break;
                case KNIGHT: c = 'N'; break;
                case BISHOP: c = 'B'; break;
                case ROOK:   c = 'R'; break;
                case QUEEN:  c = 'Q'; break;
                case KING:   c = 'K'; break;
            };
            if (COLOR(piece)) {
                c |= 0x20;
            }
            putchar(c);
        }
        putchar('\n');
    }
    putchar('\n');
}
