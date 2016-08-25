Group Members and their contribution (in percentage) :
	
	Group B:
	Jonathan Cohen	(33.33%)
	William Pierce 	(33.33%)	
	Jacob Lemanowicz(33.33%)

----------------------------------------------------------------
Project Description:
	Floppy shell that supports linux shell commands in addition to the floppy console commands we implemented in part 1. Also contains 3 additional internal commands:
quit: exit the floppy shell
cd: change directories
path: showing the path
----------------------------------------------------------------
Compling Instructions:
Part 1:
wipierce@grail:~/Group_G/part2$ make
gcc -o Flopshell help.c fmount.c showfat.c structure.c showsector.c transverse.c path.c flopshell.c readline.c removespaces.c folderdepth1.c

wipierce@grail:~/Group_G/part2$ ./Flopshell
----------------------------------------
Sample Test Run:
(NOTE: must fmount an image file in the current directory before using floppy commands)
shell# help

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

shell# showfat
	  0	  1	  2	  3	  4	  5	  6	  7	  8	  9	  a	  b	  c	  d	  e	  f

   0			free	   4	 fff	   6	 fff	 fff	   9	 fff	 fff	   c	 fff	 fff	 fff	  10
  10	  11	 fff	 fff	 fff	  15	 fff	  17	 fff	 fff	 fff	 fff	 fff	  1d	 fff	  1f	  20
  20	 fff	 fff	free	free	free	free	free	free	free	free	free	free	free	free	free	free
  30	free	free	free	free	free	free	free	free	free	free	free	free	free	free	free	free
	free	free	free	free	free	free

(output omitted for brevity……………)
shell# structure

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

hell# path + /usr
cmd: path + /usr
path: /usr added to path list

shell# traverse
cmd: traverse

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

----------------------------------------------------------------
Existence of Bugs (un-finished sections):

Does not support input redirection and does not support piping at this time.


	
		