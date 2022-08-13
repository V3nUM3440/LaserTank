#ifndef LIST /* Guards */
#define LIST

/*
Author ------- Shuber Ali Mirza
ID ----------- 20027047
list.h ------- Contains all the prototypes, declarations and macros for the laserTank program
Created ------ 23/MAR/2021
Last Updated - 23/MAR/2021
*/

/* Boolean data type */
#define False 0
#define True !False

typedef struct Position{
    int row;
    int col;
    char* face;
} Position;

typedef struct Node{
    Position data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} linkedList;

/* Declarations from list.c */
linkedList* listCreate(void);
void listInsertLast(linkedList* list, Position payload);
void listWriteLog(FILE* fp, linkedList* list);
void listFree(linkedList* list);

#endif /* LIST */