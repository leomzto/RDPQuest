#include "includes.h"

int menu(void) 
{
    int opcao;
    
    do
    {
        limparTela(0);
        
        puts("-=- RPG -=-");
        puts("1. Novo Jogo");
        puts("2. Sair");
        printf(" --> ");
        
        if(scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 2)
        {
            puts("Opcao invalida!");
            limparBuffer();
            sleep(1);
            continue;
        }
        
        if(opcao == 1)
        {
            limparTela(0);
            puts("\nCarregando jogo");
            printf("Progresso: [");
            animacaoCarregamento(10, '#', 0);
            puts("] 100%\n");
            sleep(1);
        }
        
    } while(opcao < 1 || opcao > 2);
    
    return opcao;
}

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
    for (i = 0; i < NUM_CLASSES; i++)
        printf("%d. %s | HP: %.1f | ATQ: %.1f | DEF: %.1f\n",
                i + 1, CLASSES[i].nome, CLASSES[i].vida, CLASSES[i].dano, CLASSES[i].defesa);

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
                
                printf("\n\n%s agora e %s\n", p.nome, p.classe.nome);
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

void novoJogo(Personagem p)
{
    while(p.vida > 0)
    {
        int escolha;
        puts("O que voce que fazer agora?");
        puts("1. Procurar monstros");
        puts("2. Desafiar masmorra");
        printf("3. Ver [%s]\n", p.nome);
        puts("0. Voltar ao menu");
        printf("Escolha -> ");
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
        }
    }
}

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
            sleep(2);
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

void desafiarMasmorra(Personagem *p, Masmorra *m) 
{
    int i;

    if(!m->ativa)
    {
        m->ativa = true;
        m->andar_atual = 0;
        m->andares_completos = 0;

        for(i = 0; i < NUM_ANDARES; i++)
            m->inimigos_masmorra[i] = gerarInimigosMasmorra(i);

        puts("\nEntrando na masmorra");
        animacaoCarregamento(10, '.', 0);
        limparTela(1);

        puts("\n\nVoce entrou!\nTome cuidado.");
    }

    while(m->andar_atual < NUM_ANDARES && m->ativa)
    {   
        printf("\nExplorando - Andar [%d]/[%d]\n", m->andar_atual + 1, NUM_ANDARES);
        animacaoCarregamento(10, '.', 0);
        puts("\nInimigo encontrado!");

        Inimigo* inimigo_atual = &m->inimigos_masmorra[m->andar_atual];
        
        iniciarBatalha(p, inimigo_atual);

        if (p->vida > 0 && (*inimigo_atual).vida <= 0)
        {
            printf("\n%s derrotou o inimigo do andar %d!\n", p->nome, m->andar_atual + 1);
            m->andar_atual++;
            
            p->vida += p->classe.vida * 0.3;
            if (p->vida > p->classe.vida)
                p->vida = p->classe.vida;
            
            limparTela(1);
        } 
        else if(p->vida <= 0)
        {
            m->ativa = false;
            return;
        }
    }

    if(m->andar_atual >= NUM_ANDARES)
    {
        puts("\nMasmorra finalizada!");
        m->ativa = false;
        p->vida = p->classe.vida;
        p->dano += 5;
    }
}

Inimigo gerarInimigosMasmorra(int andar)
{
    Inimigo inimigo = gerarInimigos();

    float dificuldade = 1.0 + (andar * 0.2);
    inimigo.vida *= dificuldade;
    inimigo.dano *= dificuldade;
    inimigo.defesa *= dificuldade;

    return inimigo;
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
