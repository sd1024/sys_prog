#include "apue.h"
#include <sys/wait.h>

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
