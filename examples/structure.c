#include <stdio.h>
#include <stdlib.h>

struct point {
    int x;
    int y;
} typedef point;

/* another way to write the same
struct {
    int x;
    int y;
} point;
*/

int main() {

    printf("Example of structure and pointer to structure.\nsee source for more details\n\n");

    point p1;
    p1.x = 1;
    p1.y = 2;

    point p2;
    p2.x = 3;
    p2.y = 4;

    point* pp1;
    pp1 = &p1;

    (*pp1).x = 3; //same as below
    pp1->x = 3;   //same as above

    printf("PP1 x(%d),y(%d)\n",pp1->x,pp1->y);
    printf(" P1 x(%d),y(%d)\n",p1.x,p1.y);
    printf(" P2 x(%d),y(%d)\n",p2.x,p2.y);
    printf("---\n");
    printf("PP1  (%p)\n",&pp1);
    printf("PP1 x(%p),y(%p)\n",&pp1->x,&pp1->y);
    printf(" P1 x(%p),y(%p)\n",&p1.x,&p1.y);
    printf(" P2 x(%p),y(%p)\n",&p2.x,&p2.y);

    return 0;

}
