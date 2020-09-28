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
<<<<<<< HEAD
    unsigned char capturedPiece;
    unsigned char castle; // Will use the board defined values to tell if it was queen side or king side
    unsigned char playerColor;  // The color of the player who made the move (redundancy)

=======
>>>>>>> 87321697d9800e1d6e00a9a884d44fdb9195cc0a
    unsigned char moveNumber;

    unsigned char check; // 1 = check is given, 2 = check not given

    struct Move * prev;
    struct Move * next;
} Move;

typedef struct {
    unsigned char piece;
    unsigned char capture;
    unsigned char castle;
} Undo;

<<<<<<< HEAD
int validSelection(Board *board, int location);
int* findValidMoves(Board* board, Move* lastMove, int location, unsigned char piece);
int* validPawnMoves(Board* board, Move* lastMove, int location);
int* validKnightMoves(Board* board, Move* lastMove, int location);
int* validBishopMoves(Board* board, Move* lastMove, int location);
int* validRookMoves(Board* board, Move* lastMove, int location);
int* validQueenMoves(Board* board, Move* lastMove, int location);
int* validKingMoves(Board* board, Move* lastMove, int location);

Move * newMoveNode(Move * currentMove, int src, int dst, int selectedPiece, int promotion);
Move* makeMove(Board* board, Move* currentMove, int source, int destination, int selectedPiece, int promotion);

Move * undoLastMove(Board* board, Move* prevMove);
=======
int* findValidMoves(Board* board, int location, unsigned char piece);
int validSelection(Board *board, int location);
void freeMoves(Move * move);

void make_move(Board *board, Move *move);
void do_null_move(Board *board, Undo *undo);
void undo_null_move(Board *board, Undo *undo);
void do_move(Board *board, Move *move/*, Undo *undo*/);
void undo_move(Board *board, Move *move, Undo *undo);
int score_move(Board *board, Move *move);

void move_to_string(Move *move, char *str);
void move_from_string(Move *move, const char *str);
void notate_move(Board *board, Move *move, char *result);
void print_move(Board *board, Move *move);
int parse_move(Board *board, const char *notation, Move *move);
int parse_pgn(Board *board, const char *pgn);
>>>>>>> 87321697d9800e1d6e00a9a884d44fdb9195cc0a

#endif