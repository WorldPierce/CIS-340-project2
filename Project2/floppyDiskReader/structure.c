#include "floppy.h"

void structure() {
	
	// replaced by set_flop_parm(), uses global variables by same name.
	/* 
	//int file;
	int fatcount, sectorsperfat, sectorspercluster, rootentries, bytespersector;
	//char buf[1];
	//file = open( filename, O_RDONLY, 0);
	fatcount = getdata(fd, 16, 1);
	sectorsperfat = getdata(fd, 22, 2);
	sectorspercluster = getdata(fd, 13, 1);
	rootentries = getdata(fd, 17, 2);
	bytespersector = getdata(fd, 11, 2);
	*/
	
	if (fmnt) {
		printf("\nnumber of FAT:                  %3d\n", (int) fatcount );
		printf("number of sectors used by FAT:  %3d\n", (int) sectorsperfat );
		printf("number of sectors per cluster:  %3d\n", (int) sectorspercluster );
		printf("number of ROOT Entries:         %3d\n", (int) rootentries );
		printf("number of bytes per sector:     %3d\n", (int) bytespersector );
		printf("---Sector #---   ---Sector Types---\n");
		printf("      0\t\t\tBOOT\n");
		printf("   %02d -- %02d\t\tFAT1\n", (sectorsperfat*0)+1, (sectorsperfat));
		printf("   %02d -- %02d\t\tFAT2\n", (sectorsperfat*1)+1, (sectorsperfat*2));
		printf("   %02d -- %02d\t\tROOT DIRECTORY\n\n", 
			(sectorsperfat*fatcount)+1, (rootentries / 16)+(sectorsperfat*fatcount));
	};
};

int getdata( int file, off_t offset, size_t size) {
	char buf[size];
	int value = 0, i = 0;

	lseek( file, offset, SEEK_SET);
	read(file, buf, size);

	for ( i = size - 1; i >= 0; i-- ) {
		value = value<<8;
		value = (value | ((unsigned char) *(buf+i)));
	};

	return value;
}; 
