
// defines path name maximum for shell. It is not necessarily defined. 
#ifndef PATH_MAX
#define PATH_MAX 2048
#endif

#ifndef FLOPPY_H
#define FLOPPY_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

/* shared variables */
//declaring file descriptor as universal variable -- good idea
int fmnt; 
int fd;
int fatcount;
int sectorsperfat;
int sectorspercluster;
int rootentries;
int bytespersector;


// path node declaration: path.c
typedef struct pathnode path;

struct pathnode {
	char *entry;
	struct pathnode *next;
};
// note: this was put into path.c to make it compile correctly
// path *pathlist = 0; 

/* fucntion prototypes */
// floppy.c
void takecommand( int * , int * );

// help.c
void help();

// fmount.c
void mount( char *, int *, char * );
int set_flop_parms();
void unmount( int * );

// showfat.c
void showfat();
// located in structure.c //int getdata( int , off_t , size_t );

// structure.c
void structure();
int getdata( int , off_t , size_t );

// showsector.c
void showsector(int sector);
char *getsector(int sector, int sector_size);
void clearbuffer(char *buff, int size);
void printbuffer(char *buff, int size);

// traverse.c
// old void traverse ( char *, char *, int * );
void traverse ( char *, char *, char * ); // traverse.c takes 1 in arg3 iff -L parm
void readline( int, int, int);
void folderdepth1( int, int, int, char * );
void removespaces ( char * );

// path.c
void addpath(char *e);
void removepath(char *e);
void patherror(char *e, int errnum);
char *mkpathentry(char *e);
void deletepathnode(path *p);

#endif /* FLOPPY_H */
