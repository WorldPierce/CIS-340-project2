#include "flopshell.h"

int abscmdlen(npath *current, char *e) {

	int length = 0; 
	length += strlen(current->entry);
	length += 1; // slash
	length += strlen(e);
	length += 1; // ending '\0'
	return length;
};

void makepathstring(char *p) {

	int c, pathstringlength = 0, size = pathlength();
	char *pathstring;
	
	// catch empty path
	if (pathlist == 0) {
		pathstring = (char *) malloc(sizeof(char)*6); // PATH=
		*(pathstring) = 'P';
		*(pathstring+1) = 'A';
		*(pathstring+2) = 'T';
		*(pathstring+3) = 'H';
		*(pathstring+4) = '=';
		*(pathstring+5) = '\0';
		p = pathstring;
		return; 
	};
	
	pathstringlength += 5; // for PATH=
	npath *current = pathlist;
	for ( c = 0; c < size; c++ ) {
		if (current != 0) {
			pathstringlength += strlen(current->entry)+1; // absolute path name (last / striped) + : or final \0
			current = (current->next); 
		} else {
			printf("makepathstring: pathlength has given a funny value\n");
		};
	}	
	
	pathstring = (char *) malloc( sizeof(char) * pathstringlength );
	
	current = pathlist;
	strcpy(pathstring, (current->entry));
	for  (c = 1; c < size; c++) {
		current = (current->next);
		strcat(pathstring, ":");
		strcat(pathstring, (current->entry));
	}
	
	
	p = pathstring;
	if (debug == 1) {
		printf("makepathstring: pathstring: %s \n",pathstring);
		printf("p: %s \n",p);
	}
}
	
char **envpath() {
	char **envp = ( char ** ) malloc( sizeof(char *) * 2 );
	char *c;
	makepathstring(c);
	*(envp) = c; 
	*(envp + 1) = '\0';
	if (debug == 1) printf("*envp: %s\n",*envp); 
	return envp; 
/* 
	int size = pathlength();
	char **envp = ( char ** ) malloc( sizeof(char *) * (size + 1));
	if (pathlist == 0) {
		*envp = '\0';
		return envp;
	};
	
	int c,len;
	char *pt; 
	npath *current = pathlist;
	for (c = 0; c < size ; c++ ) { 
		len = strlen(current->entry);
		pt = (char *) malloc(sizeof(char)*(len +1));
		*(envp + c) = pt;
	};
	*(envp + c) = '\0';
	return envp;
*/
};

void deleteenvp(char **envp) {
	free(*(envp));
	free(envp);
	if (debug == 1) printf("deleteenvp: deleted, hopefully.\n");

/*
	int c = 0; 
	while ( *(envp + c) != '\0') {
		free(*(envp + c));
	};
	free(envp);
*/
};
		
		
/*	int pathlength(void)
 *	input: 	void
 *	returns:	int
 *	purpose:	returns the number of path nodes in the pathlist
 */
int pathlength(){
	if (pathlist == 0) return 0;// printf("you're dumb"); 
	
	int c = 0; 
	npath *current = pathlist; 
	while (current->next) {
		current = current->next;
		c++;
	};
	c++;
	if (debug == 1) printf("path:pathlength = %d\n", c); 
	return c;
};

/*	void printpath()
 *	input: 		void
 *	returns:	void
 *	purpose:	prints current path to stdout
 */
void printpath(void) {
	printf("path: ");
	if (pathlist == 0) {
		printf("\n");
		return; 
	};
	npath *current = pathlist;
	// check if first path node exists. If so, print. 
	if (current) printf("%s", current->entry);
	// check if more paths exist. If so, print. 
	while ( current->next ) {
		current = (current->next);
		printf(":%s", current->entry);
	};
	// end with newline.
	printf("\n");
}; 
	
/*	void addpath( const char *e )
 *	input:		absolute path in null terminated string
 *	returns:	void
 *	error:		prints message to stdout
 *	purpose:	adds a path node path list
 */
void addpath(char *e) {
	// variables
	npath *pnode, *last; 
	char *pe; 
	
	// if last slash exists, strip it
	striplastslash(e);
	// expects absolute path 
	
	// check if string e is in path list
	if ( isinpath(e) ) {
		printf("path: %s is already in path list.\n",e);
		printf("path: no new path added.\n"); 
		return;
	};
	
	// find last npath node
	last = findlast(); 
	
	// check if string has length and make string persistent.
	if ( pe = mkpathentry(e) ) {
		// make pnode
		pnode = (struct pathnode *) malloc(sizeof(struct pathnode));

 		// set pnode
		pnode->entry = pe;
		pnode->next = 0;

		// temp is already set at tail
		if (pathlist == 0) {
			pathlist = pnode;
		}
		else last->next = pnode;

		// should be added
		printf("path: %s added to path list\n",e);
	}; 
};
 
void striplastslash(char *e) {
 	int c = 0; 
 	while ( *(e+c) != '\0') c++;
 	if ( c != 0 && *(e+c-1) == '/' ) *(e+c-1) = '\0';
};

// USES MALLOC!!!
char *makeabsolutepath(char *e) {
	int length = strlen(e);
	char *absolute; 
	if ( *e != '/' ) {
		char *currentpath; 
		currentpath = getcwd(0,0); 
		length += strlen(currentpath);
		absolute = (char *) malloc(sizeof(char)*length);
		strcpy(absolute, currentpath);
		strcat(absolute,"/"); 
		strcat(absolute,e);
	} else {
		length = strlen(e);
		absolute = (char *) malloc(sizeof(char)*length); 
		strcpy(absolute, e); 
	};
	return absolute; 
};
	
 
 /*	int isinpath(char *e)
  *	input:		null terminated string
  *	return:		0 is string is not in path list, 1 otherwise.
  *	purpose:	determine is a path is in string list
  */
int isinpath(char *e) {
	
 	if ( pathlist == 0 ) return 0;
 	else if ( strcmp(e,(pathlist->entry)) == 0 ) return 1;
 	else if ( pathlist->next == 0 ) return 0;
 	else {
 		npath *current = pathlist->next;
 		do {
 			if ( strcmp(e,current->entry) == 0 ) return 1;
 		} while ((current = current->next));
 	}; 
	return 0; 
}; 

/*	void removepath( const char *e )
 *	input:		absolute path name in null terminated string
 *	returns:	void.
 *	error:		prints error to stdout
 *	purpose:	removes a path node if exists.
 */
void removepath(char *e) {
	// check to see path list has entries
	if ( pathlist == 0 ) {
		patherror(e,3);
		return;
	};
	
	// variables: 
	npath *current = pathlist;
	npath *next = (current->next);
	
	// strip last slash
	striplastslash(e);
	// expects absolute path
 
	// ckeck: is e in first node
	if ( strcmp(e,(current->entry)) ) {
		// no
		// check: is there another node to check?
		while ( (current->next) != 0 ) {
			// yes	
			// check: is e the next node?
			if ( !strcmp(e,(next->entry)) ) {
				// yes: remove next node
				current->next = (next->next);
				printf("path: %s is removed from path list.\n",e);
				break;
			} else {
				// no: advance nodes
				current = next; 
				next = (current->next);
			};
		};
			// no: e is not in path list.
		patherror(e,3);
	} else {
		// yes: remove first node
		// check: is there a next node?
		if ( next != 0 ) {
			// yes: change head of path list
			pathlist = next;
			deletepathnode(current);
		} else {
			// no: set pathlist to 0
			pathlist = 0;
			printf("path: %s is removed from path list.\n",e);
			deletepathnode(current);
		};
	};
};

/*	void patherror( char *e, int errnum )
 *	input:		null terminated string
 *	return:		void
 *	purpose:	prints error message to stdout
 */
void patherror( char *e, int errnum) {
	if (errnum == 1) printf("path: %s already in path list.\n",e);
	else if (errnum == 2) printf("path: path has zero length.\n");
	else if (errnum == 3) printf("path: %s is not in path list.\n",e);
};

/* 	npath *findlast()
 *	input:	void
 *	return:	npath pointer
 *	purpose:find last npath in path list. 
 */
npath *findlast() {
	if (pathlist == 0) return pathlist;
	
	npath *last,*temp = pathlist; 
	
	do {
		last = temp;
		temp = temp->next;
		} while (temp); 
	return last; 
};

/* char *mkpathentry( const char *e )
 * input: null terminated char array; 
 * returns: null terminated char array
 * error: returns 0
 * purpose: create a persistent string stored into calloc memory space.
 *          If an error occurs, no memory is allocated.
 */
char *mkpathentry( char *e ) {
	/* declare variables */
	char *pe = 0;
	int c = 0;
	
	// count string size
	while (*(e+c) != '\0') c++;
 
	// if string does not have zero length, make a permanent string
	if ( c != 1 ) {
		pe = (char *) malloc( sizeof(char)*c );
		strcpy(pe,e);
	} else {
		patherror(e,2);
	};
	return pe;
};

/* void deletepathnode( path *p )
 * input: path *p : ONLY PASS PATH NODES!! FREES DYNAMIC ALLOCATED MEMORY
 * return: void
 * purpose: frees path node's string and path node
 */
void deletepathnode( npath *p ) {
	// make sure p is not empty.
	if (p == 0) return;
	if (debug == 1) printf("path:delete: %s\n",p->entry); 
	// free allocated memory
	free((p->entry));
	free(p);
};

void deletepathlist() {
	if ( pathlist == 0 ) return;
	
	npath *current = pathlist;
	npath *next = current->next; 
	while ( next ) {
		deletepathnode(current);
		current = next;
		next = current->next;
	};
	deletepathnode(current);
};

