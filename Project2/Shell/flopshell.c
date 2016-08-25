#include "flopshell.h"
#define FLOPPY "imagefile.img"
#include "mynode.h"


//built in commands
int num_cmds = 10;
char *flop_str[] = {"cd","help","quit","path","showfat","structure","showsector","traverse","fmount","fumount"};

int (*builtin_func[]) (char **) = {
  &cd,
  &help,
  &quit,
  &path,
  &showfat,
  &structure,
  &showsector,
  &traverse,
  &fmount,
  &fumount
};

int cd(char **args) {

  	if (args[1] == NULL) {
  		printf("cd: change directory to what? \n");   
  	} else {
  		if (chdir(args[1]) == -1) {
    		perror("cd");
    	} else {
    		char *cwd = getcwd(0,0);
    		printf("current directory: %s \n",cwd);
    		free(cwd);
  		};
  	return 1;
  	};
};

int squit() {
	debug = 0;
	deletepathlist();
	umount(args);
	return 1;
};

int quit(char **args) {
	deletepathlist();
	unmount (args); 
	return 0;
};

/*	int path( char **args )
 *	input:		char **args
 *	return:		int
 *	purpose:	does one of three things:
 *				1) print current path list
 *				2) add path to path list
 *				3) removes path from path list
 *	note:		Only accepts args with one or three words
 *				path [ + or - ] [pathname]
 *				prints error message with correct form if not.
 */
int path(char **args) {
	// get size of args
	int size = args_size(args);
	
	// if size == 1, then print path list
	if (size == 1) {
		printpath();
		return 1;
	};
	
	if (size != 3) {
		printf("Error: Usage: path [+ or -] [pathname]\n");
		return 1;
	};	 
	
	// strip last slash
	striplastslash(*(args+2));
	// make path absolute
	char *ae = makeabsolutepath(*(args+2));
	
	if ( **(args+1) == '+' ) {
		DIR *newdir = opendir(*(args+2));
		if (newdir == 0) {
			perror("path");
		} else {
			addpath(ae);
		};
	} else if ( **(args+1) == '-') {
		removepath(ae);
	}; 
	free(ae); 
	return 1;
};

int linux_cmd(char **args) {
	pid_t cpid, ppid;
	int status;
  
	cpid = fork();

	// fork failed
	if (cpid == -1) {
		perror("linux cmd fork");
		return 1;
	};
	
	
	if ( cpid == 0 ) {
    	// Child arguments
 		int exelen;
 		char exe[inputmax+1];
 		exe[inputmax] = '\0';
 		npath *current = pathlist;
 		while ( current != 0 ) {
 			strncpy(exe, current->entry,inputmax);
 			strcat(exe,"/");
 			strcat(exe,*args);
 			if ( !execve(exe,args,envpg) ) {
 				break;
 			};
 			current = current->next;
 		};
 		
 		printf("file or directory not found.\n");
		return 0;
  } else {
    	// Parent arguments
		waitpid(cpid, &status, 0);
    	//fflush(stdout);
  };

  return 1;
};

int flop_cmd(char **args) {
  int i;

  if (args[0] == NULL) {
    // no command
    return 1;
  };

  for (i = 0; i < num_cmds; i++) {
    if (strcmp(args[0], flop_str[i]) == 0) {
      return (*builtin_func[i])(args);
    };
  };
  //input isn't built in, check linux commands
  if (debug == 1) {
  	printf("not an internal command: to linux\n");
  	print_pointer_array(args);
  };
  return (int) linux_cmd(args);
};


int fmount( char **args ) {
	mount(args);
	return 1;
};

int fumount( char **args ) {
	unmount(args);
	return 1;
};

char *get_line(void) {

	struct mynode *list = createmynodelist();
    char entry;
	char *cmd;
	scanf("%c", &entry);
    while (entry != '\n' && entry != '\0' && entry!= EOF) {
        addmynode(entry,list);
        scanf("%c", &entry);

    }; 
    cmd = (char *) mynodetochararray(list);
    deletemynodelist(list);
    if (debug == 1) printf("cmd: %s\n",cmd);
    
    return cmd; 
};

 void split(char* line) {
	//parse the input up into seperate arguments
	int length = 0; 
	int c = 0, word = 0; 
	int nspaces = 0;
	int words = 0;
 
	while ( *(line + c) != '\n' && *(line +c) != '\0' ) c++; 
	c++;
	length = c; 


	for ( c = 0; c < length ; c++ ) {
		if ( *(line + c) == ' ') {
			nspaces++;
			*(line + c) = '\0';
		};
		
		if ( *(line + c) == '\n' ) {
			*(line + c) = '\0';
			break;
		}; 
	};
	
	words = nspaces + 2;
	char **nargs = (char **) malloc(sizeof(char *) * words); 
	//char *nargs[words];
	nargs[0] = line;
	for ( c = 0, word = 1; word < words ; c++ ) {
		if ( *(line + c) == '\0' ) {
			*(nargs+word) = (line + c+1); 
			//nargs[word] = (line + c);
			word++;
		};
	};
	nargs[(word-1)] = '\0'; 
	args = nargs;  
	if (debug == 1) print_pointer_array(args);			
};

void shell_loop(void) {
  char *line;
  int status; 

  do {

    printf("shell# ");
    line = (char *) get_line();
	if ( *line != '\n' ) {  
    	split(line);
    	status = flop_cmd(args);
    	if (debug == 1) print_pointer_array(args);
    	free(args);
    };
    free(line);

    fflush(stdout);
  } while (status);
};

/* int args_size(char **args)
 *	intput:		char **args
 *	return:		int
 *	purpose:	returns the number of words in args.
 */
int args_size(char **args) {
	int c = 0;
	while ( *(args + c) != '\0' ) c++;
	return c;
}; 

int pointer_array_size( char **ptar ) {
	int c = 0; 
	while ( *(ptar + c) != '\0' ) c++;
	return c;
}

void print_pointer_array( char **ptar ) {
	int c,size = pointer_array_size(ptar);
	printf("args size: %d\n",size);
	for (c = 0; c < size ; c++ ) {
		printf("*(args + %d): %s \n",c,*(ptar+c));
	};
}; 

int main(int argc, char **argv, char **envp) {
		
	debug = argc - 1; 
	if (debug == 1) {
		printf("argc: %d \n", argc);
		print_pointer_array( argv );
		print_pointer_array( envp ); 
	};
	envpg = envp;
	fmnt = 0;
	inputmax = 4096;
	fd = 0;
	pathlist = 0;
	addpath("/bin");
	addpath("/sbin");
  
  	// Run command loop.
  	shell_loop();

  	// add any clean up needed
  	return 0;
 };
