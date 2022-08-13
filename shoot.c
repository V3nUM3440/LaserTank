#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shoot.h"
#include "map.h"
#include "barrel.h"

/*
Author ------- Shuber Ali Mirza
ID ----------- 20027047
shoot.c ------ Contains all functions related to shooting the laser and destroying the tanks
Created ------ 25/FEB/2021
Last Updated - 23/MAR/2021
*/

/* Used to reset the blocks with laser to blank blocks */
/* a = array, r = rows, c = cols, pr = player row, pc = player col */
static void reset(char** a, int pr, int pc)
{
    int i;
    
    if (a[pr][pc] == '^'){
        i=pr-1;
        while (a[i][pc] == '|' || a[i][pc] == 'X'){
            if (a[i][pc] != 'X'){
                a[i][pc] = ' ';
            }
            --i;
        }
    }
    
    else if (a[pr][pc] == 'v'){
        i=pr+1;
        while (a[i][pc] == '|' || a[i][pc] == 'X'){
            if (a[i][pc] != 'X'){
                a[i][pc] = ' ';
            }
            i++;
        }
    }
    
    else if (a[pr][pc] == '<'){
        i=pc-1;
        while (a[pr][i] == '-' || a[pr][i] == 'X'){
            if (a[pr][i] != 'X'){
                a[pr][i] = ' ';
            }
            --i;
        }
    }
    
    else if (a[pr][pc] == '>'){
        i=pc+1;
        while (a[pr][i] == '-' || a[pr][i] == 'X'){
            if (a[pr][i] != 'X'){
                a[pr][i] = ' ';
            }
            i++;
        }
    }
}

/* Shoots a laser in the direction the player is facing until wall is hit */
/* a = array, r = rows, pr = player row, pc = player col */
void shoot(char** a, int r, int pr, int pc)
{
    int i;
    system("clear");
    /* Shooting up */
    if (a[pr][pc] == '^'){
        i=pr-1;
        while (a[i][pc] == ' ' || a[i][pc] == 'X'){
            if (a[i][pc] != 'X'){
                a[i][pc] = '|';
            }
            --i;
        }
        if (a[i][pc] == '^' || a[i][pc] == 'v' || a[i][pc] == '<' || a[i][pc] == '>'){
            a[i][pc] = 'X';
        }
        else if (a[i][pc] == 'B'){
            explode(a, r, i, pc);
        }
    }
    /* Shooting down */
    else if (a[pr][pc] == 'v'){
        i=pr+1;
        while (a[i][pc] == ' ' || a[i][pc] == 'X'){
            if (a[i][pc] != 'X'){
                a[i][pc] = '|';
            }
            i++;
        }
        if (a[i][pc] == '^' || a[i][pc] == 'v' || a[i][pc] == '<' || a[i][pc] == '>'){
            a[i][pc] = 'X';
        }
        else if (a[i][pc] == 'B'){
            explode(a, r, i, pc);
        }
    }
    /* Shooting left */
    else if (a[pr][pc] == '<'){
        i=pc-1;
        while (a[pr][i] == ' ' || a[pr][i] == 'X'){
            if (a[pr][i] != 'X'){
                a[pr][i] = '-';
            }
            --i;
        }
        if (a[pr][i] == '^' || a[pr][i] == 'v' || a[pr][i] == '<' || a[pr][i] == '>'){
            a[pr][i] = 'X';
        }
        else if (a[pr][i] == 'B'){
            explode(a, r, pr, i);
        }
    }
    /* Shooting right */
    else if (a[pr][pc] == '>'){
        i=pc+1;
        while (a[pr][i] == ' ' || a[pr][i] == 'X'){
            if (a[pr][i] != 'X'){
                a[pr][i] = '-';
            }
            i++;
        }
        if (a[pr][i] == '^' || a[pr][i] == 'v' || a[pr][i] == '<' || a[pr][i] == '>'){
            a[pr][i] = 'X';
        }
        else if (a[pr][i] == 'B'){
            explode(a, r, pr, i);
        }
    }
    /* Printing and sleeping map with laser */
    printArr(a, r);
    sleep(1);
    /* Reseting laser blocks to blank spaces after shooting */
    reset(a, pr, pc);
}

void killShot(char** a, int r, int pr, int pc, int er, int ec)
{
    int i;
    
    system("clear");
    
    /* Setting the loser to 'X' */
    a[er][ec] = 'X';
    
    /* Shooting up */
    if (a[pr][pc] == '^'){
        for (i=pr-1 ; i>er ; --i){
            a[i][pc] = '|';
        }
    }
    
    /* Shooting down */
    else if (a[pr][pc] == 'v'){
        for (i=pr+1 ; i<er ; i++){
            a[i][pc] = '|';
        }
    }
    
    /* Shooting left */
    else if (a[pr][pc] == '<'){
        for (i=pc-1 ; i>ec ; --i){
            a[pr][i] = '-';
        }
    }
    
    /* Shooting right */
    else if (a[pr][pc] == '>'){
        for (i=pc+1 ; i<ec ; i++){
            a[pr][i] = '-';
        }
    }
    
    /* Printing and sleeping map with laser */
    printArr(a, r);
    sleep(1);
}

/* Converts the direction characters to their string counter-parts */
/* pd = player direction */
char* convert(char pd)
{
    char* direction;
    
    if (pd == '^'){
        direction = "Up";
    }
    else if (pd == 'v'){
        direction = "Down";
    }
    else if (pd == '<'){
        direction = "Left";
    }
    else if (pd == '>'){
        direction = "Right";
    }
    
    return direction;
}
