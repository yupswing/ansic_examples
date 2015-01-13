/************************
 * PRIME                *
 * Simone Cingano 2011  *
 * **********************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <signal.h>

#define INTERVAL 1000000
#define FALSE 0
#define TRUE 1

#ifndef OS
    #define OS 1 /* 1=LINUX, 0=WINDOWS */
#endif
#if OS
     #define COL_BOLD "\033[1m"
     #define COL_RED "\e[1;31m"
     #define COL_GREEN "\e[1;32m"
     #define COL_YELLOW "\e[1;33m"
     #define COL_BLUE "\e[1;34m"
     #define COL_MAGENTA "\e[1;35m"
     #define COL_CYAN "\e[1;36m"
     #define COL_GREY "\e[1;37m"
     #define COL_NONE "\e[0m"
#else
     #define COL_BOLD ""
     #define COL_RED ""
     #define COL_GREEN ""
     #define COL_YELLOW ""
     #define COL_BLUE ""
     #define COL_MAGENTA ""
     #define COL_CYAN ""
     #define COL_GREY ""
     #define COL_NONE ""
#endif

long int *primes = NULL;
long int count = 0; /* primes counter */

char *program_name;      /* name of the program (for errors) */

int stop = 0;

FILE *file = NULL;
char *filename = "primes.db";
const char MOVE_POS = 4;      //how many animation steps
const char MOVE[4] = "|/-\\"; // animation steps
int pos = 0;

/* Prototypes */
void ex_program(int sig);
void addprime(long int number);
void stats(long int current);
long int getmaxcheck(long int number);
long int gaussestimate(long int number);
int isprime(long int number);
int loadbuffer(void);
void openbuffer(void);
void closebuffer(void);
void usage(void);
void setoptions(int argc, char *argv[]);

/* OPTIONS */
int verbose = FALSE;         /* -v         default FALSE */
int save = FALSE;            /* -s         default FALSE */
int load = FALSE;            /* -l         default FALSE */
int output = FALSE;          /* -o         default FALSE */
long int gaussmode = 0;      /* -g<number> default NONE */
long int questmode = 0;      /* -q<number> default NONE */
long int max = 0;            /* -m<number> default NONE */

int main(int argc, char *argv[]) {

    /* init signal catch */
    (void) signal(SIGINT, ex_program);

    /* save the program name for future use */
    program_name = argv[0];

    /* set options by args */
    setoptions(argc,argv);

    /* DECLARATIONS */
    long int n;                 /* n for loops */
    long int current;           /* the current number */
    long int gauss;             /* gauss estimate */

    /* SET INFINITE */
    int infinite = FALSE; if (!max) infinite = TRUE;

    /* Gauss mode */
    if (gaussmode) {
        gauss=gaussestimate(gaussmode);
        if (verbose) fprintf(stderr,"\n%s### GAUSS MODE%s\n",COL_GREEN,COL_NONE);
        if (verbose) fprintf(stderr,"Gauss: %s%lu%s/%s%lu%s (%.2f%%)\n",COL_GREEN,gauss,COL_NONE,COL_BLUE,gaussmode,COL_NONE,((gauss*100)/(float)gaussmode));
        fprintf(stdout,"%lu\n",gauss);
        exit(0);
    }

    /* Load */
    if (load) load=loadbuffer(); //on error returns 0
    if (load) {
        /* set current as last loaded prime */
        current = primes[count-1];
    } else {
        /* [FixFor2] add 2 as prime and set 2 as current */
        addprime(2);
        current = 2;
    }

    /* Output */
    if (output) {
        if (verbose) fprintf(stderr,"- Send buffer to output\n");
        /* print all known primes */
        fprintf(stdout,"%lu",primes[0]);
        for(n = 1; n < count; n++)
            fprintf(stdout,"\n%lu",primes[n]);
    }

    /* Questmode */
    if (questmode) {
        if (questmode%2==0) max = 1;
        else max = getmaxcheck(questmode);
        infinite = FALSE;
    }

    if (verbose) fprintf(stderr,"\n%s### ELABORATION%s\n",COL_GREEN,COL_NONE);

    /* Save (Open buffer) */
    if (save) openbuffer();

    if (verbose) fprintf(stderr,"%s*%s Press %sCTRL+C%s to stop elaboration\n",COL_GREEN,COL_NONE,COL_BLUE,COL_NONE);

    /* Cycle */
    do {
        current++;

        if (verbose) stats(current);

        if (!isprime(current)) continue; /* CHECK!!! */

        addprime(current);
        if (save) fprintf(file,"\n%lu",current);
        if (output) fprintf(stdout,"\n%lu",current);
        if (stop) break;
    } while (current < max || infinite);

    if (verbose) fprintf(stderr,"\n");

    /* Save (Close buffer) */
    if (save) closebuffer();

    if (questmode) {
        if (verbose) fprintf(stderr,"\n%s### QUEST MODE%s\n",COL_GREEN,COL_NONE);
        if (isprime(questmode)) { fprintf(stderr,"%lu is prime\n",questmode); fprintf(stdout,"1\n"); 
        } else { fprintf(stderr,"%lu is not prime\n",questmode); fprintf(stdout,"0\n"); }
    }

    if (verbose) {
        fprintf(stderr,"\n%s### STATS%s\n",COL_GREEN,COL_NONE);
        fprintf(stderr,"%sPrime numbers:%s %lu/%lu (%.2f%%)\n",COL_BLUE,COL_NONE,count,current,((count*100)/(float)current));
        gauss=gaussestimate(current);
        fprintf(stderr,"%sGauss estimate:%s %lu/%lu (%.2f%%) (%.2f%% err)\n",COL_BLUE,COL_NONE,gauss,current,((gauss*100)/(float)current),(100-((gauss*100)/(float)count)));
    }

    free(primes);

    fprintf(stdout,"\n");
    
    return 0;
}

/*****************************************************************************/

void ex_program(int sig) {
    if (verbose) fprintf(stderr,"\n%s*** CATCH KILL SIGNAL ***%s",COL_RED,COL_NONE);
    stop = 1;
    (void) signal(SIGINT, SIG_DFL);
}

/*****************************************************************************/

void addprime(long int number) {
    /* adds a prime to the array */

    count++;
    primes = (long int*) realloc (primes, count * sizeof(long int));
    primes[count - 1] = number;
}

void stats(long int current) {
    /* prints some eye-candy stats */

    if (current%INTERVAL==0 || current==max) {
        int n;
        for (n=0;n<100;n++) fprintf(stderr,"%c",8);
        if (max) {
            int perc;
            perc = (int)(100*(current/(float)max));
            fprintf(stderr,"%s[%s",COL_BLUE,COL_NONE);
            for (n=0;n<=50;n++) {
                if (n<perc/2) fprintf(stderr,"%s#%s",COL_GREEN,COL_NONE);
                if (n==perc/2) fprintf(stderr,"%s#%s",COL_RED,COL_NONE);
                if (n>perc/2) fprintf(stderr," ");
            }
            fprintf(stderr,"%3d%%%s]%s ",perc,COL_BLUE,COL_NONE);
        } else {
            fprintf(stderr,"%s[%s%s%c%s%s]%s ",COL_BLUE,COL_NONE,COL_GREEN,MOVE[++pos%MOVE_POS],COL_NONE,COL_BLUE,COL_NONE);
            if (pos==4) pos=0;
        }
        fprintf(stderr,"%s%lu%s/%s%lu%s (%.2f%%)",COL_GREEN,count,COL_NONE,COL_BLUE,current,COL_NONE,((100*count)/(float)current));
        fflush(stderr);
    }
}

/*****************************************************************************/

long int gaussestimate(long int number)
{
    return (long int)(number/trunc(log(number)));
}

long int getmaxcheck(long int number)
{
    return (long int)sqrt(number);
}

/*****************************************************************************/

int isprime(long int number)
{
    if (number%2==0) return 0;                /* exclude even numbers */

    long int maxn = getmaxcheck(number);  /* get higher number to check
                                                 simply SQRT(number) */
    long int n;
    for(n=0; n < count ; n++) {
        if ( primes[n] > maxn ) break;
        if ( number % primes[n] == 0 ) return 0; /* a prime is a factor 
                                                 this number is not prime */
        if ( n == count-1 ) return 0; /* the list lacks numbers [quest mode] */
    }
    return 1; /* THE NUMBER IS A PRIME!!! */
}

/*****************************************************************************/

int loadbuffer(void)
{
    /* open file for reading primes and populate array */

    if (verbose) fprintf(stderr,"\n%s### LOAD BUFFER%s\n",COL_GREEN,COL_NONE);
    if (verbose) fprintf(stderr,"%s*%s Loading from %s\n",COL_GREEN,COL_NONE,filename);

    file = fopen(filename,"r");
    if (file == NULL) {
        fprintf(stderr,"%s* Error opening file %s%s\n",COL_RED,filename,COL_NONE);
        return 0;
    }

    int number;
    char line[100]; /* or other suitable maximum line size */
    while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
    {
        number = (long int)atoi(line);
        if (max > 0 && number > max) break; /*FIXME if -s writes may write number 2 time after max */
        if (number > 0) addprime(number);
    }
    fclose(file);

    if (verbose) fprintf(stderr,"%s*%s Buffer loaded (%lu primes, continue from %s%lu%s)\n",COL_GREEN,COL_NONE,count,COL_GREEN,primes[count-1],COL_NONE);

    return 1;

}

void openbuffer(void)
{
    /* open file for writing (or appending) */

    if (verbose) fprintf(stderr,"%s*%s Open buffer %s for saving\n",COL_GREEN,COL_NONE,filename);

    char *mode = "a";
    if (!load) mode = "w";
    file = fopen(filename,mode);

    if (file == NULL) {
        fprintf(stderr,"%s* Error opening file %s%s\n",COL_RED,filename,COL_NONE);
        exit(5);
    }

    if (!load) fprintf(file,"%d",2); /* [FixFor2] */
}

void closebuffer(void)
{
    /* close file */
    fclose(file);
    if (verbose) fprintf(stderr,"%s*%s Close buffer\n",COL_GREEN,COL_NONE,filename);
}

/*****************************************************************************/

void usage(void)
{
    /* prints usage of program */
    fprintf(stderr,"\n%sUsage:%s %s [options]\n", COL_BOLD, COL_NONE ,program_name);
    fprintf(stderr,"\n%sOptions:%s\n", COL_BOLD, COL_NONE);
    fprintf(stderr,"  %s-h%s          show this help\n", COL_GREEN, COL_NONE);
    fprintf(stderr,"  %s-v%s          verbose\n", COL_GREEN, COL_NONE);
    fprintf(stderr,"  %s-l%s          load primes from <primes.db>\n", COL_GREEN, COL_NONE);
    fprintf(stderr,"  %s-s%s          save primes to <primes.db>\n", COL_GREEN, COL_NONE);
    fprintf(stderr,"  %s-o%s          send primes to <stdout>\n", COL_GREEN, COL_NONE);
    fprintf(stderr,"  %s-g<number>%s  gauss mode (estimate primes from 0 to <number>)\n", COL_GREEN, COL_NONE);
    fprintf(stderr,"  %s-q<number>%s  quest mode (calculate if <number> is prime)\n", COL_GREEN, COL_NONE);
    fprintf(stderr,"  %s-m<number>%s  set max to <number> (0 for infinite)\n", COL_GREEN, COL_NONE);
    fprintf(stderr,"\n%sInfo%s\n", COL_BOLD, COL_NONE);
    fprintf(stderr,"  * write every key by itself. mixed key (like -ls) are not allowed\n", COL_GREEN, COL_NONE, COL_GREEN, COL_NONE);
    fprintf(stderr,"  * %s-g%s ignores other keys except %s-v%s\n", COL_GREEN, COL_NONE, COL_GREEN, COL_NONE);
    fprintf(stderr,"  * use %s-o%s with \"> file\" to write in a custom file\n\n", COL_GREEN, COL_NONE);
    exit (8);
}

void setoptions(int argc, char *argv[])
{

    if (argc==1) usage();

    /* 
     * loop for each option.  
     *   Stop if we run out of arguments
     *   or we get an argument without a dash.
     */
    while ((argc > 1) && (argv[1][0] == '-')) {
        /*
         * argv[1][1] is the actual option character.
         */

        switch (argv[1][1]) {
            case 'v': /* -v verbose */
                verbose = 1; 
                break;
            case 's': /* -s save */
                save = 1; 
                break;
            case 'l': /* -l load */
                load = 1; 
                break;
            case 'o': /* -o output stdout */
                output = 1; 
                break;
            case 'q': /* -q quest mode */
                sscanf(&argv[1][2], "%lu", &questmode);
                break;
            case 'm': /* -m max number */
                sscanf(&argv[1][2], "%lu", &max);
                break;
            case 'g': /* -g gauss estimate number */
                //gaussmode = atoi(&argv[1][2]);
                sscanf(&argv[1][2], "%lu", &gaussmode);
                break;
            case 'h': /* -h help */
                usage();
                break;
            default: /* bad option */
                fprintf(stderr,"Bad option %s\n", argv[1]);
                usage();
        }
        /*
         * move the argument list up one
         * move the count down one
         */
        ++argv;
        --argc;
    }
}
