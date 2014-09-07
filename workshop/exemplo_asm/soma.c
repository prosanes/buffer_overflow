#include <stdio.h>

int soma (int a, int b)
{
    int resultado;

    resultado = a + b;

    return resultado;
}

int main(void)
{
    int dois;
    dois = soma(1,1);
    printf("1+1 = %d\n", dois);
    return 0;
}
