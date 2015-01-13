#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i, j, n;
    int **matrix;
    printf("dimensione della matrice quadrata:\n");
    scanf("%d",&n);

    matrix = (int**)calloc(n,sizeof(int*)); 
    for (i = 0; i < n; i++) 
        matrix[i] = (int*)calloc(n,sizeof(int)); 

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            printf("[%d][%d] > %p\n",i,j,&matrix[i][j]);

    return 0;
}
