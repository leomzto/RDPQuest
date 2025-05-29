#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"

#define QT_ENEMIES 18

typedef struct
{
    char name[50];
    float life, attack, deffense;
    float appearingRate;
} Enemy;

Enemy createEnemy(void);
Enemy createDungeonEnemy(int floor);

#endif
