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
<<<<<<< HEAD
<<<<<<< HEAD
    strncpy(G.message, "HP day du!", sizeof(G.message));
=======
    strncpy(G.message, "HP đầy đủ!", sizeof(G.message));
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
    strncpy(G.message, "HP đầy đủ!", sizeof(G.message));
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    G.msgTimer = 2.5f;
}

void Admin_FastGrow(void)
{
    for (int i = 0; i < MAX_CROPS; i++)
        if (G.crops[i].active)
            G.crops[i].stage = CSTAGE_READY;
<<<<<<< HEAD
<<<<<<< HEAD
    strncpy(G.message, "Tat ca cay da truong thanh!", sizeof(G.message));
=======
    strncpy(G.message, "Tất cả cây đã trưởng thành!", sizeof(G.message));
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
    strncpy(G.message, "Tất cả cây đã trưởng thành!", sizeof(G.message));
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    G.msgTimer = 2.5f;
}

void Admin_SpawnItem(ItemType item, int qty)
{
    Inv_Add(item, qty);
    snprintf(G.message, sizeof(G.message),
<<<<<<< HEAD
<<<<<<< HEAD
             "Them %s x%d", GetItemName(item), qty);
=======
             "Thêm %s x%d", GetItemName(item), qty);
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
             "Thêm %s x%d", GetItemName(item), qty);
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
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
<<<<<<< HEAD
<<<<<<< HEAD
    snprintf(G.message, sizeof(G.message), "Tieu diet %d quai!", count);
=======
    snprintf(G.message, sizeof(G.message), "Tiêu diệt %d quái vật!", count);
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
    snprintf(G.message, sizeof(G.message), "Tiêu diệt %d quái vật!", count);
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    G.msgTimer = 2.5f;
}
