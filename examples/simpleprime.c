#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>

unsigned int *primes = NULL;
unsigned int count = 0; /* primes counter */
int stop = 0;

void ex_program(int sig);
void addprime(unsigned int number);
int isprime(unsigned int number);

int main(int argc, char *argv[]) {
    (void) signal(SIGINT, ex_program);

    if (argc < 2) {
        fprintf(stderr,"primes MAX\n");
        exit(5);
    }

    fprintf(stderr,"Init elaboration\n\n");

    /* DECLARATION */
    unsigned int current; /* the current number */

    /* GET MAX */
    unsigned int max = atoi(argv[1]); /* when stop */
    int infinite = 0;
    if (max==0) infinite = 1;

    /* add 2 as prime and set 2 as current */
    addprime(2);
    current = 2;
    printf("%d\n",current);

    do {
        current++;
        if (!isprime(current)) continue; /* excludes not prime */
        addprime(current);
        printf("%d\n",current);
        if (stop) break;
    } while (current < max || infinite == 1);

    fprintf(stderr,"\nPrime numbers found: %d\n",count);
    fprintf(stderr,"Last number checked: %d\n",current);

    return 0;
}

void ex_program(int sig) {
    fprintf(stderr,"--- Kill ---\n");
    stop = 1;
    (void) signal(SIGINT, SIG_DFL);
}

void addprime(unsigned int number)
{
    count++;
    primes = (unsigned int*) realloc (primes, count * sizeof(unsigned int));
    primes[count - 1] = number;
}

int isprime(unsigned int number)
{
    if (number%2==0) return 0; /* exclude even numbers */
    // fastest way (test only < sqrt)
    float numbersqrt = sqrt(number);
    unsigned int max = numbersqrt;

    unsigned int n;
    for(n=0; n < count ; n++) {
        if ( primes[n] > max ) break;
        if ( number % primes[n] == 0 ) return 0;
    }
    return 1; /* IS PRIME! */
}
