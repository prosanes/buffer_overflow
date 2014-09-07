#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

void main (int argc, char *argv[])
{
    char str[256];

    strcpy(str, argv[1]);
    printf("The good way of calling printf:\n");
    printf("%s\n", str);
    printf("The bad way of calling printf:\n");
    printf(str);
    printf("\nTerminado ok!\n");

}
