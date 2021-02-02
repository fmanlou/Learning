#include <stdio.h>
#include <inttypes.h> /* for uintptr_t */

int main()
{
    char *pointer = "tst";
    uintptr_t ptr;

    ptr = (uintptr_t)pointer;
    printf("%s\n", (char *)ptr);
    printf("%p\n", (void *)ptr);
    ptr = ptr | 3;
    printf("%s\n", (char *)ptr);
    printf("%p\n", (void *)ptr);
}
