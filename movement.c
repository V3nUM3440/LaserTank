#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "movement.h" /* Header file */

/*
Author ------- Shuber Ali Mirza
ID ----------- 20027047
movement.c --- Contains all functions related to player movement
Created ------ 18/FEB/2021
Last Updated - 23/MAR/2021
*/


/* Moves player in direction specified */
/* a = array, pr = player row, pc = player col, m = direction to move */
char** move(char** a, int* pr, int* pc, char m)
{
    /* Moving up */
    if (m == 'w'){
        /* If already facing up, move up and leave previous location blank */
        if (a[*pr][*pc] == '^'){
            a[*pr][*pc] = ' ';
            a[*pr-1][*pc] = '^';
            *pr -= 1;
        }
        /* Else face up */
        else{
            a[*pr][*pc] = '^';
        }
    }
    
    /* Moving down */
    else if (m == 's'){
        /* If already facing down, move down and leave previous location blank */
        if (a[*pr][*pc] == 'v'){
            a[*pr][*pc] = ' ';
            a[*pr+1][*pc] = 'v';
            *pr += 1;
        }
        /* Else face down */
        else{
            a[*pr][*pc] = 'v';
        }
    }
    
    /* Moving right */
    else if (m == 'd'){
        /* If already facing right, move right and leave previous location blank */
        if (a[*pr][*pc] == '>'){
            a[*pr][*pc] = ' ';
            a[*pr][*pc+1] = '>';
            *pc += 1;
        }
        /* Else face right */
        else{
            a[*pr][*pc] = '>';
        }
    }
    
    /* Moving left */
    else if (m == 'a'){
        /* If already facing left, move left and leave previous location blank */
        if (a[*pr][*pc] == '<'){
            a[*pr][*pc] = ' ';
            a[*pr][*pc-1] = '<';
            *pc -= 1;
        }
        /* Else face left */
        else{
            a[*pr][*pc] = '<';
        }
    }
    
    /* Not correct control */
    else{
        printf("ERROR - Unknown control\n");
    }
    return a;
}
