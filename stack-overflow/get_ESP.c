/* get_ESP.c */

#include <stdio.h>

unsigned long get_ESP(void)
{
   __asm__("movl %ESP,%EAX");
}

int main()
{
    printf("ESP: 0x%x\n", get_ESP());
    getchar();
    return 0;
}
