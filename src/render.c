#include <stdio.h>
#include "render.h"
#include "paddle.h"
#include "ball.h"
#include "brick.h"

#define SCREEN_WIDTH  33
#define SCREEN_HEIGHT 20

void render_frame() {
    char screen[SCREEN_HEIGHT][SCREEN_WIDTH + 1];

    for (int r = 0; r < SCREEN_HEIGHT; r++) {
        for (int c = 0; c < SCREEN_WIDTH; c++) screen[r][c] = ' ';
        screen[r][SCREEN_WIDTH] = '\0';
    }

    /* bordes */
    for (int c = 0; c < SCREEN_WIDTH; c++) screen[0][c] = '#';
    for (int r = 0; r < SCREEN_HEIGHT; r++) {
        screen[r][0] = '#';
        screen[r][SCREEN_WIDTH - 1] = '#';
    }

    /* ladrillos */
    Brick (*bricks)[BRICK_COLS] = bricks_get();
    const int BX = 2, BY = 2, BW = 2, SP = 1;
    for (int r = 0; r < BRICK_ROWS; r++) {
        for (int c = 0; c < BRICK_COLS; c++) {
            if (!bricks[r][c].active) continue;
            int x = BX + c * (BW + SP);
            int y = BY + r;
            if (y >= 0 && y < SCREEN_HEIGHT && x >= 1 && (x+1) < SCREEN_WIDTH-1) {
                screen[y][x] = '[';
                screen[y][x+1] = ']';
            }
        }
    }

    /* plataforma */
    Paddle* p = paddle_get();
    if (p != NULL) {
        int py = SCREEN_HEIGHT - 2;
        int left = p->x - (p->width / 2);
        int right = left + p->width - 1;
        if (left < 1) left = 1;
        if (right > SCREEN_WIDTH - 2) right = SCREEN_WIDTH - 2;
        if (py >= 0 && py < SCREEN_HEIGHT) {
            for (int c = left; c <= right; c++) if (c >= 0 && c < SCREEN_WIDTH) screen[py][c] = '=';
        }
    }

    /* pelota (protección de límites) */
    Ball* b = ball_get();
    if (b != NULL && b->y >= 0 && b->y < SCREEN_HEIGHT && b->x >= 0 && b->x < SCREEN_WIDTH) {
        screen[b->y][b->x] = 'O';
    }

    /* limpiar e imprimir */
    printf("\x1b[2J\x1b[H"); /* clear + home */
    for (int r = 0; r < SCREEN_HEIGHT; r++) printf("%s\n", screen[r]);
    fflush(stdout);
}
