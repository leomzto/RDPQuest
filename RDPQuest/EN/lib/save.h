#ifndef SAVE_H
#define SAVE_H

#include "player.h"
#include <stddef.h>

#define BAR_LENGHT 20

void getSaveFolderPath(char *buffer, size_t size);
void mkdirSaves(void);
void savesList(void);
void saveGame(Player *player, int saveSlot);
Player loadSave(int slot);

#endif
