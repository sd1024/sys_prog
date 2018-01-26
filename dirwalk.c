#include <stdio.h>
#include <string.h>
#include <syscall.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/dir.h>
//#define NAME_MAX 14 /* максимальная длина имени файла */
#define MAX_PATH 1024
/* dirwalk: применяет fcn ко всем файлам из dir */

//typedef struct { /* универс. структура элемента каталога: */
//long ino; /* номер inode */
//char name[NAME_MAX+1]; /* имя + завершающий '\0' */
//} Dirent;

/*
typedef struct { /* минимальный DIR: без буферизации и т.д. 
int fd; /* файловый дескриптор каталога 
Dirent d; /* элемент каталога 
} DIR;

DIR *opendir(char *dirname);
Dirent *readdir(DIR *dfd);

void closedir(DIR *dfd);
*/
/* fsize: печатает размер файла "name" */

void fsize(char *name)
	{
	struct stat stbuf;

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: нет доступа к %s\n", name);
		return;
	}

	//if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);
		//printf("%8ld%s\n", stbuf.st_size, name);
		//printf("%s\n", name);
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
			sprintf(name, "%s/%s", dir, dp->d_name);
			printf("%s\n",name);
			//(*fcn) (name);
		}
	}

	closedir(dfd);
}

int main(int argc, char **argv) {
if (argc == 1) /* по умолчанию берется текущий каталог */
fsize(".");
else
while (--argc > 0)
fsize(*++argv);
return 0;
}
