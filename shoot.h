#ifndef SHOOT /* Guards */
#define SHOOT

/*
Author ------- Shuber Ali Mirza
ID ----------- 20027047
shoot.h ------ Contains all the prototypes, declarations and macros from shoot.c for the laserTank program
Created ------ 17/FEB/2021
Last Updated - 23/MAR/2021
*/

/* Boolean data type */
#define False 0
#define True !False

/* Declarations from shoot.c */
void shoot(char** a, int r, int pr, int pc);
char* convert(char pd);
void killShot(char** a, int r, int pr, int pc, int er, int ec);

#endif /* SHOOT */