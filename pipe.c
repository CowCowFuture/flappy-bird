#include "pipe.h"

int check_pipe_collisions(Vector2 position1, float radius, pipeset pipes)
{
  Rectangle top_pipe = {pipes.rectangle_x, pipes.offset,
			PIPE_WIDTH, PIPE_HEIGHT};
  Rectangle bottom_pipe = {pipes.rectangle_x, pipes.offset + 800,
			   PIPE_WIDTH, PIPE_HEIGHT};
  if (CheckCollisionCircleRec(position1, radius, top_pipe) ||
      CheckCollisionCircleRec(position1, radius, bottom_pipe))
    {
      return 1;
    }
  return 0;
}

void draw_pipes(pipeset pipes)
{
  DrawRectangle(pipes.rectangle_x, pipes.offset,
		PIPE_WIDTH, PIPE_HEIGHT, GREEN);
  DrawRectangle(pipes.rectangle_x, pipes.offset + 800,
		PIPE_WIDTH, PIPE_HEIGHT, BLUE);
}
