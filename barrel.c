#include <stdio.h>
#include <stdlib.h>
#include "barrel.h"

/*
Author ------- Shuber Ali Mirza
barrel.c ----- Contains functions related to functionality of barrels
Created ------ 16/MAR/2021
Last Updated - 19/MAR/2021
*/

void explode(char** a, int r, int br, int bc)
{
    int i,j;
    
    for (i=-1 ; i<2 ; i++){
        for (j=-1 ; j<2 ; j++){
            if (a[br+i][bc+j] != '#'){
                a[br+i][bc+j] = 'X';
            }
        }
    }
}