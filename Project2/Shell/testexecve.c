#include <stdio.h>

int pointer_array_size(char **ptar); 
void print_pointer_array(char **ptar); 

int pointer_array_size( char **ptar ) {
	int c = 0; 
	while ( *(ptar + c) != '\0' ) c++;
	return c;
};

void print_pointer_array( char **ptar ) {
	int c,size = pointer_array_size( ptar ); 
	printf("pointer_array_size: %d\n",size);
	for (c = 0; c < size ; c++ ) {
		printf("*(ptar + %d): %s \n",c,*(ptar+c));
	};
}; 

int main( int argc, char **argv, char **envp ) {
	print_pointer_array( envp );
	print_pointer_array( argv );
	printf("argc: %d \n",argc); 	
	return 0; 
};
