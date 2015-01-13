#include <stdio.h>
#define DEL 4

int main() {

	int ii,jj;
	
	system("clear");

	printf("\n");

	printf("\n\ncompletato   0%%");
	fflush(stdout);

	for (ii=1;ii<=100;ii++) {
		for (jj=0;jj<DEL;jj++)
			printf("%c",8);
		printf("%3d%%",ii);
		system("sleep 0.1");
		fflush(stdout);
	}
	printf("\n");
	return 0;

}
