#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

/*
Author ------- Shuber Ali Mirza
ID ----------- 20027047
map.c -------- Contains all functions related to creating the map and populating
Created ------ 25/FEB/2021
Last Updated - 16/MAR/2021
*/

/* Creates a dynamic 2d array to make the map */
/* r = rows, c = columns */
char** map(int r, int c)
{
    int i,j;
    char** a = calloc(r, sizeof(char*)); /* Making pointers to each row */
    
    for (i=0 ; i<r ; i++){
        a[i] = calloc(c, sizeof(char)); /* Assigning seperate arrays to each pointer */
    }
    
    /* Populating map with spaces */
    for (i=1 ; i<r-1 ; i++){
        for (j=1 ; j<c-1 ; j++){
            a[i][j] = ' ';
        }
    }
    
    /* Making the walls */
    for (i=0 ; i<r ; i++){
        a[i][0] = '#';
        a[i][c-1] = '#';
    }
    for (i=0 ; i<c ; i++){
        a[0][i] = '#';
        a[r-1][i] = '#';
    }
    
    return a;
}

/* Converts string to upper case */
/* s = string */
void upper(char s[])
{
    int i=0;
    while (s[i] != '\0')
    {
        if (s[i] >= 'a' && s[i] <= 'z') 
        {
            s[i] = s[i] - 32;
        }
		i++;
    }
}

/* Sets players on the map */
/* a = array, pr = player row, pc = player col, pd = player direction */
char** pLoc(char** a, int pr, int pc, char pd)
{   
    /* If "U", character face = '^' */
    if (pd == 'u'){
        a[pr][pc] = '^';
    }
    /* If "D", character face = 'v' */
    else if (pd == 'd'){
        a[pr][pc] = 'v';
    }
    /* If "L", character face = '<' */
    else if (pd == 'l'){
        a[pr][pc] = '<';
    }
    /* If "R", character face = '>' */
    else if (pd == 'r'){
        a[pr][pc] = '>';
    }
    
    return a;
}

/* Prints out the map */
/* a = array, r = rows */
void printArr(char** a, int r)
{
    int i;
    
    for (i=0 ; i<r ; i++){
        printf("%s\n", a[i]);
    }
}

/* Frees memory allocated to map(array) */
/* a = array, r = rows */
void freeMem(char** a, int r)
{
    int i;
    
    /* Freeing memory of each column */
    for (i=0 ; i<r ; i++){
        free(a[i]);
        a[i] = NULL;
    }
    /* Freeing memory of pointers to columns */
    free(a);
    a = NULL;
}
