#include "floppy.h"

void removespaces(char * filename) {
	char* i = filename;
	char* k = filename;

	while(*k != 0) {
		*i = *k++;
		if(*i != ' ') {
			i++;
		}
	}
	
	*i = 0;
}
