#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syscall.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/dir.h>
#include <wchar.h>

#define MAX_PATH 1024

void readp(char * pid){

char ppid[16];
char path[MAX_PATH]={};

strcat(path,"/proc/");
strcat(path,pid);
strcat(path,"/stat");
//printf("%s\n",path);
FILE * fd;


fd=fopen(path, "r");

if (fd == NULL)
	{
		printf("невозможно открыть файл");
		return;
	} else {
	
	fscanf(fd, "%s %*s %*c %s", pid, ppid);
	printf("%s\n", pid);
	fclose(fd);
	if (strcmp(pid,"1")!=0) 
		readp(ppid);
	else 
		return;
}

}

int main(int argc, char *argv[]) 
{
char pid[100];
	if (argc != 2) { 
		return 1;
	}	
	else 
	{
		readp(argv[1]);
	}
	return 0;
}

