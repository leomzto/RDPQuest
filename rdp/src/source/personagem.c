#include "includes.h"

Personagem criarPersonagem(void)
{
    limparBuffer();
    limparTela(0);
    // criaçao do personagem
    Personagem p;
    puts("Cricao de personagem:");
    printf("Nome -> ");
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';
    p.nome[0] = toupper(p.nome[0]);

    limparTela(0);
    printf("%s esta nascendo.\n", p.nome);
    animacaoCarregamento(10, '.', 1);

    // escolha da classe
    char escolha_classe[20];
    bool classe_valida = false;
    int i;
    printf("\n\nEscolha a classe de %s:\n", p.nome);
    for (i = 1; i < NUM_CLASSES; i++)
        printf("%d. %s | HP: %.1f | ATQ: %.1f | DEF: %.1f\n",
                i, CLASSES[i].nome, CLASSES[i].vida, CLASSES[i].dano, CLASSES[i].defesa);

    while(!classe_valida)
    {
        printf("\nEu escolho ");
        fgets(escolha_classe, sizeof(escolha_classe), stdin);
        escolha_classe[strcspn(escolha_classe, "\n")] = '\0';

        for(i = 0; i < NUM_CLASSES; i++)
        {
            if(strcasecmp(escolha_classe, CLASSES[i].nome) == 0 || (isdigit(escolha_classe[0]) && atoi(escolha_classe) == i))
            {
                limparTela(1);

                p.classe = CLASSES[i];
                printf("Atribuindo a classe %s a %s.\n",p.classe.nome, p.nome);
                animacaoCarregamento(10, '.', 1);
                
                p.classe.nome[0] = tolower(p.classe.nome[0]);
                printf("\n\n%s agora pertence a classe %s\n", p.nome, p.classe.nome);
                classe_valida = true;

                limparTela(2);
                break;
            }
        }

        if(!classe_valida)
            puts("Classe invalida.");
    }

    p.vida = p.classe.vida;
    p.dano = p.classe.dano;
    p.defesa = p.classe.defesa;

    p.vida_max = p.classe.vida;
    p.dano_max = p.classe.dano;
    p.defesa_max = p.classe.defesa;

    return p;
}

void mostrarStatus(Personagem *p)
{
    limparTela(0);
    printf("\nNome: %s", p->nome);
    printf("\nClasse: %s", p->classe.nome);
    printf("\nNivel: <nivel>");

    barraVida("\nVida", p->vida, p->classe.vida);
    printf("\nDano: %.1f", p->dano);
    printf("\nDefesa: %.1f", p->defesa);

    char escolha;
    puts("\nDeseja abrir o inventario?");
    puts("S / N --> ");
    scanf(" %c", &escolha);
    escolha = tolower(escolha);

    if(escolha == 's')
        puts("<abrir inventario>");
    
    limparBuffer();
}