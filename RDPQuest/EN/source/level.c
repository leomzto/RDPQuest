#include "level.h"
#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #define Sleep(ms) usleep(ms * 1000)
#endif

void giveXP(Player *player, int amount)
{
    player->xp += amount;
    while(player->xp >= player->maxXP)
    {
        player->xp -= player->maxXP;
        player->level++;
        player->maxXP += 100;

        player->deffense += 2;
        player->attack += 3;
        player->life_max += 5;
        player->life = player->life_max;

        printf("LEVEL UP! >> %s is now on level %d.\n", player->name, player->level);
        Sleep(3000);
    }
}



