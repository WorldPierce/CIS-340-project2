#include "floppy.h"

void showfat() {
	// replaced by global variables and set_flop_parm
	/* 
	int fatcount, sectorsperfat, sectorspercluster, rootentries, bytespersector;
	//	getdata is in structure.c
	fatcount = getdata(fd, 16, 1);
	sectorsperfat = getdata(fd, 22, 2);
	sectorspercluster = getdata(fd, 13, 1);
	rootentries = getdata(fd, 17, 2);
	bytespersector = getdata(fd, 11, 2);
	*/
	
	unsigned int t0=0,t1=0;
    unsigned char in[3];

    //setting fileid to point at begging of fat table (512 bytes)
    lseek(fd,bytespersector,SEEK_SET);
    //hortizontal
    printf("\t  0\t  1\t  2\t  3\t  4\t  5\t  6\t  7\t  8\t  9\t  a\t  b\t  c\t  d\t  e\t  f\n");
    //looping for entire FAT table must divide by 3 since we take 3 bytes at a time	//
	int i;
    for (i = 0; i < ((sectorsperfat) * (bytespersector))/3; i++) {
        //vertical index mod 8 since we take two entires per index
        if (i % 8 == 0 || i == 0) {
            printf("\n");
            printf("%4x", i*2);
        }
        //reading 3 chars(3 bytes) to buffer array
        read(fd,&in,3);
        //taking the 3 bytes and making two table entires, each 12 bits
        t0=(((int)in[1] & 0x000F)<<8) | ((int)in[0] & 0x00FF);
        t1 = (((int)in[2] & 0x00FF)<<4) | (((int)in[1]&0x00F0)>>4);
        //skips first two entires of the fat
      if(!(t0==0x0FF0)){
          if(t0 == 0){
           printf("\tfree");
          }
          else{
            printf("\t%4x",t0);
          }
          if(t1 == 0){
            printf("\tfree");
          }
          else{
           printf("\t%4x",t1);
          }
        //printf("\t%3x\t%3x", t0,t1);
      }
      else{
        printf("\t\t");
      }
}

    printf("\n");
}
