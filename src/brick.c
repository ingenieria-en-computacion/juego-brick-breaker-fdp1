#include "brick.h"

/* Matriz global de ladrillos */
static Brick bricks[BRICK_ROWS][BRICK_COLS];

void bricks_init() {
    for (int r = 0; r < BRICK_ROWS; r++) {
        for (int c = 0; c < BRICK_COLS; c++) {
            bricks[r][c].active = 1;
        }
    }
}

Brick (*bricks_get())[BRICK_COLS] {
    return bricks;
}

void brick_destroy(int row, int col) {
    if (row >= 0 && row < BRICK_ROWS && col >= 0 && col < BRICK_COLS) {
        bricks[row][col].active = 0;
    }
}
