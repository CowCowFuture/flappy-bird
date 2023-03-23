#include <raylib.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600

#define TERMINAL_VELOCITY 25
#define GRAVITY 0.5

int main(void)
{
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Flappy Bird");
  SetTargetFPS(60);

  Vector2 playerPosition = {128, 128};
  Vector2 playerVelocity = {0, 0};

  while (!WindowShouldClose())
    {
      if (IsKeyPressed(KEY_SPACE)) playerVelocity.y = -10.0;

      playerVelocity.y += GRAVITY;
      if (playerVelocity.y > TERMINAL_VELOCITY) playerVelocity.y = TERMINAL_VELOCITY;

      playerPosition.y += playerVelocity.y;

      BeginDrawing();
      ClearBackground(RAYWHITE);
      DrawCircleV(playerPosition, 25.0, GRAY);
      DrawText("Points: [PLACEHOLDER]", 10, 10, 50, GRAY);
      EndDrawing();
    }


  CloseWindow();
  return 0;
}
