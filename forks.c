#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main ()
{
pid_t pid;
pid = fork ();

	if (pid > 0)
		printf ("Я родительский процесс сpid=%d!\n", pid);
	else if (!pid)
		printf ("А я дочерний! cpid=%d\n", pid);
	else if (pid == -1)
		perror ("fork");
}
