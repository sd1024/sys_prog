
#include "apue.h"
#include <errno.h> /* оп­ре­де­ле­ние пе­ре­мен­ной errno */
#include <stdarg.h> /* спи­сок ар­гу­мен­тов пе­ре­мен­ной дли­ны ISO C */
#include <sys/wait.h>

/*
Сведения о процессе из кода завершения
*/
void pr_exit(int status)
{
	if (WIFEXITED(status))
		printf("нор­маль­ное за­вер­ше­ние, код вы­хо­да = %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("ава­рий­ное за­вер­ше­ние, но­мер сиг­на­ла = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
	WCOREDUMP(status) ? " (соз­дан файл core)" : "");
#else
	"");
#endif
	else if (WIFSTOPPED(status))
		printf("до­чер­ний про­цесс ос­та­нов­лен, но­мер сиг­на­ла = %d\n", WSTOPSIG(status));
}


static void err_doit(int, int, const char *, va_list);
/*
* Об­ра­бот­ка не­фа­таль­ных оши­бок, свя­зан­ных с сис­тем­ны­ми вы­зо­ва­ми.
* Вы­во­дит со­об­ще­ние и воз­вра­ща­ет управ­ле­ние.
*/
void err_ret(const char *fmt, ...)
{ 
va_list ap;
va_start(ap, fmt);
err_doit(1, errno, fmt, ap);
va_end(ap);
}
/*
* Об­ра­бот­ка фа­таль­ных оши­бок, свя­зан­ных с сис­тем­ны­ми вы­зо­ва­ми.
* Вы­во­дит со­об­ще­ние и за­вер­ша­ет ра­бо­ту про­цес­са.
*/
void err_sys(const char *fmt, ...)
{
va_list ap;
va_start(ap, fmt);
err_doit(1, errno, fmt, ap);
exit(1);
}
/*
* Об­ра­бот­ка не­фа­таль­ных оши­бок, не свя­зан­ных с сис­тем­ны­ми вы­зо­ва­ми.
* Код ошиб­ки пе­ре­да­ет­ся в ви­де ар­гу­мен­та.
* Вы­во­дит со­об­ще­ние и воз­вра­ща­ет управ­ле­ние.
*/
void err_cont(int error, const char *fmt, ...)
{
va_list
ap;
va_start(ap, fmt);
err_doit(1, error, fmt, ap);
va_end(ap);
}
/*
* Об­ра­бот­ка фа­таль­ных оши­бок, не свя­зан­ных с сис­тем­ны­ми вы­зо­ва­ми.
* Код ошиб­ки пе­ре­да­ет­ся в ви­де ар­гу­мен­та.
* Вы­во­дит со­об­ще­ние и за­вер­ша­ет ра­бо­ту про­цес­са.
*/
void err_exit(int error, const char *fmt, ...)
{
va_list ap;
va_start(ap, fmt);
err_doit(1, error, fmt, ap);
va_end(ap);
exit(1);
}
/*
* Об­ра­бот­ка фа­таль­ных оши­бок, свя­зан­ных с сис­тем­ны­ми вы­зо­ва­ми.
* Вы­во­дит со­об­ще­ние, соз­да­ет файл core и за­вер­ша­ет ра­бо­ту про­цес­са.
*/
void err_dump(const char *fmt, ...)
{
va_list ap;
va_start(ap, fmt);
err_doit(1, errno, fmt, ap);
va_end(ap);
abort(); /* за­пи­сать дамп па­мя­ти в файл и за­вер­шить про­цесс */
exit(1); /* этот вы­зов ни­ко­гда не дол­жен быть вы­пол­нен */
}
/*
* Об­ра­бот­ка не­фа­таль­ных оши­бок, не свя­зан­ных с сис­тем­ны­ми вы­зо­ва­ми.
* Вы­во­дит со­об­ще­ние и воз­вра­ща­ет управ­ле­ние.
*/
void err_msg(const char *fmt, ...)
{
va_list ap;
va_start(ap, fmt);
err_doit(0, 0, fmt, ap);
va_end(ap);
}
/*
* Об­ра­бот­ка фа­таль­ных оши­бок, не свя­зан­ных с сис­тем­ны­ми вы­зо­ва­ми.
* Вы­во­дит со­об­ще­ние и за­вер­ша­ет ра­бо­ту про­цес­са.

*/
void err_quit(const char *fmt, ...)
{
va_list ap;
va_start(ap, fmt);
err_doit(0, 0, fmt, ap);
va_end(ap);
exit(1);
}
/*
* Вы­во­дит со­об­ще­ние и воз­вра­ща­ет управ­ле­ние в вы­зы­ваю­щую функ­цию.
* Вы­зы­ваю­щая функ­ция оп­ре­де­ля­ет зна­че­ние фла­га "errnoflag".
*/
static void err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
char buf[MAXLINE];
vsnprintf(buf, MAXLINE-1, fmt, ap);
if (errnoflag)
snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s",
strerror(error));
strcat(buf, "\n");
fflush(stdout); /* в слу­чае, ко­гда stdout и stderr - од­но и то же уст­рой­ст­во */
fputs(buf, stderr);
fflush(NULL); /* сбра­сы­ва­ет все вы­ход­ные по­то­ки */
}


