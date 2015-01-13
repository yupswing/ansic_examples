#include <stdio.h>
#include <stdlib.h>
#include "lib/xstring.h"

#define HORIZ_LINE "-----------------------------------------------------------------------------------\n"

//WINDOWS usa cls
//LINUX usa clear
//editare prima di comilare (se non corrispondente)
#define CLEAR "clear"

void substringExample()
{
	char* mystr;
	int mystr_len = 10;
	mystr = (char*)(malloc(sizeof(char)*mystr_len+1));

	printf(HORIZ_LINE);
	printf("*** SUBSTRING EXAMPLE:\n");
	printf("inserire una stringa che verrà ridotta [max 10 char]\n> ");

	char ch;
	int ii=0;
	while(1) 
	{
		ch = getchar();
		if ((ch!=10)&&(ii<mystr_len)) mystr[ii++] = ch;
		if (ch == 10) break;
	}
	mystr[ii] = '\0';

	printf(HORIZ_LINE);

	printf("    mystr|                              |%s| len: %d\n",mystr,(int)strlen(mystr));

	char mystr2[10];
	substring(mystr2,mystr,3,4);
	printf("\n   mystr2|  substring(mystr2,mystr,3,4) |%s| len: %d\n",mystr2,(int)strlen(mystr2));

	substr(mystr,3,4);
	printf("\n    mystr|  substr(mystr,3,4)           |%s| len: %d\n",mystr,(int)strlen(mystr));

	free(mystr);

	printf(HORIZ_LINE);
}

void caseExample()
{
	char* mystr;
	int mystr_len = 20;
	mystr = (char*)(malloc(sizeof(char)*mystr_len+1));

	printf(HORIZ_LINE);
	printf("*** CASE EXAMPLE:\n");
	printf("inserire una stringa da convertire [max 20 char]\n> ");

	char ch;
	int ii=0;
	while(1) 
	{
		ch = getchar();
		if ((ch!=10)&&(ii<mystr_len)) mystr[ii++] = ch;
		if (ch==10) break;
	}
	mystr[ii] = '\0';

	printf(HORIZ_LINE);

	printf("   original: %s\n",mystr);

	toLowerCase(mystr);
	printf("toLowerCase: %s\n",mystr);

	toUpperCase(mystr);
	printf("toUpperCase: %s\n",mystr);

	free(mystr);

	printf(HORIZ_LINE);
}

void indexExample()
{
	char* mystr;
	char* mystr2;
	int mystr_len = 20;
	mystr = (char*)(malloc(sizeof(char)*mystr_len+1));
	mystr2 = (char*)(malloc(sizeof(char)*mystr_len+1));

	printf(HORIZ_LINE);
	printf("*** INDEXOF EXAMPLE:\n");
	printf("inserire una stringa [max 20 char]\n> ");

	char ch;
	int ii;

	ii=0;
	while(1) 
	{
		ch = getchar();
		if ((ch!=10)&&(ii<mystr_len)) mystr[ii++] = ch;
		if (ch==10) break;
	}
	mystr[ii] = '\0';

	printf(HORIZ_LINE);

	printf("inserire la sottostringa da cercare [max 20 char]\n> ");

	ii=0;
	while(1) 
	{
		ch = getchar();
		if ((ch!=10)&&(ii<mystr_len)) mystr2[ii++] = ch;
		if (ch==10) break;
	}
	mystr2[ii] = '\0';

	printf(HORIZ_LINE);

	printf("   original1: |%s|\n",mystr);
	printf("   original2: |%s|\n",mystr2);

	if (strmatch(mystr,mystr2))
		printf("\nle stringe sono uguali\n");
	else
		printf("\nle stringe non sono uguali\n");

	printf(HORIZ_LINE);

	printf("\n");

	int lastindex = -1;
	int tot = 0;
	do {
		printf("*** ricerca di |%s| da indice %d\n",mystr2,lastindex+1);
		lastindex = indexOf(mystr,mystr2,lastindex+1);
		printf("indexOf %3d   %s\n",lastindex,mystr);
		printf("              ");
		if (lastindex != -1) {
			tot++;
			for (ii=0;ii<lastindex;ii++) printf(" ");
			for (ii=0;ii<strlen(mystr2);ii++) printf("^");
		}
		printf("\n");
	} while (lastindex!=-1);

	printf("\nsono state trovate %d corrispondenze\n\n",tot);

	free(mystr);
	free(mystr2);

	printf(HORIZ_LINE);
}

int main ()
{

printf("%c",199);

	system(CLEAR);
	printf(HORIZ_LINE);
	printf("*** EXTENDED STRING FUNCTION EXAMPLE\n");
	printf("*** developed by fox [11/12/2005]\n");
	printf("\n");

	printf("esempi disponibili:\n\n");
	printf(" 1) SUBSTRING\n");
	printf("    estrae una sottostringa da una stringa\n");
	printf("    funzioni: substr, substring\n\n");
	printf(" 2) CASE\n");
	printf("    modifica il case di una stringa\n");
	printf("    funzioni: toLowerCase, toUpperCase (e sottofunzioni)\n\n");
	printf(" 3) INDEXOF\n");
	printf("    trova corrispondenze di una stringa in un'altra\n");
	printf("    funzioni: indexOf, strmatch\n\n");
	printf(" e) esci\n");
	
	printf("\n > ");

	char ch,choose;

	while(1) {
		ch = getchar();
		if (ch != 10) choose = ch;
		else break;
	}

	system(CLEAR);

	switch(choose) {
		case '1':
			substringExample();
			break;
		case '2':
			caseExample();
			break;
		case '3':
			indexExample();
			break;
	}

    return 0;
	
}
