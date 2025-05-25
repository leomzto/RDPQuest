#include "includes.h"

void barraVida(char *nome, float vida_atual, float vida_max)
{
    int hp = (int)((vida_atual / vida_max) * TAMANHO_BARRA);

    if(vida_atual > 0 && hp == 0) hp = 1;

    int i;
    printf("%s - [", nome);
    for(i = 0; i < hp; i++)
        printf("+");
    for(i = hp; i < TAMANHO_BARRA; i++)
        printf("-");

    printf("] (%.1f/%.1f)", vida_atual, vida_max);
}
