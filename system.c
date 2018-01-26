/*
* my_system — синхронно ответвляет дочерний процесс и ожидает команды
* "/bin/sh -c<cmd>".
*
* Возвращает –1 в случае любой ошибки или код выхода запущенного процесса
* Не блокирует и не игнорирует сигналы
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (void)
{
char cmd = "time";
int out;
out = my_system(cmd);
printf("%d",out);
return 0;
}

int my_system (const char *cmd)
{
int status;
pid_t pid;
pid = fork ();
if (pid == -1)
return -1;
else if (pid == 0) {
const char *argv[4];
argv[0] = "sh";
argv[1] = "-c";
argv[2] = cmd;
argv[3] = NULL;
execv ("/bin/sh", argv);
exit (-1);
}
if (waitpid (pid, &status, 0) == -1)
return -1;
else if (WIFEXITED (status))
return WEXITSTATUS (status);
return -1;
}
