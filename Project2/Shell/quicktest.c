#include <stdio.h>
#include <string.h>

int main(void) {
	char *string = "string";
	char another[6]; 
	another[0] ='s';
	another[1] = 't';
	another[2] = 'r';
	another[3] = 'i';
	another[4] = 'n';
	another[5] = 'g';
	
	printf("string: %s, another: %s \n",string,another);
	printf("sizeof(string): %d, sizeof(another): %d \n", sizeof(string), sizeof(another));
	printf("strlen(string): %d \n",strlen(string));
	return 0; 
};
