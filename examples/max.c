#include <stdio.h>
#include <stdlib.h>

int max(int,int);
int min(int,int);

int main() {

    int i,numbers_len;

    printf("How many numbers? ");
    scanf("%d",&numbers_len);

    //int numbers[numbers_len]; //in this context this two lines are equivalent
    int *numbers = (int*)malloc(numbers_len*sizeof(int));

    for (i=0;i<numbers_len;i++) {
        printf("N[%d] = ",i);
        scanf("%d",numbers+i);
        /* scanf("%d",&numbers[i]); */
    }

    int big = *numbers;
    int small = numbers[0];
    for (i=1;i<numbers_len;i++) {
        big = max(big,*(numbers+i));
        small = min(small,numbers[i]);
    }

    printf("The small number is %d\n",small);
    printf("The big number is %d\n",big);
}

int max(int n1, int n2) {
    // return the biggest number between n1 and n2
    return n1>n2?n1:n2;
}

int min(int n1, int n2) {
    // return the smallest number between n1 and n2
    return n1<n2?n1:n2;
}
