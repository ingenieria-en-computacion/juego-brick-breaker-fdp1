#include <stdio.h>
#include <stdlib.h>
#include "score.h"

static int score = 0;

void score_init(const char *filename) {
    /* Creación/lectura básica: si archivo no existe, se crea vacío */
    FILE *f = fopen(filename, "a");
    if (f != NULL) fclose(f);
    score = 0;
}

void score_add(int points) {
    score += points;
}

int score_get() {
    return score;
}

void score_save(const char *filename) {
    FILE *f = fopen(filename, "a");
    if (f == NULL) return;
    fprintf(f, "%d\n", score);
    fclose(f);
}
