#include "apue.h"
#include <sys/wait.h>
char *env_init[] = { "USER=unknown", "PATH=/usr/bin", NULL };
int main(void)
{
pid_t pid;
if ((pid = fork()) < 0) {
err_sys("ошиб­ка вы­зо­ва функ­ции fork");
} else if (pid == 0) {
/* за­дать пол­ный путь к фай­лу и сре­ду ок­ру­же­ния */
if (execle("/bin/bash", "uname -a", (char *)0, env_init) < 0)
err_sys("ошиб­ка вы­зо­ва функ­ции execle");
}
if (waitpid(pid, NULL, 0) < 0)
err_sys("ошиб­ка вы­зо­ва функ­ции wait");
if ((pid = fork()) < 0) {
err_sys("ошиб­ка вы­зо­ва функ­ции fork");
} else if (pid == 0) {
/* за­дать имя фай­ла, на­сле­до­вать сре­ду ок­ру­же­ния */
if (execlp("echoall", "echoall", "толь­ко 1 ар­гу­мент", (char *)0) < 0)
err_sys("ошиб­ка вы­зо­ва функ­ции execlp");
}
exit(0);
}
