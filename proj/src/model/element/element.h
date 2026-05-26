#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdbool.h>

struct Sprite;

/**
 * @brief Estrutura base para qualquer objeto físico do jogo.
 * Usada por composição em Car, Obstacle, Boost, etc.
 */
typedef struct {
    double x;               // Posição no eixo X (coluna/faixa convertida para píxeis)
    double y;               // Posição no eixo Y (posição na pista)
    int width;              // Largura da hitbox
    int height;             // Altura da hitbox
    bool is_active;         // false = já não existe no jogo (explodiu, foi apanhado, etc.)
    struct Sprite* sprite;  // Gerido pela View — nunca libertado aqui
} Element;

// Inicializa um Element já alocado (sem malloc — para usar em composição)
void init_element(Element* el, double x, double y, int width, int height);

// Construtor/Destrutor standalone (para objetos que não usam composição)
Element* create_element(double x, double y, int width, int height);
void destroy_element(Element* el);

// Colisão AABB entre quaisquer dois elementos ativos
bool check_collision(Element* el1, Element* el2);

#endif // ELEMENT_H