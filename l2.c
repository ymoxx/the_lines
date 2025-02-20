/*
  Version 2 - Depth search with randomness
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

#define MAX_SIZE 24
#define TOP_LEFT (MAX_SIZE / 2 - 2)
#define TOP_TOP (MAX_SIZE / 2 - 5)

struct sPOINT {
  short used;
  char r[8];
};

struct sPOINT field[MAX_SIZE][MAX_SIZE];

short max_lines = 0;
long n_tries;
short n_lines;
clock_t t0;

short sol_x[128], sol_y[128], sol_r[128];
short fin_x[128], fin_y[128], fin_r[128];

struct sPOINT field[MAX_SIZE][MAX_SIZE];

int DX[] = { 0,   1, 1, 1, 0, -1, -1, -1 };
int DY[] = { -1, -1, 0, 1, 1,  1,  0, -1 };

void init_field(void) {
  short x = TOP_LEFT, y = TOP_TOP;

  memset(field, 0, sizeof(field));

  field[++x][y].used = 1; field[++x][y].used = 1; field[++x][y].used = 1;
  field[x][++y].used = 1; field[x][++y].used = 1; field[x][++y].used = 1;
  field[++x][y].used = 1; field[++x][y].used = 1; field[++x][y].used = 1;
  field[x][++y].used = 1; field[x][++y].used = 1; field[x][++y].used = 1;
  field[--x][y].used = 1; field[--x][y].used = 1; field[--x][y].used = 1;
  field[x][++y].used = 1; field[x][++y].used = 1; field[x][++y].used = 1;
  field[--x][y].used = 1; field[--x][y].used = 1; field[--x][y].used = 1;
  field[x][--y].used = 1; field[x][--y].used = 1; field[x][--y].used = 1;
  field[--x][y].used = 1; field[--x][y].used = 1; field[--x][y].used = 1;
  field[x][--y].used = 1; field[x][--y].used = 1; field[x][--y].used = 1;
  field[++x][y].used = 1; field[++x][y].used = 1; field[++x][y].used = 1;
  field[x][--y].used = 1; field[x][--y].used = 1; field[x][--y].used = 1;
}

void draw_line(short x, short y, const short r) {
  field[x][y].used++; field[x][y].r[r] = 1; x += DX[r]; y += DY[r];
  field[x][y].used++; field[x][y].r[r] = 1; field[x][y].r[(r + 4) % 8] = 1; x += DX[r]; y += DY[r];
  field[x][y].used++; field[x][y].r[r] = 1; field[x][y].r[(r + 4) % 8] = 1; x += DX[r]; y += DY[r];
  field[x][y].used++; field[x][y].r[r] = 1; field[x][y].r[(r + 4) % 8] = 1; x += DX[r]; y += DY[r];
  field[x][y].used++; field[x][y].r[(r + 4) % 8] = 1;
}

void undraw_line(short x, short y, const short r) {
  field[x][y].used--; field[x][y].r[r] = 0; x += DX[r]; y += DY[r];
  field[x][y].used--; field[x][y].r[r] = 0; field[x][y].r[(r + 4) % 8] = 0; x += DX[r]; y += DY[r];
  field[x][y].used--; field[x][y].r[r] = 0; field[x][y].r[(r + 4) % 8] = 0; x += DX[r]; y += DY[r];
  field[x][y].used--; field[x][y].r[r] = 0; field[x][y].r[(r + 4) % 8] = 0; x += DX[r]; y += DY[r];
  field[x][y].used--; field[x][y].r[(r + 4) % 8] = 0;
}

int check_line(short x, short y, const short r) {
  short c = 0;

  if (field[x][y].used == 0) c = 1;                           
  if (field[x][y].r[r]) return 0;    
  x += DX[r]; y += DY[r];

  if (field[x][y].used == 0) c++;    
  if (c == 2) return 0;    
  if (field[x][y].r[r]) return 0;
  x += DX[r]; y += DY[r];

  if (field[x][y].used == 0) c++;   
  if (c == 2) return 0;
  if (field[x][y].r[r]) return 0;  
  x += DX[r]; y += DY[r];

  if (field[x][y].used == 0) c++;    
  if (c == 2) return 0;    
  if (field[x][y].r[r]) return 0; 
  x += DX[r]; y += DY[r];
  if (field[x][y].used == 0) c++;    
  if (c == 2) return 0;    

  return 1;
}

void go(void) {
  short xx[128], yy[128], rr[128];
  short n = 0;

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
  if(n == 0) return;
  n = rand() % n;
  draw_line(xx[n], yy[n], rr[n]);
  sol_x[n_lines] = xx[n];
  sol_y[n_lines] = yy[n];
  sol_r[n_lines] = rr[n];
  n_lines++;
  if(n_lines > max_lines && n_tries > 0) {
    max_lines = n_lines;
    memcpy(fin_x, sol_x, sizeof(fin_x));
    memcpy(fin_y, sol_y, sizeof(fin_x));
    memcpy(fin_r, sol_r, sizeof(fin_x));
    printf("%ld tries. %d max lines, in %.2lf seconds; %ld tries per second\n", n_tries, max_lines, (double)(clock()-t0) / CLOCKS_PER_SEC, (long)(n_tries / ( (double)(clock()-t0) / CLOCKS_PER_SEC)));
  }  
  go();
}

int main(int argc, char *argv[]) {
  printf("Lines v02.00\n");

  srand(time(NULL));
  t0 = clock();
  for(n_tries = 0;;n_tries++) {
    n_lines = 0;
    init_field();
    go();
    if(n_tries % 25000 == 0) {
      printf("%ld tries, %d max lines, in %.2lf seconds; %ld tries per second\n", n_tries, max_lines, (double)(clock()-t0) / CLOCKS_PER_SEC, (long)(n_tries / ( (double)(clock()-t0) / CLOCKS_PER_SEC)));
    }
  }
  return(0);
}
