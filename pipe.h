#include <raylib.h>

struct pipeset {
  int rectangle_x, offset;
};

int check_pipe_collisions(Vector2 position1, float radius, struct pipeset pipes)
{
  Rectangle top_pipe = {pipes.rectangle_x, pipes.offset, 100, 600};
  Rectangle bottom_pipe = {pipes.rectangle_x, pipes.offset + 800, 100, 600};
  if (CheckCollisionCircleRec(position1, radius, top_pipe) || CheckCollisionCircleRec(position1, radius, bottom_pipe))
    {
      return 1;
    }
  return 0;
}

void draw_pipes(struct pipeset pipes)
{
  DrawRectangle(pipes.rectangle_x, pipes.offset, 100, 600, GREEN);
  DrawRectangle(pipes.rectangle_x, pipes.offset + 800, 100, 600, BLUE);
}
