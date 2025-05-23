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
        puts("3. Sair");
        printf(" --> ");
        
        if(scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 3)
        {
            puts("Opcao invalida!");
            limparBuffer();
            sleep(1);
            continue;
        }

        switch(opcao)
        {
            case 1:  // criar novo jogo
            {
                limparTela(0);
                puts("Criando Mundo");
                printf("Progresso: [");
                animacaoCarregamento(10, '#', 0);
                puts("] 100%");
                
                Personagem p = criarPersonagem();
                novoJogo(p);
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
                    sleep(1);
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
                    printf("\nSave de %s carregado!\n", p.nome);
                    sleep(1);
                    novoJogo(p);
                }
                break;
            }
            case 3:  // sair
            {
                puts("\nSaindo do jogo...");
                animacaoCarregamento(5, '.', 1);
                exit(0);
            }
        }
        
    } while(true);
    
    return opcao;
}

void listarSaves(void)
{
    puts("\nSaves Disponiveis:");
    puts("-----------------");
    
    int encontrou_save = 0;
    
    for(int i = 1; i <= 5; i++)
    {
        char caminho[100];
        sprintf(caminho, PASTA_SAVE "save0%d.txt", i);
        
        FILE *arquivo = fopen(caminho, "r");
        if(arquivo != NULL) {
            char nome_personagem[50] = "Vazio";
            char classe[20] = "Desconhecida";
            char linha[100];
            
            while(fgets(linha, sizeof(linha), arquivo) != NULL)
            {
                if(strstr(linha, "#Nome<") != NULL)
                {
                    sscanf(linha, "#Nome<%[^>]>", nome_personagem);
                }
                else if(strstr(linha, "#Classe<") != NULL)
                {
                    sscanf(linha, "#Classe<%[^>]>", classe);
                }
            }
            
            printf("%d - %s (%s)\n", i, nome_personagem, classe);
            encontrou_save = 1;
            fclose(arquivo);
        }
        else
            printf("%d - Slot vazio\n", i);
    }
    
    if(!encontrou_save)
        puts("Nenhum save encontrado!");
    puts("-----------------");
}

void salvarJogo(Personagem *p, int espaco)
{
    char caminho[100];
    sprintf(caminho, PASTA_SAVE "save0%d.txt", espaco);

    FILE *arquivo = fopen(caminho, "w");
    if(arquivo == NULL)
    {
        puts("Erro ao salvar progresso.");
        return;
    }

    fprintf(arquivo, "#Nome<%s>\n", p->nome);
    fprintf(arquivo, "#Classe<%s>\n", p->classe.nome);
    fprintf(arquivo, "#Vida<%.0f/%.0f>\n", p->vida, p->vida_max);
    fprintf(arquivo, "#Dano<%.0f>\n", p->dano);
    fprintf(arquivo, "#Defesa<%.0f>\n", p->defesa);
    //nivel fprintf(arquivo, "#Nivel<%d>\n", p->nivel);
    //xp    fprintf(arquivo, "#xp<%.0f>\n", p->xp);
    //itens inventario

    fclose(arquivo);
    printf("Salvo!\n%s\n", caminho);
}

Personagem carregarSave(int slot)
{
    char caminho[100];
    sprintf(caminho, PASTA_SAVE "save0%d.txt", slot);
    
    FILE *arquivo = fopen(caminho, "r");
    if(arquivo == NULL) {
        printf("Erro: Save %d nao encontrado.\n", slot);
        Personagem p_vazio = {0};
        return p_vazio;
    }

    Personagem p = {0};
    char linha[100];
    char nome_classe[20];

    while(fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if(strstr(linha, "#Nome<") != NULL) 
            sscanf(linha, "#Nome<%[^>]>", p.nome);
        
        else if(strstr(linha, "#Classe<") != NULL)
        {
            sscanf(linha, "#Classe<%[^>]>", nome_classe);
            
            for(int i = 0; i < NUM_CLASSES; i++) {
                if(strcmp(CLASSES[i].nome, nome_classe) == 0)
                {
                    p.classe = CLASSES[i];
                    break;
                }
            }
        }
        else if(strstr(linha, "#Vida<") != NULL) 
            sscanf(linha, "#Vida<%f/%f>", &p.vida, &p.vida_max);
        
        else if(strstr(linha, "#Dano<") != NULL) 
            sscanf(linha, "#Dano<%f>", &p.dano);
        
        else if(strstr(linha, "#Defesa<") != NULL) 
            sscanf(linha, "#Defesa<%f>", &p.defesa);
    }
    
    fclose(arquivo);
    
    if(strlen(p.nome) == 0) 
        printf("ERRO: Save %d esta corrompido.\n", slot);
    else 
        printf("Save %d carregado com sucesso!\n", slot);
    
    return p;
}

void novoJogo(Personagem p)
{
    while(p.vida > 0)
    {
        int escolha;
        puts("<< Rogue de Prompt >>\n");
        puts("| 1. Procurar monstros");
        puts("| 2. Desafiar masmorra");
        printf("| 3. Ver [%s]\n", p.nome);
        puts("| 4. Salvar progresso");
        puts("|  0. Voltar ao menu");
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
