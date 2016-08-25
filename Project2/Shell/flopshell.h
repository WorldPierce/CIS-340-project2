
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
int totalsectorcount;

int inputmax;
char **args; 
char **envpg;

int debug; 

// path node declaration: path.c


struct pathnode {
	char *entry;
	struct pathnode *next;
};

typedef struct pathnode npath;

npath *pathlist;
// note: this was put into path.c to make it compile correctly
// path *pathlist = 0; 

/* function prototypes */
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
int showsector(char **args);
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
void makepathstring(char *p);
char **envpath();
void deleteenvp(char **envp);
int pathlength(void);
void addpath(char *e);
void striplastslash(char *e);
char *makeabsolutepath(char *e); 
void removepath(char *e);
void patherror(char *e, int errnum);
npath *findlast(void);
char *mkpathentry(char *e);
void deletepathnode(npath *p);
void deletepathlist();

// flopshell.c
int abscmdlen(npath *current, char *e);
int args_size(char **args);
int pointer_array_size( char **ptar );

void print_pointer_array(char **ptar);
void split(char *line);
int flop_cmd(char **args);
int cd(char **arg);
int quit(char **arg);
int squit(); 
int path(char **arg);
int fmount(char **args); // calls other mount.
int fumount(char **args); // calls other unmount.
char *get_line(void);
#endif /* FLOPPY_H */
