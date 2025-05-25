#include "includes.h"

int menu(void) 
{
    int opcao;
    
    do
    {
        limparTela(0);
        
        puts("-=- Rogue De Prompt -=-");
        puts("1. Novo Jogo");
        puts("2. Carregar Save");
        puts("0. Sair");
        printf(" --> ");
        
        if(scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 2)
        {
            puts("Opcao invalida!");
            limparBuffer();
            Sleep(1000);
            continue;
        }

        switch(opcao)
        {
            case 0:  // sair
            {
                puts("\nSaindo do jogo");
                animacaoCarregamento(5, '.', 1);
                exit(0);
            }
            case 1:  // criar novo jogo
            {
                limparTela(0);
                puts("Criando Mundo");
                printf("Progresso: [");
                animacaoCarregamento(10, '#', 0);
                puts("] 100%");
                
                Personagem p = criarPersonagem();
                jogo(p);
                return 1;
            }
            case 2:  // carregar jogo
            {
                limparTela(0);
                listarSaves();
                
                int slot;
                printf("\nEscolha o save (1-5): ");
                if(scanf("%d", &slot) != 1 || slot < 1 || slot > 5)
                {
                    puts("Slot invalido!");
                    limparBuffer();
                    Sleep(1);
                    continue;
                }
                
                limparTela(0);
                puts("Carregando Save");
                printf("Progresso: [");
                animacaoCarregamento(10, '#', 0);
                puts("] 100%");
                
                Personagem p = carregarSave(slot);
                if(strlen(p.nome) > 0)
                {
                    limparTela(1);
                    jogo(p);
                }
                break;
            }
        }
        
    } while(true);
    
    return opcao;
}

void jogo(Personagem p)
{
    while(p.vida > 0)
    {
        int escolha;
        puts("<< Rogue de Prompt >>\n");
        puts("| 1. Procurar monstros");
        puts("| 2. Desafiar masmorra");
        printf("| 3. Ver [%s]\n", p.nome);
        puts("| 4. Salvar progresso");
        puts("| 0. Voltar ao menu");
        printf("\nEscolha -> ");
        scanf("%d", &escolha);
        limparBuffer();

        switch(escolha)
        {
            case 0:
                return;
            case 1:
            {
                Inimigo inimigo = gerarInimigos();
                iniciarBatalha(&p, &inimigo);
                break;
            }
            case 2:
            {
                Masmorra m;
                desafiarMasmorra(&p, &m);
                break;
            }
            case 3:
            {
                mostrarStatus(&p);
                break;
            }
            case 4:
            {
                int slot;
                listarSaves();
                printf("Escolha o slot para salvar (1-5): ");
                scanf("%d", &slot);
                limparBuffer();
                salvarJogo(&p, slot);
                break;
            }
        }
    }
}



