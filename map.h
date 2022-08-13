#ifndef MAP /* Guards */
#define MAP

/*
Author ------- Shuber Ali Mirza
ID ----------- 20027047
map.h -------- Contains all the prototypes, declarations and macros from map.c for the laserTank program
Created ------ 23/MAR/2021
Last Updated - 23/MAR/2021
*/

/* Boolean data type */
#define False 0
#define True !False

/* Bounds checking (From Worksheet 2) */
#define BETWEEN(l , h , v) ((v < l || v > h || l > h)? (False) : (True)) /* l=low , h=high , v=value */

/* Declarations from map.c */
char** map(int r, int c);
char** pLoc(char** a, int pr, int pc, char pd);
void printArr(char** a, int r);
void upper(char s[]);
void freeMem(char** a, int r);

#endif /* MAP */