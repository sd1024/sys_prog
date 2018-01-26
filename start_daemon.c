#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
pid_t pid, sid;

void sigurg_handler(int signalno)
{
	exit(EXIT_SUCCESS);
}

int daemonize ()
{
// создаем потомка
//pid = fork();
printf("pid %d\n",pid);
 if (pid < 0)  
    {
		//printf("pid < 0 %d\n",pid);
        return 1;
    }
else if (!pid) { // если это потомок


//printf("pid %d\n",pid);
// создаём новый сеанс, чтобы не зависеть от родителя
sid=setsid();
 if (sid < 0)  
    {
		//printf("sid < 0 %d\n",sid);
        return 1;
    }
	
// закрываем дискрипторы ввода/вывода/ошибок, так как нам они больше не понадобятся
printf("%d\n",sid);
close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);
} else {


	return 0;
	}
}



int main() {
signal(SIGURG, sigurg_handler);
daemonize();
//sleep(100);
while(1) {

sleep(1);
}


return 0;
}
