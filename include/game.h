#ifndef GAME_H
#define GAME_H

// Inicializa todos los elementos del juego
void game_init();

// Ejecuta un paso del ciclo principal del juego
// Debe llamar internamente a input, updates y render
void game_loop_step();

// Devuelve si el juego terminó
int game_is_over();

// --- FALTA ESTA FUNCIÓN ---
// Devuelve 1 si el jugador ganó, 0 si no
int game_player_won();

#endif

