#include <memory.h>
#include "lines.h"

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
