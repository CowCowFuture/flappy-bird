#include <stdlib.h>
#include <time.h>

#include <raylib.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600

#define PLAYER_RADIUS 25.0

#define TERMINAL_VELOCITY 25
#define GRAVITY 0.5

struct pipeset {
  Rectangle top_pipe,  bottom_pipe;
};

int check_pipe_collisions(Vector2 position1, float radius, struct pipeset pipes)
{
  if (CheckCollisionCircleRec(position1, radius, pipes.top_pipe) || CheckCollisionCircleRec(position1, radius, pipes.bottom_pipe))
    {
      return 1;
    }
  return 0;
}

int main(void)
{
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Flappy Bird");
  SetTargetFPS(60);
  // Randomness
  srand(time(NULL));

  Vector2 playerPosition = {128, 128};
  Vector2 playerVelocity = {0, 0};

  int offset = rand() % 200 - 500;
  const Rectangle generic_pipe = {50, offset, 100, WINDOW_HEIGHT};
  struct pipeset pipes = {generic_pipe, (Rectangle){generic_pipe.x, generic_pipe.y + 800, generic_pipe.width, generic_pipe.height}};

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
      DrawRectangleRec(pipes.top_pipe, GREEN);
      DrawRectangleRec(pipes.bottom_pipe, BLUE);

      DrawText(string, 10, 10, 50, GRAY);
      EndDrawing();
    }

  CloseWindow();
  return 0;
}
