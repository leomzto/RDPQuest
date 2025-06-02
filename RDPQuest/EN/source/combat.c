#include "combat.h"
#include "utils.h"
#include "player.h"
#include "enemy.h"
// #include "save.h"
#include "miscellaneous.h"
#include "level.h"
#include "items.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int startBattle(Player *player, Enemy *enemy)
{
    float playerMaxLife = player->class.life;
    float enemyMaxLife = enemy->life;

    clearScreen(0);
    printf("Searching for enemies\n");
    loadingScreen(10, '.', 1);
    printf("\nEnemy ahead.\n");
    printf("Starting battle\n");
    loadingScreen(10, '.', 1);
    clearScreen(1);

    healthBar(player->name, player->life, playerMaxLife);
    printf("VS.:\n");
    healthBar(enemy->name, enemy->life, enemyMaxLife);

    float playerAttack = player->attack - enemy->deffense;
    if(playerAttack < 1) playerAttack = 1;
    float enemyAttack = enemy->attack - player->deffense;
    if(enemyAttack < 1) enemyAttack = 1;

    while(player->life > 0 && enemy->life > 0)
    {
        printf("\n[1] Attack\n");
        printf("[2] Run\n");

        char playerChoice[20];
        while(true)
        {
            printf("I'll ");
            fgets(playerChoice, sizeof(playerChoice), stdin);
            playerChoice[strcspn(playerChoice, "\n")] = '\0';

            // Choice: [1] Attack
            if(strcasecmp(playerChoice, "attack") == 0 || strcmp(playerChoice, "1") == 0)
            {
                // Player's turn
                printf("\nAttacking %s [", enemy->name);
                loadingScreen(7, '>', 0);
                printf("]\n");

                enemy->life -= playerAttack;
                if(enemy->life < 0) enemy->life = 0;

                clearScreen(1);
                healthBar(player->name, player->life, playerMaxLife);
                printf("VS.:\n");
                healthBar(enemy->name, enemy->life, enemyMaxLife);
                printf("%s attacked %s dealing %.2f damage.\n", player->name, enemy->name, playerAttack);

                // Enemy's turn
                if(enemy->life > 0)
                {
                    printf("\n%s is attacking you [", enemy->name);
                    loadingScreen(7, '>', 0);
                    printf("]\n");

                    player->life -= enemyAttack;
                    if(player->life < 0) player->life = 0;
                    clearScreen(1);
                    healthBar(player->name, player->life, playerMaxLife);
                    printf("VS.:\n");
                    healthBar(enemy->name, enemy->life, enemyMaxLife);
                    printf("%s attacked you dealing %.2f damage.\n", enemy->name, enemyAttack);
                }
                break;
            }
            // Choice: [2] Run
            else if(strcasecmp(playerChoice, "run") == 0 || strcmp(playerChoice, "2") == 0)
            {
                printf("You choose run.... What a noob.\n");
                loadingScreen(3, '|', 0);
                clearScreen(1);
                return 0;
            }
            // Choice: invalid choice
            else printf("Invalid choise.\nYou can either ATTACK or RUN\n");
        }
        // If player won
        if(enemy->life <= 0)
        {
            float combatPerk = player->class.life * 0.3;
            player->life += combatPerk;
            if(player->life > player->class.life)
                player->life = player->class.life;
            printf("%.2f of life recovered\n", combatPerk);

            printf("\n| You won the battle againts %s!\n", enemy->name);
            Item loot = dropItem();
            //printf("| [LOOT] %s have found a %s!\n", player->name, loot.itemName);
            addItemToInventory(player, loot);
            int qt_xp = (rand() % 16) + 5;
            giveXP(player, qt_xp);
            printf("| [XP] +%d\n", qt_xp);
            clearScreen(3);
            return 1;
        }
        // else if enemy won
        else if(player->life <= 0)
        {
            printf("You lost the battle against %s...\n", enemy->name);
            clearScreen(2);
            printf("Game Over\n");
            clearScreen(2);
            return -1;
        }
    }
    return 0;
}
