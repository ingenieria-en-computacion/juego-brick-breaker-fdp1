#include <stdio.h>
#include "menu.h"
#include "game.h"
#include "score.h"

int main() {
    int opt = 0;

    while (1) {
        menu_show();
        opt = menu_get_option();

        if (opt == 1) {
            game_init();

            while (!game_is_over())
                game_loop_step();

            if (game_player_won())
                printf("\n¡Felicidades! Has destruido todos los bloques.\n");
            else
                printf("\nHas perdido. La pelota cayó fuera del área.\n");

            printf("Puntuación: %d\n", score_get());
            score_save("scores.txt");

            printf("Presiona ENTER...");
            getchar();

        } else if (opt == 2) {
            printf("\nINSTRUCCIONES:\n");
            printf("Usa flechas o A/D para mover.\n");
            printf("Presiona ENTER...");
            getchar();

        } else if (opt == 3) {
            printf("Saliendo...\n");
            break;
        }
    }

    return 0;
}
