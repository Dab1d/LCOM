#ifndef __PROJ_WIN_VIEW_H
#define __PROJ_WIN_VIEW_H

/* Screen: 1024x768, car sprite: 64x64 */
#define WIN_CAR_X  480   /* (1024 - 64) / 2 */
#define WIN_CAR_Y  352   /* (768  - 64) / 2 */

/* winner: 1 = P1 (azul), 2 = P2 (vermelho) */
void win_view_draw(int winner);

#endif /* __PROJ_WIN_VIEW_H */
