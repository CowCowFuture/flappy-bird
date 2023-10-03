#include <stdlib.h>
#include <time.h>

#include <raylib.h>

#include "pipe.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600

#define PLAYER_RADIUS 25.0

#define RANDOM_OFFSET rand() % 200 - 500

#define TERMINAL_VELOCITY 25
#define GRAVITY 0.5

int main(void)
{
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Flappy Bird");
  SetTargetFPS(60);
  // Randomness
  srand(time(NULL));
  
  Vector2 playerPosition = {128, 128};
  Vector2 playerVelocity = {0, 0};

  pipeset pipes[100];
  for (int i = 0; i < 100; i++) { pipes[i] = (pipeset){WINDOW_WIDTH + i * (PIPE_WIDTH + 175), RANDOM_OFFSET}; }

  while (!WindowShouldClose())
    {
      if (IsKeyPressed(KEY_SPACE)) playerVelocity.y = -10.0;
      
      playerVelocity.y += GRAVITY;
      if (playerVelocity.y > TERMINAL_VELOCITY) playerVelocity.y = TERMINAL_VELOCITY;
      
      playerPosition.y += playerVelocity.y;

      char* string = "w chad";
      for (int i = 0; i < 100; i++)
	{
	  if (pipes[i].rectangle_x > -PIPE_WIDTH)
	    {
	      pipes[i].rectangle_x -= 5;
	    }
	  else {
	    pipes[i].rectangle_x = pipes[i - 1].rectangle_x - PIPE_WIDTH;
	    pipes[i].offset = RANDOM_OFFSET;
	  }
	  if (check_pipe_collisions(playerPosition, PLAYER_RADIUS, pipes[i])) { string = "l bozo"; }
	  }

      BeginDrawing();
      ClearBackground(RAYWHITE);
      DrawCircleV(playerPosition, PLAYER_RADIUS, GRAY);
      
      // Pipes
      for (int i = 0; i < 100; i++) { draw_pipes(pipes[i]); }
      
      DrawText(string, 10, 10, 50, GRAY);
      EndDrawing();
    }

  CloseWindow();
  return 0;
}
