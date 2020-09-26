#ifndef MOVE_H
#define MOVE_H

#include "board.h"

#define MAX_MOVES 256
#define SAVED_MOVES 6



typedef struct {
    unsigned char src;
    unsigned char dst;
    unsigned char promotion;
    unsigned char capturedPiece;
    unsigned char castle; // Will use the board defined values to tell if it was queen side or king side
    unsigned char playerColor;  // The color of the player who made the move (redundancy)

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

int validSelection(Board *board, int location);

Move * newMoveNode(Move * currentMove, int src, int dst, int selectedPiece, int promotion);
void makeMove(Board *board, Move *move);

void undoHalfMove();
Move * undoLastMove(Board* board, Move* prevMove);



void do_null_move(Board *board, Undo *undo);
void undo_null_move(Board *board, Undo *undo);
void do_move(Board *board, Move *move, Undo *undo);
void undo_move(Board *board, Move *move, Undo *undo);
int score_move(Board *board, Move *move);

void move_to_string(Move *move, char *str);
void move_from_string(Move *move, const char *str);
void notate_move(Board *board, Move *move, char *result);
void print_move(Board *board, Move *move);
int parse_move(Board *board, const char *notation, Move *move);
int parse_pgn(Board *board, const char *pgn);

#endif