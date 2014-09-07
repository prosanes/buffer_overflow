/* stack4.c
    Le um arquivo e tem um  problema de overflow */

#include <stdlib.h>
#include <stdio.h>

FILE *badfile;

unsigned long get_ESP(void)
{
    __asm__("movl %esp,%eax");
}

int bof(int arg)
{
    int i;
    unsigned char buffer[8];

    printf("endereco da pilha: %p\n", get_ESP());
    printf("arg         : %p | %x\n", &arg, arg);
    printf("i           : %p | %x\n", &i, i);
    printf("p badfile   : %p | %x\n", &badfile, badfile);
    for (i = 0; i < 8; i++)
        printf("p buffer[%2d]: %p | %x\n", i, &buffer[i], buffer[i]);
    for (i = 8; i < 35; i++)
        printf("valores [%4d]: %p | %x\n", i, &buffer[i], buffer[i]);

    badfile = fopen("badfile", "r");
    fread( buffer, sizeof( char ), 1024, badfile);
    printf("--------------------*********************------------\n");
    for (i = 0; i < 8; i++)
        printf("p buffer[%2d]: %p | %x\n", i, &buffer[i], buffer[i]);
    for (i = 8; i < 35; i++)
        printf("valores [%4d]: %p | %x\n", i, &buffer[i], buffer[i]);

    printf("Copiou\n");
    //exit(1);
    return 1;
}

void print_overflow()
{
    printf("desviou o caminho\n");
}

int main (int argc, char **argv)
{
    unsigned long pilha;

    printf("endereco do print overflow: %p\n", print_overflow);

    pilha = get_ESP();
    printf("endereco da pilha: %x \n", pilha);

    bof(0);
    printf("Not gonna do it!\n");
    return 1;
}
    
