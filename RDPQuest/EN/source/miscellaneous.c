#include <stdio.h>
#include "miscellaneous.h"
#include "player.h"

#define BAR_LENGTH 20

void healthBar(char *string, float currentLife, float maxLife)
{
    int hp = (int)((currentLife / maxLife) * BAR_LENGTH);
    if (currentLife > 0 && hp == 0) hp = 1;

    printf("%s - [", string);
    for (int i = 0; i < hp; i++) printf("+");
    for (int i = hp; i < BAR_LENGTH; i++) printf("-");
    printf("] (%.2f/%.2f)\n", currentLife, maxLife);
}

void xpBar(char *string, int currentXP, int maxXP)
{
    int xp = (int)(((float)currentXP / maxXP) * BAR_LENGTH);
    if (currentXP > 0 && xp == 0) xp = 1;

    printf("%s - [", string);
    for (int i = 0; i < xp; i++) printf("#");
    for (int i = xp; i < BAR_LENGTH; i++) printf("-");
    printf("] (%d/%d)\n", currentXP, maxXP);
}
