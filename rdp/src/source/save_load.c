#include "includes.h"

#define PASTA_SAVE "/game/saves/" // caminho do save

void listarSaves(void)
{
    puts("\nSaves Disponiveis:");
    puts("-----------------");
    
    bool encontrou_save = false;

    int i;
    for(i = 1; i <= 5; i++)
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
            encontrou_save = true;
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
    if(arquivo == NULL)
    {
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
            
            for(int i = 0; i < NUM_CLASSES; i++)
            {
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