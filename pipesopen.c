#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

#define BUFLEN 4096
int main(int argc, char *argv[]) 
{
	FILE * fp;
	int count=0;
	char sym;
	char buf[BUFLEN];
	char cmd[100]={};
	if (argc < 2) { 
		return 1;
	} else  {	
		strcat(cmd,argv[1]);
		strcat(cmd," ");
		strcat(cmd,argv[2]);
		//printf("%s\n",cmd);
		fp=popen(cmd, "r");
		if (fp==NULL) {
		exit(1);
		} else {
			while ((sym=fgetc(fp)) != EOF) {
				if ((sym)=='0')
					count++;
			}	
		printf ("%d\n",count);
		pclose(fp);
			}
	}
	return 0;
}
