#ifndef BOARD_H
#define BOARD_H

#define WHITE 0x00
#define BLACK 0x10

#define EMPTY 0x00
#define PAWN 0x01
#define KNIGHT 0x02
#define BISHOP 0x03
#define ROOK 0x04
#define QUEEN 0x05
#define KING 0x06

#define WHITE_PAWN 0x01
#define WHITE_KNIGHT 0x02
#define WHITE_BISHOP 0x03
#define WHITE_ROOK 0x04
#define WHITE_QUEEN 0x05
#define WHITE_KING 0x06

#define BLACK_PAWN 0x11
#define BLACK_KNIGHT 0x12
#define BLACK_BISHOP 0x13
#define BLACK_ROOK 0x14
#define BLACK_QUEEN 0x15
#define BLACK_KING 0x16

#define PIECE(x) ((x) & 0x0f)
#define COLOR(x) ((x) & 0x10)

#define RF(rank, file) (((rank)*8) + (file))

struct Board{
    int squares[64];
    int color;
    int lostPawns_black;
    int lostRooks_black;
    int lostBishops_black;
    int lostKnights_black;
    int lostQueens_black;
    int lostKings_black;
    int lostPawns_white;
    int lostRooks_white;
    int lostBishops_white;
    int lostKnights_white;
    int lostQueens_white;
    int lostKings_white;
 
};

void board_clear(struct Board *board);
void board_reset(struct Board *board);
void board_set(struct Board *board, int sq, int piece);
void board_print(struct Board *board);
//void board_load_fen(Board *board, char *fen);

#endif