#include <stdio.h>

int main ()
{
char * ppid[5]={0};
FILE * fd;	
fd=fopen("/proc/self/stat", "r");
	
if (fd == NULL)
	{
		printf("невозможно открыть файл");
		return 1;
	} else{

	fscanf(fd, "%*d %*s %*c %d", &ppid);
	printf("%d\n", ppid);
	fclose(fd);

	return 0;
	}
}
