#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"

#define QT_ENEMIES 12

typedef struct
{
    char name[50];
    float life, attack, deffense;
    float appearingRate;
} Enemy;

Enemy createEnemy(void);
void startBattle(Player *player, Enemy *enemy);
Enemy createDungeonEnemy(int floor);

#endif // ENEMY_H
