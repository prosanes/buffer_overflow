#include <stdlib.h>
#include <stdio.h>

FILE* badfile;

void bof(int arg)
{
    char buffer[8];

    badfile = fopen("badfile", "r");
    fread(buffer, sizeof( char ), 1024, badfile);
}

void print_overflow()
{
    printf("Desviou o caminho!\n");
}

int main(void)
{
    bof(0);
    printf("Nao desviou o caminho!\n");
    
    return 0;
}
    
