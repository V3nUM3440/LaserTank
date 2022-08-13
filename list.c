#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/*
Author ------- Shuber Ali Mirza
ID ----------- 20027047
list.c ------- Contains functions required for linked list
Created ------ 23/MAR/2021
Last Updated - 23/MAR/2021
*/

/* Makes linked list and initializes the head and tail nodes */
linkedList* listCreate(void)
{
    linkedList* list = malloc(sizeof(linkedList));
    Position new;
    new.face = "UNDEFINED";
    list->head = malloc(sizeof(Node));
    list->tail = malloc(sizeof(Node));
    
    list->head->data = new;
    list->head->next = list->tail;
    list->head->prev = NULL;
    
    list->tail->data = new;
    list->tail->prev = list->head;
    list->tail->next = NULL;
    
    return list;
}

/* Inserts Position struct at end of list */
void listInsertLast(linkedList* list, Position payload)
{
    if (strcmp(list->head->data.face, "UNDEFINED") == 0){
        list->head->data = payload;
        list->size++;
    }
    else if (strcmp(list->tail->data.face, "UNDEFINED") == 0){
        list->tail->data = payload;
        list->size++;
    }
    else{
        Node* new = malloc(sizeof(Node));
        new->data = payload;
        new->next = NULL;
        new->prev = list->tail;
        list->tail->next = new;
        list->tail = new;
        list->size++;
    }
}

/* Write Position struct from all nodes to file provided */
void listWriteLog(FILE* fp, linkedList* list)
{
    Node* curr = list->head, *next;
    int i;
    
    if (list->size > 0){
        for (i=0 ; i<list->size ; i++){
            next = curr->next;
            fprintf(fp, "%d, %d, %s\n", (curr->data).row, (curr->data).col, (curr->data).face);
            curr = next;
        }
    }
}

/* Frees all memory allocated to list and all it's nodes */
void listFree(linkedList* list)
{
    Node *curr, *new;
    curr = list->head;
    
    while (curr != NULL){
        new = curr->next;
        free(curr);
        curr = new;
    }
    free(list);
}