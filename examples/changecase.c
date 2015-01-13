#include <stdio.h>

int main() {

    char c;
    printf("type a character: ");
    scanf("%c",&c);

    if (c >= 65 && c <= 90) { //upper
        printf("%c <- to lowercase\n", c+32);
    } else if (c >= 97 && c <= 122) { //lower
        printf("%c <- to uppercase\n", c-32);
    } else {
        printf("%c <- same\n", c);
    }

    return 0;
}
