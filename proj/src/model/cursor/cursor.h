#ifndef CURSOR_H
#define CURSOR_H

#include <stdbool.h>

typedef struct {
    int x, y;
    int screen_w, screen_h;
    bool clicked;   // true apenas no frame em que lb passou de 0 para 1
    bool lb_prev;
} Cursor;

Cursor* create_cursor(int initial_x, int initial_y, int screen_w, int screen_h);
void destroy_cursor(Cursor *cursor);

// dx e dy vêm diretamente do packet; lb_current é packet->lb
void cursor_update(Cursor *cursor, int dx, int dy, bool lb_current);

int cursor_get_x(const Cursor *cursor);
int cursor_get_y(const Cursor *cursor);
bool cursor_left_clicked(const Cursor *cursor);

#endif /* CURSOR_H */
