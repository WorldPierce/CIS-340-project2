#include "floppy.h"

void traverse ( char *input, char *filename, char *arg ) {
	int i, argument;
	
	if ( arg[1] == '-' && arg[2] == 'l' ) {
		argument = 1;
	} else {
		argument = 0;
	}

	/* Print table if arg -l */
	if (argument == 1) {
		printf( "\n\t*****************************" );
		printf( "\n\t** FILE ATTRIBUTE NOTATION **" );
		printf( "\n\t**                         **" );
		printf( "\n\t** R ------ READ ONLY FILE **" );
		printf( "\n\t** S ------ SYSTEM FILE    **" );
		printf( "\n\t** H ------ HIDDEN FILE    **" );
		printf( "\n\t** A ------ ARCHIVE FILE   **" );
		printf( "\n\t*****************************\n" );
	}

	for ( i = 0; i < 100; i++ ) {
		readline( 19 , i, argument );
	}

	printf( "\n\n");
};
