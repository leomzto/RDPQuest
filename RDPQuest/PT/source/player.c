#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "funcs.h"
#include "utils.h"

const Class CLASSES[QT_CLASSES] = {
    {"supreme_adm", 1000.0f, 1000.0f, 1000.0f},
    {"Guerreiro", 120.0f, 20.0f, 15.0f},
    {"Bruxo", 80.0f, 30.0f, 5.0f},
    {"Arqueiro", 100.0f, 25.0f, 10.0f},
    {"Paladino", 130.0f, 18.0f, 20.0f},
    {"Barbaro", 160.0f, 28.0f, 12.0f},
    {"Ladino", 90.0f, 22.0f, 8.0f}
};

Player generatePlayer(void)
{
    clearBuffer();
    clearScreen(0);

    // Player building
    Player player;
    printf("Criacao de personagem:\n");
    printf("Nome -> ");
    fgets(player.name, sizeof(player.name), stdin);
    player.name[strcspn(player.name, "\n")] = '\0';
    player.name[0] = toupper(player.name[0]);

    clearScreen(0);
    printf("%s esta nascendo.\n", player.name);
    loadingScreen(10, '.', 1);

    // Class choice
    char classChoice[20];
    bool validClass = false;

    printf("Escolha a classe de %s:\n", player.name);
    for(int i = 1; i < QT_CLASSES; i++)
        printf("[%d] %s | HP: %.2f | ATQ: %.2f | DEF: %.2f\n",
                i, CLASSES[i].name, CLASSES[i].life, CLASSES[i].attack, CLASSES[i].deffense);

    while(!validClass)
    {
        printf("Eu escolho ser ");
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
                 printf("Atribuindo a classe %s a %s.\n", player.class.name, player.name);
                 loadingScreen(10, '.', 1);


                printf("%s agora e %s.\n", player.name, player.class.name);
                validClass = true;

                clearScreen(2);
                break;
            }
        }
        if(!validClass) printf("Classe invalida.\n");
    }

    player.life = player.class.life;
    player.attack = player.class.attack;
    player.deffense = player.class.deffense;

    player.life_max = player.class.life;
    player.attack_max = player.class.attack;
    player.deffense_max = player.class.deffense;

    return player;
}

void showStats(Player *player)
{
    clearScreen(0);
    printf("\nNome: %s", player->name);
    printf("\nClasse: %s", player->class.name);
    printf("\nNivel: <level>");

    healthBar("\nVida", player->life, player->class.life);
    printf("\nAtaque: %.2f", player->attack);
    printf("\nDefesa: %.2f", player->deffense);

    char invOption;
    printf("Abrir mochila? (s | n) ");
    scanf(" %c", &invOption);
    invOption = tolower(invOption);

    if(invOption != 'n') printf("<abrir inventario>\n");

    clearBuffer();
}
