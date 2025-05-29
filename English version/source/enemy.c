#include "enemy.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "player.h"
#include "utils.h"
#include "funcs.h"

const Enemy ENEMIES[] = {
    {"Skeleton", 50.0f, 10.0f, 5.0f, 25.0f},
    {"Warrior Skeleton", 80.0f, 15.0f, 8.0f, 15.0f},
    {"Orc", 120.0f, 20.0f, 10.0f, 20.0f},
    {"Orc Chief", 200.0f, 30.0f, 15.0f, 5.0f},
    {"Goblin", 40.0f, 12.0f, 4.0f, 25.0f},
    {"Goblin Chief", 90.0f, 18.0f, 6.0f, 10.0f},
    {"Young Dragon", 300.0f, 40.0f, 20.0f, 3.0f},
    {"Elder Dragon", 600.0f, 70.0f, 35.0f, 1.0f},
    {"Slime", 30.0f, 8.0f, 2.0f, 30.0f},
    {"King Slime", 150.0f, 18.0f, 10.0f, 5.0f},
    {"Demon", 100.0f, 25.0f, 10.0f, 7.0f},
    {"Lord Demon", 500.0f, 50.0f, 25.0f, 0.5f}
};

Enemy createEnemy(void)
{
    float spawn_chance = 0.0f;

    for(int i = 0; i < QT_ENEMIES; i++)
        spawn_chance += ENEMIES[i].appearingRate;

    float draftEnemies = ((float)rand() / RAND_MAX) * spawn_chance;

    float general_chance = 0.0f;
    for(int i = 0; i < QT_ENEMIES; i++)
    {
        general_chance += ENEMIES[i].appearingRate;
        if(draftEnemies <= general_chance)
            return ENEMIES[i];
    }

    return ENEMIES[0];
}

void startBattle(Player *player, Enemy *enemy)
{
    float playerMaxLife = player->class.life;
    float enemyMaxLife = enemy->life;

    clearScreen(1);
    printf("Searching for enemies\n");
    loadingScreen(10, '.', 1);
    printf("Enemy ahead.\n");
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
        printf("[1] Atacck\n");
        printf("[2] Run\n");

        char playerChoice[20];
        while(true)
        {
            printf("I choose ");
            fgets(playerChoice, sizeof(playerChoice), stdin);
            playerChoice[strcspn(playerChoice, "\n")] = '\0';

            // Choice: [1] Attack
            if(strcasecmp(playerChoice, "attack") == 0 || strcmp(playerChoice, "1") == 0)
            {
                // Player's turn
                printf("Attacking %s [", enemy->name);
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
                    printf("%s is attacking you [", enemy->name);
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
                return;
            }
            // Choice: invalid choice
            else printf("Invalid choise. You can either ATTACK or RUN\n");
        }
        // If player won
        if(enemy->life <= 0)
        {
            float combatPerk = player->class.life * 0.3;
            player->life += combatPerk;
            if(player->life > player->class.life)
                player->life = player->class.life;
            printf("%.2f of life recovered\n", combatPerk);

            printf("You won the battle againts %s!\n", enemy->name);
            clearScreen(2);
            break;
        }
        // else if enemy won
        else if(player->life <= 0)
        {
            printf("You lost the battle against %s...\n", enemy->name);
            clearScreen(2);
            printf("Game Over\n");
            clearScreen(2);
            exit(0);
        }
    }
}

Enemy createDungeonEnemy(int floor)
{
    Enemy enemy = createEnemy();

    float difficulty = 1.0 + (floor * 0.3);
    enemy.life *= difficulty;
    enemy.attack *= difficulty;
    enemy.deffense *= difficulty;

    return enemy;
}
