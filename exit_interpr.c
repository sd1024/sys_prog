#include "apue.h"
#include <sys/wait.h>
int main(void)
{
pid_t pid;
int status;
if ((pid = fork()) < 0)
	err_sys("ошиб­ка вы­зо­ва функ­ции fork");
else if (pid == 0)
/* до­чер­ний про­цесс */
	exit(7);
if (wait(&status) != pid) /* до­ж­дать­ся за­вер­ше­ния до­чер­не­го про­цес­са */
	err_sys("ошиб­ка вы­зо­ва функ­ции wait");
	pr_exit(status);
/* и вы­вес­ти код за­вер­ше­ния */
if ((pid = fork()) < 0)
	err_sys("ошиб­ка вы­зо­ва функ­ции fork");
else if (pid == 0)
/* до­чер­ний про­цесс */
	abort();
/* по­слать сиг­нал SIGABRT */
if (wait(&status) != pid) /* до­ж­дать­ся за­вер­ше­ния до­чер­не­го про­цес­са */
	err_sys("ошиб­ка вы­зо­ва функ­ции wait");
	pr_exit(status);
/* и вы­вес­ти код за­вер­ше­ния */
if ((pid = fork()) < 0)
err_sys("ошиб­ка вы­зо­ва функ­ции fork");
else if (pid == 0)
/* до­чер­ний про­цесс */
status /= 0;
/* де­ле­ние на 0 сге­не­ри­ру­ет сиг­нал SIGFPE */
if (wait(&status) != pid) /* до­ж­дать­ся за­вер­ше­ния до­чер­не­го про­цес­са */
err_sys("ошиб­ка вы­зо­ва функ­ции wait");
pr_exit(status);
/* и вы­вес­ти код за­вер­ше­ния */
exit(0);
}
