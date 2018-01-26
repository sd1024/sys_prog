#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main ()
{
	pid_t pid;
	pid = fork ();

	if (pid == -1)
		perror ("fork");

		/* дочерний ... */
	if (!pid) {
		const char *args[] = { "windlass", NULL };
	
		int ret;
		ret = execv ("/bin/windlass", args);
	
		if (ret == -1) {
			perror ("execv");
			exit (EXIT_FAILURE);
		}
	}
return 0;
}
