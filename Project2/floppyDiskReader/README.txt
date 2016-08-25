Group Members and their contribution (in percentage) :
	
	Group B:
	Jonathan Cohen	(33.33%)
	William Pierce 	(33.33%)	
	Jacob Lemanowicz(33.33%)

----------------------------------------------------------------
Project Description:
	Floppy console that supports a number of floppy disk related commands. Program repeatedly prints prompt and takes following user commands:
help - show commands of floppy console 
quit - leave floppy console
fmount <img_file> - mount floppy image 
fumount - unmount mounted image 
structure - list structure of floppy disk
traverse [-l] - list contents of root directory, -l to list all details
showsector [sector#] - show contents in hex dump of specified sector
showfat - show content of FAT table

----------------------------------------------------------------
Compling Instructions:
Part 1:
wipierce@grail:~/Group_G/part1$ make
gcc -o Floppy floppy.c help.c fmount.c showfat.c structure.c showsector.c transverse.c
wipierce@grail:~/Group_G/part1$ ./Floppy
----------------------------------------
Sample Test Run:
Part 1:
wipierce@grail:~/Group_G/part1$ ./Floppy
Enter command or type help for list of commands.

floppy: help
***************************************************************************
**  help: Show the help dialouge.                                        **
**  quit or q: Leave the floppy console.                                 **
**  fmount <img_file>: Mount a floppy image.                             **
**  fumount: Unmount the mounted image.                                  **
**  structure: List the structure of the floppy disk.                    **
**  traverse: List the content in the root directory. Use -l as..        **
**            .. argument to show more detailed information.             **
**  showsector [sector num]: Show the contents of the specific sector.   **
**  showfat: Show the content of the FAT table.                          **
***************************************************************************
floppy: fmount imagefile.img

Filename : imagefile.img
File mounted successfully.

floppy: structure

number of FAT:                    2
number of sectors used by FAT:    9
number of sectors per cluster:    1
number of ROOT Entries:         224
number of bytes per sector:     512
---Sector #---   ---Sector Types---
      0			BOOT
   01 -- 09		FAT1
   10 -- 18		FAT2
   19 -- 32		ROOT DIRECTORY

floppy: showsector 10
       0   1   2   3   4   5   6   7   8   9   a   b   c   d   e   f
  0:  f0  ff  ff   0  40   0  ff  6f   0  ff  ff  ff   9  f0  ff  ff
 10:  cf   0  ff  ff  ff  ff   f   1  11  f0  ff  ff  ff  ff  15  f0
 20:  ff  17  f0  ff  ff  ff  ff  ff  ff  ff  1d  f0  ff  1f   0   2
 30:  ff  ff  ff   0   0   0   0   0   0   0   0   0   0   0   0   0
 40:   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
 50:   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
 60:   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
 70:   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   ……………(many lines omitted)

floppy: showfat
	  0	  1	  2	  3	  4	  5	  6	  7	  8	  9	  a	  b	  c	  d	  e	  f

   0			free	   4	 fff	   6	 fff	 fff	   9	 fff	 fff	   c	 fff	 fff	 fff	  10
  10	  11	 fff	 fff	 fff	  15	 fff	  17	 fff	 fff	 fff	 fff	 fff	  1d	 fff	  1f	  20
  20	 fff	 fff	free	free	free	free	free	free	free	free	free	free	free	free	free	free
  30	free	free	free	free	free	free	free	free	free	free	free	free	free	free	free	free
  40	free	free	free	free	free	free	free	free	free	free	free	free	free	free	free	free
  50	free	free	free	free	free	free	free	free	free	free	free	free	free	free	free	free
…..(many lines omitted **may need to adjust window size to see properly formatted output)

floppy: traverse

/A.CLA
/ALOOP1.CLA
/ALOOP1.JAV
/ALOOP2.CLA
/ALOOP2.JAV
/ALOOP3.CLA
/ALOOP3.JAV
/B.CLA
/CONDIT.CLA
/CONDIT.JAV
/D.CLA
/DEMO.CLA
/DEMO.JAV
/DIR1   			<DIR>
/DIR1/.   			<DIR>
/DIR1/..   			<DIR>
/DIR1/DIR2   			<DIR>
/DIR1/C.CLA
/POLYTEST.CLA
/POLYTEST.JAV
/SOME.CLA

floppy: fumount
File unmounted successfully.

floppy: quit

Exiting floppy interface.

----------------------------------------------------------------
Existence of Bugs (un-finished sections):

	No Bugs in the following Project.


	
		