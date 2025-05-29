#include "items.h"
#include <stdio.h>
#include <stdlib.h>
#include "player.h"

// itemName,            lifeBuff, atackBuff, defenseBuff, xpGiven, dropRate
const Item ITEMS[QT_ITEMS] = {
    // Potions
    {"Elixir of Life",            50, 0, 0, 0, 15.0f},
    {"Greater Elixir of Life",    120, 0, 0, 0, 10.0f},
    {"Shielding Draught",         0, 0, 5, 0, 12.0f},
    {"Berserker's Fury Potion",   0, 7, -2, 0, 8.0f},
    {"Experience Bottle",         0, 0, 0, 20, 15.0f},
    {"Greater Exp. Bottle",       0, 0, 0, 40, 9.8f},
    {"Legendary Exp. Bottle",     0, 0, 0, 100, 1.05f},

    // Weapons
    {"Bonecrusher Sword",         0, 6, 0, 0, 14.0f},
    {"Orcish War Axe",            0, 8, -1, 0, 10.0f},
    {"Shadowfang Dagger",         0, 5, 0, 0, 13.0f},
    {"Demon's Fang Blade",        0, 10, -3, 0, 6.0f},
    {"Dragon Talon Claw",         0, 9, 1, 0, 1.7f},
    {"Slimebound Staff",          10, 4, 2, 0, 11.0f},

    // Helmets
    {"Skullcap of the Fallen",   15, 0, 3, 0, 14.0f},
    {"Ironhide Helm",            20, 0, 5, 0, 12.0f},
    {"Warlord's Iron Helmet",    25, 2, 4, 0, 10.0f},
    {"Phantom Hood",             10, 3, 1, 0, 1.0f},
    {"Shadow Veil",               5, 1, 3, 0, 1.5f},
    {"Hellfire Helm",            30, 4, 5, 0, 1.5f},
    {"Demonic Crown",            35, 5, 6, 0, 1.4f},
    {"Dragon Scale Helm",        40, 3, 7, 0, 1.6f},
    {"Cursed Warlord's Helm",    45, 6, 8, 0, 1.3f},

    // Chestplates
    {"Boneplate Armor",          40, 0, 6, 0, 12.0f},
    {"Ironhide Chestplate",      50, 0, 8, 0, 10.0f},
    {"Rogue's Shadow Cape",      20, 4, 4, 0, 1.9f},
    {"Hellfire Chestplate",      60, 3, 9, 0, 1.7f},
    {"Demonic Chestguard",       70, 6, 10, 0, 1.5f},
    {"Dragon Scale Armor",       80, 5, 12, 0, 1.4f},

    // Amulets
    {"Amulet of Vitality",        50, 0, 0, 0, 2.1f},
    {"Amulet of the Berserker",   0, 8, -2, 0, 1.8f},
    {"Amulet of the Guardian",    30, 0, 6, 0, 1.9f},
    {"Amulet of Arcane Power",    0, 7, 0, 0, 1.7f},
    {"Amulet of Shadows",         10, 3, 3, 0, 1.6f},
    {"Amulet of the Dragon",      40, 5, 5, 0, 1.5f}
};

Item dropItem(void)
{
    float drop_chance = 0.0f;

    for(int i = 0; i < QT_ITEMS; i++)
        drop_chance += ITEMS[i].dropRate;

    float draftItems = ((float)rand() / RAND_MAX) * drop_chance;

    float general_chance = 0.0f;
    for(int i = 0; i < QT_ITEMS; i++)
    {
        general_chance += ITEMS[i].dropRate;
        if(draftItems <= general_chance)
            return ITEMS[i];
    }

    return ITEMS[4]; // Exp. Bottle
}
