#include "save.h"
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

void getSaveFolderPath(char *buffer, size_t size)
{
    const char *user = getenv("USERPROFILE");
    if(user)
        snprintf(buffer, size, "%s/.RDPQuest/saves/", user);
    else
        snprintf(buffer, size, "./saves/");
}

void mkdirSaves(void)
{
    char path[512];
    getSaveFolderPath(path, sizeof(path));

    char parentPath[512];
    snprintf(parentPath, sizeof(parentPath), "%s/.RDPQuest", getenv("USERPROFILE"));

    struct stat st = {0};
    if (stat(parentPath, &st) == -1)
        MKDIR(parentPath);

    if (stat(path, &st) == -1)
    {
        if (MKDIR(path) != 0)
            perror("Error creating save directory");
    }
}

void savesList(void)
{
    clearScreen(0);
    char folder[512];
    getSaveFolderPath(folder, sizeof(folder));
    printf("Your Saves:\n------------\n");

    bool saveFound = false;
    for(int i = 1; i <= 5; i++)
    {
        char path[600];
        snprintf(path, sizeof(path), "%ssave0%d.sav", folder, i);

        FILE *saveFile = fopen(path, "r");
        if(saveFile != NULL)
        {
            char playerName[50] = "Empty";
            int playerLevel = 0;
            char playerClass[20] = "Unknown";
            char fileLine[100];

            while(fgets(fileLine, sizeof(fileLine), saveFile) != NULL)
            {
                if(strstr(fileLine, "#Name<") != NULL)
                    sscanf(fileLine, "#Name<%[^>]>", playerName);
                else if(strstr(fileLine, "#Level<") != NULL)
                    sscanf(fileLine, "#Level<%d>", &playerLevel);
                else if(strstr(fileLine, "#Class<") != NULL)
                    sscanf(fileLine, "#Class<%[^>]>", playerClass);
            }
            printf("[%d] - %s[%d] (%s)\n", i, playerName, playerLevel, playerClass);
            saveFound = true;
            fclose(saveFile);
        }
        else
            printf("[%d] - Empty Slot\n", i);
    }

    if(!saveFound) printf("You have 0 saves.\n");
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
        printf("Saving");
        loadingScreen(5, '%', 0);
        printf("ERROR 0001: Could not create save file\n");
        return;
    }

    fprintf(gameFile, "#Name<%s>\n", player->name);
    fprintf(gameFile, "#Class<%s>\n", player->class.name);
    fprintf(gameFile, "#Life<%.2f/%.2f>\n", player->life, player->life_max);
    fprintf(gameFile, "#Attack<%.2f>\n", player->attack);
    fprintf(gameFile, "#Deffense<%.2f>\n", player->deffense);
    fprintf(gameFile, "#Level<%d>\n", player->level);
    fprintf(gameFile, "#XP<%d/%d>\n", player->xp, player->maxXP);

    fclose(gameFile);
    printf("Saved!\n%s\n", path);
    clearScreen(2);
}

Player loadSave(int slot)
{
    char folder[512], path[600];
    getSaveFolderPath(folder, sizeof(folder));
    snprintf(path, sizeof(path), "%ssave0%d.sav", folder, slot);

    FILE *loadGame = fopen(path, "r");
    if(loadGame == NULL)
    {
        printf("ERROR: Save %d does not exist.\n", slot);
        Player playerEmpty = {0};
        return playerEmpty;
    }

    Player player = {0};
    char fileLine[100];
    char playerClass[20];

    while(fgets(fileLine, sizeof(fileLine), loadGame) != NULL)
    {
        if(strstr(fileLine, "#Name<") != NULL)
            sscanf(fileLine, "#Name<%[^>]>", player.name);
        else if(strstr(fileLine, "#Class<") != NULL)
        {
            sscanf(fileLine, "#Class<%[^>]>", playerClass);
            playerClass[strcspn(playerClass, "\n")] = '\0';

            for(int i = 0; i < QT_CLASSES; i++)
            {
                if(strcasecmp(CLASSES[i].name, playerClass) == 0)
                {
                    player.class = CLASSES[i];
                    break;
                }
            }
        }
        else if(strstr(fileLine, "#Life<") != NULL)
            sscanf(fileLine, "#Life<%f/%f>", &player.life, &player.life_max);
        else if(strstr(fileLine, "#Attack<") != NULL)
            sscanf(fileLine, "#Attack<%f>", &player.attack);
        else if(strstr(fileLine, "#Deffense<") != NULL)
            sscanf(fileLine, "#Deffense<%f>", &player.deffense);
        else if(strstr(fileLine, "#Level<") != NULL)
            sscanf(fileLine, "#Level<%d>", &player.level);
        else if(strstr(fileLine, "#XP<") != NULL)
            sscanf(fileLine, "#XP<%d/%d>", &player.xp, &player.maxXP);
    }

    fclose(loadGame);

    if(strlen(player.name) == 0)
        printf("ERROR: Save %d is corrupted.\n", slot);
    else
        printf("Save %d loaded!\n", slot);

    return player;
}
