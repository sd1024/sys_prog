#include "apue.h"
int main(void)
{
char buf[MAXLINE];

while (fgets(buf, MAXLINE, stdin) != NULL)
	if (fputs(buf, stdout) == EOF)
		err_sys("ошиб­ка вы­во­да");
	if (ferror(stdin))
		err_sys("ошиб­ка вво­да");
	exit(0);
}
