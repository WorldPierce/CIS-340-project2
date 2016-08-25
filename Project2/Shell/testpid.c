#include <stdio.h>
#include <unistd.h>

int main (void) {
	pid_t pid, cpid;

	pid = getpid(); 

	printf("pid: %d\n",pid); 
	cpid = fork();

	printf("cpid = fork(): %d\n",cpid); 

	if (pid == getpid()) {
		printf("parent is  waiting\n"); 
		wait(2);
		printf("parent done waiting.\n");
	} else {
		printf("cpid: %d\n",cpid);
	};
	return 0; 
}; 

