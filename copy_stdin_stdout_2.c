#include "apue.h"
int
main(void)
{
int
c;
while ((c = getc(stdin)) != EOF)
if (putc(c, stdout) == EOF)
err_sys("ошиб­ка вы­во­да");
if (ferror(stdin))
err_sys("ошиб­ка вво­да");
exit(0);
}
