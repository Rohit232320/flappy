#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>

#include "settings.h"
#include "bg_gnd.h"
#include "pipe.h"
#include "bird.h"
#include "score.h"

typedef enum {
    RUN,
    IDLE,
    GAMEOVER
} GameState;

static const char *TITLE = "FlappyBird";

/* Window logic */
float GAME_WIDTH = BASE_WIDTH;

/* Assets */
static Texture2D flappy_bird_tx;
static Texture2D gameover_tx;

static Sound hit_snd;
static Sound point_snd;
static Sound wing_snd;

/* Game state */
static GameState gs = IDLE;
static bool start_screen = true;
static float gameover_timer = 0;

/* ------------------------------------------------ */

static void update_game_width(void)
{
    float screenW = (float)GetScreenWidth();
    float screenH = (float)GetScreenHeight();
    float scale = screenH / (float)HEIGHT;
    if (scale > 0) {
        GAME_WIDTH = screenW / scale;
    }
}

/* ------------------------------------------------ */

static bool check_collision(void) {
    return bird_collision_roof() ||
           bird_collision_gnd() ||
           pipe_collision_bird(bird_get_rect());
}

static void check_score(void) {
    if (pipe_is_passed(bird_get_rect())) {
        PlaySound(point_snd);
        score_inc();
    }
}

static void reset(void) {
    bird_reset();
    score_reset();
    pipe_reset();
}

/* ---------------- GAME STATES ---------------- */

static void state_run(float dt) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_SPACE)) {
        PlaySound(wing_snd);
        bird_flap();
    }

    pipe_maybe_spawn();
    pipe_move_all(dt);
    bird_apply_gravity(dt);
    bird_animate(dt);

    if (check_collision()) {
        PlaySound(hit_snd);
        gs = GAMEOVER;
        gameover_timer = 0;
    } else {
        check_score();
    }
}

// static void state_run(float dt) {
//     // Check for UP ARROW key
//     if (IsKeyPressed(KEY_UP)) {
//         PlaySound(wing_snd);
//         bird_flap();
//     }
//     // Check for DOWN ARROW key
//     else if (IsKeyPressed(KEY_DOWN)) {
//         PlaySound(wing_snd);
//         bird_flap();
//     }
//     // Check for SPACE key as backup
//     else if (IsKeyPressed(KEY_SPACE)) {
//         PlaySound(wing_snd);
//         bird_flap();
//     }

//     pipe_maybe_spawn();
//     pipe_move_all(dt);
//     bird_apply_gravity(dt);
//     bird_animate(dt);

//     if (check_collision()) {
//         PlaySound(hit_snd);
//         gs = GAMEOVER;
//         gameover_timer = 0;
//     } else {
//         check_score();
//     }
// }

static void state_gameover(float dt) {
    gameover_timer += dt;
    if (gameover_timer > 0.5f && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_SPACE))) {
        reset();
        gs = IDLE;
        start_screen = true;
    }
}

// static void state_gameover(float dt) {
//     gameover_timer += dt;
//     if (gameover_timer > 0.5f && IsKeyPressed(KEY_SPACE)) {
//         reset();
//         gs = IDLE;
//         start_screen = true;
//     }
// }

static void state_idle(float dt) {
    bird_animate(dt);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_SPACE)) {
        gs = RUN;
        start_screen = false;
        pipe_spawn();
    }
}

// static void state_idle(float dt) {
//     bird_animate(dt);
//     if (IsKeyPressed(KEY_SPACE)) {
//         gs = RUN;
//         start_screen = false;
//         pipe_spawn();
//     }
//}

/* ---------------- SCREENS ---------------- */

static void start_screen_load_assets(void) {
    flappy_bird_tx = LoadTexture("sprites/flappy-bird.png");

    if (FileExists("sprites/gameover.png")) {
        gameover_tx = LoadTexture("sprites/gameover.png");
    } else {
        gameover_tx.id = 0;
    }
}

static void start_screen_unload_assets(void) {
    UnloadTexture(flappy_bird_tx);
    if (gameover_tx.id) UnloadTexture(gameover_tx);
}

/* ---------------- RENDER ---------------- */

static void render(void) {
    BeginDrawing();
    ClearBackground(BLACK);

    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0.0f, 0.0f };
    camera.offset = (Vector2){ 0.0f, 0.0f };
    camera.rotation = 0.0f;
    camera.zoom = (float)GetScreenHeight() / (float)HEIGHT;

    BeginMode2D(camera);
    
    bg_draw();
    gnd_draw();

    if (start_screen) {
        DrawTexture(
            flappy_bird_tx,
            (GAME_WIDTH - flappy_bird_tx.width) / 2,
            HEADER_Y,
            WHITE
        );
    }
    else if (gs == GAMEOVER) {
        pipe_draw_all();
        score_draw_gameover();
    }
    else {
        pipe_draw_all();
        score_draw();
    }

    bird_draw();
    
    EndMode2D();
    EndDrawing();
}

/* ---------------- INIT ---------------- */

static void init_renderer(void) {
    // Proper 16:9 window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);

    // Optional (makes resizing possible)
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    SetTargetFPS(FPS);
    InitAudioDevice();

    update_game_width();
}

static void load_assets(void) {
    bg_gnd_load_assets();
    start_screen_load_assets();
    score_load_assets();
    pipe_load_assets();
    bird_load_assets();
}

static void load_audio(void) {
    hit_snd = LoadSound("audio/hit.wav");
    point_snd = LoadSound("audio/point.wav");
    wing_snd = LoadSound("audio/wing.wav");
}

static void init_game(void) {
    Time t = GetRandomValue(DAY, NIGHT);
    bg_set_tx(t);
    pipe_set_tx(t);
    bird_set_tx();
}

/* ---------------- LOOP ---------------- */

static void game_loop(void) {
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Toggle Fullscreen on F11 or 'F' key
        if (IsKeyPressed(KEY_F11) || IsKeyPressed(KEY_F)) {
            ToggleFullscreen();
        }

        // If window is resizable or just toggled fullscreen, keep scaling correct
        if (IsWindowResized() || IsKeyPressed(KEY_F11) || IsKeyPressed(KEY_F)) {
            update_game_width();
        }

        if (gs == RUN) state_run(dt);
        else if (gs == GAMEOVER) state_gameover(dt);
        else state_idle(dt);

        gnd_update(dt);
        render();
    }
}

/* ---------------- CLEANUP ---------------- */

static void cleanup(void) {
    bg_gnd_unload_assets();
    start_screen_unload_assets();
    score_unload_assets();
    pipe_unload_assets();
    bird_unload_assets();

    UnloadSound(hit_snd);
    UnloadSound(point_snd);
    UnloadSound(wing_snd);

    CloseWindow();
}

/* ---------------- MAIN ---------------- */

int main(void) {
    init_renderer();
    load_assets();
    load_audio();
    init_game();
    game_loop();
    cleanup();
    return 0;
}
