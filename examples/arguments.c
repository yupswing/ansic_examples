#include <stdio.h>

int main(int argc, char* argv[])
{
	printf("*** %s *** copyleft SC\n\n",argv[0]);

	int ii;
	for (ii=0;ii<argc;ii++) 	{
		printf("arg%d: %s\n",ii,argv[ii]);
	}

	printf("\n");

	return 0;
}
