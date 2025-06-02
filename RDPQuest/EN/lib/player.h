#ifndef PLAYER_H
#define PLAYER_H

#include "items.h"

#define QT_CLASSES 11
#define INVENTORY_SIZE 20

typedef struct
{
    char name[20];
    float life, attack, deffense;
} Class;

typedef struct Player
{
    char name[50];
    Class class;
    float life, attack, deffense;
    float life_max, attack_max, deffense_max;
    int level, xp, maxXP;
    Item inventory[INVENTORY_SIZE];
    int inventoryCount;
} Player;

extern const Class CLASSES[QT_CLASSES];

Player generatePlayer(void);
void showStats(Player *player);

#endif
