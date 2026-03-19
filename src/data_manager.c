#include "data_manager.h"
#include "quest_system.h"
#include "achievement_system.h"

#define SAVE_MAGIC   0x53574C44U  /* "SWLD" = SunnyWorld */
#define SAVE_VERSION 7  /* v7: +achievement unlocked/progress per account */

static const char *ITEM_NAMES[ITEM_COUNT] = {
    "Cà Rốt","Củ Cải","Bắp Cải","Súp Lơ",
    "Cải xoăn","Canh cải","Khoai","Bí Ngô",
    "Đỗ","Hướng dương","Lúa mì",
    "Ca-rot","Cu-cai","Bap-cai","Sup-lo",
    "Cai-xoan","Canh-cai","Khoai","Bi-ngo",
    "Cu-do","Huong-duong","Lua-mi",
    "Trứng","Sữa","Len",
    "Gỗ","Đá","Thức ăn",
    "Thuc-an",
    "Ngọc"
};

static const int ITEM_PRICES[ITEM_COUNT] = {
    12,14,12,18, 12,14,16,22, 10,20,10,
    28,35,25,45, 22,32,35,65, 20,50,18,
    22,45,38,
    15,6,28,   /* Go=15, Da=6, Ca=28 */
    20,
    500   /* Ngoc: gia tri cao */
};

const char *GetItemName(ItemType item)
{
    if (item < 0 || item >= ITEM_COUNT) return "???";
    return ITEM_NAMES[item];
}
int GetItemPrice(ItemType item)
{
    if (item < 0 || item >= ITEM_COUNT) return 0;
    return ITEM_PRICES[item];
}

/* ── Inventory ── */
int Inv_Find(ItemType item)
{
    for (int i = 0; i < INV_SLOTS; i++)
        if (G.player.inv[i].type == item && G.player.inv[i].quantity > 0)
            return i;
    return -1;
}
int Inv_Count(ItemType item)
{
    int tot = 0;
    for (int i = 0; i < INV_SLOTS; i++)
        if (G.player.inv[i].type == item) tot += G.player.inv[i].quantity;
    return tot;
}
bool Inv_Add(ItemType item, int qty)
{
    if (item == ITEM_NONE || qty <= 0) return false;
    for (int i = 0; i < INV_SLOTS; i++)
        if (G.player.inv[i].type == item) { G.player.inv[i].quantity += qty; return true; }
    for (int i = 0; i < INV_SLOTS; i++)
        if (G.player.inv[i].type == ITEM_NONE) {
            G.player.inv[i].type = item; G.player.inv[i].quantity = qty; return true;
        }
    strncpy(G.message, "Túi đồ đầy!", sizeof(G.message)); G.msgTimer = 2.0f;
    return false;
}
bool Inv_Remove(ItemType item, int qty)
{
    int s = Inv_Find(item);
    if (s < 0 || G.player.inv[s].quantity < qty) return false;
    G.player.inv[s].quantity -= qty;
    if (G.player.inv[s].quantity == 0) G.player.inv[s].type = ITEM_NONE;
    return true;
}

/* Dồn các slot có item về đầu, đẩy slot rỗng xuống cuối */
void Inv_Compact(void)
{
    int write = 0;
    for (int read = 0; read < INV_SLOTS; read++) {
        if (G.player.inv[read].type != ITEM_NONE && G.player.inv[read].quantity > 0) {
            if (write != read)
                G.player.inv[write] = G.player.inv[read];
            write++;
        }
    }
    /* Xóa các slot còn lại */
    for (int i = write; i < INV_SLOTS; i++) {
        G.player.inv[i].type     = ITEM_NONE;
        G.player.inv[i].quantity = 0;
    }
}

/* ── Economy ── */
bool Economy_BuyItem(ItemType item, int qty)
{
    int cost = GetItemPrice(item) * qty;
    if (G.player.money < cost) {
        strncpy(G.message,"Không đủ tiền!",sizeof(G.message)); G.msgTimer=2.0f; return false;
    }
    if (!Inv_Add(item, qty)) return false;
    G.player.money -= cost;
    snprintf(G.message,sizeof(G.message),"Mua %s x%d (-$%d)",GetItemName(item),qty,cost);
    G.msgTimer=2.0f; return true;
}
bool Economy_SellSlot(int slot)
{
    if (slot<0||slot>=INV_SLOTS) return false;
    InvSlot *s = &G.player.inv[slot];
    if (s->type==ITEM_NONE||s->quantity==0) return false;
    int earned = GetItemPrice(s->type)*s->quantity;
    G.player.money += earned;
    extern int achTotalEarned; achTotalEarned += earned; /* BUG FIX #8 */
    snprintf(G.message,sizeof(G.message),"Bán %s x%d (+$%d)",GetItemName(s->type),s->quantity,earned);
    G.msgTimer=2.0f;
    Quest_Progress(2, earned);
    s->type=ITEM_NONE; s->quantity=0;
    Inv_Compact();
    return true;
}
/* Bán một phần số lượng từ slot */
bool Economy_SellPartial(int slot, int qty)
{
    if (slot<0||slot>=INV_SLOTS||qty<=0) return false;
    InvSlot *s = &G.player.inv[slot];
    if (s->type==ITEM_NONE||s->quantity==0) return false;
    if (qty > s->quantity) qty = s->quantity;
    int earned = GetItemPrice(s->type)*qty;
    G.player.money += earned;
    snprintf(G.message,sizeof(G.message),"Bán %s x%d (+$%d)",GetItemName(s->type),qty,earned);
    G.msgTimer=2.0f;
    Quest_Progress(2, earned);
    s->quantity -= qty;
    if (s->quantity==0) s->type=ITEM_NONE;
    Inv_Compact();
    return true;
}

/* Bán toàn bộ item có giá trong túi đồ */
int Economy_SellAll(void)
{
    int totalEarned = 0;
    int totalQty    = 0;
    for (int i = 0; i < INV_SLOTS; i++) {
        InvSlot *s = &G.player.inv[i];
        if (s->type == ITEM_NONE || s->quantity == 0) continue;
        int price = GetItemPrice(s->type);
        if (price <= 0) continue;
        totalEarned += price * s->quantity;
        totalQty    += s->quantity;
        Quest_Progress(2, price * s->quantity);
        s->type     = ITEM_NONE;
        s->quantity = 0;
    }
    if (totalEarned > 0) {
        G.player.money += totalEarned;
        snprintf(G.message, sizeof(G.message),
                 "Bán tất cả: %d vật (+$%d)!", totalQty, totalEarned);
        G.msgTimer = 2.5f;
    } else {
        strncpy(G.message, "Không có hàng hóa để bán!", sizeof(G.message));
        G.msgTimer = 1.5f;
    }
    Inv_Compact();
    return totalEarned;
}
int Level_ExpNeeded(int level)
{
    /* EXP tăng dần theo cấp: level*level*50 + 100 */
    return EXP_BASE + level * level * 50;
}
void Level_AddExp(int amount)
{
    LevelData *lv = &G.player.lvl;
    if (lv->level >= MAX_LEVEL) return;
    lv->exp += amount;
    while (lv->exp >= lv->expToNext && lv->level < MAX_LEVEL) {
        lv->exp    -= lv->expToNext;
        lv->level++;
        lv->expToNext = Level_ExpNeeded(lv->level);
        G.levelUpAnim  = true;
        G.levelUpTimer = 3.0f;
        snprintf(G.message, sizeof(G.message), "LEVEL UP! Bạn đạt cấp %d!", lv->level);
        G.msgTimer = 3.5f;
        /* Phần thưởng lên cấp */
        G.player.money += lv->level * 50;
        G.player.maxHp  = PLAYER_MAX_HP + (lv->level - 1) * 5;
        G.player.hp     = G.player.maxHp;
    }
}

/* ── Save / Load per account ── */
void Game_SavePlayer(const char *path)
{
    MakeDirectory("saves");
    FILE *f = fopen(path,"wb");
    if (!f) return;
    /* ENHANCEMENT #4: Magic number + version de detect save file cu */
    unsigned int magic = SAVE_MAGIC;
    int version = SAVE_VERSION;
    fwrite(&magic,   sizeof(unsigned int),1,f);
    fwrite(&version, sizeof(int),         1,f);
    /* v5: lưu Unix timestamp để tính offline time khi load */
    time_t saveTime = time(NULL);
    fwrite(&saveTime, sizeof(time_t), 1, f);
    fwrite(&G.player,     sizeof(Player), 1, f);
    fwrite(&G.day,        sizeof(int),    1, f);
    fwrite(G.quests,      sizeof(Quest),  MAX_QUESTS, f);
    fwrite(&G.cropCount,  sizeof(int),    1, f);
    fwrite(G.crops,       sizeof(Crop),   MAX_CROPS, f);
    fwrite(&G.barnCount,  sizeof(int),    1, f);
    fwrite(G.barns,       sizeof(Barn),   MAX_BARNS, f);
    fwrite(&G.animalCount,sizeof(int),    1, f);
    fwrite(G.animals,     sizeof(Animal), MAX_ANIMALS, f);
    for (int r=0;r<MAP_ROWS;r++)
    for (int c=0;c<MAP_COLS;c++) {
        fwrite(&G.map[r][c].type,      sizeof(TileType),1,f);
        fwrite(&G.map[r][c].owned,     sizeof(bool),    1,f);
        fwrite(&G.map[r][c].chopCount, sizeof(int),     1,f); /* ENHANCEMENT #2: luu trang thai cay */
    }
    /* ENHANCEMENT #3: Luu achievement counters */
    extern int achTotalHarvested, achTotalKills, achTotalPlanted, achTotalCollected, achTotalEarned;
    fwrite(&achTotalHarvested, sizeof(int),1,f);
    fwrite(&achTotalKills,     sizeof(int),1,f);
    fwrite(&achTotalPlanted,   sizeof(int),1,f);
    fwrite(&achTotalCollected, sizeof(int),1,f);
    fwrite(&achTotalEarned,    sizeof(int),1,f);
    /* v7: Luu trang thai unlocked + progress tung thanh tuu per account */
    extern Achievement achievements[MAX_ACHIEVEMENTS];
    for (int _a=0; _a<MAX_ACHIEVEMENTS; _a++) {
        fwrite(&achievements[_a].unlocked, sizeof(bool),1,f);
        fwrite(&achievements[_a].progress, sizeof(int), 1,f);
    }
    /* Luu kho do (storage chest) */
    fwrite(G.storage, sizeof(InvSlot), STORAGE_SLOTS, f);
    /* Luu barn HP */
    fwrite(G.barnHp, sizeof(int), MAX_BARNS, f);
    
    fclose(f);
    Game_Log(TextFormat("Saved: %s", path));
}
void Game_LoadPlayer(const char *path)
{
    FILE *f = fopen(path,"rb");
    if (!f) {
        /* Lần đầu login – reset fresh */
        G.player.hp = G.player.maxHp = PLAYER_MAX_HP;
        G.player.money = STARTING_MONEY;
        G.player.pos   = (Vector2){ MAP_PX_W*0.5f, MAP_PX_H*0.5f };
        G.player.lvl.level = 1;
        G.player.lvl.exp   = 0;
        G.player.lvl.expToNext = Level_ExpNeeded(1);
        /* seed khởi đầu */
        Inv_Add(ITEM_SEED_CARROT,5);
        Inv_Add(ITEM_FEED,10);
        return;
    }
    /* Kiem tra magic + version */
    unsigned int magic_r = 0; int version_r = 0;
    fread(&magic_r,   sizeof(unsigned int),1,f);
    fread(&version_r, sizeof(int),         1,f);
    if (magic_r != SAVE_MAGIC || version_r != SAVE_VERSION) {
        fclose(f);
        /* Save cu hoac bi hong: reset ve fresh */
        G.player.hp = G.player.maxHp = PLAYER_MAX_HP;
        G.player.money = STARTING_MONEY;
        G.player.pos   = (Vector2){ MAP_PX_W*0.5f, MAP_PX_H*0.5f };
        G.player.lvl.level = 1;
        G.player.lvl.exp   = 0;
        G.player.lvl.expToNext = Level_ExpNeeded(1);
        Inv_Add(ITEM_SEED_CARROT,5);
        Inv_Add(ITEM_FEED,10);
        snprintf(G.message,sizeof(G.message),"bắt đầu lại từ đầu!");
        G.msgTimer = 4.0f;
        return;
    }
    /* v5: đọc timestamp để tính offline seconds */
    time_t saveTime = 0;
    fread(&saveTime, sizeof(time_t), 1, f);
    float offlineSecs = (saveTime > 0) ? (float)(time(NULL) - saveTime) : 0.0f;
    /* Giới hạn 12 giờ offline để tránh giá trị quá lớn */
    if (offlineSecs > 43200.0f) offlineSecs = 43200.0f;
    if (offlineSecs < 0.0f)     offlineSecs = 0.0f;

    /* giu username va role da login */
    char savedUser[MAX_NAME_LEN]; PlayerRole savedRole;
    strncpy(savedUser, G.player.username, MAX_NAME_LEN-1);
    savedRole = G.player.role;

    fread(&G.player,      sizeof(Player), 1, f);
    fread(&G.day,         sizeof(int),    1, f);
    fread(G.quests,       sizeof(Quest),  MAX_QUESTS, f);
    fread(&G.cropCount,   sizeof(int),    1, f);
    fread(G.crops,        sizeof(Crop),   MAX_CROPS, f);
    fread(&G.barnCount,   sizeof(int),    1, f);
    fread(G.barns,        sizeof(Barn),   MAX_BARNS, f);
    fread(&G.animalCount, sizeof(int),    1, f);
    fread(G.animals,      sizeof(Animal), MAX_ANIMALS, f);
    for (int r=0;r<MAP_ROWS;r++)
    for (int c=0;c<MAP_COLS;c++) {
        G.map[r][c].cropIdx   = -1;
        G.map[r][c].barnIdx   = -1;
        G.map[r][c].chopCount = 0;   /* rừng mọc lại đầy mỗi lần đăng nhập */
        G.map[r][c].chopTimer = 0.0f;
        fread(&G.map[r][c].type,      sizeof(TileType),1,f);
        fread(&G.map[r][c].owned,     sizeof(bool),    1,f);
        int savedChop = 0;
        fread(&savedChop, sizeof(int), 1, f); /* đọc nhưng bỏ qua — không restore chopCount */
    }
    /* ENHANCEMENT #3: Load achievement counters */
    extern int achTotalHarvested, achTotalKills, achTotalPlanted, achTotalCollected, achTotalEarned;
    achTotalHarvested = 0; achTotalKills = 0; achTotalPlanted = 0;
    achTotalCollected = 0; achTotalEarned = 0;
    fread(&achTotalHarvested, sizeof(int),1,f);
    fread(&achTotalKills,     sizeof(int),1,f);
    fread(&achTotalPlanted,   sizeof(int),1,f);
    fread(&achTotalCollected, sizeof(int),1,f);
    fread(&achTotalEarned,    sizeof(int),1,f);
    /* v7: Load trang thai unlocked + progress tung thanh tuu per account */
    extern Achievement achievements[MAX_ACHIEVEMENTS];
    for (int _a=0; _a<MAX_ACHIEVEMENTS; _a++) {
        fread(&achievements[_a].unlocked, sizeof(bool),1,f);
        fread(&achievements[_a].progress, sizeof(int), 1,f);
    }
    /* Load kho do */
    fread(G.storage, sizeof(InvSlot), STORAGE_SLOTS, f);
    /* Load barn HP */
    fread(G.barnHp, sizeof(int), MAX_BARNS, f);
  
    fclose(f);  /* Đóng file — mọi fread đã xong */

    /* Re-link crops */
    for (int i=0;i<MAX_CROPS;i++)
        if (G.crops[i].active)
            G.map[G.crops[i].tileY][G.crops[i].tileX].cropIdx = i;
    /* Re-link barns – phải đánh dấu toàn bộ vùng 5x5, không chỉ ô góc */
    for (int i=0;i<MAX_BARNS;i++)
        if (G.barns[i].active)
            for (int dr=0;dr<BARN_H;dr++)
            for (int dc=0;dc<BARN_W;dc++) {
                int tr=G.barns[i].tileY+dr, tc=G.barns[i].tileX+dc;
                if (tr>=0&&tr<MAP_ROWS&&tc>=0&&tc<MAP_COLS)
                    G.map[tr][tc].barnIdx = i;
            }

    /* ── OFFLINE GROWTH: cộng thời gian offline vào timers ── */
    if (offlineSecs > 0.0f) {
        /* Crops: tiến triển growTimer theo thời gian offline */
        for (int i = 0; i < MAX_CROPS; i++) {
            Crop *cr = &G.crops[i];
            if (!cr->active) continue;

            float remaining = offlineSecs;

            /* WATERED → GROWING sau 1 giây */
            if (cr->stage == CSTAGE_WATERED) {
                float need = 1.0f - cr->growTimer;
                if (remaining >= need) {
                    remaining     -= need;
                    cr->stage      = CSTAGE_GROWING;
                    cr->growTimer  = 0.0f;
                } else {
                    cr->growTimer += remaining;
                    remaining      = 0.0f;
                }
            }
            /* GROWING → READY sau GROW_SECS_STAGE giây */
            if (cr->stage == CSTAGE_GROWING && remaining > 0.0f) {
                cr->growTimer += remaining;
                if (cr->growTimer >= GROW_SECS_STAGE) {
                    cr->stage     = CSTAGE_READY;
                    cr->growTimer = 0.0f;
                    G.map[cr->tileY][cr->tileX].type = TILE_SOIL_PLANTED;
                }
            }
        }

        /* Animals: tiến triển feedTimer và produceTimer */
        for (int i = 0; i < MAX_ANIMALS; i++) {
            Animal *a = &G.animals[i];
            if (!a->active) continue;

            /* feedTimer đếm ngược đến khi đói */
            if (!a->hungry) {
                a->feedTimer -= offlineSecs;
                if (a->feedTimer <= 0.0f) {
                    a->hungry    = true;
                    a->feedTimer = FEED_SECS;
                }
            }

            /* produceTimer chỉ chạy khi no */
            if (!a->hungry && !a->hasProduct) {
                a->produceTimer -= offlineSecs;
                if (a->produceTimer <= 0.0f) {
                    a->hasProduct   = true;
                    a->produceTimer = PRODUCE_SECS;
                }
            }
        }

        /* Thông báo kết quả offline */
        int readyCrops = 0, readyAnimals = 0, hungryAnimals = 0;
        for (int i = 0; i < MAX_CROPS;   i++) if (G.crops[i].active   && G.crops[i].stage == CSTAGE_READY)   readyCrops++;
        for (int i = 0; i < MAX_ANIMALS; i++) if (G.animals[i].active && G.animals[i].hasProduct)             readyAnimals++;
        for (int i = 0; i < MAX_ANIMALS; i++) if (G.animals[i].active && G.animals[i].hungry)                 hungryAnimals++;

        int offlineMins = (int)(offlineSecs / 60);
        if (offlineMins > 0)
            snprintf(G.message, sizeof(G.message),
                     "Offline %d phút: %d cây chín, %d sản phẩm động vật%s",
                     offlineMins, readyCrops, readyAnimals,
                     hungryAnimals > 0 ? ", động vật đói!" : ".");
        else
            snprintf(G.message, sizeof(G.message),
                     "Offline %ds: %d cây chín, %d sản phẩm động vật.",
                     (int)offlineSecs, readyCrops, readyAnimals);
        G.msgTimer = 6.0f;
    }
}
void Game_Log(const char *event)
{
    MakeDirectory("logs");
    FILE *f = fopen(LOG_FILE,"a");
    if (!f) return;
    time_t t=time(NULL); struct tm *tm_=localtime(&t);
    fprintf(f,"[%02d:%02d:%02d] %s\n",tm_->tm_hour,tm_->tm_min,tm_->tm_sec,event);
    fclose(f);
}