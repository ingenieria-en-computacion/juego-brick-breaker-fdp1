#include <stdio.h>
#include "paddle.h"

#define SCREEN_WIDTH  33
#define SCREEN_HEIGHT 20

/* Plataforma global */
static Paddle paddle;

/* Inicializa la plataforma en el centro inferior */
void paddle_init() {
    paddle.width = 7; /* ancho por defecto (puedes ajustar) */
    paddle.x = SCREEN_WIDTH / 2; /* centro X */
}

/* Atualiza la posición del paddle según direction:
   -1 = izquierda, 1 = derecha, 0 = sin cambio
*/
void paddle_update(int direction) {
    if (direction == 0) return;

    int half = paddle.width / 2;
    int left = paddle.x - half;
    int right = paddle.x + half;

    if (direction < 0) {
        /* mover izquierda si cabe */
        if (left > 1) paddle.x--;
    } else if (direction > 0) {
        /* mover derecha si cabe */
        if (right < SCREEN_WIDTH - 2) paddle.x++;
    }
}

/* Devuelve puntero a la plataforma global */
Paddle* paddle_get() {
    return &paddle;
}
