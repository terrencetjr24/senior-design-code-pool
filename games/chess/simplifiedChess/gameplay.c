#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "move.h"
#include "gameplay.h"

int playGame(Board* board, Move * currentMove){
    int winner = 99; // 1 = black -- 0 = white
    int userInput;
    gameState state = waitingForFirst;
    Move * nextMove = malloc(sizeof(Move));
    int * validMoves;

    int lengthOfList;
    int index;

    while (currentMove->moveNumber < MAX_MOVES){
        userInput = getInput();
        // user is selecting the board
        if (userInput >= 0 && userInput < 64){
            switch (state){
                case waitingForFirst:
                    printf("first input\n");
                    nextMove->src = userInput;
                    nextMove->piece = validSelection(board, userInput);
                    nextMove->promotion = 0;

                    if (nextMove->piece){
                        validMoves = findValidMoves(board, userInput, (unsigned char)(nextMove->piece));
                        if (validMoves == NULL){
                            printf("no possible moves, try again\n");
                            break;
                        }
                        state = waitingForSecond;
                    }
                    else{
                        printf("Invalid Piece, try again\n");
                    }
                    break;

                case waitingForSecond:
                    printf("second input\n");
                    nextMove->dst = userInput;
                    lengthOfList = sizeof(validMoves) / sizeof(int);
                    for(index = 0; index < lengthOfList; index++){
                        if (userInput == validMoves[index])
                            break;
                    }
                    if (index == lengthOfList){
                        printf("Invalid selection made, try again\n");
                    }
                    else if(PIECE(nextMove->piece) == PAWN && ((COLOR(board->color) && userInput < 8) || (!COLOR(board->color) && userInput > 55))) {
                        //promotion
                        state = waitingForThird;
                    }
                    else{
                        // make the desired move
                        do_move(board, nextMove);
                        // Saving the move into currentMove
                        currentMove->next = nextMove;
                        nextMove->prev = currentMove;
                        currentMove = nextMove;
                        nextMove = NULL;
                        // Then free the valid move list
                        free(validMoves);
                    }
                    break;
                
                case waitingForThird:
                    printf("promotion input\n");
                    nextMove->promotion = userInput;

                    // make the desired move
                    do_move(board, nextMove);
                    // creating another Move node, linking it and the currentMove, and assigning current move to the new empty node
                    currentMove->next = nextMove;
                    nextMove->prev = currentMove;
                    currentMove = nextMove;
                    currentMove->next = malloc(sizeof(Move));
                    nextMove = currentMove->next;
                    // Then free the valid move list
                    free(validMoves);
                default:
                    printf("invalid state. Exitting\n");
                    exit(0);
            }
        }
        // User wants to undo first half of previous move
        else if (userInput == 64){
            // If the first selection has already been recieved, then we'll respond to this request
            if (state == waitingForSecond){
                // Then free the valid move list
                free(validMoves);
                // Change state back to first
                state = waitingForFirst;
            }
        }
        // User wants to undo the entire previous move
        else if (userInput == 65){
            // undo the first selection
            if (state == waitingForSecond){
                
            }

            // Now undo the entire previous move regardless
        }
	// User wants to resign
        else if (userInput == 66){
            if (board->color)
                winner = 0;
            else
                winner = 1;
            break;
        }
    }

    return winner;
}


void nextMove(Board * board){

}

void undoLastMove(){

}

//////////////////////////////////////////////////////
// Microcontroller Functions
//////////////////////////////////////////////////////
/*
//  Function to allow the user to make the next move, to undo the previous move, or to resign
// 0 - 63 = a desired location (user is initiating a move or finishing a move)
// 64 = undo first half of move selection 
// 65 = undo the entire previous move
// 66 = resign the game
// 
*/
int getInput(){
    int value;

    value = 8; //Just for testing

    return value;

}
