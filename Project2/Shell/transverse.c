#include "flopshell.h"

int traverse ( char **args ) {
	int i, argument = 0;
	int size = args_size(args);
	size++;
	if (args[1] != '\0') {
	// check for correct argument
	if ( size > 1 ) {
		if ( strncmp( *(args+1), "-l",2) ) { 
			printf("traverse: %s is not a valid option.\n", *(args +1));
			printf("traverse: -l is the only valid option.\n");
		} else {
			argument = 1;
		};
	};
	
	};
	
	// should work past here
	
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

	printf("\n\n");
	
	return 1; 
};
