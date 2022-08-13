#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "map.h"
#include "movement.h"
#include "shoot.h"
#include "loss.h"
#include "list.h"

/*
Author ------- Shuber Ali Mirza
ID ----------- 20027047
main.c ------- Contains the main function that makes the laser tank game
Created ------ 25/FEB/2021
Last Updated - 23/MAR/2021
*/

int main(int argc, char* argv[])
{   
    /*
    row = map rows
    col = map columns
    pR = player rows
    pC = player cols
    pr = pointer to player row
    pc = pointer to player col
    er = enemy row
    ec = enemy col
    br = variable to read barrel row
    bc = variabel to read barrel col
    pd = player direction
    ed = enemy direction
    a = array that stores map
    player = Position struct that stores player row, col and face/action
    */
    int row, col, pR, pC, *pr, *pc, er, ec, br, bc;
    char pd, ed;
    char** a;
    Position* player = malloc(sizeof(Position));
    /* If LOG defined, create linked list and open log.txt for writing */
    #ifdef LOG
        FILE *lP = fopen("log.txt", "w");
        linkedList* list = listCreate();
    #endif
    /* Variable for losing status */
    int lost = False;
    /* Variable to store user input */
    char option[20];
    
    /* Opening file for reading map details */
    FILE *fP = fopen(argv[1], "r");
    /* Initializing map */
    fscanf(fP, "%d,%d", &row, &col);
    a = map(row, col);
    /* Reading and making player position into pointers */
    fscanf(fP, "%d,%d,%c", &pR, &pC, &pd);
    pr = &pR;
    pc = &pC;
    /* Reading enemy location */
    fscanf(fP, "%d,%d,%c", &er, &ec, &ed);
    /* Reading all remaining entries as barrels */
    while(!feof(fP)){
        fscanf(fP, "%d,%d", &br, &bc);
        /* If barrel out of bounds, display error and continue to the next */
        if ((BETWEEN(1, row-2, br) == False) || (BETWEEN(1, col-2, bc) == False)){
            printf("ERROR - Barrel at %d, %d Out of Bounds\n", br, bc);
            sleep(1);
        }
        else{
            a[br][bc] = 'B';
        }
    }
    /* Closing map file */
    fclose(fP);
    
    /* Checking if player and enemy are within the map */
    if ((BETWEEN(1, row-2, *pr) == False) || (BETWEEN(1, col-2, *pc) == False)){
        printf("ERROR - Player not in range (Map size includes wall, index starts at 0)\n");
    }
    else if ((BETWEEN(1, row-2, er) == False) || (BETWEEN(1, col-2, ec) == False)){
        printf("ERROR - Enemy not in range (Map size includes wall, index starts at 0)\n");
    }
    else{
        /* Assigning player and enemy locations */
        pLoc(a, *pr, *pc, pd); /* Player */
        pLoc(a, er, ec, ed); /* Enemy */

        /* Adding location and face details to Position struct */
        player->row = *pr;
        player->col = *pc;
        player->face = convert(a[*pr][*pc]);
        /* If LOG defined, insert Position struct at end of linked list */
        #ifdef LOG
            listInsertLast(list, *player);
        #endif

        /* While not lost and won */
        while ((lost == False) && (a[er][ec] != 'X') && (a[*pr][*pc] != 'X')){
            system("clear");

            /* Printing map */
            printArr(a, row);
            printf("%d, %d, %s\n\n", player->row, player->col, player->face);

            /* Instructions */
            printf("Rules:\n");
            printf("--> If player shoots enemy tank ==================== WIN\n");
            printf("--> If player shoots barrel close to enemy ========= WIN\n");
            printf("--> If player moves in front of enemy tank ========= LOSS\n");
            printf("--> If player shoots barrel close to themselves ==== LOSS\n");

            /* Giving user options */
            printf("\nW to Go/Face UP\n");
            printf("S to Go/Face DOWN\n");
            printf("A to Go/Face LEFT\n");
            printf("D to Go/Face RIGHT\n");
            printf("F to Shoot LASER\n");
            printf("Action: ");
            scanf("%s", option);

            /* If user enter more than one character, ignore */
            if (option[1] != '\0'){
                option[0] = '\0';
            }
            /* Making user input case insensitive */
            upper(option);

            /* If "W", moving up */
            if (strcmp(option, "W") == 0){
                /* If moving out of map */
                if ((*pr-1 == 0) && (a[*pr][*pc] == '^')){
                    printf("ERROR\n");
                }
                /* If moving to damaged area */
                else if ((a[*pr-1][*pc] == 'X') && (a[*pr][*pc] == '^')){
                    printf("ERROR\n");
                }
                /* If moving to barrel */
                else if ((a[*pr-1][*pc] == 'B') && (a[*pr][*pc] == '^')){
                    printf("ERROR\n");
                }
                /* If moving to same block as enemy */
                else if ((*pr-1 == er) && (*pc == ec) && (a[*pr][*pc] == '^')){
                    printf("ERROR\n");
                }
                else{
                    move(a, pr, pc, 'w');
                }
            }
            /* If "S", move down */
            else if (strcmp(option, "S") == 0){
                /* If moving out of map */
                if ((*pr+1 == row-1) && (a[*pr][*pc] == 'v')){
                    printf("ERROR\n");
                }
                /* If moving to damaged area */
                else if ((a[*pr+1][*pc] == 'X') && (a[*pr][*pc] == 'v')){
                    printf("ERROR\n");
                }
                /* If moving to barrel */
                else if ((a[*pr+1][*pc] == 'B') && (a[*pr][*pc] == 'v')){
                    printf("ERROR\n");
                }
                /* If moving to same block as enemy */
                else if ((*pr+1 == er) && (*pc == ec) && (a[*pr][*pc] == 'v')){
                    printf("ERROR\n");
                }
                else{
                    move(a, pr, pc, 's');
                }
            }
            /* If "A", move left */
            else if (strcmp(option, "A") == 0){
                /* If moving out of map */
                if ((*pc-1 == 0) && (a[*pr][*pc] == '<')){
                    printf("ERROR\n");
                }
                /* If moving to damaged area */
                else if ((a[*pr][*pc-1] == 'X') && (a[*pr][*pc] == '<')){
                    printf("ERROR\n");
                }
                /* If moving to barrel */
                else if ((a[*pr][*pc-1] == 'B') && (a[*pr][*pc] == '<')){
                    printf("ERROR\n");
                }
                /* If moving to same block as enemy */
                else if ((*pc-1 == ec) && (*pr == er) && (a[*pr][*pc] == '<')){
                    printf("ERROR\n");
                }
                else{
                    move(a, pr, pc, 'a');
                }
            }
            /* If "D", move right */
            else if (strcmp(option, "D") == 0){
                /* If moving out of map */
                if ((*pc+1 == col-1) && (a[*pr][*pc] == '>')){
                    printf("ERROR\n");
                }
                /* If moving to damaged area */
                else if ((a[*pr][*pc+1] == 'X') && (a[*pr][*pc] == '>')){
                    printf("ERROR\n");
                }
                /* If moving to barrel */
                else if ((a[*pr][*pc+1] == 'B') && (a[*pr][*pc] == '>')){
                    printf("ERROR\n");
                }
                /* If moving to same block as enemy */
                else if ((*pc+1 == ec) && (*pr == er) && (a[*pr][*pc] == '>')){
                    printf("ERROR\n");
                }
                else{
                    move(a, pr, pc, 'd');
                }
            }
            /* If "F", shoot laser */
            else if (strcmp(option, "F") == 0){
                shoot(a, row, *pr, *pc);
            }

            /* Updating Position struct after completing action */
            player->row = *pr;
            player->col = *pc;
            if ((*option) == 'F'){
                player->face = "Laser";
            }
            else{
                player->face = convert(a[*pr][*pc]);
            }
            /* If LOG defined, insert Position struct at end of linked list */
            #ifdef LOG
                listInsertLast(list, *player);
            #endif

            /* Checking if player lost after moving */
            lost = loss(*pr, *pc, er, ec, ed);
        }

        /* If player lost, enemy takes the win shot */
        if (lost == True){
            killShot(a, row, er, ec, *pr, *pc);
            printf("!!!!!!!!!!!! YOU LOST !!!!!!!!!!!!\n");
            sleep(1);
        }
        /* If barrel explodes close to player */
        else if (a[*pr][*pc] == 'X'){
            printf("!!!!!!!!!!!! YOU LOST !!!!!!!!!!!!\n");
            sleep(1);
        }
        else{
            printf("!!!!!!!!!!!! YOU WON !!!!!!!!!!!!\n");
            sleep(1);
        }
        system("clear");
    }
    
    /* If LOG defined, write linked list content to log.txt, close file and free list */
    #ifdef LOG
        listWriteLog(lP, list);
        fclose(lP);
        listFree(list);
    #endif
    
    /* Freeing memory allocated to Position struct */
    free(player);
    /* Freeing memory allocated to map */
    freeMem(a, row);
    
    return 0;
}
