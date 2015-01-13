#include <stdio.h>
#define DEL 7

/* OS = 1 LINUX
   OS = 0 WINDOWS */

#ifndef OS
	#define OS 1
#endif
#if OS
	#define CLEAR "clear"
	#define COL_RED "\e[1;31m"
	#define COL_GREEN "\e[1;32m"
	#define COL_BLUE "\e[1;34m"
	#define COL_NONE "\e[0m"
#else
	#define CLEAR "cls"
	#define COL_RED ""
	#define COL_GREEN ""
	#define COL_BLUE ""
	#define COL_NONE ""
#endif



typedef enum { NONE, RED, GREEN, BLUE } color;

void printcolor(color col);
void printline(const char* text, color col);

int main() {
	
	//system(CLEAR);

	printf("\n");

	printline("test",GREEN);
	printline("test",RED);
	printline("test",GREEN);

	printf("\n\n");
	return 0;

}

void printline(const char* text, color col) {
	
	int jj;

	if (OS) printcolor(col);
	printf("\n * ");
	if (OS) printcolor(NONE);
	printf("%s",text);
	
	printf("\n");
	for (jj=0;jj<DEL;jj++)
		printf("%c",8);

	if (OS) printcolor(BLUE);
	printf("[");
	if (OS) printcolor(col);
	printf(" OK ");
	if (OS) printcolor(BLUE);
	printf("]");
}

void printcolor(color col) {
	switch (col) {
		case RED:
		printf("%s",COL_RED);
		break;
		case BLUE:
		printf("%s",COL_BLUE);
		break;
		case GREEN:
		printf("%s",COL_GREEN);
		break;
		default:
		printf("%s",COL_NONE);
	}
}
