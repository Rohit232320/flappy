#ifndef SCORE_H
#define SCORE_H

#define SCORE_TEXTURES 10

void score_load_assets(void);
void score_inc(void);
void score_reset(void);
void score_draw(void);
void score_draw_gameover(void);  // New function to draw scores on game over screen
unsigned int score_get_current(void);  // Get current score
unsigned int score_get_high(void);
void score_unload_assets(void);

#endif
