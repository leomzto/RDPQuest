#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "player.h"
#include "enemy.h"
#include "dungeon.h"
#include "utils.h"
#include "funcs.h"

int gameMenu(void)
{
    int menuChoice;

    do{
        clearScreen(0);

        printf("-= Prompt Rogue =-\n");
        printf("1. Novo Jogo\n");
        printf("2. Carregar Save\n");
        printf("0. Sair\n");
        printf(" --> ");

        if(scanf("%d", &menuChoice) != 1 || menuChoice < 0 || menuChoice > 2)
        {
            printf("Opcao invalida.\n");
            clearBuffer();
            continue;
        }

        switch(menuChoice)
        {
            case 0: // Exit
            {
                printf("Fechando o jogo\n");
                loadingScreen(3, '.', 1);
                exit(0);
            }
            case 1: // New game
            {
                clearScreen(0);
                printf("Carregando o mundo\n");
                printf("Progresso: [");
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
                printf("Escolha um save (1 - 5): ");
                if(scanf("%d", &saveSlot) != 1 || saveSlot < 1 || saveSlot > 5)
                {
                    printf("Slot invalido.\n");
                    clearBuffer();
                    continue;
                }

                clearScreen(0);
                printf("Carregando save\n");
                printf("Progresso: [");
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
        printf("| 1. Procurar por inimigos\n");
        printf("| 2. Procurar masmorras\n");
        printf("| 3. Inspecionar [%s]\n", player.name);
        printf("| 4. Salvar progresso\n");
        printf("| 0. Voltar ao menu\n");
        printf("\t-> ");
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
                printf("Escolha o save (1-5): ");
                scanf("%d", &saveSlot);
                clearBuffer();
                saveGame(&player, saveSlot);
                break;
            }
        }
    }
}

