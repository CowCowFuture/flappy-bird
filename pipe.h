#include <raylib.h>

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
