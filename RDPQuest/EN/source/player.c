#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "save.h"
#include "utils.h"
#include "miscellaneous.h"
#include "level.h"

const Class CLASSES[QT_CLASSES] = {
    {"supreme_adm", 999.9f, 999.9f, 999.9f}, // Test class

    {"Warrior",     160.0f, 25.0f, 20.0f},
    {"Wizard",      100.0f, 40.0f,  8.0f},
    {"Archer",      120.0f, 32.0f, 12.0f},
    {"Paladin",     180.0f, 22.0f, 28.0f},
    {"Barbarian",   200.0f, 30.0f, 10.0f},
    {"Rogue",       110.0f, 28.0f, 10.0f},
    {"Necromancer",  90.0f, 38.0f,  9.0f},
    {"Knight",      170.0f, 24.0f, 25.0f},
    {"Assassin",    100.0f, 35.0f,  8.0f},
    {"Monk",        130.0f, 26.0f, 18.0f}
};

Player generatePlayer(void)
{
    clearBuffer();
    clearScreen(0);

    // Player building
    Player player;
    printf("Player building:\n");
    printf("Name -> ");
    fgets(player.name, sizeof(player.name), stdin);
    player.name[strcspn(player.name, "\n")] = '\0';
    player.name[0] = toupper(player.name[0]);

    clearScreen(0);
    printf("%s is comming to life.\n", player.name);
    loadingScreen(10, '.', 1);
    clearScreen(0);

    // Class choice
    char classChoice[20];
    bool validClass = false;

    printf("Choose %s's class:\n", player.name);
    for(int i = 1; i < QT_CLASSES; i++)
        printf("[%d] %s | HP: %.2f | ATK: %.2f | DEF: %.2f\n",
                i, CLASSES[i].name, CLASSES[i].life, CLASSES[i].attack, CLASSES[i].deffense);

    while(!validClass)
    {
        printf("\n>>> I wanna be a ");
        fgets(classChoice, sizeof(classChoice), stdin);
        classChoice[strcspn(classChoice, "\n")] = '\0';

        for(int i = 0; i < QT_CLASSES; i++)
        {
            if(strcasecmp(classChoice, CLASSES[i].name) == 0 ||
                (isdigit(classChoice[0]) &&
                atoi(classChoice) == i))
            {
                 clearScreen(1);

                 player.class = CLASSES[i];
                 player.class.name[0] = tolower(player.class.name[0]);
                 printf("Assigning the %s class to %s.\n", player.class.name, player.name);
                 loadingScreen(10, '.', 1);
                //printf("\n%s is now a %s.\n", player.name, player.class.name);
                validClass = true;

                clearScreen(1);
                break;
            }
        }
        if(!validClass) printf("Invalid class.\n");
    }

    player.life = player.class.life;
    player.attack = player.class.attack;
    player.deffense = player.class.deffense;

    player.level = 1;
    player.xp = 0;
    player.maxXP = 50;

    player.life_max = player.class.life;
    player.attack_max = player.class.attack;
    player.deffense_max = player.class.deffense;

    return player;
}

void showStats(Player *player)
{
    clearScreen(0);
    printf("\n| Name: %s", player->name);
    printf("\n| Class: %s", player->class.name);
    printf("\n| Level: %d", player->level);
    xpBar("\n| XP", player->xp, player->maxXP);
    healthBar("\n| Life", player->life, player->class.life);
    printf("| Attack: %.2f", player->attack);
    printf("\n| Deffense: %.2f", player->deffense);
    printf("\n| [ENTER]");

    clearBuffer();
    clearScreen(0);
}
