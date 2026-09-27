#include <stdio.h>

int main(void) {
    int x = 42;         /* an ordinary variable */
    int *p = &x;        /* a pointer storing the address of x */

    printf("value of x directly     : %d\n", x);
    printf("address of x (&x)       : %p\n", (void *)&x);
    printf("content of p (the addr) : %p\n", (void *)p);
    printf("value via *p            : %d\n", *p);

    *p = 99;            /* modifying through the pointer changes x itself */
    printf("\nafter  *p = 99  ->  x = %d\n", x);

    return 0;
}
