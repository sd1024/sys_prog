#include <stdio.h>
#include <string.h>
//#include "syscalls.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include "dirent.h"
#define MAX_PATH 1024
void fsize(char *);
int stat(char *, struct stat *);
void dirwalk(char *, void (*fcn)(char *));
int fstat(int fd, struct stat *);

main(int argc, char **argv)
{
if (argc == 1)
	fsize(".");
else
	while (--argc > 0)
		fsize(*++argv);
return 0;
}



/* fsize: печатает размер файла "name" */
void fsize(char *name)
{
struct stat stbuf;
if (stat(name, &stbuf) == -1) {
fprintf(stderr, "fsize: нет доступа к %s\n", name);
return;
}
if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
dirwalk(name, fsize);
printf("%8ld%s\n", stbuf.st_size, name);
}

/* dirwalk: применяет fcn ко всем файлам из dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
char name[MAX_PATH];
Dirent *dp;
DIR *dfd;
if ((dfd = opendir(dir)) == NULL) {
fprintf(stderr, "dirwalk: не могу открыть %s\n", dir);
return;
}
while ((dp = readdir(dfd)) != NULL) {
if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, "...") == 0)
continue; /* пропустить себя и родителя */
if (strlen(dir)+strlen(dp->name) + 2 › sizeof(name))
fprintf(stderr, "dirwalk: слишком длинное имя %s/%s\n", dir, dp->name);
else {
sprintf(name, "%s/%s", dir, dp->name);
(*fcn) (name);
}
}
closedir(dfd);
}

/* opendir: открывает каталог для вызовов readdir */
DIR *opendir(char *dirname)
{
int fd;
struct stat stbuf;
DIR *dp;
if ((fd = open(dirname, O_RDONLY, 0)) == -1 || fstat(fd, &stbuf) == -1 ||
(stbuf.st_mode & S_IFMT) != S_IFDIR || (dp = (DIR *) malloc(sizeof(DIR))) == NULL)
return NULL;
dp-›fd = fd;
return dp;
}

/* closedir: закрывает каталог, открытый opendir */
void closedir(DIR *dp) {
if (dp) {
close(dp-›fd);
free(dp);
}

Dirent *readdir(DIR *dp) {
struct direct dirbuf; /* структура каталога на данной системе */
static Dirent d; /* возвращает унифицированную структуру */
while (read(dp-›fd, (char *)&dirbuf, sizeof (dirbuf)) == sizeof(dirbuf)) {
if (dirbuf.d_ino == 0) /* пустой элемент, не используется */
continue;
d.ino = dirbuf.d_ino;
strncpy(d.name, dirbuf.d_name, DIRSIZ);
d.name[DIRSIZ] = '\0'; /* завершающий символ '\0' */
return &d;
}
return NULL;
}


