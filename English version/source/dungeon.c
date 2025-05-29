#include "dungeon.h"

#include <stdio.h>
#include <stdbool.h>

#include "player.h"
#include "enemy.h"
#include "utils.h"

void joinDungeon(Player *player, Dungeon *dungeon)
{
    if(!dungeon->active)
    {
        dungeon->active = true;
        dungeon->current_floor = 0;
        dungeon->completed_floors = 0;

        for(int floor = 0; floor < DG_FLOORS; floor++)
            dungeon->dungeon_enemies[floor] = createDungeonEnemy(floor);

        printf("Entering the dungeon\n");
        loadingScreen(10, '.', 0);
        clearScreen(1);
        printf("Be cautious...\n");
    }

    while(dungeon->current_floor < DG_FLOORS && dungeon->active)
    {
        printf("Prospecting the %d floor\n", dungeon->current_floor + 1);
        loadingScreen(10, '.', 0);
        printf("Enemy ahead!\n");

        Enemy *current_enemy = &dungeon->dungeon_enemies[dungeon->current_floor];
        startBattle(player, current_enemy);

        if(player->life > 0 && current_enemy->life <= 0)
        {
            printf("%s defeated the %d floor enemy!\n", player->name, dungeon->current_floor + 1);
            dungeon->current_floor++;

            float dungeonFloorPerk = player->class.life * 0.3;
            player->life += dungeonFloorPerk;
            if(player->life > player->class.life)
                player->life = player->class.life;
            printf("%.2f of life recovered.\n", dungeonFloorPerk);

            clearScreen(1);
        }
        else if(player->life <= 0)
        {
            dungeon->active = false;
            return;
        }
    }

        if(dungeon->current_floor >= DG_FLOORS)
        {
            printf("You beated the dungeon!\n");
            printf("Life fully recovered\n+5 atk points\n");
            dungeon->active = false;
            player->life = player->class.life;
            player->attack += 5;
        }
}
