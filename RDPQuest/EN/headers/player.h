#ifndef PLAYER_H
#define PLAYER_H

#define QT_CLASSES 7

typedef struct
{
    char name[20];
    float life, attack, deffense;
} Class;

typedef struct
{
    char name[50];
    Class class;
    float life, attack, deffense;
    float life_max, attack_max, deffense_max;
    int level, xp, maxXP;
} Player;

extern const Class CLASSES[QT_CLASSES];

Player generatePlayer(void);
void showStats(Player *player);

#endif
