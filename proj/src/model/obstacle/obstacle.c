#include "obstacle.h"
#include "../car/car.h"
#include <stdlib.h>


// Linha de ecrã onde o carro está visualmente (igual ao definido em track.c)
#define CAR_SCREEN_ROW (TRACK_VISIBLE_ROWS - 2)

// ---------------------------------------------------------------------------
// Helpers de conversão grelha <-> píxeis
// ---------------------------------------------------------------------------

static double lane_to_x(int lane) {
    return (double)(lane * CAR_LANE_WIDTH);
}

static double row_to_y(int logical_row, int scroll_row, float scroll_offset) {
    int screen_row = logical_row - scroll_row;
    return (double)(screen_row * TRACK_TILE_HEIGHT) - (double)scroll_offset;
}

// ---------------------------------------------------------------------------
// Geração aleatória das dimensões do obstáculo
// ---------------------------------------------------------------------------

static int random_range(int min, int max) {
    return min + rand() % (max - min + 1);
}

static void generate_obstacle_size(int lane_min, int lane_max,
                                   int* out_lane_start, int* out_lane_end,
                                   int* out_row_span) {
    int available_lanes = lane_max - lane_min + 1; // ex: 5 faixas disponíveis

    // Largura aleatória mas nunca bloqueia todas as faixas do jogador
    int max_width = (available_lanes - 1 < OBSTACLE_MAX_LANES)
                  ? available_lanes - 1
                  : OBSTACLE_MAX_LANES;
    int width = random_range(OBSTACLE_MIN_LANES, max_width);

    // Posição inicial aleatória dentro dos limites da metade do jogador
    int lane_start = lane_min + rand() % (available_lanes - width + 1);

    *out_lane_start = lane_start;
    *out_lane_end   = lane_start + width - 1;
    *out_row_span   = random_range(OBSTACLE_MIN_ROWS, OBSTACLE_MAX_ROWS);
}

// ---------------------------------------------------------------------------
// Construtor / Destrutor
// ---------------------------------------------------------------------------

Obstacle* create_obstacle(int row_start, int lane_min, int lane_max) {
    Obstacle* obs = (Obstacle*) malloc(sizeof(Obstacle));
    if (obs == NULL) return NULL;

    int lane_start, lane_end, row_span;
    generate_obstacle_size(lane_min, lane_max, &lane_start, &lane_end, &row_span);

    obs->lane_start = lane_start;
    obs->lane_end   = lane_end;
    obs->row_start  = row_start;
    obs->row_end    = row_start + row_span - 1;

    // Posição e hitbox em píxeis (scroll ainda a 0 — será atualizado no primeiro tick)
    double x      = lane_to_x(lane_start);
    double y      = (double)(row_start * TRACK_TILE_HEIGHT);
    int    width  = (lane_end - lane_start + 1) * CAR_LANE_WIDTH;
    int    height = row_span * TRACK_TILE_HEIGHT;

    init_element(&obs->base, x, y, width, height);

    return obs;
}

void destroy_obstacle(Obstacle* obs) {
    if (obs != NULL) {
        free(obs);
    }
}

// ---------------------------------------------------------------------------
// Update e colisão
// ---------------------------------------------------------------------------

void obstacle_update(Obstacle* obs, int scroll_row, float scroll_offset) {
    if (obs == NULL || !obs->base.is_active) return;

    // Atualiza Y em píxeis com base no scroll atual da pista
    obs->base.y = row_to_y(obs->row_start, scroll_row, scroll_offset);

    // Desativa se já passou completamente pelo carro (saiu pelo topo do ecrã)
    if (obs->base.y + obs->base.height < 0) {
        obs->base.is_active = false;
    }
}

bool obstacle_is_visible(const Obstacle* obs) {
    if (obs == NULL || !obs->base.is_active) return false;

    int screen_height = TRACK_VISIBLE_ROWS * TRACK_TILE_HEIGHT;
    return obs->base.y < screen_height && obs->base.y + obs->base.height > 0;
}

bool obstacle_collides_with_car(const Obstacle* obs, int car_lane, int car_screen_row) {
    if (obs == NULL || !obs->base.is_active) return false;

    // Colisão na grelha lógica — mais fiável do que colisão em píxeis para este tipo de jogo
    bool lane_hit = (car_lane >= obs->lane_start && car_lane <= obs->lane_end);
    bool row_hit  = (car_screen_row >= 0); // o carro está sempre em CAR_SCREEN_ROW

    // Verifica se a linha do carro está dentro da zona do obstáculo no ecrã
    // usando a posição Y em píxeis do obstáculo
    int car_y     = CAR_SCREEN_ROW * TRACK_TILE_HEIGHT;
    int obs_y_top = (int)obs->base.y;
    int obs_y_bot = obs_y_top + obs->base.height;

    row_hit = (car_y >= obs_y_top && car_y < obs_y_bot);

    return lane_hit && row_hit;
}
