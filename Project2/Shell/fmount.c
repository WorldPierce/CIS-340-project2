#include "flopshell.h"

//void mount( char *input, int *mounted, char *filename ) {
void mount( char **args ) {
	
	int size = args_size(args);
	if (size != 2) {
		printf("fmount: error: not valil input. \n");
		printf("fmount input: fmount [filename] \n");
		return;
	}; 
	
	if ( fmnt == 1 ) {
		printf("fmount: file already mounted. \n");
		return;
	};
	
	char *filename = *(args+1);

	fd = open( filename, O_RDONLY );
	if ( fd < 0 ) {
		printf( "File not found, unable to mount.\n\n");
	} else {
		printf( "File mounted successfully.\n\n");
		fmnt = 1;
		set_flop_parms();
	};
};

int set_flop_parms() {
	/* uses getdata in struct.c */
	if (fmnt) {
		fatcount = getdata(fd, 16, 1);
		sectorsperfat = getdata(fd, 22, 2);
		sectorspercluster = getdata(fd, 13, 1);
		rootentries = getdata(fd, 17, 2);
		bytespersector = getdata(fd, 11, 2);
		totalsectorcount = getdata(fd,19,2);
		return 1;
	} else {
		printf("No floppy mounted.\n");
		return 0; 
	};		 
}; 

void unmount( char **args ) {
	if ( fmnt == 0 ) {
		printf( "No image mounted, cannot unmount.\n\n");
		return;
	} else {
		printf ( "File unmounted successfully.\n\n");
		close(fd);
		fmnt = 0;
	};
};
