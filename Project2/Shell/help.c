#include "flopshell.h"


int help(char **args) {
	printf( "\n***************************************************************************\n" );
	printf( "**  help: Show the help dialouge.                                        **\n" );
	printf( "**  quit or q: Leave the floppy console.                                 **\n" );
	printf( "**  fmount <img_file>: Mount a floppy image.                             **\n" );
	printf( "**  fumount: Unmount the mounted image.                                  **\n" );
	printf( "**  structure: List the structure of the floppy disk.                    **\n" );
	printf( "**  traverse: List the content in the root directory. Use -l as..        **\n" );
	printf( "**            .. argument to show more detailed information.             **\n" );
	printf( "**  showsector [sector num]: Show the contents of the specific sector.   **\n" );
	printf( "**  showfat: Show the content of the FAT table.                          **\n" );
	printf( "***************************************************************************\n\n" );
	return 1;
};
