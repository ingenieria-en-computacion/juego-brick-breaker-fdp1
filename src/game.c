#include <stdio.h>
#include "game.h"
#include "paddle.h"
#include "ball.h"
#include "brick.h"
#include "render.h"
#include "input.h"
#include "score.h"

#ifdef _WIN32
  #include <windows.h> // Sleep
#else
  #include <unistd.h>  // usleep
#endif

#define FRAME_DELAY_MS 40  // ~25 FPS

static int game_over = 0;
static int player_won = 0;

void game_init() {
    bricks_init();
    paddle_init();
    ball_init();                // inicia pelota (ahora la colocamos relativa al paddle)
    score_init("scores.txt");
    game_over = 0;
    player_won = 0;
}

void game_loop_step() {
    int dir = input_update();

    /* salida por tecla (si tu input devuelve 2 para salir) */
    if (dir == 2) {
        game_over = 1;
        return;
    }

    /* mover paddle */
    if (dir == -1 || dir == 1) paddle_update(dir);

    /* actualizar pelota */
    ball_update();

    /* perder si la pelota cae al fondo */
    Ball* b = ball_get();
    if (b->y >= (20 - 1)) {  // SCREEN_HEIGHT - 1
        game_over = 1;
        player_won = 0;
    }

    /* ganar si no quedan ladrillos */
    {
        Brick (*m)[BRICK_COLS] = bricks_get();
        int any = 0;
        for (int r = 0; r < BRICK_ROWS && !any; r++)
            for (int c = 0; c < BRICK_COLS; c++)
                if (m[r][c].active) { any = 1; break; }

        if (!any) { game_over = 1; player_won = 1; }
    }

    /* render del frame */
    render_frame();

    /* --- pequeño delay para evitar parpadeo y velocidad descontrolada --- */
#ifdef _WIN32
    Sleep(FRAME_DELAY_MS);
#else
    usleep(FRAME_DELAY_MS * 1000);
#endif
}

int game_is_over() { return game_over; }
int game_player_won() { return player_won; }
