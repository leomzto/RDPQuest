#include "includes.h"

int main(void)
{
    srand(time(NULL));

    while(1)
    {
        int opcao;
        opcao = menu();

        Personagem p;

        if(opcao == 1)
        {
            p = criarPersonagem();
            novoJogo(p);
        }
        else if(opcao == 2)
        {
            puts("Saindo");
            animacaoCarregamento(5, '.', 0);
            puts("");
            break;
        }
    }

    return 0;
}