#ifndef TRACK_H
#define TRACK_H

#include <stdbool.h>

// Dimensões da grelha lógica da pista
#define TRACK_LANES        10   // 5 por jogador (P1: 0-4, P2: 5-9)
#define TRACK_LANES_PER_PLAYER 5
#define PLAYER1_LANE_START  0
#define PLAYER1_LANE_END    4
#define PLAYER2_LANE_START  5
#define PLAYER2_LANE_END    9

#define TRACK_TOTAL_ROWS   200    // Linhas totais da pista até à meta
#define TRACK_VISIBLE_ROWS 12     // Linhas visíveis no ecrã em simultâneo
#define TRACK_TILE_HEIGHT  50     // Altura de cada tile em píxeis

#define CAR_SCREEN_ROW (TRACK_VISIBLE_ROWS - 2)

// Tipos de tile possíveis em cada célula da grelha
typedef enum {
    TILE_EMPTY    = 0,  // Estrada livre
    TILE_OBSTACLE = 1,  // Obstáculo — causa dano ao carro
    TILE_BOOST    = 2,  // Boost — avança o carro N tiles
    TILE_FINISH   = 3   // Meta — termina a corrida
} TileType;

// Temas visuais da pista (cada tema tem texturas de chão e paisagem lateral diferentes)
typedef enum {
    TRACK_THEME_CITY    = 0,
    TRACK_THEME_DESERT  = 1,
    TRACK_THEME_FOREST  = 2,
    TRACK_THEME_COUNT       // Sentinela — número total de temas
} TrackTheme;

/**
 * @brief Estrutura principal da pista.
 */
typedef struct {
    TileType grid[TRACK_TOTAL_ROWS][TRACK_LANES]; // Grelha lógica completa
    int      scroll_row;    // Linha lógica no topo do ecrã (avança a cada tick)
    float    scroll_offset; // Offset em píxeis dentro do tile atual (0..TRACK_TILE_HEIGHT-1)
    float    scroll_speed;  // Píxeis de scroll por tick (velocidade da pista)
    TrackTheme theme;       // Tema visual desta corrida
} Track;

// Construtor / Destrutor
Track* create_track(TrackTheme theme);
void   destroy_track(Track* track);

/**
 * @brief Avança o scroll da pista um tick.
 * Atualiza scroll_offset e scroll_row conforme a velocidade.
 */
void track_update(Track* track);

/**
 * @brief Devolve o tipo de tile na posição lógica (row, lane).
 * row=0 é o topo da pista (início), row=TRACK_TOTAL_ROWS-1 é a meta.
 */
TileType track_get_tile(const Track* track, int row, int lane);

/**
 * @brief Devolve o tipo de tile que está atualmente à frente do carro no ecrã.
 * Usa scroll_row para converter posição de ecrã em posição lógica.
 * screen_row: linha visível (0 = topo do ecrã, TRACK_VISIBLE_ROWS-1 = fundo)
 */
TileType track_get_visible_tile(const Track* track, int screen_row, int lane);

/**
 * @brief Verifica se o carro numa dada faixa colidiu com um tile neste tick.
 * Devolve o tipo do tile colidido (TILE_EMPTY se não há colisão).
 */
TileType track_check_car_tile(const Track* track, int lane);

/**
 * @brief Remove um tile da grelha (após ser apanhado/colidido).
 * Substitui por TILE_EMPTY para não voltar a colidir.
 */
void track_clear_tile(Track* track, int row, int lane);

/**
 * @brief Devolve true se a corrida terminou (scroll chegou à meta).
 */
bool track_is_finished(const Track* track);

#endif // TRACK_H
