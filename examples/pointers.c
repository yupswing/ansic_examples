#include <stdio.h>
#include <stdlib.h>

int main() {

	/*--------------------------------------------*/
	//utilizzo base dei puntatori

	int aa;
	int* bb;
    int** cc;
	
	aa = 7;
	bb = &aa;
    cc = &bb;
	
	printf("--------------------------------------------\n");
	printf("\n");
    printf("int a; int *b; int **c;\n");
    printf("a = 7; b = &a; c = &b\n");
	printf("\n");
	printf("Indirizzo di a      [&a] %p\n",&aa);
	printf("Indirizzo di b      [&b] %p\n",&bb);
	printf("Indirizzo di c      [&b] %p\n",&cc);
	printf("Valore di a         [ a] %d\n",aa);
	printf("Valore di b 	    [ b] %p\n",bb);
	printf("Valore di c 	    [ b] %p\n",cc);
	printf("Valore puntato di b [*b] %d\n",*bb);
	printf("Valore puntato di c [*c] %p\n",*cc);
	printf("Valore puntato di c [**c] %d\n",**cc);
	printf("\n--------------------------------------------\n");

	printf("\n");

	/*--------------------------------------------*/
	//utilizzo di MALLOC per l'allocazione
	//di array dinamici

	int* array;
	int allocazioni = 10;
	
	printf("ALLOCAZIONE DI %d INT\n\n",allocazioni);
	array = (int*)malloc(sizeof(int)*allocazioni);
    printf("array = (int*)malloc(sizeof(int)*10);\n");
    printf("for (i=0;i<10;i++) array[i] = i*100;\n\n");

    printf("sizeof(int) is %d\n\n",(int)sizeof(int));
	
	int ii;

	for (ii=0;ii<allocazioni;ii++) {
		//array[ii] = ii*100;	//sinonimi
		*(array+ii) = ii*100;
	}
	for (ii=0;ii<allocazioni;ii++) {
		printf("array[%d] = *(array+%d) = %3d	indirizzo: %p\n",ii,ii,array[ii],array+ii);
	}

	free(array);

	printf("\n--------------------------------------------\n");
	

}
