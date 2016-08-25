#include "floppy.h"

void mount( char *input, int *mounted, char *filename ) {
	scanf( "%s", filename );
	printf("\nFilename : %s\n", filename);
	//int filetest;

	fd = open( filename, O_RDONLY );
	if ( fd < 0 ) {
		printf( "File not found, unable to mount.\n\n");
		*mounted = 0;
	} else {
		printf( "File mounted successfully.\n\n");
		*mounted = 1;
		fmnt = 1;
		set_flop_parms();
	};

	//close(filetest);
};

int set_flop_parms() {
	/* uses getdata in struct.c */
	if (fmnt) {
		fatcount = getdata(fd, 16, 1);
		sectorsperfat = getdata(fd, 22, 2);
		sectorspercluster = getdata(fd, 13, 1);
		rootentries = getdata(fd, 17, 2);
		bytespersector = getdata(fd, 11, 2);
		return 1;
	} else {
		printf("No floppy mounted.\n");
		return 0; 
	};		 
}; 

void unmount( int *mounted ) {
	if ( *mounted == 0 ) {
		printf( "No image mounted, cannot unmount.\n\n");
		return;
	} else {
		printf ( "File unmounted successfully.\n\n");
		*mounted = 0;
		close(fd);
		fmnt = 0;
	};
};
