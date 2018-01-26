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
/*
typedef struct { /* универс. структура элемента каталога: */
//	long ino; /* номер inode */
//	char name[NAME_MAX+1]; /* имя + завершающий '\0' */
//} Dirent;
int countp=0;
/* fsize: печатает размер файла с именем "name" */
void fsize(char *name)
{
	
    struct stat stbuf;

    if (stat(name, &stbuf) != 0) {
       // fprintf(stderr, "fsize: нет доступа к %s\n", name);
        return;
    }
	
    //if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
        dirwalk(name, fsize);
	//	printf("name:  %s\n", name);

		
    	
	//}
//printf("%8ld %s\n", stbuf.st_size, name);
//statread (name);

}
/* dirwalk: применяет fcn ко всем файлам из dir */
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
//printf("%s\n",name);
//strcat(path,strcat(name,"/stat"));
FILE * fd;	
fd=fopen(name, "r");
//printf("%s\n",pname);
if (fd == NULL)
	{
//		printf("невозможно открыть файл: %s\n", name);
		return 1;
	} else {	
	fscanf(fd,"%d %s",&pid,pname);
	//printf("%s\n", pid);
	//printf("%s\n", pname);
	if (strcmp(pname,"(java)") == 0) {
		//printf("sh: %d\n", pid);
		countp++;
		printf("%d\n", countp);
	}
	//printf("OK");

}
	fclose(fd);
	return 0;
}




int main() {

fsize("/proc/");
return 0;
}
