#include <stdio.h>

int main()
{
    int isodd,number=0;
    printf("Enter a number: ");
    scanf("%d",&number);
    if (odd(number)==1) printf("%d is odd\n",number);
    else printf("%d is even\n",number);
    return 0;
}

int odd(int number) {
    if (number%2==0) return 0;
    return 1;
}
