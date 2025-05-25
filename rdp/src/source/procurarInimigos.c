#include "includes.h"

void iniciarBatalha(Personagem *p, Inimigo *i)
{
    char escolha_jogador[20];
    float vida_maxima_p = p->classe.vida;
    float vida_maxima_i = i->vida;

    float golpe_jogador = p->dano - i->defesa;
    if(golpe_jogador < 1) golpe_jogador = 1;
    float golpe_inimigo = i->dano - p->defesa;
    if(golpe_inimigo < 1) golpe_inimigo = 1;

    limparTela(1);
    puts("\nProcurando inimigos");
    animacaoCarregamento(10, '.', 1);

    puts("\n\nInimigo encontrado.");
    puts("Iniciando batalha");
    animacaoCarregamento(10, '.', 2);
    limparTela(0);

    barraVida(p->nome, p->vida, vida_maxima_p);
    puts("\nVS.:");
    barraVida(i->nome, i->vida, vida_maxima_i);

    while(p->vida > 0 && i->vida > 0)
    {
        puts("\n1. Atacar");
        puts("2. Correr");

        while(1)
        {
            printf("Eu escolho ");
            fgets(escolha_jogador, sizeof(escolha_jogador), stdin);
            escolha_jogador[strcspn(escolha_jogador, "\n")] = '\0';

            // escolheu atacar
            if(strcasecmp(escolha_jogador, "atacar") == 0 || strcmp(escolha_jogador, "1") == 0)
            {
                // vez do jogador
                printf("\nAtacando %s [", i->nome);
                animacaoCarregamento(7, '>', 0);
                puts("]");

                i->vida -= golpe_jogador;
                if (i->vida < 0) i->vida = 0;
                
                limparTela(1);

                barraVida(p->nome, p->vida, vida_maxima_p);
                puts("");
                barraVida(i->nome, i->vida, vida_maxima_i);
                printf("\nVoce atacou %s e causou %.1f de dano.\n", i->nome, golpe_jogador);

                // vez do inimigo
                if(i->vida > 0)
                {
                    printf("%s esta te atacando [", i->nome);
                    animacaoCarregamento(7, '>', 0);
                    puts("]");

                    p->vida -= golpe_inimigo;
                    if (p->vida < 0) p->vida = 0;
                    
                    limparTela(1);

                    barraVida(p->nome, p->vida, vida_maxima_p);
                    puts("");
                    barraVida(i->nome, i->vida, vida_maxima_i);

                    printf("\n%s realizou um contra ataque causando %.1f de dano.\n", i->nome, golpe_inimigo);
                }
                break;
            }
            // escolheu correr
            else if(strcasecmp(escolha_jogador, "correr") == 0 || strcmp(escolha_jogador, "2") == 0)
            {
                puts("Voce escolheu correr, seu cagao.");
                limparTela(1);
                return;
            }
            else
                puts("\nEscolha invalida.\nVoce so pode atacar ou correr.");
        }

        if(i->vida <= 0)
        {
            p->vida += p->classe.vida * 0.3;
            if (p->vida > p->classe.vida) 
                p->vida = p->classe.vida;

            printf("\nVoce venceu a luta contra %s!\n", i->nome);
            limparTela(2);
            break;
        }
        else if(p->vida <= 0)
        {
            printf("\nVoce perdeu a luta contra %s.\n", i->nome);
            limparTela(2);
            puts("Game Over");
            Sleep(2);
            exit(0);
        }
    }
}

Inimigo gerarInimigos(void)
{
    float chance_spawn = 0.0f;

    int i;
    for(i = 0; i < 12; i++)
        chance_spawn += INIMIGOS[i].chances_de_aparecer;

    float sortear_inimigos = ((float)rand() / RAND_MAX) * chance_spawn;

    float chance_geral = 0.0f;
    for(i = 0; i < 12; i++)
    {
        chance_geral += INIMIGOS[i].chances_de_aparecer;
        if(sortear_inimigos <= chance_geral)
            return INIMIGOS[i];
    }

    return INIMIGOS[0];
}