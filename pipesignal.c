#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

int count1=0;
int count2=0;

void handler_sigusr1(int signalno)
{
	count1++;	
}

void handler_sigusr2(int signalno)
{
	count2++;
}

void handler_term(int signalno)
{
	printf("%d %d\n",count1,count2);
	exit(EXIT_SUCCESS);
}
int main()
{
signal(SIGUSR1, handler_sigusr1); 
signal(SIGUSR2, handler_sigusr2); 
signal(SIGTERM, handler_term); 

while(1) {
usleep(10000);
}
return 0;
}
