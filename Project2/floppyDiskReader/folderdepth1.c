#include "floppy.h"

void folderdepth1( int secnum, int i, int argument, char * foldername ) {
	char argv[3], name[9], ext[4], attrib[2], cluster[3], date[3], time[3], stopcheck[3];
	char min[3], hour[3], sec[3];
	int filesize[4];
	int file, isfolder = 0, tcluster, temp, tattrib, k, tcheck, tdate;
	int timemin, timehour, timesec, dateday, datemonth, dateyear;
	int  t1 = 0;

		clearbuffer(ext, 4); clearbuffer(name, 9);
		clearbuffer(date, 3); clearbuffer(time, 3);
		clearbuffer(min, 3); clearbuffer(sec, 3);
		clearbuffer(hour, 3);

		lseek (fd, secnum*bytespersector, SEEK_SET);
		lseek (fd, 32*i , SEEK_CUR );

		read(fd, name, 8);
		read(fd, ext, 3);
		read(fd, attrib, 2);
		lseek(fd, (secnum*bytespersector)+(32*i)+26, SEEK_SET);
		read(fd, cluster, 3);
		lseek(fd, (secnum*bytespersector)+(32*i)+24, SEEK_SET);
		read(fd, date, 3);
		lseek(fd, (secnum*bytespersector)+(32*i)+22, SEEK_SET);
		read(fd, time, 2);
		lseek(fd, (secnum*bytespersector)+(32*i)+28, SEEK_SET);
		read(fd, filesize, 4);
		lseek(fd, 0, SEEK_SET);

		/* Check #1 to see if file that is read should actually be printed */
		tcheck = 1;
		lseek (fd, secnum*bytespersector, SEEK_SET);
		lseek (fd, 32*i, SEEK_CUR );
		read(fd, stopcheck, 3);
		tcheck = (int) (stopcheck[1] &0x0F );
		tcheck << 8;
		temp = (int) stopcheck[0];
		tcheck = tcheck | temp;
		if ( tcheck == 0 ) {
			goto label;
		}

		/* Check #2 to see if first character in filename is valid */
		clearbuffer(stopcheck, 3);
		tcheck = 1;
		lseek(fd, secnum*bytespersector, SEEK_SET);
		lseek(fd, 32*i, SEEK_CUR);
		read(fd, stopcheck, 1);
		if ( isalpha(stopcheck[0]) > 0 || isdigit((int)stopcheck[0]) > 0 || stopcheck[0] == '.' ) {
		} else {
			goto label;
		}

		/* Getting the attribute of the file */
		tattrib = (int) (attrib[1] &0x0F );
		tattrib << 8;
		temp = (int) attrib[0];
		tattrib = tattrib | temp;
		if ( tattrib == 15 ) {
			goto label;
		}

		/* Printing the attribute if arg -l */
		if ( argument == 1 ) {
			isfolder = 0;
			if ( tattrib == 32 ) {
				printf( "\n-A---" );
			} else if ( tattrib == 1 ) {
				printf( "\n-R---" );
			} else if ( tattrib == 4 ) {
				printf( "\n-S---" );
			} else if ( tattrib == 2 ) {
				printf( "\n-H---" );
			} else if ( tattrib == 16 || tattrib == 0 ) {
				printf( "\n-----" );
				isfolder = 1;
			}
		}

		/* If no -l it checks for if the file is a folder */
		if ( argument == 0 ) {
			if ( tattrib == 16 || tattrib == 0 ) {
				isfolder = 1;
			}
		}

		/* Getting and printing last date modified goes here */
		if ( argument == 1) {
			dateday = (int) ( date[0] &0x1F );
			datemonth = (int) ( date[0] &0xE0 ) >> 5;
			temp = (int) ( date[1] &0x01) << 3;
			datemonth = temp | datemonth;
			dateyear = (int) ( date[1] &0xFE ) >> 1;
			dateyear = 1980 + dateyear;

			printf( "\t %2d/%2d/%d", datemonth, dateday, dateyear );
		}

		/* Getting and printing last time modified goes here */
		if ( argument == 1) {
			timesec = (int) ( time[0] &0x1F );
			timemin = (int) ( time[0] &0xE0 ) >> 5;
			temp = (int) ( time[1] &0x07) << 3;
			timemin = temp | timemin;
			timehour = (int) ( time[1] &0xF8 ) >> 3;

			if ( timehour < 10 ) {
				printf("  0%d:", timehour);
			} else {
				printf("  %2d:", timehour);
			}
			if ( timemin < 10 ) {
				printf("0%d:", timemin);
			} else {
				printf("%2d:", timemin);
			}
			if ( timesec < 10 ) {
				printf("0%d", timesec );
			} else {
				printf("%2d", timesec);
			}
		}

		/* Printing if it is a directory */
		if ( argument == 1 ) {
			if ( isfolder == 1 ) {
				printf( "\t\t<DIR>");
			} else {
				printf( "\t\t");
			}
		}

		/* Getting and printing filesize goes here */
		if ( argument == 1 ) {
			if ( filesize[0] != 0 ) {
				printf("\t%d", filesize[0]); 
			} else {
				printf("\t");
			}
		}

		/* Getting starting ID cluster */
		if ( argument == 1 ) {
			tcluster = (int) (cluster[1] &0x0F );
			tcluster << 8;
			temp = (int) cluster[0];
			tcluster = tcluster | temp;
		}

		removespaces(name);

		/* Printing file name, extension, and starting cluster number */
		if ( argument == 1 ) {
			if ( isfolder == 1 ) {
				printf( "\t/%s/%s   \t\t\t%2d", foldername, name, tcluster);
			} else {
				printf( "\t/%s/%s.%s   \t\t\t%2d", foldername, name, ext, tcluster);
			}
		} else {
			if ( isfolder == 1) {
				printf( "\n/%s/%s", foldername, name);
			} else {
				printf( "\n/%s/%s.%s", foldername, name, ext);
			}
		}

		/* Priting <DIR> if -l argument is not present */
		if ( argument != 1 ) {
			if ( isfolder == 1 ) {
				printf( "   \t\t\t<DIR>");
			}
		}

		label:
		;
}
