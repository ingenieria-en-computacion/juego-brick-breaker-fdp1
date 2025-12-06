#include "input.h"
#include "library_compat.h"

int input_update() {
    if (!kbhit()) return 0;

    int c = getch_compat();

#ifdef _WIN32
    /* Flechas en Windows regresan primero 224, luego el código */
    if (c == 0 || c == 224) {
        int code = getch_compat();
        if (code == 75) return -1; // izquierda
        if (code == 77) return 1;  // derecha
    }
#else
    /* Linux: códigos ANSI */
    if (c == 27) { 
        if (kbhit() && getch_compat() == '[') {
            int code = getch_compat();
            if (code == 'D') return -1; // izquierda
            if (code == 'C') return 1;  // derecha
        }
    }
#endif

    /* soporte adicional para 'a' y 'd' */
    if (c == 'a' || c == 'A') return -1;
    if (c == 'd' || c == 'D') return 1;

    return 0;
}
