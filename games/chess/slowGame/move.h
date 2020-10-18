#ifndef MOVE_H
#define MOVE_H

#include "board.h"

#define MAX_MOVES 256
#define SAVED_MOVES 6


typedef struct Move {
    unsigned char src;
    unsigned char dst;
    unsigned char piece;
    unsigned char promotion;
    unsigned char capturedPiece;
    unsigned char castle; // Will use the board defined values to tell if it was queen side or king side
    unsigned char playerColor;  // The color of the player who made the move (redundancy)

    int moveNumber;

    unsigned char check; // 1 = check is given, 2 = check not given

    struct Move * prev;
    struct Move * next;
} Move;

typedef struct {
    unsigned char piece;
    unsigned char capture;
    unsigned char castle;
} Undo;

int validSelection(Board *board, int location);
int* findValidMoves(Board* board, Move* lastMove, int location, unsigned char piece, int * lengthOfValidMoves);
int* validPawnMoves(Board* board, Move* lastMove, int location, int * lengthOfValidMoves);
int validatePawnMove(Board * board, int src, int dest, int * lengthOfValidMoves);
int* validKnightMoves(Board* board, Move* lastMove, int location, int * lengthOfValidMoves);
int* validBishopMoves(Board* board, Move* lastMove, int location, int * lengthOfValidMoves);
int* validRookMoves(Board* board, Move* lastMove, int location, int * lengthOfValidMoves);
int* validQueenMoves(Board* board, Move* lastMove, int location, int * lengthOfValidMoves);
int* validKingMoves(Board* board, Move* lastMove, int location, int * lengthOfValidMoves);

Move * newMoveNode(Move * currentMove, int src, int dst, int selectedPiece, int promotion);
Move* makeMove(Board* board, Move* currentMove, int source, int destination, int selectedPiece, int promotion);

Move * undoLastMove(Board* board, Move* prevMove);


#endif
