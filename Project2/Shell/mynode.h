
#ifndef _MYNODEH_
#define _MYNODEH_

#include <stdlib.h>
#include <stdio.h>
/* -used for variable input- */
struct mynode {
        int called;
        char c; 
        struct mynode *next; 
        struct mynode *prev;
};

struct mynode *createmynodelist(void);
void deletemynodelist(struct mynode *node);
void addmynode(char e, struct mynode *list);

char getmynodechar(struct mynode *node);
char getmynodecharat(int n, struct mynode *list);
struct mynode *getmynodeat(int n, struct mynode *list);
int mynodelistlength(struct mynode *node);
char lastmynodechar(struct mynode *node);
char *mynodetochararray(struct mynode *list);
void freechararray(char *array);

struct mynode *nextmynode(struct mynode *current);
struct mynode *prevmynode(struct mynode *current);
struct mynode *findtail(struct mynode *node);
struct mynode *findhead(struct mynode *node);

/*      ---      */
/*      test funct      */
/*
void printmynodelist(struct mynode *list);
void printmynodelistdetail(struct mynode *list);
void printmynodedetail(struct mynode *node);

int getmyarraysize(char *array);
void printmyarray(char *array);
*/
/*      ---     */

#endif
