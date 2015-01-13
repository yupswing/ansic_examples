#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

char* mystrcpy(char *strdst, char *strsrc);
long unsigned int mystrlen(char *strsrc);

char *source;
char destination[10];

int main(void) {

    source = (char*)malloc(10*sizeof(char));
    source = "test";

    printf("char *source;\nsource = (char*)malloc(10*sizeof(char));\nchar destination[10];\n\n");

    /* STRCPY */
    strcpy(destination,source);
    printf("source %s | &source %p | &source[0] %p\n", source, &source, &source[0]);
    printf("strlen | source: %lu\n",(long unsigned int)strlen(source));
    printf("strcpy | destination: %s\n",destination);
    printf("destination %s | &destination %p | &destination[0] %p\n\n", destination, &destination, &destination[0]);

    /* STRCPY CLONE */
    mystrcpy(destination,source);
    printf("source %s | &source %p | &source[0] %p\n", source, &source, &source[0]);
    printf("mystrlen | source: %lu\n",(long unsigned int)mystrlen(source));
    printf("mystrcpy | destination: %s\n",destination);
    printf("destination %s | &destination %p | &destination[0] %p\n\n", destination, &destination, &destination[0]);

    printf("*src %c | src %p | &src %p | &src[0] %p | &src[1] %p | ...\n", *source, source, &source, &source[0], &source[1]);
    printf("*dst %c | dst %p | &dst %p | &dst[0] %p | &dst[1] %p | ...\n", *destination, destination, &destination, &destination[0], &destination[1]);

    return 0;
}

long unsigned int mystrlen(char *strsrc) {
    char *sp = &strsrc[0];
    char *op = sp;
    while(*sp!='\0') sp++;
    return sp-op;
}

char* mystrcpy(char *strdst, char *strsrc) {
    char *dp = &strdst[0], *sp = &strsrc[0];
    while(*sp!='\0') *dp++ = *sp++;
    *dp = '\0';
    return strdst;
}
