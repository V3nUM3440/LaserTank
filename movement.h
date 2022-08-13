#ifndef MOVEMENT /* Guards */
#define MOVEMENT

/*
Author ------- Shuber Ali Mirza
ID ----------- 20027047
movement.h --- Contains all the prototypes, declarations and macros from movement.c for the laserTank program
Created ------ 23/MAR/2021
Last Updated - 23/MAR/2021
*/

/* Boolean data type */
#define False 0
#define True !False

/* Declarations from movement.c */
char** move(char** a, int* pr, int* pc, char m);

#endif /* MOVEMENT */