#include "apue.h"
#include <errno.h> /* оп­ре­де­ле­ние пе­ре­мен­ной errno */
#include <stdarg.h> /* спи­сок ар­гу­мен­тов пе­ре­мен­ной дли­ны ISO C */
#include <syslog.h>
static void log_doit(int, int, int, const char *, va_list ap);
extern int log_to_stderr;
/*
* Ини­циа­ли­зи­ро­вать syslog(), ес­ли про­цесс ра­бо­та­ет в ре­жи­ме де­мо­на.
*/
void log_open(const char *ident, int option, int facility)
{
if (log_to_stderr == 0)
openlog(ident, option, facility);
}
/*
* Об­ра­бот­ка не­фа­таль­ных оши­бок, свя­зан­ных с сис­тем­ны­ми вы­зо­ва­ми.
* Вы­во­дит со­об­ще­ние, со­от­вет­ст­вую­щее со­дер­жи­мо­му пе­ре­мен­ной errno,
* и воз­вра­ща­ет управ­ле­ние.
*/
void log_ret(const char *fmt, ...)
{
va_list
ap;
va_start(ap, fmt);
log_doit(1, errno, LOG_ERR, fmt, ap);
va_end(ap);
}
/*
* Об­ра­бот­ка фа­таль­ных оши­бок, свя­зан­ных с сис­тем­ны­ми вы­зо­ва­ми.
* Вы­во­дит со­об­ще­ние и за­вер­ша­ет ра­бо­ту про­цес­са.
*/
void log_sys(const char *fmt, ...)
{
va_list
ap;
va_start(ap, fmt);
log_doit(1, errno, LOG_ERR, fmt, ap);
va_end(ap);
exit(2);
}
/*
* Об­ра­бот­ка не­фа­таль­ных оши­бок, не свя­зан­ных с сис­тем­ны­ми вы­зо­ва­ми.
* Вы­во­дит со­об­ще­ние и воз­вра­ща­ет управ­ле­ние.
*/
void log_msg(const char *fmt, ...)
{
va_list ap;
va_start(ap, fmt);
log_doit(0, 0, LOG_ERR, fmt, ap);
va_end(ap);
}

/*
* Об­ра­бот­ка фа­таль­ных оши­бок, не свя­зан­ных с сис­тем­ны­ми вы­зо­ва­ми.
* Вы­во­дит со­об­ще­ние и за­вер­ша­ет ра­бо­ту про­цес­са.
*/
void log_quit(const char *fmt, ...)
{
va_list
ap;
va_start(ap, fmt);
log_doit(0, 0, LOG_ERR, fmt, ap);
va_end(ap);
exit(2);
}
/*
* Об­ра­бот­ка фа­таль­ных оши­бок, свя­зан­ных с сис­тем­ны­ми вы­зо­ва­ми.
* Но­мер ошиб­ки пе­ре­да­ет­ся в па­ра­мет­ре.
* Вы­во­дит со­об­ще­ние и за­вер­ша­ет ра­бо­ту про­цес­са.
*/
void
log_exit(int error, const char *fmt, ...)
{
va_list
ap;
va_start(ap, fmt);
log_doit(1, error, LOG_ERR, fmt, ap);
va_end(ap);
exit(2);
}
/*
* Вы­во­дит со­об­ще­ние и воз­вра­ща­ет управ­ле­ние в вы­зы­ваю­щую функ­цию.
* Вы­зы­ваю­щая функ­ция долж­на оп­ре­де­лить зна­че­ния ар­гу­мен­тов "errnoflag" и "priority".
*/
static void log_doit(int errnoflag, int error, int priority, const char *fmt, va_list ap)
{
char buf[MAXLINE];
vsnprintf(buf, MAXLINE-1, fmt, ap);
if (errnoflag)
snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s",
strerror(error));
strcat(buf, "\n");
if (log_to_stderr) {
fflush(stdout);
fputs(buf, stderr);
fflush(stderr);
} else {
syslog(priority, "%s", buf);
}
}


void err_quit(const char *fmt, ...)
{
va_list
ap;
va_start(ap, fmt);
err_doit(0, 0, fmt, ap);
va_end(ap);
exit(1);
}
/*
* Вы­во­дит со­об­ще­ние и воз­вра­ща­ет управ­ле­ние в вы­зы­ваю­щую функ­цию.
* Вы­зы­ваю­щая функ­ция оп­ре­де­ля­ет зна­че­ние фла­га "errnoflag".
*/
void err_doit(int errnoflag, int error, const char *fmt, va_list ap)
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
