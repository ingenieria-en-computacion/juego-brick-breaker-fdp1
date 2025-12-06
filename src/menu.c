#include <stdio.h>
#include "menu.h"

void menu_show() {
    printf("==============================\n");
    printf("     BRICK BREAKER - MENU     \n");
    printf("==============================\n");
    printf("1) Iniciar juego\n");
    printf("2) Instrucciones\n");
    printf("3) Salir\n");
    printf("==============================\n");
    printf("Elige una opción: ");
}

int menu_get_option() {
    int opt = 0;
    if (scanf("%d", &opt) != 1) {
        /* limpiar entrada si hay fallo */
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }
    /* limpiar resto de línea */
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    return opt;
}
