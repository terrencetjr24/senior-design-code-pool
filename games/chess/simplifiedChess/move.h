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
    unsigned char moveNumber;

    struct Move * prev;
    struct Move * next;
} Move;

typedef struct {
    unsigned char piece;
    unsigned char capture;
    unsigned char castle;
} Undo;

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

#endif