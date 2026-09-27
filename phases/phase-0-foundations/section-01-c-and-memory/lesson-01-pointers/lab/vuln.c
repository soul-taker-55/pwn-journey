#include <stdio.h>

int main(void) {
    int x = 42;         /* متغيّر عادي */
    int *p = &x;        /* مؤشّر يخزّن عنوان x */

    printf("قيمة x مباشرةً      : %d\n", x);
    printf("عنوان x (&x)        : %p\n", (void *)&x);
    printf("محتوى p (يخزّن العنوان): %p\n", (void *)p);
    printf("القيمة عبر *p       : %d\n", *p);

    *p = 99;            /* التعديل عبر المؤشّر يغيّر x نفسه */
    printf("\nبعد  *p = 99  ->  x = %d\n", x);

    return 0;
}
