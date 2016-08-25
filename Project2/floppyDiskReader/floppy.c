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
	//char input[20];
	char input[30]; 
	char arg[5];
	int i = 0;
	char filename[255];

	printf( "floppy: ");

	scanf( "%s", input);

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
		} else {
			fgets( arg, 4, stdin );
			// old traverse( input, filename, mounted );
			traverse( input, filename, arg );
		}
	} else if ( strncmp( input, "showsector", 10 ) == 0 ) {
		if( *mounted == 0 ) {
		printf( "No image mounted.\n\n");
		} else {
			//**CHANGE** made it to take command line argument after showsector call
			int sector = 0;
			scanf("%d",&sector);
			if((int)sector > 0 && (int)sector < 2879){
				showsector((int)sector);
			}
			else{
				showsector(0);
			}
		}
	} else if ( strcmp( input, "showfat" ) == 0 ) {
		if( *mounted == 1 ){
		showfat(fd);
		}else{
			printf("No file mounted\n");
		}
	} else {
		printf( "\nCommand not recognized. \n\n" );
	}
}
