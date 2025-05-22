#include "includes.h"
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void limparBuffer(void)
{
    while(getchar() != '\n');
}

void animacaoCarregamento(int tempo_da_animacao, char caractere_da_animacao, int tempo_pos_animacao)
{
    int i;
    for(i = 0; i < tempo_da_animacao; i++)
    {
#ifdef _WIN32
        Sleep(250); // milissegundos
#else
        usleep(250000); // microssegundos
#endif
        printf("%c", caractere_da_animacao);
        fflush(stdout);
    }

#ifdef _WIN32
    Sleep(tempo_pos_animacao * 1000);
#else
    sleep(tempo_pos_animacao);
#endif
}

void limparTela(int tempo)
{
#ifdef _WIN32
    Sleep(tempo * 1000);
    system("cls");
#else
    sleep(tempo);
    system("clear");
#endif
}
