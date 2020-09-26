#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "move.h"
#include "gameplay.h"

int playGame(Board* board, Move * currentMove){
    int winner = 99; // 0 = white; 1 = black; 2 = draw
    int userInput;
    gameState state = waitingForFirst;


    int source = -1;
    int destination = -1;
    int selectedPiece;
    int * validMoves;
    int promotion = -1;

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
                    else if(PIECE(selectedPiece) == PAWN && ((COLOR(board->color) && userInput < 8) || (!COLOR(board->color) && userInput > 55))) {
                        //promotion
                        state = waitingForThird;
                    }
                    else{
                        // make the desired move
                            // create a new move node (passing through the inputs and the current node)
                            // Execute the new move on the actual board
                        // Saving the move into currentMove
                        // creating another Move node, linking it and the currentMove, and assigning current move to the new empty node
                        // Reset source and destination to -1
                        // Then free the valid move list
                    }
                    break;
                // Hanlding pawn promotions
                case waitingForThird:
                    // For pawn promotions 0 = Queen, 1 = Knight, 2 = Bishop, 3 = Rook
                    promotion = userInput;

                    // Upgrade the pawn to the desired unit
                    // make the desired move
                        // create a new move node (passing through the inputs and the current node)
                        // Execute the new move on the actual board
                    // creating another Move node, linking it and the currentMove, and assigning current move to the new empty node
                    // Reset source and destination to -1
                    // Then free the valid move list
                    break;
                    
                default:
                    printf("invalid state. Exitting\n");
                    exit(0);
            }
            // After every move these things will be checked
            // (Only want to check after a move to avoid wasted processing time)
            if ((state == waitingForSecond) || (state == waitingForThird)){
                // Looking for checkmate
                    // look for check before jumping into this to avoid wasting time
                // Looking for stalemate
                // Looking for ...
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
// For pawn promotions 0 = Queen, 1 = Knight, 2 = Bishop, 3 = Rook
*/
int getInput(){

    int value = -1;
    printf("Enter a # between 0 and 66\n");
    scanf("%d", &value);

    while(value < 0 || value > 66){
        printf("Enter a # between 0 and 66\n");
        scanf("%d", &value);
    }

    return value;
}
