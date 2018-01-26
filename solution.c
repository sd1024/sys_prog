#include <stdio.h>
#include <string.h>
#include <syscall.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/dir.h>
#include <wchar.h>

#define MAX_PATH 1024

int countp=0;

void fsize(char *name)
{
	
    struct stat stbuf;

    if (stat(name, &stbuf) != 0) {

        return;
    }
	
        dirwalk(name, fsize);


}

void dirwalk(char *dir, void (*fcn)(char *))
{
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;
	if ((dfd = opendir(dir)) == NULL) {
		fprintf(stderr, "dirwalk: не могу открыть %s\n", dir);
		return;
	}

	while ((dp = readdir(dfd)) != NULL) {
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "...") == 0)
			continue; /* пропустить себя и родителя */
		if (strlen(dir)+strlen(dp->d_name) + 2 > sizeof(name))
			fprintf(stderr, "dirwalk: слишком длинное имя %s/%s\n", dir, dp->d_name);
		else {
			sprintf(name, "%s%s", dir, dp->d_name);
			//printf("%s\n",name);
			//(*fcn) (name);
			statread(name);
		}
	}

	closedir(dfd);
}


int statread (char * name)
{
char pname[1024];
int pid;

strcat(name,"/stat");
FILE * fd;	
fd=fopen(name, "r");

if (fd == NULL)
	{
		return 1;
	} else {	
	fscanf(fd,"%d %s",&pid,pname);

	if (strcmp(pname,"(genenv)") == 0) {
		//printf("sh: %d\n", pid);
		countp++;
		
	}


}
	fclose(fd);
	return 0;
}




int main() {

fsize("/proc/");
printf("%d\n", countp);
return 0;
}
