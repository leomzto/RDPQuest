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

        printf("Entrando na masmorra\n");
        loadingScreen(10, '.', 0);
        clearScreen(1);
        printf("Tenha cuidado...\n");
    }

    while(dungeon->current_floor < DG_FLOORS && dungeon->active)
    {
        printf("Explorando o %d andar\n", dungeon->current_floor + 1);
        loadingScreen(10, '.', 0);
        printf("Inimigo a frente!\n");

        Enemy *current_enemy = &dungeon->dungeon_enemies[dungeon->current_floor];
        startBattle(player, current_enemy);

        if(player->life > 0 && current_enemy->life <= 0)
        {
            printf("%s derrotou o inimigo do %d andar!\n", player->name, dungeon->current_floor + 1);
            dungeon->current_floor++;

            float dungeonFloorPerk = player->class.life * 0.3;
            player->life += dungeonFloorPerk;
            if(player->life > player->class.life)
                player->life = player->class.life;
            printf("%.2f de vida recuperada.\n", dungeonFloorPerk);

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
            printf("Voce completou a masmorra!\n");
            printf("Vida restaurada\n+5 pontos de ataque\n");
            dungeon->active = false;
            player->life = player->class.life;
            player->attack += 5;
        }
}
