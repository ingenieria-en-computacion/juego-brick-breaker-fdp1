#include <stddef.h>
#include "ball.h"
#include "paddle.h"
#include "brick.h"

#define SCREEN_WIDTH  33
#define SCREEN_HEIGHT 20

static Ball ball;

/* --- CONFIGURACIÓN DE VELOCIDAD --- */
static int speed_counter = 0;
static const int BALL_SPEED = 4;   // ← CAMBIA ESTE número para ajustar la velocidad (2 = más lento)

/* --- CONSTANTES DE LADRILLOS --- */
const int BRICKS_START_Y = 2;
const int BRICKS_START_X = 2;
const int BRICK_DRAW_WIDTH = 2;
const int BRICK_SPACING = 1;

void ball_init() {
    ball.x = SCREEN_WIDTH / 2;
    ball.y = SCREEN_HEIGHT / 2;
    ball.dx = 1;
    ball.dy = -1;
}

/* --- ACTUALIZA LA PELOTA --- */
void ball_update() {

    /* hace que se mueva solo cada BALL_SPEED frames */
    speed_counter++;
    if (speed_counter < BALL_SPEED)
        return;

    speed_counter = 0;

    ball.x += ball.dx;
    ball.y += ball.dy;

    /* paredes */
    if (ball.x <= 1) { ball.x = 1; ball.dx *= -1; }
    else if (ball.x >= SCREEN_WIDTH - 2) { ball.x = SCREEN_WIDTH - 2; ball.dx *= -1; }

    if (ball.y <= 1) { ball.y = 1; ball.dy *= -1; }

    /* plataforma */
    Paddle* p = paddle_get();
    int py = SCREEN_HEIGHT - 2;
    int left = p->x - (p->width / 2);
    int right = left + p->width - 1;

    if (ball.dy > 0 && ball.y == py - 1 &&
        ball.x >= left && ball.x <= right) {

        ball.dy *= -1;

        int center = p->x;
        if (ball.x < center) ball.dx = -1;
        else if (ball.x > center) ball.dx = 1;
        else ball.dx = 0;
    }

    /* ladrillos */
    Brick (*bricks)[BRICK_COLS] = bricks_get();

    for (int r = 0; r < BRICK_ROWS; r++) {
        for (int c = 0; c < BRICK_COLS; c++) {

            if (!bricks[r][c].active) continue;

            int bx = BRICKS_START_X + c * (BRICK_DRAW_WIDTH + BRICK_SPACING);
            int by = BRICKS_START_Y + r;

            if (ball.y == by && (ball.x == bx || ball.x == bx + 1)) {
                bricks[r][c].active = 0;
                ball.dy *= -1;
                return;
            }
        }
    }
}

Ball* ball_get() {
    return &ball;
}
