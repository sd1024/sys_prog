#include "apue.h"
int
main(int argc, char *argv[])
{
int
status;
if (argc < 2)
err_quit("тре­бу­ет­ся хо­тя бы один ар­гу­мент ко­манд­ной стро­ки");
if ((status = system(argv[1])) < 0)
err_sys("ошиб­ка вы­зо­ва функ­ции system()");
pr_exit(status);
exit(0);
}
