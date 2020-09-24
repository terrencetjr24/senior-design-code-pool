#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "move.h"
#include "gameplay.h"

int playGame(Board* board, Move * currentMove){
    int winner = 99; // 1 = black -- 0 = white
    int userInput;
    gameState state = waitingForFirst;


    int source = -1;
    int destination = -1;
    int selectedPiece;
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
                    source = userInput;
                    selectedPiece = validSelection(board, source);

                    if (selectedPiece){
                        validMoves = findValidMoves(board, source, (unsigned char)selectedPiece);
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
                    destination = userInput;
                    lengthOfList = sizeof(validMoves) / sizeof(int);
                    for(index = 0; index < lengthOfList; index++){
                        if (destination == validMoves[index])
                            break;
                    }
                    if (index == lengthOfList){
                        print("Invalid selection made, try again\n");
                    }
                    else{
                        // make the desired move
                        // Saving the move into currentMove
                        // creating another Move node, linking it and the currentMove, and assigning current move to the new empty node
                        // Reset source and destination to -1
                        // Then free the valid move list
                    }
                    break;
                    
                default:
                    printf("invalid state. Exitting\n");
                    exit(0);
            }
        }
        // User wants to undo first half of previous move
        else if (userInput == 64){
            // If the first selection has already been recieved, then we'll respond to this request
            if (state == waitingForSecond){
                // Reset source and destination to -1
                // Then free the valid move list
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


void nextMove(){

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
