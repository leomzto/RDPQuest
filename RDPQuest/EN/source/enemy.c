#include "enemy.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "player.h"
#include "utils.h"
#include "save.h"
#include "miscellaneous.h"
#include "level.h"

const Enemy ENEMIES[] = {
    // Comon Enemies
    {"Skeleton",           50.0f,   10.0f,  5.0f,  15.0f},
    {"Goblin",             40.0f,   12.0f,  4.0f,  15.0f},
    {"Slime",              30.0f,    8.0f,  2.0f,  12.0f},

    // Medium Enemies
    {"Warrior Skeleton",   80.0f,   15.0f,  8.0f,   8.0f},
    {"Orc",               120.0f,   20.0f, 10.0f,   7.0f},
    {"Goblin Chief",       90.0f,   18.0f,  6.0f,   7.0f},
    {"King Slime",        150.0f,   18.0f, 10.0f,   6.0f},
    {"Demon",             100.0f,   25.0f, 10.0f,   6.0f},

    // Rare Enemies
    {"Orc Chief",         200.0f,   30.0f, 15.0f,   4.0f},
    {"Wraith",             90.0f,   25.0f,  5.0f,   3.5f},
    {"Fire Elemental",    120.0f,   35.0f, 10.0f,   3.0f},
    {"Dark Knight",       180.0f,   40.0f, 20.0f,   2.5f},
    {"Young Dragon",      300.0f,   40.0f, 20.0f,   2.0f},
    {"Lich",              250.0f,   50.0f, 15.0f,   1.5f},

    // Epic/Legendary Enemies
    {"Elder Dragon",      600.0f,   70.0f, 35.0f,   0.7f},
    {"Lord Demon",        500.0f,   50.0f, 25.0f,   0.5f},
    {"Ancient Golem",     700.0f,   55.0f, 40.0f,   0.8f},
    {"Death Reaper",      400.0f,   80.0f, 30.0f,   0.5f}
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

Enemy createDungeonEnemy(int floor)
{
    Enemy enemy = createEnemy();

    float difficulty = 1.0 + (floor * 0.3);
    enemy.life *= difficulty;
    enemy.attack *= difficulty;
    enemy.deffense *= difficulty;

    return enemy;
}
