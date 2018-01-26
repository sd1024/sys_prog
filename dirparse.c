#include "apue.h"
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h> /* оп­ре­де­ле­ние пе­ре­мен­ной errno */
#include <stdarg.h> /* спи­сок ар­гу­мен­тов пе­ре­мен­ной дли­ны ISO C */
#include <syslog.h>






/* тип функ­ции, ко­то­рая бу­дет вы­зы­вать­ся для каж­до­го встре­чен­но­го фай­ла */
typedef int Myfunc(const char *, const struct stat *, int);
static Myfunc myfunc;
static int myftw(char *, Myfunc *);
static int dopath(Myfunc *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char *argv[])  {
	int ret;
	if (argc != 2)
		printf("Ис­поль­зо­ва­ние: ftw <на­чаль­ный_ка­та­лог>");
		ret = myftw(argv[1], myfunc); /* вы­пол­ня­ет всю ра­бо­ту */
		ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
		if (ntot == 0)
			ntot = 1;/* во из­бе­жа­ние де­ле­ния на 0; вы­вес­ти 0 для всех счет­чи­ков */
		printf("обыч­ные фай­лы = %7ld, %5.2f %%\n", nreg, nreg*100.0/ntot);
		printf("ка­та­ло­ги = %7ld, %5.2f %%\n", ndir, ndir*100.0/ntot);
		printf("спе­ци­аль­ные фай­лы блоч­ных уст­ройств = %7ld, %5.2f %%\n", nblk, nblk*100.0/ntot);
		printf("спе­ци­аль­ные фай­лы сим­воль­ных уст­ройств = %7ld, %5.2f %%\n", nchr, nchr*100.0/ntot);
		printf("FIFO = %7ld, %5.2f %%\n", nfifo, nfifo*100.0/ntot);
		printf("сим­во­ли­че­ские ссыл­ки = %7ld, %5.2f %%\n", nslink, nslink*100.0/ntot);
		printf("со­ке­ты = %7ld, %5.2f %%\n", nsock, nsock*100.0/ntot);
		exit(ret);
}

/*
* Обой­ти де­ре­во ка­та­ло­гов, на­чи­ная с ка­та­ло­га "pathname".
* Поль­зо­ва­тель­ская функ­ция func() вы­зы­ва­ет­ся для каж­до­го встре­чен­но­го фай­ла.
*/
#define FTW_F 1 /* файл, не яв­ляю­щий­ся ка­та­ло­гом */
#define FTW_D 2 /* ка­та­лог */
#define FTW_DNR 3 /* ка­та­лог, ко­то­рый не дос­ту­пен для чте­ния */
#define FTW_NS 4 /* файл, ин­фор­ма­цию о ко­то­ром */
/* не­воз­мож­но по­лу­чить с по­мо­щью stat */
static char *fullpath; /* пол­ный путь к каж­до­му из фай­лов */
static size_t pathlen;
/* воз­вра­ща­ем то, что вер­ну­ла функ­ция func() */
static int myftw(char *pathname, Myfunc *func) {
	fullpath = path_alloc(&len); /* вы­де­лить па­мять для PATH_MAX+1 байт */
/* (лис­тинг 2.3) */
	if (pathlen <= strlen(pathname)) {
		pathlen = strlen(pathname) * 2;
	if ((fullpath = realloc(fullpath, pathlen)) == NULL)
		printf("ошиб­ка вы­зо­ва realloc");
}
strcpy(fullpath, pathname);
return(dopath(func));
}
/*
* Об­ход де­ре­ва ка­та­ло­гов, на­чи­ная с "fullpath". Ес­ли "fullpath" не яв­ля­ет­ся
* ка­та­ло­гом, для не­го вы­зы­ва­ет­ся lstat(), func() и за­тем вы­пол­ня­ет­ся воз­врат.
* Для ка­та­ло­гов про­из­во­дит­ся ре­кур­сив­ный вы­зов функ­ции.
*/
static int
/* воз­вра­ща­ем то, что вер­ну­ла функ­ция func() */
dopath(Myfunc* func) {
	struct stat statbuf;
	struct dirent *dirp;
	DIR  *dp;
	int ret, n;
	if (lstat(fullpath, &statbuf) < 0) /* ошиб­ка вы­зо­ва функ­ции stat */
		return(func(fullpath, &statbuf, FTW_NS));
	if (S_ISDIR(statbuf.st_mode) == 0) /* не ка­та­лог */
		return(func(fullpath, &statbuf, FTW_F));
/*
* Это ка­та­лог. Сна­ча­ла вы­зо­вем функ­цию func(),
* а за­тем об­ра­бо­та­ем все фай­лы в этом ка­та­ло­ге.
*/
	if ((ret = func(fullpath, &statbuf, FTW_D)) != 0)
		return(ret);
	n = strlen(fullpath);
	if (n + NAME_MAX + 2 > pathlen) { /* уве­ли­чить раз­мер бу­фе­ра */
		pathlen *= 2;
	if ((fullpath = realloc(fullpath, pathlen)) == NULL)
	printf("ошиб­ка вы­зо­ва realloc");
	}
	fullpath[n++] = '/';
	fullpath[n] = 0;
	if ((dp = opendir(fullpath)) == NULL) /* ка­та­лог не­дос­ту­пен */
		return(func(fullpath, &statbuf, FTW_DNR));
	
	while ((dirp = readdir(dp)) != NULL) {
		if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
			continue; /* про­пус­тить ка­та­ло­ги "." и ".." */
		strcpy(&fullpath[n], dirp->d_name); /* до­ба­вить имя по­сле слэ­ша */
		if ((ret = dopath(func)) != 0)
		/* ре­кур­сия */
		break; /* вы­ход по ошиб­ке */
	}

	fullpath[n-1] = 0; /* сте­реть часть стро­ки от слэ­ша и до кон­ца */
	if (closedir(dp) < 0)
		printf("не­воз­мож­но за­крыть ка­та­лог %s", fullpath);
	return(ret);
	}

static int myfunc(const char *pathname, const struct stat *statptr, int type) {
	switch (type) {
	case FTW_F:
		switch (statptr->st_mode & S_IFMT) {
			case S_IFREG: nreg++; break;
			case S_IFBLK: nblk++; break;
			case S_IFCHR: nchr++; break;
			case S_IFIFO: nfifo++; break;
			case S_IFLNK: nslink++; break;
			case S_IFSOCK: nsock++; break;
			case S_IFDIR: /* ка­та­ло­ги долж­ны иметь type = FTW_D*/
			printf("при­знак S_IFDIR для %s", pathname);
		}
		break;
	case FTW_D:
		ndir++;
		break;
	case FTW_DNR:
			printf("за­крыт дос­туп к ка­та­ло­гу %s", pathname);
		break;
	case FTW_NS:
		printf("ошиб­ка вы­зо­ва функ­ции stat для %s", pathname);
		break;
	default:
		printf("не­из­вест­ный тип %d для фай­ла %s", type, pathname);
	}
return(0);
}


char *
path_alloc(size_t *sizep) /* ес­ли ре­зуль­тат не пус­той ука­за­тель, */
/* то так­же воз­вра­ща­ет­ся раз­мер вы­де­лен­ной па­мя­ти */
{
char
*ptr;
size_t size;
if (posix_version == 0)
posix_version = sysconf(_SC_VERSION);
if (xsi_version == 0)
xsi_version = sysconf(_SC_XOPEN_VERSION);
if (pathmax == 0) { /* пер­вый вы­зов функ­ции */
errno = 0;
if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
if (errno == 0)
pathmax = PATH_MAX_GUESS; /* ес­ли кон­стан­та не оп­ре­де­ле­на */
else
err_sys("ошиб­ка вы­зо­ва pathconf с па­ра­мет­ром _PC_PATH_MAX");
} else {
pathmax++; /* до­ба­вить 1, т. к. путь от­но­си­тель­но кор­ня */
}
}
/*
* До вер­сии POSIX.1-2001 не га­ран­ти­ру­ет­ся, что PATH_MAX вклю­ча­ет
* за­вер­шаю­щий ну­ле­вой байт. То же для XPG3.
*/
if ((posix_version < 200112L) && (xsi_version < 4))
size = pathmax + 1;
else
size = pathmax;
if ((ptr = malloc(size)) == NULL)
err_sys("malloc error for pathname");
if (sizep != NULL)
*sizep = size;
return(ptr);
}





