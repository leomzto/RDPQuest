#include "includes.h"

void limparBuffer(void)
{
    while(getchar() != '\n');
}

void animacaoCarregamento(int tempo_da_animacao, char caractere_da_animacao, int tempo_pos_animacao)
{
    int i;
    for(i = 0; i < tempo_da_animacao; i++)
    {
        usleep(250000);
        printf("%c", caractere_da_animacao);
        fflush(stdout);
    }
    sleep(tempo_pos_animacao);
}

void limparTela(int tempo, char comando[])
{
    sleep(tempo);
    system(comando);
}