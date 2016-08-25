#include "flopshell.h"

// function prototype

int showsector(char **args) {

	int size = args_size(args);
	
	if ( size == 1 ) {
		printf("showsector: Which sector?\n");
		return 1;
	};
	
	if ( size > 2 ) {
		printf("showsector: invalid input.\n");
		printf("showsector [sector number]\n");
	}; 
	
	if ( (atoi(args[1])) >= totalsectorcount ) {
		printf("showsector: error: out of bounds. \n");
	};
	
	int sector = atoi(args[1]); 
	char *buffer = getsector(sector, bytespersector);
    printbuffer(buffer, bytespersector);
    free(buffer);
    return 1;
};

char *getsector(int sector, int sector_size) {
  char *buffer = (char *) malloc(sizeof(char)*sector_size);
  clearbuffer(buffer, sector_size);

  long sector_start = ((long) sector_size) * sector;
  long off_set = lseek(fd, sector_start, SEEK_SET);
  int r_size = read(fd, buffer, sector_size);

  return buffer;
};

void clearbuffer(char *buffer, int size) {
    int c;
    for (c = 0; c < size; c++) {
        *(buffer + c) = '\0';
    };
};

void printbuffer(char *buffer, int size) {
    int c;
  	int column_size = 3;
    printf("%*c  ",column_size,' ');
    for (c = 0; c < 16; c++) printf("%*x ",column_size,c);

    for(c = 0; c < size; c++) {
        if (c%16 == 0) printf("\n%*x: ",column_size,c);
        printf("%*x ",column_size,(unsigned char) *(buffer + c));
    };
    printf("\n");
};

// for testing
/*
int main(int argc, char *argv[]) {
  int f = open("imagefile.img", O_RDONLY,0);
  int sector;
  if (argc > 1) {
    sector = atoi(argv[1]);
  } else {
    sector = 0;
  };
  showsector(f,sector,512);
};

*/
