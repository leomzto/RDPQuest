#include "includes.h"
//adicionado tudo em utility.c
void limparBuffer(void)
{
    while(getchar() != '\n');
}

void animacaoCarregamento(int tempo, char caractere, int espera)
{
    for(int i = 0; i < tempo; i++)
    {
        Sleep(250);
        putchar(caractere);
        fflush(stdout);
    }
    Sleep(espera * 1000);

}

void limparTela(int espera)
{
    Sleep(espera * 1000);
    system("cls");
}
