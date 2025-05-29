#include "funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#ifdef _WIN32
    #include <direct.h>
    #include <sys/stat.h>
    #define MKDIR(dir) _mkdir(dir)
    #define stat _stat
#else
    #include <sys/stat.h>
    #include <unistd.h>
    #define MKDIR(dir) mkdir(dir, 0777)
#endif

#include "player.h"
#include "utils.h"

#define BAR_LENGHT 20

void healthBar(char *string, float currentLife, float maxLife)
{
    int hp = (int)((currentLife / maxLife) * BAR_LENGHT);
    if(currentLife > 0 && hp == 0) hp = 1;

    printf("%s - [", string);
    for(int i = 0; i < hp; i++) printf("+");
    for(int i = hp; i < BAR_LENGHT; i++) printf("-");
    printf("] (%.2f/%.2f)", currentLife, maxLife);
}

void getSaveFolderPath(char *buffer, size_t size)
{
    const char *user = getenv("USERPROFILE");
    if(user)
    {
        snprintf(buffer, size, "%s/.RDPQuest/saves/", user);
    }
    else
    {
        snprintf(buffer, size, "./saves/");
    }
}

void mkdirSaves(void)
{
    char path[512];
    getSaveFolderPath(path, sizeof(path));

    char parentPath[512];
    snprintf(parentPath, sizeof(parentPath), "%s/.RDPQuest", getenv("USERPROFILE"));

    struct stat st = {0};
    if (stat(parentPath, &st) == -1) {
        MKDIR(parentPath);
    }

    if (stat(path, &st) == -1)
    {
        if (MKDIR(path) != 0)
            perror("Erro criando diretorio de saves");
    }
}

void savesList(void)
{
    char folder[512];
    getSaveFolderPath(folder, sizeof(folder));
    printf("Seus saves:\n------------\n");

    bool saveFound = false;
    for(int i = 1; i <= 5; i++)
    {
        char path[600];
        snprintf(path, sizeof(path), "%ssave0%d.sav", folder, i);

        FILE *saveFile = fopen(path, "r");
        if(saveFile != NULL)
        {
            char playerName[50] = "Indigente";
            char playerClass[20] = "Plebeu";
            char fileLine[100];

            while(fgets(fileLine, sizeof(fileLine), saveFile) != NULL)
            {
                if(strstr(fileLine, "#Nome<") != NULL)
                    sscanf(fileLine, "#Nome<%[^>]>", playerName);
                else if(strstr(fileLine, "#Classe<") != NULL)
                    sscanf(fileLine, "#Classe<%[^>]>", playerClass);
            }
            printf("[%d] - %s (%s)\n", i, playerName, playerClass);
            saveFound = true;
            fclose(saveFile);
        }
        else
            printf("[%d] - Disponivel\n", i);
    }

    if(!saveFound) printf("ERRO 0001: Nao foi possivel criar o arquivo\n");
    printf("------------\n");
}

void saveGame(Player *player, int saveSlot)
{
    char folder[512], path[600];
    getSaveFolderPath(folder, sizeof(folder));
    snprintf(path, sizeof(path), "%ssave0%d.sav", folder, saveSlot);

    FILE *gameFile = fopen(path, "w");
    if(gameFile == NULL)
    {
        printf("Salvando");
        loadingScreen(5, '%', 0);
        printf("ERRO 0001: Nao foi possivel criar o arquivo\n");
        return;
    }

    fprintf(gameFile, "#Nome<%s>\n", player->name);
    fprintf(gameFile, "#Classe<%s>\n", player->class.name);
    fprintf(gameFile, "#Vida<%.2f/%.2f>\n", player->life, player->life_max);
    fprintf(gameFile, "#Ataque<%.2f>\n", player->attack);
    fprintf(gameFile, "#Defesa<%.2f>\n", player->deffense);

    fclose(gameFile);
    printf("Salvo!\n%s\n", path);
}

Player loadSave(int slot)
{
    char folder[512], path[600];
    getSaveFolderPath(folder, sizeof(folder));
    snprintf(path, sizeof(path), "%ssave0%d.sav", folder, slot);

    FILE *loadGame = fopen(path, "r");
    if(loadGame == NULL)
    {
        printf("ERRO: Save %d nao existe.\n", slot);
        Player playerEmpty = {0};
        return playerEmpty;
    }

    Player p = {0};
    char fileLine[100];
    char playerClass[20];

    while(fgets(fileLine, sizeof(fileLine), loadGame) != NULL)
    {
        if(strstr(fileLine, "#Nome<") != NULL)
            sscanf(fileLine, "#Nome<%[^>]>", p.name);
        else if(strstr(fileLine, "#Classe<") != NULL) {
            sscanf(fileLine, "#Classe<%[^>]>", playerClass);
            for(int i = 0; i < QT_CLASSES; i++) {
                if(strcmp(CLASSES[i].name, playerClass) == 0)
                {
                    p.class = CLASSES[i];
                    break;
                }
            }
        }
        else if(strstr(fileLine, "#Vida<") != NULL)
            sscanf(fileLine, "#Vida<%f/%f>", &p.life, &p.life_max);
        else if(strstr(fileLine, "#Ataque<") != NULL)
            sscanf(fileLine, "#Ataque<%f>", &p.attack);
        else if(strstr(fileLine, "#Defesa<") != NULL)
            sscanf(fileLine, "#Defesa<%f>", &p.deffense);
    }

    fclose(loadGame);

    if(strlen(p.name) == 0)
        printf("ERRO: Save %d esta corrompido.\n", slot);
    else
        printf("Save %d carregado!\n", slot);

    return p;
}
