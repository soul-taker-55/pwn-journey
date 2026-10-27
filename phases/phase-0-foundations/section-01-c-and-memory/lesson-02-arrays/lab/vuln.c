#include <stdio.h>

int main(void) {
    /* A guard variable placed right AFTER the array in source order.
       We'll watch what happens to it when we write out of bounds. */
    int canary = 0x1111;

    int numbers[4] = {10, 20, 30, 40};   /* 4 ints, side by side, 4 bytes each */
    char name[4]   = {'P', 'W', 'N', 0}; /* 4 chars, 1 byte each, 0 = '\0'     */

    printf("=== int array layout (element size = 4 bytes) ===\n");
    for (int i = 0; i < 4; i++) {
        printf("numbers[%d] = %-3d   address = %p\n",
               i, numbers[i], (void *)&numbers[i]);
    }

    printf("\nbase address (numbers)   = %p\n", (void *)numbers);
    printf("base address (&numbers[0]) = %p\n", (void *)&numbers[0]);
    printf("-> these two are the SAME: the array name is the address of element 0.\n");

    printf("\n=== indexing IS pointer arithmetic ===\n");
    printf("numbers[2]      = %d\n", numbers[2]);
    printf("*(numbers + 2)  = %d   <- identical, always\n", *(numbers + 2));

    printf("\n=== char array layout (element size = 1 byte) ===\n");
    for (int i = 0; i < 4; i++) {
        printf("name[%d] = '%c' (0x%02x)   address = %p\n",
               i, name[i] ? name[i] : '.', (unsigned char)name[i],
               (void *)&name[i]);
    }

    printf("\ncanary (guard var) before = 0x%x\n", canary);

    /* ------------------------------------------------------------------ *
     * OUT-OF-BOUNDS DEMO  (see lab/README.md before enabling)
     *
     * numbers has valid indexes 0..3. Writing numbers[4] is PAST the end.
     * C does NOT stop you. On a typical stack layout the write lands in the
     * neighbouring memory -- which may well be `canary`.
     *
     * To observe it: remove the // in front of the next line, then
     *   gcc -fno-stack-protector vuln.c -o vuln_oob
     *   ./vuln_oob
     * and compare the canary value printed below.
     * ------------------------------------------------------------------ */
    // numbers[4] = 0xdead;   /* <-- uncomment ME for the out-of-bounds demo */

    printf("canary (guard var) after  = 0x%x\n", canary);
    printf("\n(If 'after' changed without touching canary by name, you just\n");
    printf(" watched a 1-element buffer overflow corrupt its neighbour.)\n");

    return 0;
}
