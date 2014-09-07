#include <stdio.h>

void main();
void imprime();

int funcao()
{
    unsigned char l[2];
    int i;


    l[14] = ((unsigned long int) imprime & 0x000000ff);
    l[15] = ((unsigned long int) imprime & 0x0000ff00) >> 8;
    l[16] = ((unsigned long int) imprime & 0x00ff0000) >> 16;
    l[17] = ((unsigned long int) imprime & 0xff000000) >> 24;

    printf("main: %p\n", main);
    printf("i: %p\n", &i);

    for (i = 0; i < 30; i++)
        printf("l0: %p | %x\n", &l[i], l[i]);

}

void main()
{
    funcao();
}

void imprime()
{
    printf("HA!\n");
}

