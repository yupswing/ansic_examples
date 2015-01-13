#include <stdio.h>

void printAscii(){

	int ii,jj;
	unsigned int counter = 0;
	unsigned char ch;
	printf(" ---------------------------------------------------------------------------------\n");
	for (ii=0;ii<32;ii++) {
		printf(" | ");
		for (jj=0;jj<8;jj++) {
			counter = ii+(32*jj);
			ch = counter++;
			switch (ch){
				case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 11:case 12:case 14:
				case 15:case 16:case 17:case 18:case 19:case 20:case 21:case 22:case 23:case 24:
				case 25:case 26:case 27:case 28:case 29:case 30:case 31:case 127:
					printf("%3d     | ",ch);
					break;
				case 0:
					printf("%3d END | ",ch);
					break;
				case 9:
					printf("%3d TAB | ",ch);
					break;
				case 10:
					printf("%3d NL  | ",ch);
					break;
				case 13:
					printf("%3d RET | ",ch);
					break;
				default:
					printf("%3d  %c  | ",ch,ch);
			}
		}
		printf("\n");
	}
	printf(" ---------------------------------------------------------------------------------\n");
	
}

int main ()
{
	
	printf("\n");
	printf("*************************************\n");
	printf("*** EXTENDED ASCII TABLE EXAMPLE\n");
	printf("*************************************\n");
	printf("\n");

	printAscii();

	printf("\n");
	
}
