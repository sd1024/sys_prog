#include <stdio.h>
#include <stdlib.h>

	struct mainFile {
	int num_acc;
	char name[10];
	float balance;
	};

	struct transFile {
	int num_account;
	float sum;
	} tf={0, 1000};


int main()
{
	
	int num_file = 0;
	FILE *writeMain;

	if ((writeMain = fopen("mainfile.txt", "w")) == NULL) {
		printf("File mainfile.txt could not be opened.\n");
	} else 
		create_mf(writeMain);

	printf("Complete\n");
	fclose(writeMain);
return 0;
}

int create_mf(FILE *fPtr)
{
	struct mainFile mf = {0, "admin", 1000};

	if (!fwrite(&mf, sizeof(struct mainFile),1,fPtr)){
		perror ("fread");
		printf("Error");
		return 1;
	} else return 0;
}
/*
void create_tf(int *ptr, int size)
{
	FILE *writeTrans;

	if ((writeTrans = fopen("transfile.txt", "w")) == NULL)
		printf("File transfile.txt could not be opened.\n);
	else {
		fprintf(writeTrans, "%-8d%-12s%10f",num_acc, name, balance);
	}

}
*/
