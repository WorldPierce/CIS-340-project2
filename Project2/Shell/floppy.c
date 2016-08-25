#include "floppy.h"

/*
help: 			DONE
quit: 			DONE
fmount: 		DONE
fumount: 		DONE
structure: 		DONE
traverse:
showsector:     DONE
showfat:        DONE
*/

int main() {
	int exit = 0;
	int mounted = 0;
	fmnt = 0;


	printf( "Enter command or type help for list of commands.\n\n");

	while( exit < 1 ) {
		takecommand( &mounted , &exit );
	}

	printf( "\nExiting floppy interface.\n\n");
	return 0;
}

void takecommand( int *mounted, int *exit ) {
	char input[20];
	int i = 0;
	char filename[255];


	printf( "floppy: ");
	scanf( "%s", input );

	if ( strcmp( input, "help" ) == 0 ) {
		help();
	} else if ( strcmp( input, "quit" ) == 0 || strcmp( input, "q" ) == 0 ) {
		*exit = 1;
	} else if ( strncmp( input, "fmount", 6 ) == 0 ) {
		if ( *mounted == 1 ) {
		printf("File already mounted. Please unmount to mount new file.\n\n");
	    } else{
		mount( input, mounted, filename );
		}
	} else if ( strcmp( input, "fumount" ) == 0 ) {
		unmount( mounted );
	} else if ( strcmp( input, "structure" ) == 0 ) {
		if(*mounted == 1){
			structure(fd);
		}else{
			printf("No File Mounted\n");
		}
	} else if ( strncmp( input, "traverse", 8 ) == 0 ) {
		if( *mounted == 0 ) {
		printf( "No image mounted.\n\n");
		}else {
			// old traverse( input, filename, mounted );
			traverse(input,filename,1);
		}
	} else if ( strncmp( input, "showsector", 10 ) == 0 ) {
		if( *mounted == 0 ) {
		printf( "No image mounted.\n\n");
		}else{
			showsector(10);
		}
	} else if ( strcmp( input, "showfat" ) == 0 ) {
		if( *mounted == 1 ){
		showfat(fd);
		}else{
			printf("No file mounted\n");
		}
	} else if ( strncmp( input, "stat",4 ) == 0 ) {
		printf( "Mounted : %d\n", *mounted);
		printf( "Filename : %s\n\n", filename);
	} else {
		printf( "\nCommand not recognized. \n\n" );
	}
}
