#ifndef SETTINGS_H
#define SETTINGS_H

/*
The game renders to a fixed buffer of WIDTH * HEIGHT
and then scales the window based on monitor size.
*/

typedef enum {
  DAY,
  NIGHT
} Time;

// what percentage of the monitor should scaled window height be ?
#define W_HEIGHT_PERC 0.7f

#define FPS 60

// Height for buffer to render to.
#define HEIGHT 426
extern float GAME_WIDTH;
// Original width used for reference
#define BASE_WIDTH 240

// Fixed window size (for testing)
#define WINDOW_WIDTH  480
#define WINDOW_HEIGHT 852


// Position of Header (FlappyBird icon / Score).
// (0, HEADER_Y).
#define HEADER_Y 25

// Spacing bw score digits.
#define SCORE_SPACING 2

// Width, Height of pipes.
#define PIPE_WIDTH 52
#define PIPE_HEIGHT 320

// Horizontal gap bw pipes.
#define PIPE_H_GAP 180

// Vertical gap bw pipes.
#define PIPE_V_GAP 160

// Pipe height will be bw these 2 values.
#define PIPE_MIN_H 50
// Max height is GROUND_Y - PIPE_V_GAP - minimum bottom height
#define PIPE_MAX_H (GROUND_Y - PIPE_V_GAP - 50)

// Maximum number of pipes on screen at any time.
#define MAX_PIPES 10
 
// Speed at which pipes, ground scroll to the left.
#define SCROLL_SPEED 120

// (HEIGHT - (PIPE_HEIGHT + PIPE_V_GAP + PIPE_MIN_H))
#define GROUND_HEIGHT 60

// Ground position (0, GROUND_Y).
// (HEIGHT - GROUND_HEIGHT)
#define GROUND_Y 366

// Bird rectangle width, height.
// Same as Bird sprite.
#define BIRD_WIDTH 20
#define BIRD_HEIGHT 15
 
// Starting (X, Y) for Bird.
#define BIRD_STARTX 72 // (WIDTH / 4)
#define BIRD_STARTY 256 // (HEIGHT / 2)

#define GRAVITY 1200

// Bird flap strength.
// More negative the value, higher the bird flaps.
// Depends on Gravity too.
#define FLAP -420

#define BIRD_ANIMATION_SPEED 5

#endif