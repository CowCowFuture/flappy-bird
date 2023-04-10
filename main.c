#include <stdlib.h>
#include <time.h>

#include <raylib.h>

#include "pipe.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600

#define PLAYER_RADIUS 25.0

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

  struct pipeset pipes = {20, rand() % 200 - 500};

    while (!WindowShouldClose())
    {
      if (IsKeyPressed(KEY_SPACE)) playerVelocity.y = -10.0;

      playerVelocity.y += GRAVITY;
      if (playerVelocity.y > TERMINAL_VELOCITY) playerVelocity.y = TERMINAL_VELOCITY;

      playerPosition.y += playerVelocity.y;
      // Pipes
      char* string;
      if (check_pipe_collisions(playerPosition, PLAYER_RADIUS, pipes))
	{
	  string = "l bozo";
	} else
	{
	  string = "w chad";
	}

      BeginDrawing();
      ClearBackground(RAYWHITE);
      DrawCircleV(playerPosition, PLAYER_RADIUS, GRAY);

      // Pipes
      draw_pipes(pipes);

      DrawText(string, 10, 10, 50, GRAY);
      EndDrawing();
    }

  CloseWindow();
  return 0;
}
