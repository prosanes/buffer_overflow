#include <stdio.h>

void main();

int funcao()
{
    unsigned char l[2];
    int i;

    l[14] = (main & 0x000000FF);
    //l[13] = (main & 0x0000FF00) >> 8;
    //l[12] = (main & 0x00FF0000) >> 16;
    //l[11] = (main & 0xFF000000) >> 24;

    printf("main: %p\n", main);
    printf("i: %p\n", &i);

    for (i = 0; i < 30; i++)
        printf("l0: %p | %x\n", &l[i], l[i]);

}

void main()
{
    funcao();
}

