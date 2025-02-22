/*
  Version 1 - Depth search
*/

#include <stdio.h>
#include <memory.h>

#include "lines.h"

int n_max_lines = 0;
int n_lines = 0;

void go(void) {
  for (int x = 0; x < MAX_SIZE; x++) {
    for (int y = 0; y < MAX_SIZE; y++) {
        for (int r = 0; r < 8; r++) {
          if(!field[x][y].used) continue;
  
          if (check_line(x, y, r)) {
            draw_line(x, y, r);
            n_lines++;
            if(n_lines > n_max_lines) {
              n_max_lines = n_lines;
              printf("Found new maximum number of lines: %d\n", n_max_lines);
            }
            go();
            undraw_line(x, y, r);
            n_lines--;
          }
        }
    }
  }
}

int main(int argc, char *argv[]) {
  printf("Lines L2 version 1.00\n");

  init_field();
  go();
  return(0);
}
