#include "mynode.h"


/*
doubly linked mynode list functions
*/

/*      mynode create and remove mynode list    */

// createmynodelist() returns a pointer to a new linked list
struct mynode *createmynodelist(void) {
        struct mynode *list = (struct mynode *) malloc(sizeof(struct mynode));
        list->called = 0;
        list->next = 0;
        list->prev = 0;
        return list;
};

// deletemynodelist(struct mynode *node) deletes and frees malloc memory 
// of all nodes in linked list containing mynode node
void deletemynodelist(struct mynode *node) {
        struct mynode *head = findhead(node);
        while (head->next !=0) {
                head = head->next; 
                free(head->prev);
        };
        free(head);
};

/*      list manipulation       */

// addmynode(char e, struct mynode *list) adds a node containing char e
// to linked list with head of mynode list
void addmynode(char e, struct mynode *list) {
        if (list->called == 0) {
                list->c = e;
                list->called=1;
                list->next=0;
                list->prev=0;
        } else {
                struct mynode *node = (struct mynode *) malloc(sizeof(struct mynode));
                struct mynode *tail = findtail(list);
                node->c = e;
                node->called = 1;
                node->prev = tail;
                node->next = 0;
                tail->next = node;
        };
};

/*      mynode list queries     */

// getintput gets input form file integer handle filedesc and stores it in linked list list
char getmynodechar(struct mynode *node) {
        char c; 
        c = (node->c);
        return c;
};

char getmynodecharat(int n, struct mynode *list) {
        int listlength = mynodelistlength(list);
        if ( n < 0 || n >= listlength ) return '\0';
        else {
                struct mynode *nthmynode = getmynodeat(n,list);
                return (nthmynode->c);
        };
};

struct mynode *getmynodeat(int n, struct mynode *list) {
        int listlength = mynodelistlength(list);
        if ( n < 0 ) return list;
        else if ( n == 0 ) return (struct mynode *) findhead(list);
        else if ( n == listlength - 1) return (struct mynode *) findtail(list);
        else if ( n >= listlength ) return (struct mynode *) findtail(list);
        else {
                struct mynode *current = (struct mynode *) findhead(list);
                int c = 0; 
                while ( c != n ) {
                        current=(current->next);
                };
                return current;
        };
};

// returns mynode list length 
int mynodelistlength(struct mynode *node) {
        if (node->called == 0) {
                return 0; 
        } else {
                int c = 0;
                struct mynode *head, *current;
                head = findhead(node);
                current = head;  
                while (current->next != 0) {
                        current = (current->next);
                        c++;
                };
                return c;
        };
};

// lastmynodechar(struct mynode *node) returns value of last linked list node
char lastmynodechar(struct mynode *node) {
        struct mynode *tail = findtail(node);
        return (tail->c);
};

char *mynodetochararray(struct mynode *list) {
        int listlength = mynodelistlength(list);
        if (listlength == 0) {
                char *array = (char *) malloc(sizeof(char)); 
                *array = '\0'; // added
                return array;
        } else {
                struct mynode *current = list;
                int c = 0;
                if (lastmynodechar(list) != '\0') listlength++;
                char *array = (char *) malloc(sizeof(char) * listlength + 1); 
                while (current->next != 0) {
                        *(array+c) = getmynodechar(current);
                        current=(current->next);
                        c++;
                };
                *(array+c) = getmynodechar(current);
                *(array+c+1) = '\0'; // added 
                return array;
        };
        
};

void freechararray(char *array) {
        free(array);
};

/*      mynode list iterators   */
struct mynode *nextmynode(struct mynode *current) {
        struct mynode *next = 0;
        if (current->next != 0) {
                next = (current->next); 
        }
        return next;
};

struct mynode *prevmynode(struct mynode *current) {
        struct mynode *prev = 0; 
        if (current->prev !=0) prev = (struct mynode *) (current-prev);
        return prev;
};

// *findtail(struct mynode *node) returns a pointer to the tail of the // linked list containing mynode *node
struct mynode *findtail(struct mynode *node) {
        if (node->next == 0) {
                return node;
        } else {
                struct mynode *current;
                current = node; 
                while (current->next != 0) {
                        current = (current->next);
                };
                return current;
        };
};

// findhead(struct mynode *node) returns a pointer to the head of linked list
// contianing node
struct mynode *findhead(struct mynode *node) {
        if (node->prev == 0) {
                return node;
        } else {
                struct mynode *current;
                current = node; 
                while (current->prev != 0) {
                        current = (current->prev);
                };
                return current;
        };
};

/*      ---      */

/*
test functions
*/
/*
// print a mynode list
void printmynodelist(struct mynode *list) {
        struct mynode *current = list;
        printf("----mynodelist output----\n");
        while (current->next != 0) {
                printf("%c",current->c);
                current = (current->next);
        }; 
        printf("%c", current->c);
        printf("----end\n----mynodelist output----\n");
};

void printmynodelistdetail(struct mynode *list) {
        struct mynode *current = list;
        while (current->next != 0) {
                printmynodedetail(current);
                current= (current->next);
        };
        printmynodedetail(current);
};
/*
void printmynodedetail(struct mynode *node) {
        printf("-------\n");
        printf("node: %x", node);
        printf("\n");
        printf("node: c: %c",node->c);
        printf("\n");
        printf("node: called: %d",node->called);
        printf("\n");
        printf("node: prev: %x",node->prev);
        printf("\n");
        printf("node: next: %x",node->next);
        printf("\n");
        printf("-------\n");
        
}; 

int getmyarraysize(char *array) {
        int c = 0; 
        while (*(array+c) != '\0' && c < 50) c++;
        c++;
        return c;
};

// accepts null term char array, prints to stdout.
void printmyarray(char *array) {
        int c = 0; 
        printf("----array output----\n");
        while (*(array+c) != '\0') {
                printf("%c",*(array+c));
                c++;
        };
        printf("----end\n----array output----\n");
};
*/
/*      ---     */
