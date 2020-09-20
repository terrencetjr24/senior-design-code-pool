#include <stdio.h>
#include <stdlib.h>
#include "board.h"

struct Board board;

int main(int argc, char **argv) {
    board_clear(&board);
    board_reset(&board);
    board_print(&board);
    return 0;
}
