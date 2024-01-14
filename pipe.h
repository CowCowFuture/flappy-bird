#include <raylib.h>

#define PIPE_WIDTH 100
#define PIPE_HEIGHT 600

typedef struct pipeset {
  int rectangle_x, offset;
  int scorable; // 1 or 0
} pipeset;

int check_pipe_collisions(Vector2 position1, float radius, pipeset pipes);

void draw_pipes(pipeset pipes);
