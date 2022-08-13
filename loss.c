#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loss.h"

/*
Author ------- Shuber Ali Mirza
ID ----------- 20027047
loss.c ------- Contains all functions related to the condition of losing
Created ------ 25/FEB/2021
Last Updated - 16/MAR/2021
*/

/* Determines wheather the player has lost or not */
/* pr = player row, pc = player col, er = enemy row, ec = enemy col, ed = enemy direction */
int loss(int pr, int pc, int er, int ec , char ed)
{
    int lost = False;
    
    /* If player in same row and lower column than enemy */
    if ((pr == er) && (pc < ec) && (ed == 'l')){
        lost = True;
    }
    /* If player in same row and higher column than enemy */
    else if ((pr == er) && (pc > ec) && (ed == 'r')){
        lost = True;
    }
    /* If player in same column and lower row than enemy */         
    else if ((pc == ec) && (pr < er) && (ed == 'u')){
        lost = True;
    }
    /* If player in same column and higher row than enemy */         
    else if ((pc == ec) && (pr > er) && (ed == 'd')){
        lost = True;
    }
    
    return lost;
}
