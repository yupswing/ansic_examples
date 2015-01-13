// Example usage: wc < filepath

#include <stdio.h>

int main()
{
    int nc = 0, nl = 0, nw = 0;
    int i;
    char c;

    while ( (c = getchar()) != EOF ) {
        nc++;
        if (c == '\n') nl++;
    }
    printf("Number of characters in file = %d\n", nc);
    printf("Number of lines in file = %d\n", nl);
    //printf("Number of words in file = %d\n", nw);
    return 0;
}
