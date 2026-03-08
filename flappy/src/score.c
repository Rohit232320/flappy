#include <raylib.h>
#include <string.h>
#include <stdio.h>
#include "settings.h"
#include "score.h"

static unsigned int score = 0;
static unsigned int high_score = 0;
// static Texture2D score_tx[SCORE_TEXTURES];

/* ---------- High score file ---------- */
static void save_high_score(void) {
    FILE *fp = fopen("highscore.dat", "w");
    if (fp) {
        fprintf(fp, "%u", high_score);
        fclose(fp);
    }
}

static void load_high_score(void) {
    FILE *fp = fopen("highscore.dat", "r");
    if (fp) {
        fscanf(fp, "%u", &high_score);
        fclose(fp);
    }
}
/* ------------------------------------ */

static void score_box_update(void) {
    // No longer caching text into a texture
}

void score_load_assets(void) {
    // for (int i = 0; i < SCORE_TEXTURES; i++)
    //     score_tx[i] = LoadTexture(TextFormat("sprites/%d.png", i));

    load_high_score();
}

void score_inc(void) {
    score++;
    if (score > high_score) {
        high_score = score;
        save_high_score();
    }
    score_box_update();
}

void score_reset(void) {
    score = 0;
    score_box_update();
}

void score_draw(void) {
    const char *str = TextFormat("%d", score);
    int w = MeasureText(str, 20);
    DrawText(str, (GAME_WIDTH - w) / 2, HEADER_Y, 20, WHITE);
}

void score_draw_gameover(void) {
    DrawRectangle(GAME_WIDTH/2 - 120, HEIGHT/2 - 60, 240, 120, (Color){220,220,180,230});
    DrawText(TextFormat("SCORE: %d", score), GAME_WIDTH/2 - 90, HEIGHT/2 - 40, 20, BLACK);
    DrawText(TextFormat("HIGH: %d", high_score), GAME_WIDTH/2 - 90, HEIGHT/2, 20, BLACK);
}

void score_unload_assets(void) {
    // for (int i = 0; i < SCORE_TEXTURES; i++)
    //     UnloadTexture(score_tx[i]);
}
