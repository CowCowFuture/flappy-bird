/*
 * flappy bird -- flappy bird
 * Copyright (C) 2024  ccf
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <raylib.h>

#include "pipe.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600

#define RANDOM_OFFSET rand() % 200 - 500

#define PIPES 5
#define PIPE_SPACING 175

#define PLAYER_RADIUS 25.0
#define TERMINAL_VELOCITY 25

Vector2 playerPosition = {128, 128};
float playerVelocity = 0;


char string[26] = "Points: ";
int score = -1; // Below 0 takes you to the main menu.

pipeset pipes[PIPES];

void gameplay()
{
  if (IsKeyPressed(KEY_SPACE)) playerVelocity = -10.0;

  // Gravity only used once, I don't need it to be a macro(?)
  playerVelocity += 0.5;
  if (playerVelocity > TERMINAL_VELOCITY)
    playerVelocity = TERMINAL_VELOCITY;

  playerPosition.y += playerVelocity;

  for (int i = 0; i < PIPES; i++) {
    if (pipes[i].rectangle_x > -PIPE_WIDTH) {
      pipes[i].rectangle_x -= 5;
    } else{
      int lastPipe = (i + PIPES - 1) % PIPES;
      pipes[i].rectangle_x = pipes[lastPipe].rectangle_x + PIPE_WIDTH + PIPE_SPACING;
      pipes[i].offset = RANDOM_OFFSET;
      pipes[i].scorable = 1;
    }

    if (check_pipe_collisions(playerPosition, PLAYER_RADIUS, pipes[i]) || playerPosition.y > WINDOW_HEIGHT) {
      score = -1;
    } else if (pipes[i].rectangle_x <= playerPosition.x &&
	       playerPosition.x <= pipes[i].rectangle_x + PIPE_WIDTH &&
	       pipes[i].scorable == 1) {
      score++;
      pipes[i].scorable = 0;
    }
    sprintf(string, "Score: %i", score);
  }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawCircleV(playerPosition, PLAYER_RADIUS, GRAY);

    // Pipes
    for (int i = 0; i < PIPES; i++)
      draw_pipes(pipes[i]);

    // Player
    DrawText(string, 10, 10, 50, GRAY);
    EndDrawing();
}

int button_pressed(int x, int y, int width, int height)
{
  return (GetMouseX() >= x && GetMouseX() <= x + width &&
	  GetMouseY() >= y && GetMouseY() <= y + height &&
	  IsMouseButtonPressed(0));
}

void main_menu() {
  if (button_pressed((WINDOW_WIDTH - 200)/2, (WINDOW_HEIGHT - 100)/2, 200, 100)) {
    // Initalize Player
    playerPosition.y = 128;
    playerVelocity = 0;

    // Initalize Pipes
    for (int i = 0; i < PIPES; i++)
	pipes[i] = (pipeset){WINDOW_WIDTH + i * (PIPE_WIDTH + PIPE_SPACING), RANDOM_OFFSET, 1};

    score = 0;
  }

  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawRectangle((WINDOW_WIDTH - 200)/2, (WINDOW_HEIGHT - 100)/2, 200, 100, GRAY);
  DrawText("[PLAY]", (WINDOW_WIDTH - 150)/2, (WINDOW_HEIGHT - 55)/2, 50, RAYWHITE);
  EndDrawing();
}

int main()
{
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Flappy Bird");
  SetTargetFPS(60);
  // Randomness
  srand(time(NULL));

  while (!WindowShouldClose()) {
    if (score < 0)
      main_menu();
    else
      gameplay();
  }

  CloseWindow();
  return 0;
}
