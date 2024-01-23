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

#include "pipe.h"

int check_pipe_collisions(Vector2 position1, float radius, pipeset pipes)
{
  Rectangle top_pipe = {pipes.rectangle_x, pipes.offset,
			PIPE_WIDTH, PIPE_HEIGHT};
  Rectangle bottom_pipe = {pipes.rectangle_x, pipes.offset + 800,
			   PIPE_WIDTH, PIPE_HEIGHT};
  if (CheckCollisionCircleRec(position1, radius, top_pipe) ||
      CheckCollisionCircleRec(position1, radius, bottom_pipe))
    return 1;
  return 0;
}

void draw_pipes(pipeset pipes)
{
  DrawRectangle(pipes.rectangle_x, pipes.offset,
		PIPE_WIDTH, PIPE_HEIGHT, GREEN);
  DrawRectangle(pipes.rectangle_x, pipes.offset + 800,
		PIPE_WIDTH, PIPE_HEIGHT, BLUE);
}
