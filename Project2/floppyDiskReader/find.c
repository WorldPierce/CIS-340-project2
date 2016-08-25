#include "floppy.h"

typedef struct mynode list; 

struct mynode {
	int set;
	void *entry;
	int nfree;
	struct mynode *next;
	struct mynode *prev;
}; 

list *newlistnode() {
	struct mynode *list = (struct mynode *) calloc(sizeof(struct mynode));
};

void addtolist(void *e, int needsfreed, list *listname) {
	list *current = listname; 
	while (current->next != 0) current = current->next; 
	
	list new = newlistnode(); 
	new->entry = e;
	new->nfree = needsfreed; 
	new->prev = listname; 
	
	listname->next = new;
}; 


void path(); 
