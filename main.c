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

  
  char string[26] = "Points: ";
  int score = 0;

  pipeset pipes[PIPES];
  for (int i = 0; i < PIPES; i++)
    pipes[i] = (pipeset){WINDOW_WIDTH + i * (PIPE_WIDTH + 175), RANDOM_OFFSET};

  while (!WindowShouldClose())
    {
      if (IsKeyPressed(KEY_SPACE)) playerVelocity.y = -10.0;
      
      playerVelocity.y += GRAVITY;
      if (playerVelocity.y > TERMINAL_VELOCITY) playerVelocity.y = TERMINAL_VELOCITY;
      
      playerPosition.y += playerVelocity.y;

      for (int i = 0; i < PIPES; i++)
	{
	  if (pipes[i].rectangle_x > -PIPE_WIDTH)
	    {
	      pipes[i].rectangle_x -= 5;
	    }
	  else {
	    int lastPipe = (i > 0) ? i - 1 : PIPES - 1;
	    pipes[i].rectangle_x = pipes[lastPipe].rectangle_x + PIPE_WIDTH + 175;
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
