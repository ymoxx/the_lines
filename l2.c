/*
  Version 2 - Depth search with randomness
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

#include "lines.h"

short max_lines = 0;
long n_tries;
short n_lines;
clock_t t0;

void go(void) {
  // I doubt there will be more than 128 possibilities in a single picture, need the arrays to store
  // the possibilities so we can then randomly pick one by one
  short xx[128], yy[128], rr[128];
  short n;

  for(;;) {
    n = 0;    
    for (int x = 0; x < MAX_SIZE; x++) {
      for (int y = 0; y < MAX_SIZE; y++) {
          for (int r = 0; r < 8; r++) {
            if(!field[x][y].used) continue;
    
            if (check_line(x, y, r)) {
              xx[n] = x;
              yy[n] = y;
              rr[n++] = r;
            }
          }
      }
    }
    // Dont have any results? That's it, return
    if(n == 0) break;

    // Pick one by random
    n = rand() % n;
    draw_line(xx[n], yy[n], rr[n]);
    n_lines++;

    // Got a new maximum?
    max_lines = n_lines > max_lines ? n_lines : max_lines;
  }
}

int main(int argc, char *argv[]) {
  printf("Lines L2 version 1.00\n");

  // Get start tune
  srand(time(NULL));
  t0 = clock();

  for(n_tries = 0;;n_tries++) {
    // Reset everything
    n_lines = 0;
    init_field();

    // Draw one picture
    go();

    // Print some statistics, so we see progress
    if(n_tries % 25000 == 0) {
      printf("%ld tries, %d max lines, in %.2lf seconds; %ld tries per second\n", n_tries, max_lines, (double)(clock()-t0) / CLOCKS_PER_SEC, (long)(n_tries / ( (double)(clock()-t0) / CLOCKS_PER_SEC)));
    }
  }
  return(0);
}
