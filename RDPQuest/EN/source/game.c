#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "player.h"
#include "enemy.h"
#include "dungeon.h"
#include "utils.h"
#include "save.h"

int gameMenu(void)
{
    int menuChoice;

    do{
        clearScreen(0);

        printf("-= Prompt Rogue =-\n");
        printf("1. New Game\n");
        printf("2. Load Save\n");
        printf("0. Exit\n");
        printf(" --> ");

        if(scanf("%d", &menuChoice) != 1 || menuChoice < 0 || menuChoice > 2)
        {
            printf("Invalid option.\n");
            clearBuffer();
            continue;
        }

        switch(menuChoice)
        {
            case 0: // Exit
            {
                printf("Closing game\n");
                loadingScreen(3, '.', 1);
                exit(0);
            }
            case 1: // New game
            {
                clearScreen(0);
                printf("Generatin World\n");
                printf("Progres: [");
                loadingScreen(10, '#', 0);
                printf("]\n");

                Player player = generatePlayer();
                startGame(player);
                return 1;
            }
            case 2: // Load Save
            {
                clearScreen(0);
                savesList();

                int saveSlot;
                printf("Choose your save (1 - 5)\nPress \'0' to return ");
                if(scanf("%d", &saveSlot) != 1 || saveSlot < 0 || saveSlot > 5)
                {
                    printf("Invalid slot.\n");
                    clearBuffer();
                    continue;
                }
                if(saveSlot == 0)
                    return 0;
                clearBuffer();

                clearScreen(0);
                printf("Loading save\n");
                printf("Progress: [");
                loadingScreen(10, '#', 0);
                printf("]\n");

                Player player = loadSave(saveSlot);
                if(strlen(player.name) > 0)
                {
                    clearScreen(1);
                    startGame(player);
                }
                break;
            }
        }
    } while(true);

    return menuChoice;
}

void startGame(Player player)
{
    while(player.life > 0)
    {
        int option;
        printf("<< Prompt Rogue >>\n");
        printf("| 1. Search for enemies\n");
        printf("| 2. Look for dungeons\n");
        printf("| 3. Inspect [%s]\n", player.name);
        printf("| 4. Save progression\n");
        printf("| 0. Back to menu\n");
        printf("| -> ");
        scanf("%d", &option);
        clearBuffer();

        switch(option)
        {
            case 0: // Back to menu
                return;
            case 1: // Search for enemies
            {
                Enemy enemy = createEnemy();
                startBattle(&player, &enemy);
                break;
            }
            case 2: // Look for dungeons
            {
                Dungeon dungeon;
                joinDungeon(&player, &dungeon);
                break;
            }
            case 3: // Inspect player
            {
                showStats(&player);
                break;
            }
            case 4: // Save progression
            {
                int saveSlot;
                savesList();
                printf("Chose the save slot (1-5): ");
                scanf("%d", &saveSlot);
                clearBuffer();
                saveGame(&player, saveSlot);
                break;
            }
        }
    }
}

