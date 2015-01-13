#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char label[20];
} LABEL;

typedef struct {
    char* label;
} LABEL2;

typedef struct {
    LABEL* label;
    int x;
    int y;
    int z;
} POINT;

typedef struct {
    LABEL2* label;
    int x;
    int y;
    int z;
} POINT2;
 
int main()
{
    LABEL* l;

    l = (LABEL*)malloc(5*sizeof(LABEL));
    int i;
    for (i=0;i<5;i++) {
        sprintf(l[i].label,"%dtest",i);
    }

    /* LABEL2 */
    LABEL2 l2;
    l2.label = (char*)malloc(10*sizeof(char));
    l2.label = "test";

    POINT p = { l, 2, 3 };
    printf("%s,%d,%d\n",p.label[2].label,p.x,p.y);
    printf("%p,%p,%p\n",&p.label[2].label,&p.x,&p.y);
    printf("sizeof point %lu\n",sizeof(POINT));
    printf("sizeof point2 %lu\n",sizeof(POINT2));
    printf("sizeof label %lu\n",sizeof(LABEL));
    printf("sizeof label2 %lu\n",sizeof(LABEL2));
    return 0;
}
