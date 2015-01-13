#include <stdio.h>

/* ---------------------------------------------------
** SYSTEM COMMAND EXAMPLE
** developed by fox [11/12/2005]
** 
** piccolo e banale esempio che mostra l'utilizzo delle
** funzioni SYSTEM (che esegue un comando in bash) e
** SLEEP(X) (che blocca l'esecuzione per X secondi)
**
** in entrambi i casi il controllo (PC) viene momentaneamente
** sospeso e passato a esecuzioni esterne
** --------------------------------------------------- */

int main()
{
	system("clear");

	printf("\n");
	printf("*** SYSTEM COMMAND EXAMPLE\n");
	printf("*** developed by fox [11/12/2005]\n");
	printf("\n");
	printf("------------------------------------------------------------------------\n");
	printf("questo semplice programma compila il programma helloworld\n");
	printf("premere INVIO per compilare o CTRL+C per uscire");
	getchar();

	printf("------------------------------------------------------------------------\n");
	printf("fra tre secondi verrà eseguita la compilazione (CTRL+C per annullare)\n");
	sleep(1);
	printf("fra due secondi...\n");
	sleep(1);
	printf("fra un secondo...\n");
	sleep(1);

	system("gcc helloworld.c -o helloworld");

	printf("\nsh: gcc helloworld.c -o helloworld\n\n");

	printf("** compilazione eseguita\n");
	sleep(1);

	system("clear");

	printf("------------------------------------------------------------------------\n");

	printf("premere INVIO per eseguire il programma o CTRL+C per uscire");
	getchar();

	printf("------------------------------------------------------------------------\n");

	printf("\nsh: ./helloworld\n\n");

	printf("------------------------------------------------------------------------\n");
	system("./helloworld");
	printf("------------------------------------------------------------------------\n");
	printf("\nsh: rm helloworld\n\n");

	system("rm helloworld");

	printf("esecuzione terminata\n\n");

	return 0;
}
