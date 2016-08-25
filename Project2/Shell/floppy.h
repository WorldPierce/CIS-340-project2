
// defines path name maximum for shell. It is not necessarily defined. 
#ifndef PATH_MAX
#define PATH_MAX 2048
#endif

#ifndef INPUTMAX
#define INPUTMAX 4096
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
int fmnt = 0; 
int fd = 0;
int fatcount;
int sectorsperfat;
int sectorspercluster;
int rootentries;
int bytespersector;
int totalsectorcount;

// path node declaration: path.c
struct pathnode {
	char *entry;
	struct pathnode *next;
};

typedef struct pathnode path;
// note: this was put into path.c to make it compile correctly
// path *pathlist = 0; 

/* fucntion prototypes */
// floppy.c
void takecommand( int * , int * );

// help.c
int help(char **args); // help redefined in flopshell.c

// fmount.c
void mount( char **args );
int set_flop_parms();
void unmount( char **args );

// showfat.c
int showfat( char **args );
// located in structure.c //int getdata( int , off_t , size_t );

// structure.c
int structure( char **args );
int getdata( int , off_t , size_t );

// showsector.c
int showsector(int sector);
char *getsector(int sector, int sector_size);
void clearbuffer(char *buff, int size);
void printbuffer(char *buff, int size);

// traverse.c
int traverse ( char **args );

// readline.c 
void readline( int, int, int ); 

// folderdepth1.c
void folderdepth1( int, int, int, char * ); 

// removespaces.c
void removespaces(char *); 

// path.c
int pathlength(void);
void addpath(char *e);
void removepath(char *e);
void patherror(char *e, int errnum);
char *mkpathentry(char *e);
void deletepathnode(path *p);
void deletepathlist();

// flopshell.c
int args_size(char **args);
int cd(char **arg);
int quit(char **arg);
int pth(char **arg);
int fmount(char **args); // calls other mount.
int fumount(char **args); // calls other unmount.
#endif /* FLOPPY_H */
