#include "apue.h"

int	main(int argc, char *argv[])
{
	int i;
	struct stat buf;
	char *ptr;

	for (i = 1; i < argc; i++) {
		printf("%s: ", argv[i]);
		if (lstat(argv[i], &buf) < 0) {
			err_ret("ошиб­ка вы­зо­ва функ­ции lstat");
			continue;
		}		
		if (S_ISREG(buf.st_mode))
			ptr = "обыч­ный файл";
		else if (S_ISDIR(buf.st_mode))
			ptr = "ка­та­лог";
		else if (S_ISCHR(buf.st_mode))
			ptr = "файл сим­воль­но­го уст­рой­ст­ва";
		else if (S_ISBLK(buf.st_mode))
			ptr = "файл блоч­но­го уст­рой­ст­ва";
		else if (S_ISFIFO(buf.st_mode))
			ptr = "fifo";
		else if (S_ISLNK(buf.st_mode))
			ptr = "сим­во­ли­че­ская ссыл­ка";
		else if (S_ISSOCK(buf.st_mode))
			ptr = "со­кет";
		else
			ptr = "** не­из­вест­ный тип фай­ла **";
			printf("%s\n", ptr);
		}
	exit(0);
}
