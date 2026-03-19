#ifndef ADMIN_COMMANDS_H
#define ADMIN_COMMANDS_H

#include "types.h"

void Admin_GiveMoney(int amount);
void Admin_FullHeal(void);
void Admin_FastGrow(void);
void Admin_SpawnItem(ItemType item, int qty);
void Admin_KillAllEnemies(void);

#endif
