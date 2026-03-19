#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H
#include "types.h"

const char *GetItemName(ItemType item);
int         GetItemPrice(ItemType item);

bool Inv_Add(ItemType item, int qty);
bool Inv_Remove(ItemType item, int qty);
int  Inv_Find(ItemType item);
int  Inv_Count(ItemType item);
void Inv_Compact(void);  /* Dồn slot rỗng xuống cuối */

bool Economy_BuyItem(ItemType item, int qty);
bool Economy_SellSlot(int invSlot);
bool Economy_SellPartial(int invSlot, int qty);
int  Economy_SellAll(void);   /* Bán toàn bộ nông sản + sản phẩm chăn nuôi */

/* Level / EXP */
void Level_AddExp(int amount);
int  Level_ExpNeeded(int level);

/* Save per account */
void Game_SavePlayer(const char *path);
void Game_LoadPlayer(const char *path);
void Game_Log(const char *event);

#endif