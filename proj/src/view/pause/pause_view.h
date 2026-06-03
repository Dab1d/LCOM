#ifndef __PROJ_PAUSE_VIEW_H
#define __PROJ_PAUSE_VIEW_H

/* Screen: 1024x768 */
#define PAUSE_PANEL_W   300
#define PAUSE_PANEL_H   200
#define PAUSE_PANEL_X   362   /* (1024 - 300) / 2 */
#define PAUSE_PANEL_Y   284   /* (768  - 200) / 2 */
#define PAUSE_BTN_W     200
#define PAUSE_BTN_H      44
#define PAUSE_BTN_X     412   /* PAUSE_PANEL_X + (300 - 200) / 2 */
#define PAUSE_RESUME_Y  356   /* PAUSE_PANEL_Y + 72 */
#define PAUSE_QUIT_Y    414   /* PAUSE_RESUME_Y + 44 + 14 */

/* selected: 0 = RESUME highlighted, 1 = QUIT highlighted */
void pause_view_draw(int selected);

#endif /* __PROJ_PAUSE_VIEW_H */
