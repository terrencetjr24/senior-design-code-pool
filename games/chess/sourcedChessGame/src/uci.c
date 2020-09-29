#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bk.h"
#include "board.h"
#include "move.h"
#include "perft.h"
#include "search.h"
#include "tinycthread.h"
#include "uci.h"
#include "util.h"
#include "gen.h"

#define RESET -1

static Board board;
static Search search;
static thrd_t thrd;

void handle_uci() {
    printf("id name Mister Queen\n");
    printf("id author Michael Fogleman\n");
    printf("uciok\n");
}

void handle_isready() {
    printf("readyok\n");
}

void handle_fen(char *fen) {
    board_load_fen(&board, fen);
}

void handle_startpos() {
    board_reset(&board);
}

void handle_startpos_moves(char *moves) {
    Move move;
    board_reset(&board);
    char *key;
    char *token = tokenize(moves, " ", &key);
    // while(moves != NULL) {
    //     printf("%c", moves);
    //     moves += sizeof(char);
    // }
    while (token) {
        move_from_string(&move, token);
        make_move(&board, &move);
        token = tokenize(NULL, " ", &key);
    }
}

static int thread_func(void *arg) {
    do_search(&search, &board);
    return 0;
}

static void thread_start() {
    thrd_create(&thrd, thread_func, NULL);
}

void handle_go(char *line) {
    search.uci = 1;
    search.use_book = 1;
    search.duration = 4;
    char *key;
    char *token = tokenize(line, " ", &key);
    while (token) {
        if (strcmp(token, "infinite") == 0) {
            search.duration = 0;
            search.use_book = 0;
        }
        else if (strcmp(token, "movetime") == 0) {
            char *arg = tokenize(NULL, " ", &key);
            search.duration = atoi(arg) / 1000.0;
        }
        else if (strcmp(token, "ponder") == 0) {
            return; // no pondering yet
        }
        token = tokenize(NULL, " ", &key);
    }
    thread_start();
}

void handle_stop() {
    search.stop = 1;
    thrd_join(thrd, NULL);
}

int parse_line() {
    char data[1024];
    if (fgets(data, 1024, stdin) == NULL) {
        return 0;
    }
    char *line = strip(data);
    if (strcmp(line, "uci") == 0) {
        handle_uci();
    }
    if (strcmp(line, "isready") == 0) {
        handle_isready();
    }
    if (strcmp(line, "position startpos") == 0) {
        handle_startpos();
    }
    if (starts_with(line, "position startpos moves ")) {
        handle_startpos_moves(line + 24);
    }
    if (starts_with(line, "position fen ")) {
        handle_fen(line + 13);
    }
    if (starts_with(line, "go")) {
        handle_go(line);
    }
    if (strcmp(line, "stop") == 0) {
        handle_stop();
    }
    if (strcmp(line, "quit") == 0) {
        return 0;
    }
    if (strcmp(line, "perft") == 0) {
        perft_tests();
    }
    if (strcmp(line, "bk") == 0) {
        bk_tests();
    }
    int index;
    if (sscanf(line, "test %d", &index) == 1) {
        test_position(index);
    }
    return 1;
}

void uci_main() {
    setbuf(stdout, NULL);
    board_reset(&board);

    int winner = RESET; // 0 = white; 1 = black; 2 = draw
    int userInput;
    gameState state = waitingForFirst;

    int source = RESET;
    int destination = RESET;
    unsigned char promotion = RESET;
    int index;

    Move legalMoves[MAX_MOVES];
    int numLegalMoves = 0;
    memset(legalMoves, -1, sizeof(Move) * MAX_MOVES);

    int highlightedDests[MAX_MOVES];
    int numhighlightedDests = 0;
    memset(highlightedDests, -1, sizeof(int) * MAX_MOVES);

    Move * currentMove = malloc(sizeof(Move));

    while (winner == RESET){
        userInput = getInput();
        // user is selecting the board
        if (userInput >= 0 && userInput < 64){
            switch (state){
                case waitingForFirst:
                    source = userInput;
                    numLegalMoves = gen_legal_moves(&board, legalMoves);
                    numhighlightedDests = 0;
                    for(int i = 0; i < numLegalMoves; i++){
                        if(legalMoves[i].src == source) {
                            highlightedDests[numhighlightedDests++] = legalMoves[i].dst;
                        }
                    }
                    if (numhighlightedDests == 0){
                        // Jump to error state
                        // Tell user their selection was invalid
                        break;
                    }
                    state = waitingForSecond;
                    // display highlighted squares
                    break;

                case waitingForSecond:
                    destination = userInput;
                    for(index = 0; index < numhighlightedDests; index++){
                        if (destination == highlightedDests[index])
                            break;
                    }
                    if (index == numhighlightedDests){
                        printf("Invalid selection made, try again\n");
                    }
                    // it's already being checked for a valid move, can simply check the piece and destination
                    else if(PIECE(board.squares[source]) == PAWN && ((destination < 8) || (destination > 55))) {
                        //promotion
                        state = waitingForThird;
                    }
                    else{
                        // make the desired move
                            // create a new move node (passing through the inputs and the current node)
                            // Execute the new move on the actual board
                            // Saving the move into currentMove
                        currentMove->src = source;
                        currentMove->dst = destination;
                        currentMove->promotion = EMPTY;
                        make_move(&board, currentMove);
                        // Reset selectedPiece, source, destination, and promotion to -1
                        source = destination = promotion = RESET;
                        // Then free the valid move list
                        memset(legalMoves, -1, sizeof(Move) * MAX_MOVES);
                        memset(highlightedDests, -1, sizeof(Move) * MAX_MOVES);
                        state = checking;
                        board_print(&board);
                    }
                    break;
                // Hanlding pawn promotions
                case waitingForThird:
                    // For pawn promotions Knight = 2, Bishop = 3, Rook = 4, Queen = 5
                    promotion = (unsigned char)userInput;

                    // make the desired move
                        // create a new move node (passing through the inputs and the current node)
                        // Execute the new move on the actual board
                        // Saving the move into currentMove
                    currentMove->src = source;
                    currentMove->dst = destination;
                    currentMove->promotion = promotion;
                    make_move(&board, currentMove);
                    // Reset selectedPiece, source, destination, and promotion to -1
                    source = destination = promotion = RESET;
                    // Then free the valid move list
                    memset(legalMoves, -1, sizeof(Move) * MAX_MOVES);
                    memset(highlightedDests, -1, sizeof(Move) * MAX_MOVES);
                    state = checking;
                    board_print(&board);
                    break;
                    
                default:
                    printf("invalid state or jumped into checking state too early\n");
            }
            // After every move these things will be checked
            if (state == checking){
                // Looking for checkmate
                    // look for check before jumping into this to avoid wasting time
                if(numLegalMoves == 0) {
                    if(is_check(&board)) {
                        //checkmate
                        if(board.color == BLACK) winner = 1;
                        else winner = 0;
                    }
                    else{
                        //stalemate
                        winner = 2;
                    }
                }
                // Checking for 3 fold repitions
                // winner = checkForRepetition(currentMove);
                // Looking for ...

                // Resetting state
                state = waitingForFirst;
            }
        }
        // User wants to undo first half or second half of previous move
        else if (userInput == 64){
            // If the first selection has already been recieved, then we'll respond to this request
            if (state == waitingForSecond){
                // Reset source and selectedPiece to -1
                source = RESET;
                // Then free the valid move list
                memset(legalMoves, -1, sizeof(Move) * MAX_MOVES);
                memset(highlightedDests, -1, sizeof(Move) * MAX_MOVES);
                // Reverting the game state
                state = waitingForFirst;
            }
            else if (state == waitingForThird){
                // reset destination
                destination = RESET;
                // Reverting the game state
                state = waitingForSecond;
            }
        }
        // User wants to undo the entire previous move
        // else if (userInput == 65){
        //     // undo the first (and second) selection values if there are any
        //     if ((state == waitingForSecond) | (state == waitingForThird)){
        //         // resetting source, selectedPiece, and promotion
        //         source = selectedPiece = destination = promotion = RESET;
        //         // free the validMoves list
        //         free(validMoves);
        //     }
        //     // Now undo the entire previous move regardless
        //     currentMove = undoLastMove(board, currentMove);

        //     // Reset the game state
        //     state = waitingForFirst;
        // }
	    // User wants to resign
        else if (userInput == 66){
            if (board.color)
                winner = 0;
            else
                winner = 1;
        }
    }
    printf("winner is player %d\n", winner);
}

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
