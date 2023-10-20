#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include <raylib.h>

#include "pipe.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600

#define PLAYER_RADIUS 25.0

#define RANDOM_OFFSET rand() % 200 - 500

#define PIPES 5
#define PIPE_SPACING 175

#define TERMINAL_VELOCITY 25

int main(void)
{
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Flappy Bird");
  SetTargetFPS(60);
  // Randomness
  srand(time(NULL));
  
  Vector2 playerPosition = {128, 128};
  float playerVelocity = 0;

  
  char string[26] = "Points: ";
  int score = 0;

  pipeset pipes[PIPES];
  for (int i = 0; i < PIPES; i++)
    pipes[i] = (pipeset){WINDOW_WIDTH + i * (PIPE_WIDTH + PIPE_SPACING), RANDOM_OFFSET};

  while (!WindowShouldClose())
    {
      if (IsKeyPressed(KEY_SPACE)) playerVelocity = -10.0;

      // Gravity only used once, I don't need it to be a macro(?)
      playerVelocity += 0.5;
      if (playerVelocity > TERMINAL_VELOCITY) playerVelocity = TERMINAL_VELOCITY;
      
      playerPosition.y += playerVelocity;

      for (int i = 0; i < PIPES; i++)
	{
	  if (pipes[i].rectangle_x > -PIPE_WIDTH) {
	      pipes[i].rectangle_x -= 5;
	    }
	  else {
	    int lastPipe = (i > 0) ? i - 1 : PIPES - 1;
	    pipes[i].rectangle_x = pipes[lastPipe].rectangle_x + PIPE_WIDTH + PIPE_SPACING;
	    pipes[i].offset = RANDOM_OFFSET;
	  }

	  if (check_pipe_collisions(playerPosition, PLAYER_RADIUS, pipes[i]))
	    strcpy(string, "l bozo");
	  if (playerPosition.x >= pipes[i].rectangle_x &&
	      playerPosition.x <= pipes[i].rectangle_x + PIPE_WIDTH &&
	      !check_pipe_collisions(playerPosition, PLAYER_RADIUS, pipes[i]))
	    {
	      score++;
	    }
	  sprintf(string, "Points: %i", score / 20);
	  
	}

      BeginDrawing();
      ClearBackground(RAYWHITE);
      DrawCircleV(playerPosition, PLAYER_RADIUS, GRAY);
      
      // Pipes
      for (int i = 0; i < PIPES; i++)
	draw_pipes(pipes[i]);
      
      DrawText(string, 10, 10, 50, GRAY);
      EndDrawing();
    }

  CloseWindow();
  return 0;
}
