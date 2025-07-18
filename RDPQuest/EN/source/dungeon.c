#include "dungeon.h"

#include <stdio.h>
#include <stdbool.h>

#include "player.h"
#include "enemy.h"
#include "combat.h"
#include "utils.h"
#include "miscellaneous.h"
#include "level.h"
#include "items.h"
#include <stdlib.h>

void joinDungeon(Player *player, Dungeon *dungeon)
{
    if(!dungeon->active)
    {
        dungeon->active = true;
        dungeon->current_floor = 0;
        dungeon->completed_floors = 0;

        for(int floor = 0; floor < DG_FLOORS; floor++)
            dungeon->dungeon_enemies[floor] = createDungeonEnemy(floor);
        clearScreen(0);
        printf("Entering the dungeon\n");
        loadingScreen(10, '.', 0);
        clearScreen(1);
        printf("Be cautious...\n");
    }

    while(dungeon->current_floor < DG_FLOORS && dungeon->active)
    {
        printf("Prospecting the %d floor\n", dungeon->current_floor + 1);
        loadingScreen(10, '.', 0);

        Enemy *current_enemy = &dungeon->dungeon_enemies[dungeon->current_floor];
        int result = startBattle(player, current_enemy);

        if(result == 1) // Defeated current floor
        {
            printf("%s defeated the %d floor enemy!\n", player->name, dungeon->current_floor + 1);
            dungeon->current_floor++;

            float dungeonFloorPerk = player->class.life * 0.3;
            player->life += dungeonFloorPerk;
            if(player->life > player->class.life)
                player->life = player->class.life;
            printf("%.2f of life recovered.\n", dungeonFloorPerk);
            Item loot = dropItem();
            //printf("| [LOOT] %s have found a %s!\n", player->name, loot.itemName);
            addItemToInventory(player, loot);
            int qt_xp = (rand() % 16) + 10;
            giveXP(player, qt_xp);
            printf("[XP] +%d\n", qt_xp);

            clearScreen(2);
        }
        else if(result == 0) // Run
        {
            dungeon->active = false;
            printf("You fled the dungeon.\n");
            return;
        }
        else if(result == -1) // Died
        {
            dungeon->active = false;
            return;
        }
    }

    if(dungeon->current_floor >= DG_FLOORS) // Defeated al floors
    {
        printf("You beated the dungeon!\n");
        printf("Life fully recovered\n+5 atk points\n");
        dungeon->active = false;
        player->life = player->life_max;
        player->attack += 5;
        Item loot = dropItem();
        //printf("| [LOOT] %s have found a %s!\n", player->name, loot.itemName);
        addItemToInventory(player, loot);
        int qt_xp = (rand() % 26) + 25;
        giveXP(player, qt_xp);
        printf("[XP] +%d\n", qt_xp);
    }
}

