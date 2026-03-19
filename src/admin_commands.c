#include "admin_commands.h"
#include "data_manager.h"

void Admin_GiveMoney(int amount)
{
    G.player.money += amount;
    snprintf(G.message, sizeof(G.message), "+$%d", amount);
    G.msgTimer = 2.5f;
}

void Admin_FullHeal(void)
{
    G.player.hp = G.player.maxHp;
    strncpy(G.message, "HP đầy đủ!", sizeof(G.message));
    G.msgTimer = 2.5f;
}

void Admin_FastGrow(void)
{
    for (int i = 0; i < MAX_CROPS; i++)
        if (G.crops[i].active)
            G.crops[i].stage = CSTAGE_READY;
    strncpy(G.message, "Tất cả cây đã trưởng thành!", sizeof(G.message));
    G.msgTimer = 2.5f;
}

void Admin_SpawnItem(ItemType item, int qty)
{
    Inv_Add(item, qty);
    snprintf(G.message, sizeof(G.message),
             "Thêm %s x%d", GetItemName(item), qty);
    G.msgTimer = 2.5f;
}

void Admin_KillAllEnemies(void)
{
    int count = 0;
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (G.enemies[i].active && G.enemies[i].state != ESTATE_DEAD) {
            G.enemies[i].state = ESTATE_DEAD;
            G.enemies[i].hp    = 0;
            G.enemyCount--;
            count++;
        }
    }
    snprintf(G.message, sizeof(G.message), "Tiêu diệt %d quái vật!", count);
    G.msgTimer = 2.5f;
}
