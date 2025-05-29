#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdbool.h>
#include "player.h"
#include "enemy.h"

#define DG_FLOORS 5

typedef struct
{
    int current_floor;
    int completed_floors;
    bool active;
    Enemy dungeon_enemies[DG_FLOORS];
} Dungeon;

void joinDungeon(Player *player, Dungeon *dungeon);

#endif
