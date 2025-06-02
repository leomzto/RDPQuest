#ifndef ITEMS_H
#define ITEMS_H

typedef struct Player Player;

#define QT_ITEMS 34

typedef struct
{
    char itemName[50];
    float lifeBuff, attackBuff, defenseBuff;
    int xpGiven;
    float dropRate;
} Item;

extern const Item ITEMS[QT_ITEMS];

Item dropItem(void);
void addItemToInventory(Player *player, Item item);
void showInventory(Player *player);

#endif
