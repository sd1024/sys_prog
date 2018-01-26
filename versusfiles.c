#include <stdio.h>
#define maxline 1000

void fileversus(FILE *, FILE *);

int main(int argc, char *argv[]) {
FILE *file1, *file2;
while (--argc > 0 && argc < 3) {
	if ((file1 = fopen(*++argv, "r")) == NULL) {
		printf("cat: не могу открыть файл %s\n", *argv);
		return 1;
	} else if ((file2 = fopen(*++argv, "r")) == NULL) {
		printf("cat: не могу открыть файл %s\n", *argv);
		return 1;
	} else {
printf("versus...\n");
		fileversus(file1, file2);
		fclose(file1);
		fclose(file2);
		return 0;
		}
	}

}

void fileversus(FILE *file1, FILE *file2) {
int c;
char s1[maxline];
char s2[maxline];
char *line1, *line2;

do {
line1=fgets(s1, maxline, file1);
line2=fgets(s2, maxline, file2);
printf("do...\n");
	if (line1 == s1 && line2 == s2) {
		if(strcmp(line1, line2) != 0) {
			printf ("\n%s\n",line1);
			line1 = line2 = NULL;
		} 
	}
} while (line1 != NULL || line2 != NULL);
}
