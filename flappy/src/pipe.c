#include <raylib.h>
#include <stdbool.h>
#include "settings.h"
#include "pipe.h"

/*
The pipe algorithm uses a circular buffer strategy
to reuse pipes as there will only be a fixed number of
pipes on screen at anytime.
*/

// Pipes array.
static Pipe pipes[MAX_PIPES] = {0};

// Index of the most recently spawned pipe in the pipes array.
static int curr_pipe = 0;

// Index of the next pipe the bird has to pass through in the pipes array.
static int next_pipe = 0;

// Array to store all pipe textures.
static Texture2D pipe_tx[NIGHT + 1][PIPE_DOWN + 1];
static Time curr_pipe_tx = DAY;

void pipe_load_assets(void) {
  Image pipe_img = LoadImage("sprites/pipe-green.png");
  pipe_tx[DAY][PIPE_UP] = LoadTextureFromImage(pipe_img);
  ImageFlipVertical(&pipe_img);
  pipe_tx[DAY][PIPE_DOWN] = LoadTextureFromImage(pipe_img);

  UnloadImage(pipe_img);
  pipe_img = LoadImage("sprites/pipe-red.png");
  pipe_tx[NIGHT][PIPE_UP] = LoadTextureFromImage(pipe_img);
  ImageFlipVertical(&pipe_img);
  pipe_tx[NIGHT][PIPE_DOWN] = LoadTextureFromImage(pipe_img);

  UnloadImage(pipe_img);
}

void pipe_set_tx(Time t) {
  curr_pipe_tx = t;
}

// void pipe_spawn(void) {
//   int h = GetRandomValue(PIPE_MIN_H, PIPE_MAX_H);
//   Pipe *curr_ppipe = &pipes[curr_pipe];
//   curr_ppipe->top = (Rectangle){WIDTH, 0, PIPE_WIDTH, h};
//   curr_ppipe->bottom = (Rectangle){WIDTH, curr_ppipe->top.height + PIPE_V_GAP,
//      PIPE_WIDTH, HEIGHT - curr_ppipe->top.height - PIPE_V_GAP - GROUND_HEIGHT};
//   curr_ppipe->alive = true;
// }

void pipe_spawn(void) {
  int h = GetRandomValue(PIPE_MIN_H, PIPE_MAX_H);
  Pipe *curr_ppipe = &pipes[curr_pipe];
  curr_ppipe->top = (Rectangle){GAME_WIDTH, 0, PIPE_WIDTH, h};
  
  float bottom_start = h + PIPE_V_GAP;
  float bottom_height = GROUND_Y - bottom_start;
  
  curr_ppipe->bottom = (Rectangle){GAME_WIDTH, bottom_start, PIPE_WIDTH, bottom_height};
  curr_ppipe->alive = true;
  curr_ppipe->scored = false;
}

void pipe_maybe_spawn(void) {
    /*
    Spawn a new pipe if the previously spawned pipe is
    PIPE_H_GAP or more far away from the window's right edge.
    */
    if (pipes[curr_pipe].alive == false || 
        pipes[curr_pipe].top.x + PIPE_WIDTH < GAME_WIDTH - PIPE_H_GAP) {
        curr_pipe = (curr_pipe + 1) % MAX_PIPES;
        pipe_spawn();
    }
}

void pipe_move_all(float dt) {
  for (int i = 0; i < MAX_PIPES; i++) {
    if (pipes[i].alive) {
      pipes[i].top.x -= SCROLL_SPEED * dt;
      pipes[i].bottom.x = pipes[i].top.x;
      if (pipes[i].top.x + pipes[i].top.width <= 0)
        pipes[i].alive = false;
    }
  }
}

bool pipe_collision_bird(Rectangle bird_rect) {
  // Check collision with all alive pipes, not just next_pipe
  for (int i = 0; i < MAX_PIPES; i++) {
    if (pipes[i].alive) {
      if (CheckCollisionRecs(bird_rect, pipes[i].top) ||
          CheckCollisionRecs(bird_rect, pipes[i].bottom)) {
        return true;
      }
    }
  }
  return false;
}

// bool pipe_is_passed(Rectangle bird_rect) {
//   /*
//   Check if the bird has passed pipes[next_pipe].
//   if yes, return true and set next_pipe to next pipe
//   the bird has to pass through.
//   */
//   // Only check if the pipe is alive
//   if (pipes[next_pipe].alive && 
//       bird_rect.x > pipes[next_pipe].top.x + PIPE_WIDTH) {
//     next_pipe = (next_pipe + 1) % MAX_PIPES;
//     return true;
//   }
//   return false;
// }

bool pipe_is_passed(Rectangle bird_rect) {
  // Find the leftmost alive pipe (the one the bird should pass next)
  int leftmost_pipe = -1;
  float leftmost_x = GAME_WIDTH + 1000;
  
  for (int i = 0; i < MAX_PIPES; i++) {
    if (pipes[i].alive && pipes[i].top.x < leftmost_x) {
      leftmost_x = pipes[i].top.x;
      leftmost_pipe = i;
    }
  }
  
  // If we found the leftmost pipe and bird has passed it
  if (leftmost_pipe != -1 && 
      bird_rect.x > pipes[leftmost_pipe].top.x + PIPE_WIDTH) {
    if (!pipes[leftmost_pipe].scored) {
      pipes[leftmost_pipe].scored = true;
      return true;
    }
  }
  
  return false;
}
bool pipe_visible(void) {
  return (pipes[curr_pipe].alive &&
          (pipes[curr_pipe].top.x + PIPE_WIDTH > 0));
}

void pipe_draw_all(void) {
  for (int i = 0; i < MAX_PIPES; i++) {
    if (pipes[i].alive) {
      // Draw top pipe (hanging down from top) - cut from bottom of texture
      DrawTextureRec(
        pipe_tx[curr_pipe_tx][PIPE_DOWN], 
        (Rectangle){0, PIPE_HEIGHT - pipes[i].top.height, PIPE_WIDTH, pipes[i].top.height}, 
        (Vector2){pipes[i].top.x, 0}, 
        WHITE
      );
      
      // Draw bottom pipe (standing up from bottom)
      DrawTextureRec(
        pipe_tx[curr_pipe_tx][PIPE_UP], 
        (Rectangle){0, 0, PIPE_WIDTH, pipes[i].bottom.height}, 
        (Vector2){pipes[i].bottom.x, pipes[i].bottom.y}, 
        WHITE
      );
    }
  }
}

// void pipe_reset(void) {
//   curr_pipe = next_pipe = 0;
//   // Properly reset all pipes to inactive state
//   for (int i = 0; i < MAX_PIPES; i++) {
//     pipes[i].alive = false;
//   }
// }
void pipe_reset(void) {
  curr_pipe = next_pipe = 0;
  for (int i = 0; i < MAX_PIPES; i++) {
    pipes[i].alive = false;
    pipes[i].scored = false;
  }
}

void pipe_unload_assets(void) {
    UnloadTexture(pipe_tx[DAY][PIPE_UP]);
    UnloadTexture(pipe_tx[DAY][PIPE_DOWN]);
    UnloadTexture(pipe_tx[NIGHT][PIPE_UP]);
    UnloadTexture(pipe_tx[NIGHT][PIPE_DOWN]);
}