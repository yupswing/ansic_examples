#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *s1, *s2;
    s1 = (char*)malloc(10*sizeof(char));
    s2 = (char*)malloc(10*sizeof(char));
    s1 = "1234567890";
    s2 = "abcdefghij";

    printf("s1 address %p\ns2 address %p\n",s1,s2);
    printf("s1 value %s\ns2 value %s\n",s1,s2);

    int x;
    printf(" |s1--------s2--------|\n  ");
    for (x=0;x<10;x++) {
        printf("%c",s1[x]);
    }
    for (x=0;x<10;x++) {
        printf("%c",s2[x]);
    }
    printf("    print s1[0-9] s2[0-9]\n  ");
    for (x=0;x<22;x++) {
        printf("%c",s1[x]);
    }
    printf("    print s1[0-22] ( ( n + \\0 ) * 2) \n");

    return 0;
}
