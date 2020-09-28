#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "move.h"
#include "gameplay.h"

#define RESET -1

int playGame(Board* board, Move * currentMove){
    int winner = RESET; // 0 = white; 1 = black; 2 = draw
    int userInput;
    gameState state = waitingForFirst;
<<<<<<< HEAD

    int source = RESET;
    int destination = RESET;
    int selectedPiece = RESET;
=======
    Move * nextMove = malloc(sizeof(Move));
>>>>>>> 87321697d9800e1d6e00a9a884d44fdb9195cc0a
    int * validMoves;
    int promotion = RESET;

    int lengthOfList;
    int index;

<<<<<<< HEAD
    while ((currentMove->moveNumber < MAX_MOVES) && (winner == RESET)){
=======
    while (currentMove->moveNumber < MAX_MOVES){
        //check for checkmate
        if(isCheckmate(board)) {
            winner = !(board->color);
            break;
        }
>>>>>>> 87321697d9800e1d6e00a9a884d44fdb9195cc0a
        userInput = getInput();
        // user is selecting the board
        if (userInput >= 0 && userInput < 64){
            switch (state){
                case waitingForFirst:
<<<<<<< HEAD
                    source = userInput;
                    selectedPiece = validSelection(board, source);

                    if (selectedPiece){
                        validMoves = findValidMoves(board, currentMove, source, (unsigned char)selectedPiece);
=======
                    printf("piece selection: %d\n", userInput);
                    nextMove->src = userInput;
                    nextMove->piece = validSelection(board, userInput);
                    nextMove->promotion = 0;

                    if (nextMove->piece){
                        validMoves = findValidMoves(board, userInput, (unsigned char)(nextMove->piece));
>>>>>>> 87321697d9800e1d6e00a9a884d44fdb9195cc0a
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
<<<<<<< HEAD
                    destination = userInput;
=======
                    printf("movement selection: %d\n", userInput);
                    nextMove->dst = userInput;
>>>>>>> 87321697d9800e1d6e00a9a884d44fdb9195cc0a
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
                    // it's already being checked for a valid move, can simply check the piece and destination
                    else if(PIECE(selectedPiece) == PAWN && ((destination < 8) || (destination > 55))) {
                        //promotion
                        state = waitingForThird;
                    }
                    else{
                        // make the desired move
<<<<<<< HEAD
                            // create a new move node (passing through the inputs and the current node)
                            // Execute the new move on the actual board
                            // Saving the move into currentMove
                        currentMove = makeMove(board, currentMove, source, destination, selectedPiece, promotion);
                        // Reset selectedPiece, source, destination, and promotion to -1
                        selectedPiece = source = destination = promotion = RESET;
                        // Then free the valid move list
                        free(validMoves);
                        state = checking;
                    }
                    break;
                // Hanlding pawn promotions
                case waitingForThird:
                    // For pawn promotions Knight = 2, Bishop = 3, Rook = 4, Queen = 5
                    promotion = userInput;

                    // make the desired move
                        // create a new move node (passing through the inputs and the current node)
                        // Execute the new move on the actual board
                        // Saving the move into currentMove
                    currentMove = makeMove(board, currentMove, source, destination, selectedPiece, promotion);
                    // Reset selectedPiece, source, destination, and promotion to -1
                    selectedPiece = source = destination = promotion = RESET;
                    // Then free the valid move list
                    free(validMoves);
                    state = checking;
                    break;
                    
=======
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
                    printf("promotion input: %d\n", userInput);
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
>>>>>>> 87321697d9800e1d6e00a9a884d44fdb9195cc0a
                default:
                    printf("invalid state. Exitting\n");
                    exit(0);
            }
            // After every move these things will be checked
            if (state = checking){
                // Looking for checkmate
                    // look for check before jumping into this to avoid wasting time
                if (currentMove->check == 1){
                    winner = checkForCheckMate(board, currentMove);
                }
                // Looking for stalemate
                winner = checkForStaleMate(board, currentMove);
                // Looking for castling priveleges
                checkForCastlingPriveleges(board);
                // Looking for ...

                // Resetting state
                state = waitingForFirst;
            }
        }
        // User wants to undo first half or second half of previous move
        else if (userInput == 64){
            // If the first selection has already been recieved, then we'll respond to this request
            if (state == waitingForSecond){
<<<<<<< HEAD
                // Reset source and selectedPiece to -1
                source = selectedPiece = RESET;
                // Then free the valid move list
                free(validMoves);
                // Reverting the game state
                state = waitingForFirst;
            }
            else if (state == waitingForThird){
                // reset destination
                destination = RESET;
                // Reverting the game state
                state = waitingForSecond;
=======
                // Then free the valid move list
                free(validMoves);
                // Change state back to first
                state = waitingForFirst;
>>>>>>> 87321697d9800e1d6e00a9a884d44fdb9195cc0a
            }
        }
        // User wants to undo the entire previous move
        else if (userInput == 65){
            // undo the first (and second) selection values if there are any
            if (state == waitingForSecond | state == waitingForThird){
                // resetting source, selectedPiece, and promotion
                source = selectedPiece = destination = promotion = RESET;
                // free the validMoves list
                free(validMoves);
            }
            // Now undo the entire previous move regardless
            currentMove = undoLastMove(board, currentMove);

            // Reset the game state
            state = waitingForFirst;
        }
	// User wants to resign
        else if (userInput == 66){
            if (board->color)
                winner = 0;
            else
                winner = 1;
        }

        board->color = !(board->color);
    }
    return winner;
}


<<<<<<< HEAD
=======
void nextMove(Board * board){

}

void undoLastMove(){

}

int isCheckmate(Board * board) {
    return 0;
}

>>>>>>> 87321697d9800e1d6e00a9a884d44fdb9195cc0a
//////////////////////////////////////////////////////
// Microcontroller Functions
//////////////////////////////////////////////////////
/*
//  Function to allow the user to make the next move, to undo the previous move, or to resign
// 0 - 63 = a desired location (user is initiating a move or finishing a move)
// 64 = undo first half or second halaf of move selection 
// 65 = undo the entire previous move
// 66 = resign the game
// 
// For pawn promotions 0 = Queen, 1 = Knight, 2 = Bishop, 3 = Rook
//
// When using with the microcontroller, the above integers are only what the 
// gameplay function wants. The microcontroller can go about translating these
// in whatever way it would like
*/
int getInput(){
<<<<<<< HEAD

    int value = -1;
    printf("Enter a # between 0 and 66\n");
    scanf("%d", &value);
=======
    int value = -1;
    printf("Enter a # between 0 and 66\n");
    scanf("%d", &value);

    while(value < 0 || value > 66){
        printf("Enter a # between 0 and 66\n");
        scanf("%d", &value);
    }
>>>>>>> 87321697d9800e1d6e00a9a884d44fdb9195cc0a

    while(value < 0 || value > 66){
        printf("Enter a # between 0 and 66\n");
        scanf("%d", &value);
    }

    return value;
}
