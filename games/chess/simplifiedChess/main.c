#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "move.h"
#include "gameplay.h"

//test

unsigned char moveNumber;

int main(int argc, char **argv) {
    Board* board = malloc(sizeof(Board));
    if (board == NULL){
        printf("Failed to allocate memory\n");
    }
    
    Move* firstMove = malloc(sizeof(Move));

    board_clear(board);
    board_reset(board);
    board_print(board);

    int result = 3; //0 = white won; 1 - black won; 2 - tie/stalemate
    
    // Game loop
    while(1){
        result = playGame(board, firstMove);
        if (result == 1){
            printf("Black won!!\n");
            break;
        }
        else if (result == 0){
            printf("White won!!\n");
            break;
        }
        else if (result == 2){
            printf("Draw game...\n");
            break;
        }
        else{
            printf("Something went wrong. Exitting");
            break;
        }
    }
    free(board);
    // Free the moveList (make function for this)
    return 0;
}
