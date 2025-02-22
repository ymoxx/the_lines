#ifndef __LINES_H
#define __LINES_H

#define MAX_SIZE 24

#define TOP_LEFT (MAX_SIZE / 2 - 2)
#define TOP_TOP (MAX_SIZE / 2 - 5)

struct sPOINT {
  short used;
  char r[8];
};

extern struct sPOINT field[MAX_SIZE][MAX_SIZE];

extern int DX[];
extern int DY[];

void init_field(void);
void draw_line(short x, short y, const short r);
void undraw_line(short x, short y, const short r);
int check_line(short x, short y, const short r);

#endif