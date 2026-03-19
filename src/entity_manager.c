#include "entity_manager.h"
#include "data_manager.h"
#include "quest_system.h"
<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
/* ── Map init: toàn bộ là cỏ xanh ── */
void EntityManager_InitMap(void)
{
    for (int r = 0; r < MAP_ROWS; r++)
        for (int c = 0; c < MAP_COLS; c++)
        {
<<<<<<< HEAD
<<<<<<< HEAD
            G.map[r][c].type = TILE_GRASS;
            G.map[r][c].cropIdx = -1;
            G.map[r][c].barnIdx = -1;
            G.map[r][c].owned = false;
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            G.map[r][c].type      = TILE_GRASS;
            G.map[r][c].cropIdx   = -1;
            G.map[r][c].barnIdx   = -1;
            G.map[r][c].owned     = false;
            G.map[r][c].chopCount = 0;    /* cây mọc đầy sau mỗi lần login */
            G.map[r][c].chopTimer = 0.0f;
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        }
    /* Suối trái */
    for (int r = 0; r < MAP_ROWS; r++)
    {
        G.map[r][0].type = TILE_WATER_TILE;
        G.map[r][1].type = TILE_WATER_TILE;
    }
    /* Đường đi ngang */
    for (int c = 2; c < MAP_COLS; c++)
        G.map[MAP_ROWS - 3][c].type = TILE_PATH;
    /* Viền đá */
    for (int c = 0; c < MAP_COLS; c++)
    {
        G.map[0][c].type = TILE_STONE;
        G.map[MAP_ROWS - 1][c].type = TILE_STONE;
    }
    for (int r = 0; r < MAP_ROWS; r++)
        G.map[r][MAP_COLS - 1].type = TILE_STONE;
}

/* ── Animals init (không tạo sẵn, phải mua chuồng trước) ── */
void EntityManager_InitAnimals(void) { /* trống – spawn khi mua */ }

/* ── Land purchase ── */
bool Land_BuyPlot(int tileX, int tileY)
{
    /* Mua 5×5 tile tính từ (tileX, tileY) */
<<<<<<< HEAD
<<<<<<< HEAD
    int price = LAND_PRICE_BASE + G.barnCount * 50;
    if (G.player.money < price)
    {
        snprintf(G.message, sizeof(G.message), "Can $%d de mua dat!", price);
        G.msgTimer = 2.5f;
        return false;
    }
    /* Kiểm tra toàn bộ 5×5 đều là grass và không có cây */
    for (int dr = 0; dr < LAND_PLOT_H; dr++)
        for (int dc = 0; dc < LAND_PLOT_W; dc++)
        {
            int r = tileY + dr, c = tileX + dc;
            if (r < 1 || r >= MAP_ROWS - 1 || c < 2 || c >= MAP_COLS - 1)
            {
                strncpy(G.message, "Vi tri khong hop le!", sizeof(G.message));
                G.msgTimer = 2.0f;
                return false;
            }
            if (G.map[r][c].type != TILE_GRASS || G.map[r][c].owned)
            {
                strncpy(G.message, "O dat nay da duoc su dung!", sizeof(G.message));
                G.msgTimer = 2.0f;
                return false;
            }
            if (Tile_IsTree(c, r))
            {
                strncpy(G.message, "Phai don cay truoc moi dat dat duoc!", sizeof(G.message));
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    /* BUG FIX #10: Gia dat tang theo so o dat da mua, khong phai so chuong */
    int plotTiles = 0;
    for (int _r=0;_r<MAP_ROWS;_r++) for (int _c=0;_c<MAP_COLS;_c++)
        if (G.map[_r][_c].owned) plotTiles++;
    int ownedPlots = plotTiles / (LAND_PLOT_W * LAND_PLOT_H);
    int price = LAND_PRICE_BASE + ownedPlots * 50;
    if (G.player.money < price)
    {
        snprintf(G.message, sizeof(G.message), "Cần $%d để mua đất!", price);
        G.msgTimer = 2.5f;
        return false;
    }
    /* Kiểm tra toàn bộ 5×5: grass, chưa owned, không cây, không đè building/home */
    for (int dr = 0; dr < LAND_PLOT_H; dr++)
        for (int dc = 0; dc < LAND_PLOT_W; dc++)
        {
            int r = tileY + dr, c2 = tileX + dc;
            if (r < 1 || r >= MAP_ROWS - 1 || c2 < 2 || c2 >= MAP_COLS - 1)
            {
                strncpy(G.message, "Vị trí không hợp lệ!", sizeof(G.message));
                G.msgTimer = 2.0f;
                return false;
            }
            /* Không được đặt đè lên đất/chuồng đã có */
            if (G.map[r][c2].owned)
            {
                strncpy(G.message, "Ô đất này đã được sử dụng!", sizeof(G.message));
                G.msgTimer = 2.0f;
                return false;
            }
            /* Không đặt đè lên buildings (tọa độ chính xác + 1 tile padding)
               HOME: col 30-32, row 10-11
               Row buildings: col 18-44, row 15-16 */
            bool onHome      = (c2>=29 && c2<=33 && r>=9  && r<=12);
            bool onRowBldg   = (c2>=17 && c2<=45 && r>=14 && r<=17);
            if (onHome || onRowBldg)
            {
                strncpy(G.message, "Không thể đặt đè lên công trình!", sizeof(G.message));
                G.msgTimer = 2.5f;
                return false;
            }
            /* Không cần check TILE_GRASS — cho phép đặt mọi địa hình trên farm */
            if (Tile_IsTree(c2, r))
            {
                strncpy(G.message, "Phải dọn cây trước khi đặt đất được!", sizeof(G.message));
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
                G.msgTimer = 2.5f;
                return false;
            }
        }
    G.player.money -= price;
    for (int dr = 0; dr < LAND_PLOT_H; dr++)
        for (int dc = 0; dc < LAND_PLOT_W; dc++)
        {
            G.map[tileY + dr][tileX + dc].type = TILE_SOIL_BOUGHT;
            G.map[tileY + dr][tileX + dc].owned = true;
            G.map[tileY + dr][tileX + dc].cropIdx = -1;
            G.map[tileY + dr][tileX + dc].barnIdx = -1;
        }
<<<<<<< HEAD
<<<<<<< HEAD
    snprintf(G.message, sizeof(G.message), "Da mua dat 5x5! (-$%d)", price);
=======
    snprintf(G.message, sizeof(G.message), "Đã mua đất 5x5! (-$%d)", price);
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
    snprintf(G.message, sizeof(G.message), "Đã mua đất 5x5! (-$%d)", price);
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    G.msgTimer = 2.5f;
    return true;
}

<<<<<<< HEAD
<<<<<<< HEAD
/* ── Barn build ── */
bool Barn_Build(AnimalType type, int tileX, int tileY)
{
    if (G.barnCount >= MAX_BARNS)
    {
        strncpy(G.message, "Da dat gioi han chuong!", sizeof(G.message));
        G.msgTimer = 2.0f;
        return false;
    }
    if (G.player.money < BARN_PRICE)
    {
        snprintf(G.message, sizeof(G.message), "Can $%d de xay chuong!", BARN_PRICE);
        G.msgTimer = 2.0f;
        return false;
    }
    /* Cần 3×3 tile đã mua */
    for (int dr = 0; dr < BARN_H; dr++)
        for (int dc = 0; dc < BARN_W; dc++)
        {
            int r = tileY + dr, c = tileX + dc;
            if (r < 0 || r >= MAP_ROWS || c < 0 || c >= MAP_COLS ||
                !G.map[r][c].owned || G.map[r][c].barnIdx >= 0)
            {
                strncpy(G.message, "Can 5x5 dat (5x3 dat da mua de xay chuong!", sizeof(G.message));
                G.msgTimer = 2.5f;
                return false;
            }
        }
    G.player.money -= BARN_PRICE;
    int bi = G.barnCount++;
    Barn *b = &G.barns[bi];
    b->type = type;
    b->tileX = tileX;
    b->tileY = tileY;
    b->animalCount = 0;
    b->active = true;
    for (int dr = 0; dr < BARN_H; dr++)
        for (int dc = 0; dc < BARN_W; dc++)
            G.map[tileY + dr][tileX + dc].barnIdx = bi;
    snprintf(G.message, sizeof(G.message), "Da xay chuong! (-$%d)", BARN_PRICE);
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
/* ── Barn_Build: đặt chuồng 5x5 tại (tileX,tileY)
   - Cho phép đặt trên đất chưa mua HOẶC đã mua (không có chuồng)
   - Tốn BARN_PRICE; nếu đất chưa mua thì tốn thêm giá đất
*/
bool Barn_Build(AnimalType type, int tileX, int tileY)
{
    if (G.barnCount >= MAX_BARNS) {
        strncpy(G.message, "Đã đạt giới hạn chuồng!", sizeof(G.message));
        G.msgTimer = 2.0f; return false;
    }

    /* Kiểm tra từng tile 5x5 */
    int tilesToBuy = 0;
    for (int dr = 0; dr < BARN_H; dr++)
    for (int dc = 0; dc < BARN_W; dc++) {
        int r = tileY + dr, cc = tileX + dc;
        /* Biên map */
        if (r < 1 || r >= MAP_ROWS-1 || cc < 1 || cc >= MAP_COLS-1) {
            strncpy(G.message, "Vị trí chuồng ra ngoài bản đồ!", sizeof(G.message));
            G.msgTimer = 2.0f; return false;
        }
        /* Đã có chuồng khác */
        if (G.map[r][cc].barnIdx >= 0) {
            strncpy(G.message, "Vị trí này đã có chuồng!", sizeof(G.message));
            G.msgTimer = 2.0f; return false;
        }
        /* Đá hoặc nước */
        if (G.map[r][cc].type == TILE_STONE || G.map[r][cc].type == TILE_WATER_TILE) {
            strncpy(G.message, "Không thể đặt chuồng lên đá/nước!", sizeof(G.message));
            G.msgTimer = 2.0f; return false;
        }
        /* Building zone (HOME + hàng dưới) */
        bool onHome  = (cc>=29&&cc<=33 && r>=9 &&r<=12);
        bool onBldg  = (cc>=17&&cc<=45 && r>=14&&r<=17);
        if (onHome || onBldg) {
            strncpy(G.message, "Không thể đặt chuồng lên công trình!", sizeof(G.message));
            G.msgTimer = 2.0f; return false;
        }
        if (!G.map[r][cc].owned) tilesToBuy++;
    }

    /* Tính giá */
    int extraCost = 0;
    if (tilesToBuy > 0) {
        int ownedTiles = 0;
        for (int _r=0;_r<MAP_ROWS;_r++) for (int _c=0;_c<MAP_COLS;_c++)
            if (G.map[_r][_c].owned) ownedTiles++;
        int ownedPlots = ownedTiles / (LAND_PLOT_W * LAND_PLOT_H);
        extraCost = LAND_PRICE_BASE + ownedPlots * 50;
    }
    int totalCost = BARN_PRICE + extraCost;

    if (G.player.money < totalCost) {
        if (extraCost > 0)
            snprintf(G.message, sizeof(G.message),
                "Cần $%d (chuồng $%d + đất $%d)!", totalCost, BARN_PRICE, extraCost);
        else
            snprintf(G.message, sizeof(G.message), "Cần $%d để xây chuồng!", BARN_PRICE);
        G.msgTimer = 2.5f; return false;
    }

    /* Trừ tiền, đặt chuồng */
    G.player.money -= totalCost;
    int bi = G.barnCount++;
    Barn *b = &G.barns[bi];
    b->type = type; b->tileX = tileX; b->tileY = tileY;
    b->animalCount = 0; b->active = true;

    for (int dr = 0; dr < BARN_H; dr++)
    for (int dc = 0; dc < BARN_W; dc++) {
        int r = tileY + dr, cc = tileX + dc;
        if (!G.map[r][cc].owned) {
            G.map[r][cc].owned   = true;
            G.map[r][cc].cropIdx = -1;
        }
        /* Đổi tile về cỏ để không hiện đất nâu dưới chuồng */
        if (G.map[r][cc].type == TILE_SOIL_BOUGHT ||
            G.map[r][cc].type == TILE_SOIL_DUG    ||
            G.map[r][cc].type == TILE_SOIL_WET)
            G.map[r][cc].type = TILE_GRASS;
        G.map[r][cc].barnIdx = bi;
    }

    /* Khởi tạo HP chuồng */
    G.barnHp[bi]       = BARN_MAX_HP;
    G.barnDmgTimer[bi] = 0.0f;

    static const char *typeNames[] = {"Gà", "Lợn", "Cừu"};
    snprintf(G.message, sizeof(G.message),
             "Đã xây Chuồng %s! (-$%d)", typeNames[type], totalCost);
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    G.msgTimer = 2.5f;
    return true;
}

<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======

>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
/* ── Buy animal into barn ── */
bool Barn_BuyAnimal(int barnIdx)
{
    
    if (barnIdx < 0 || barnIdx >= G.barnCount)
        return false;
    Barn *b = &G.barns[barnIdx];
    if (!b->active)
        return false;
    if (b->animalCount >= MAX_ANIMALS_PER_BARN)
    {
<<<<<<< HEAD
<<<<<<< HEAD
        strncpy(G.message, "Chuong da day (toi da 5 con)!", sizeof(G.message));
=======
        strncpy(G.message, "Chuồng đã đầy (tối đa 5 con)!", sizeof(G.message));
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
        strncpy(G.message, "Chuồng đã đầy (tối đa 5 con)!", sizeof(G.message));
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        G.msgTimer = 2.0f;
        return false;
    }
    if (G.player.money < ANIMAL_PRICE)
    {
<<<<<<< HEAD
<<<<<<< HEAD
        snprintf(G.message, sizeof(G.message), "Can $%d de mua dong vat!", ANIMAL_PRICE);
=======
        snprintf(G.message, sizeof(G.message), "Cần $%d để mua động vật!", ANIMAL_PRICE);
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
        snprintf(G.message, sizeof(G.message), "Cần $%d để mua động vật!", ANIMAL_PRICE);
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        G.msgTimer = 2.0f;
        return false;
    }
    /* Tìm slot animal trống */
    int ai = -1;
    for (int i = 0; i < MAX_ANIMALS; i++)
        if (!G.animals[i].active)
        {
            ai = i;
            break;
        }
    if (ai < 0)
        return false;

    G.player.money -= ANIMAL_PRICE;
    Animal *a = &G.animals[ai];
    memset(a, 0, sizeof(Animal));
    a->type = b->type;
    a->barnIdx = barnIdx;
    a->active = true;
<<<<<<< HEAD
<<<<<<< HEAD
    a->feedTimer = FEED_SECS;
    a->hungry = false;
    a->produceTimer = PRODUCE_SECS;
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    /* Khởi tạo timer theo loại động vật */
    static const float _INIT_FEED[ANIMAL_COUNT]    = { 60.0f,  90.0f, 120.0f };
    static const float _INIT_PRODUCE[ANIMAL_COUNT] = { 80.0f, 120.0f, 160.0f };
    a->feedTimer    = (a->type >= 0 && a->type < ANIMAL_COUNT) ? _INIT_FEED[a->type]    : FEED_SECS;
    a->produceTimer = (a->type >= 0 && a->type < ANIMAL_COUNT) ? _INIT_PRODUCE[a->type] : PRODUCE_SECS;
    a->hungry = false;
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    a->hasProduct = false;
    /* Vị trí ngẫu nhiên trong chuồng */
    /* Spawn ngẫu nhiên trong vùng nội thất chuồng 5x5 (tiles 1..3) */
    /* Spawn ngẫu nhiên trong toàn bộ chuồng 5x5 (chừa viền 0.5 tile) */
    a->pos.x = (b->tileX + 1 + GetRandomValue(0,2)) * TILE_SIZE + TILE_SIZE/2;
a->pos.y = (b->tileY + 1 + GetRandomValue(0,2)) * TILE_SIZE + TILE_SIZE/2;
 b->animalCount++;
    if (G.animalCount <= ai)
        G.animalCount = ai + 1;

<<<<<<< HEAD
<<<<<<< HEAD
    snprintf(G.message, sizeof(G.message), "Da mua %s! (-$%d)",
             b->type == ANIMAL_CHICKEN ? "Ga" : b->type == ANIMAL_PIG ? "Lon"
                                                                      : "Cuu",
=======
    snprintf(G.message, sizeof(G.message), "Đã mua %s! (-$%d)",
             b->type == ANIMAL_CHICKEN ? "Gà" : b->type == ANIMAL_PIG ? "Lợn"
                                                                      : "Cừu",
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
    snprintf(G.message, sizeof(G.message), "Đã mua %s! (-$%d)",
             b->type == ANIMAL_CHICKEN ? "Gà" : b->type == ANIMAL_PIG ? "Lợn"
                                                                      : "Cừu",
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
             ANIMAL_PRICE);
    G.msgTimer = 2.5f;
    return true;
}

/* ── Update crops ── */
/* ── Xóa chuồng (hoàn tiền 50%) ── */
bool Barn_Delete(int tileX, int tileY)
{
    int r = tileY, c = tileX;
    if (r < 0 || r >= MAP_ROWS || c < 0 || c >= MAP_COLS) return false;
    int bi = G.map[r][c].barnIdx;
    if (bi < 0 || bi >= G.barnCount) return false;
    Barn *b = &G.barns[bi];
    if (!b->active) return false;

    /* Xóa toàn bộ động vật trong chuồng */
    for (int i = 0; i < MAX_ANIMALS; i++) {
        if (G.animals[i].active && G.animals[i].barnIdx == bi) {
            G.animals[i].active = false;
        }
    }
    /* Hoàn 50% tiền chuồng */
    int refund = BARN_PRICE / 2;
    G.player.money += refund;
    /* Xóa đánh dấu barnIdx trên tiles 5x5 */
    for (int dr = 0; dr < BARN_H; dr++)
    for (int dc = 0; dc < BARN_W; dc++) {
        int tr = b->tileY + dr, tc = b->tileX + dc;
        if (tr >= 0 && tr < MAP_ROWS && tc >= 0 && tc < MAP_COLS) {
            G.map[tr][tc].barnIdx = -1;
            /* Đất trở lại trạng thái đã mua nếu còn owned */
            if (G.map[tr][tc].owned)
                G.map[tr][tc].type = TILE_SOIL_BOUGHT;
        }
    }
    b->active = false;
    b->animalCount = 0;
<<<<<<< HEAD
<<<<<<< HEAD
    snprintf(G.message, sizeof(G.message), "Da xoa chuong! (+$%d)", refund);
=======
    snprintf(G.message, sizeof(G.message), "Đã xóa chuồng! (+$%d)", refund);
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
    snprintf(G.message, sizeof(G.message), "Đã xóa chuồng! (+$%d)", refund);
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    G.msgTimer = 2.5f;
    return true;
}

<<<<<<< HEAD
<<<<<<< HEAD
/* ── Xóa ô đất 5x5 (đất chưa trồng — hoàn tiền 30%) ── */
/* ── Xóa vùng đất 3x3 xung quanh tile được click (hoàn tiền 30%) ── */
=======
/* ── Plot_Delete: xóa đúng khối owned chứa tile được click ── */
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
/* ── Plot_Delete: xóa đúng khối owned chứa tile được click ── */
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
bool Plot_Delete(int tileX, int tileY)
{
    int r = tileY, c = tileX;
    if (r < 0 || r >= MAP_ROWS || c < 0 || c >= MAP_COLS) return false;
    if (!G.map[r][c].owned) return false;
    if (G.map[r][c].barnIdx >= 0) {
        strncpy(G.message, "Phai xoa chuong truoc!", sizeof(G.message));
<<<<<<< HEAD
<<<<<<< HEAD
        G.msgTimer = 2.0f;
        return false;
    }

    /* Vùng 3x3 căn giữa tại tile được click */
    int ox = c - 1, oy = r - 1;
    int deleted = 0;

    /* Xóa cây (crop) trong vùng 3x3 trước */
    for (int i = 0; i < MAX_CROPS; i++) {
        Crop *cp = &G.crops[i];
        if (!cp->active) continue;
        if (cp->tileX >= ox && cp->tileX < ox + 3 &&
            cp->tileY >= oy && cp->tileY < oy + 3) {
            G.map[cp->tileY][cp->tileX].cropIdx = -1;
            G.map[cp->tileY][cp->tileX].type    = TILE_SOIL_BOUGHT;
            cp->active = false;
            G.cropCount--;
        }
    }
    /* Xóa tiles 3x3 về cỏ (chỉ tile owned, không có chuồng) */
    for (int dr = 0; dr < 3; dr++)
    for (int dc = 0; dc < 3; dc++) {
        int tr = oy + dr, tc = ox + dc;
        if (tr < 0 || tr >= MAP_ROWS || tc < 0 || tc >= MAP_COLS) continue;
        if (!G.map[tr][tc].owned) continue;
        if (G.map[tr][tc].barnIdx >= 0) continue;
        G.map[tr][tc].type    = TILE_GRASS;
        G.map[tr][tc].owned   = false;
        G.map[tr][tc].cropIdx = -1;
        G.map[tr][tc].barnIdx = -1;
        deleted++;
    }
    if (deleted == 0) {
        strncpy(G.message, "Khong co dat de xoa!", sizeof(G.message));
        G.msgTimer = 1.5f;
        return false;
    }
    int refund = (LAND_PRICE_BASE * deleted * 30) / (100 * 9);
    G.player.money += refund;
    snprintf(G.message, sizeof(G.message), "Da xoa %d o dat! (+$%d)", deleted, refund);
    G.msgTimer = 2.5f;
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        G.msgTimer = 2.0f; return false;
    }
    /* Tìm corner trái-trên: quét ngược từ tile click trên cả 2 chiều */
    int ox = c, oy = r;
    while (ox > 0 && G.map[oy][ox-1].owned && G.map[oy][ox-1].barnIdx<0) ox--;
    while (oy > 0 && G.map[oy-1][ox].owned && G.map[oy-1][ox].barnIdx<0) oy--;
    /* Đo chiều rộng/cao từ corner đó */
    int pw = 0; while (ox+pw < MAP_COLS && G.map[oy][ox+pw].owned && G.map[oy][ox+pw].barnIdx<0) pw++;
    int ph = 0; while (oy+ph < MAP_ROWS && G.map[oy+ph][ox].owned && G.map[oy+ph][ox].barnIdx<0) ph++;
    if (pw <= 0 || ph <= 0) {
        strncpy(G.message, "Khong co dat de xoa!", sizeof(G.message)); G.msgTimer=1.5f; return false;
    }
    /* Xóa crop trong vùng */
    for (int i=0;i<MAX_CROPS;i++) {
        Crop *cp=&G.crops[i]; if(!cp->active) continue;
        if(cp->tileX>=ox&&cp->tileX<ox+pw&&cp->tileY>=oy&&cp->tileY<oy+ph){
            G.map[cp->tileY][cp->tileX].cropIdx=-1;
            G.map[cp->tileY][cp->tileX].type=TILE_GRASS;
            cp->active=false; G.cropCount--;
        }
    }
    /* Xóa tiles */
    int deleted=0;
    for (int dr=0;dr<ph;dr++) for(int dc=0;dc<pw;dc++) {
        int tr=oy+dr, tc=ox+dc;
        if(tr<0||tr>=MAP_ROWS||tc<0||tc>=MAP_COLS) continue;
        if(!G.map[tr][tc].owned || G.map[tr][tc].barnIdx>=0) continue;
        G.map[tr][tc].type=TILE_GRASS; G.map[tr][tc].owned=false;
        G.map[tr][tc].cropIdx=-1; G.map[tr][tc].barnIdx=-1;
        deleted++;
    }
    int refund=(LAND_PRICE_BASE*deleted*30)/(100*25);
    G.player.money+=refund;
    snprintf(G.message,sizeof(G.message),"Da xoa dat! (+$%d)",refund);
    G.msgTimer=2.5f;
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    return true;
}

/* ── Bắt đầu di chuyển chuồng ── */
bool Barn_StartMove(int tileX, int tileY)
{
    int bi = G.map[tileY][tileX].barnIdx;
    if (bi < 0) return false;
    Barn *b = &G.barns[bi];
    if (!b->active) return false;
<<<<<<< HEAD
<<<<<<< HEAD
    /* Bỏ đánh dấu tiles hiện tại (tạm thời) */
    for (int dr = 0; dr < BARN_H; dr++)
    for (int dc = 0; dc < BARN_W; dc++) {
        int tr = b->tileY + dr, tc = b->tileX + dc;
        if (tr >= 0 && tr < MAP_ROWS && tc >= 0 && tc < MAP_COLS)
            G.map[tr][tc].barnIdx = -1;
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    /* Bỏ đánh dấu barnIdx và owned — tile cũ về cỏ */
    for (int dr = 0; dr < BARN_H; dr++)
    for (int dc = 0; dc < BARN_W; dc++) {
        int tr = b->tileY + dr, tc = b->tileX + dc;
        if (tr >= 0 && tr < MAP_ROWS && tc >= 0 && tc < MAP_COLS) {
            G.map[tr][tc].barnIdx = -1;
            G.map[tr][tc].owned   = false;
            G.map[tr][tc].type    = TILE_GRASS;
        }
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    }
    G.isMoving    = true;
    G.moveBarnIdx = bi;
    G.movePlot    = false;
<<<<<<< HEAD
<<<<<<< HEAD
    strncpy(G.message, "Di chuyen chuong: click vi tri moi | RClick: Huy", sizeof(G.message));
=======
    strncpy(G.message, "Di chuyển chuồng: click vị trí mới | RClick: hủy", sizeof(G.message));
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
    strncpy(G.message, "Di chuyển chuồng: click vị trí mới | RClick: hủy", sizeof(G.message));
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    G.msgTimer = 4.0f;
    return true;
}

<<<<<<< HEAD
<<<<<<< HEAD
/* ── Bắt đầu di chuyển ô đất 5x5 ── */
=======
/* ── Plot_StartMove: dùng corner-scan, lưu kích thước thực ── */
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
/* ── Plot_StartMove: dùng corner-scan, lưu kích thước thực ── */
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
bool Plot_StartMove(int tileX, int tileY)
{
    if (!G.map[tileY][tileX].owned) return false;
    if (G.map[tileY][tileX].barnIdx >= 0) {
        strncpy(G.message, "Phai di chuyen chuong truoc!", sizeof(G.message));
<<<<<<< HEAD
<<<<<<< HEAD
        G.msgTimer = 2.0f;
        return false;
    }
    int ox = (tileX / LAND_PLOT_W) * LAND_PLOT_W;
    int oy = (tileY / LAND_PLOT_H) * LAND_PLOT_H;
    /* Bỏ đánh dấu owned tạm thời */
    for (int dr = 0; dr < LAND_PLOT_H; dr++)
    for (int dc = 0; dc < LAND_PLOT_W; dc++) {
        int tr = oy + dr, tc = ox + dc;
        if (tr >= 0 && tr < MAP_ROWS && tc >= 0 && tc < MAP_COLS) {
            G.map[tr][tc].owned = false;
            G.map[tr][tc].type  = TILE_GRASS;
        }
    }
    G.isMoving        = true;
    G.movePlot        = true;
    G.moveBarnIdx     = -1;
    G.movePlotTileX   = ox;
    G.movePlotTileY   = oy;
    strncpy(G.message, "Di chuyen o dat: click vi tri moi | RClick: Huy", sizeof(G.message));
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        G.msgTimer = 2.0f; return false;
    }
    /* Corner trái-trên: quét ngược từ tile click */
    int ox = tileX, oy = tileY;
    while (ox > 0 && G.map[oy][ox-1].owned && G.map[oy][ox-1].barnIdx<0) ox--;
    while (oy > 0 && G.map[oy-1][ox].owned && G.map[oy-1][ox].barnIdx<0) oy--;
    /* Kích thước thực từ corner */
    int pw = 0; while (ox+pw < MAP_COLS && G.map[oy][ox+pw].owned && G.map[oy][ox+pw].barnIdx<0) pw++;
    int ph = 0; while (oy+ph < MAP_ROWS && G.map[oy+ph][ox].owned && G.map[oy+ph][ox].barnIdx<0) ph++;
    /* Bỏ owned tạm thời — lưu vị trí cây tương đối để move theo */
    for (int dr=0;dr<ph;dr++) for(int dc=0;dc<pw;dc++) {
        int tr=oy+dr, tc=ox+dc;
        if (tr>=0&&tr<MAP_ROWS&&tc>=0&&tc<MAP_COLS) {
            /* Cập nhật tọa độ cây thành offset tương đối (âm để nhận ra) */
            int ci = G.map[tr][tc].cropIdx;
            if (ci >= 0 && ci < MAX_CROPS && G.crops[ci].active) {
                /* Lưu offset: tileX/Y bây giờ là vị trí tương đối so với corner */
                G.crops[ci].tileX = dc;  /* offset col từ corner */
                G.crops[ci].tileY = dr;  /* offset row từ corner */
            }
            G.map[tr][tc].owned   = false;
            G.map[tr][tc].type    = TILE_GRASS;
            G.map[tr][tc].cropIdx = -1;
        }
    }
    G.isMoving      = true;
    G.movePlot      = true;
    G.moveBarnIdx   = -1;
    G.movePlotTileX = ox;
    G.movePlotTileY = oy;
    G.movePlotW     = pw;   /* kích thước thực */
    G.movePlotH     = ph;
    snprintf(G.message,sizeof(G.message),"Di chuyen dat %dx%d: click vi tri moi | RClick: huy",pw,ph);
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    G.msgTimer = 4.0f;
    return true;
}

/* ── Đặt object đang di chuyển xuống vị trí mới ── */
bool Object_PlaceAtTile(int tileX, int tileY)
{
    if (!G.isMoving) return false;

    if (G.movePlot) {
<<<<<<< HEAD
<<<<<<< HEAD
        /* Di chuyển ô đất 5x5 */
        /* Kiểm tra vùng đích trống */
        for (int dr = 0; dr < LAND_PLOT_H; dr++)
        for (int dc = 0; dc < LAND_PLOT_W; dc++) {
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        /* Dùng kích thước thực lưu khi StartMove */
        int pw = G.movePlotW > 0 ? G.movePlotW : LAND_PLOT_W;
        int ph = G.movePlotH > 0 ? G.movePlotH : LAND_PLOT_H;
        for (int dr = 0; dr < ph; dr++)
        for (int dc = 0; dc < pw; dc++) {
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            int tr = tileY + dr, tc = tileX + dc;
            if (tr < 1 || tr >= MAP_ROWS-1 || tc < 2 || tc >= MAP_COLS-1) {
                strncpy(G.message, "Vi tri ngoai ban do!", sizeof(G.message));
                G.msgTimer = 2.0f; return false;
            }
<<<<<<< HEAD
<<<<<<< HEAD
            if (G.map[tr][tc].type != TILE_GRASS || G.map[tr][tc].owned) {
=======
            if (G.map[tr][tc].owned) {
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
            if (G.map[tr][tc].owned) {
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
                strncpy(G.message, "Vi tri bi chiem!", sizeof(G.message));
                G.msgTimer = 2.0f; return false;
            }
        }
<<<<<<< HEAD
<<<<<<< HEAD
        /* Đặt ô đất */
        for (int dr = 0; dr < LAND_PLOT_H; dr++)
        for (int dc = 0; dc < LAND_PLOT_W; dc++) {
=======
        for (int dr = 0; dr < ph; dr++)
        for (int dc = 0; dc < pw; dc++) {
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
        for (int dr = 0; dr < ph; dr++)
        for (int dc = 0; dc < pw; dc++) {
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            int tr = tileY + dr, tc = tileX + dc;
            G.map[tr][tc].type    = TILE_SOIL_BOUGHT;
            G.map[tr][tc].owned   = true;
            G.map[tr][tc].cropIdx = -1;
            G.map[tr][tc].barnIdx = -1;
        }
<<<<<<< HEAD
<<<<<<< HEAD
        G.isMoving = false;
        strncpy(G.message, "Da di chuyen o dat!", sizeof(G.message));
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        /* Dời cây trồng về vị trí mới: tìm các crop có offset (dc,dr) trong phạm vi */
        int ox2 = G.movePlotTileX, oy2 = G.movePlotTileY;
        for (int i = 0; i < MAX_CROPS; i++) {
            Crop *cp = &G.crops[i];
            if (!cp->active) continue;
            /* Nhận dạng crop thuộc plot này: tileX/Y hiện tại là offset (0..pw-1, 0..ph-1) */
            if (cp->tileX >= 0 && cp->tileX < pw && cp->tileY >= 0 && cp->tileY < ph) {
                /* Kiểm tra xem crop này có thực sự thuộc plot gốc không
                   bằng cách kiểm tra nó không còn liên kết tile nào */
                bool orphan = true;
                for (int r2=0;r2<MAP_ROWS&&orphan;r2++)
                for (int c2=0;c2<MAP_COLS&&orphan;c2++)
                    if (G.map[r2][c2].cropIdx == i) orphan = false;
                if (!orphan) continue;
                int newR = tileY + cp->tileY;
                int newC = tileX + cp->tileX;
                if (newR>=0&&newR<MAP_ROWS&&newC>=0&&newC<MAP_COLS) {
                    cp->tileX = newC;
                    cp->tileY = newR;
                    /* Cập nhật tile type theo stage */
                    TileType tt = (cp->stage==CSTAGE_READY) ? TILE_SOIL_PLANTED
                                : (cp->stage==CSTAGE_GROWING||cp->stage==CSTAGE_WATERED)
                                  ? TILE_SOIL_WET : TILE_SOIL_DUG;
                    G.map[newR][newC].type    = tt;
                    G.map[newR][newC].cropIdx = i;
                }
            }
        }
        /* Dồn lại những tile có cây nhưng stage chưa xác định về SOIL_BOUGHT */
        for (int dr = 0; dr < ph; dr++)
        for (int dc = 0; dc < pw; dc++) {
            int tr = tileY + dr, tc = tileX + dc;
            if (G.map[tr][tc].cropIdx < 0 &&
                G.map[tr][tc].type == TILE_SOIL_BOUGHT) { /* giữ nguyên */ }
        }
        G.isMoving = false;
        strncpy(G.message, "Da di chuyen dat (keo theo cay)!", sizeof(G.message));
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        G.msgTimer = 2.0f;
        return true;
    } else {
        /* Di chuyển chuồng */
        int bi = G.moveBarnIdx;
        if (bi < 0 || bi >= G.barnCount) { G.isMoving = false; return false; }
        Barn *b = &G.barns[bi];
<<<<<<< HEAD
<<<<<<< HEAD
        /* Kiểm tra 5x5 tại vị trí mới */
        for (int dr = 0; dr < BARN_H; dr++)
        for (int dc = 0; dc < BARN_W; dc++) {
            int tr = tileY + dr, tc = tileX + dc;
            if (tr < 0 || tr >= MAP_ROWS || tc < 0 || tc >= MAP_COLS ||
                !G.map[tr][tc].owned || G.map[tr][tc].barnIdx >= 0) {
                strncpy(G.message, "Can 5x5 dat da mua!", sizeof(G.message));
                G.msgTimer = 2.0f;
                /* Đặt lại vị trí cũ */
                for (int dr2 = 0; dr2 < BARN_H; dr2++)
                for (int dc2 = 0; dc2 < BARN_W; dc2++) {
                    int tr2 = b->tileY+dr2, tc2 = b->tileX+dc2;
                    if (tr2 >= 0 && tr2 < MAP_ROWS && tc2 >= 0 && tc2 < MAP_COLS)
                        G.map[tr2][tc2].barnIdx = bi;
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        /* Chuồng di chuyển tự do — chỉ cần trong biên map và không đè chuồng khác */
        for (int dr = 0; dr < BARN_H; dr++)
        for (int dc = 0; dc < BARN_W; dc++) {
            int tr = tileY + dr, tc = tileX + dc;
            if (tr < 1 || tr >= MAP_ROWS-1 || tc < 1 || tc >= MAP_COLS-1) {
                strncpy(G.message, "Vi tri ngoai ban do!", sizeof(G.message));
                G.msgTimer = 2.0f;
                /* Khôi phục barnIdx cũ */
                for (int dr2=0;dr2<BARN_H;dr2++) for(int dc2=0;dc2<BARN_W;dc2++) {
                    int tr2=b->tileY+dr2, tc2=b->tileX+dc2;
                    if(tr2>=0&&tr2<MAP_ROWS&&tc2>=0&&tc2<MAP_COLS) G.map[tr2][tc2].barnIdx=bi;
                }
                G.isMoving = false; return false;
            }
            if (G.map[tr][tc].barnIdx >= 0 && G.map[tr][tc].barnIdx != bi) {
                strncpy(G.message, "Vi tri da co chuong!", sizeof(G.message));
                G.msgTimer = 2.0f;
                for (int dr2=0;dr2<BARN_H;dr2++) for(int dc2=0;dc2<BARN_W;dc2++) {
                    int tr2=b->tileY+dr2, tc2=b->tileX+dc2;
                    if(tr2>=0&&tr2<MAP_ROWS&&tc2>=0&&tc2<MAP_COLS) G.map[tr2][tc2].barnIdx=bi;
                }
                G.isMoving = false; return false;
            }
            if (G.map[tr][tc].type==TILE_STONE||G.map[tr][tc].type==TILE_WATER_TILE) {
                strncpy(G.message, "Khong the dat chuong len da/nuoc!", sizeof(G.message));
                G.msgTimer = 2.0f;
                for (int dr2=0;dr2<BARN_H;dr2++) for(int dc2=0;dc2<BARN_W;dc2++) {
                    int tr2=b->tileY+dr2, tc2=b->tileX+dc2;
                    if(tr2>=0&&tr2<MAP_ROWS&&tc2>=0&&tc2<MAP_COLS) G.map[tr2][tc2].barnIdx=bi;
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
                }
                G.isMoving = false; return false;
            }
        }
        /* Dịch động vật theo */
        float dx = (float)((tileX - b->tileX) * TILE_SIZE);
        float dy = (float)((tileY - b->tileY) * TILE_SIZE);
        for (int i = 0; i < MAX_ANIMALS; i++) {
            if (G.animals[i].active && G.animals[i].barnIdx == bi) {
                G.animals[i].pos.x += dx;
                G.animals[i].pos.y += dy;
            }
        }
<<<<<<< HEAD
<<<<<<< HEAD
        /* Gán tile mới */
        b->tileX = tileX; b->tileY = tileY;
        for (int dr = 0; dr < BARN_H; dr++)
        for (int dc = 0; dc < BARN_W; dc++) {
            int tr = tileY + dr, tc = tileX + dc;
            G.map[tr][tc].barnIdx = bi;
        }
        G.isMoving    = false;
        G.moveBarnIdx = -1;
        strncpy(G.message, "Da di chuyen chuong!", sizeof(G.message));
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        /* Reset tile cũ về cỏ nếu không owned trước đó */
        for (int dr=0;dr<BARN_H;dr++) for(int dc=0;dc<BARN_W;dc++) {
            int tr=b->tileY+dr, tc=b->tileX+dc;
            if(tr>=0&&tr<MAP_ROWS&&tc>=0&&tc<MAP_COLS) {
                G.map[tr][tc].barnIdx = -1;
                /* Nếu tile chưa owned (cỏ) → đặt lại cỏ */
                if (!G.map[tr][tc].owned)
                    G.map[tr][tc].type = TILE_GRASS;
            }
        }
        /* Gán tile mới: owned + barnIdx */
        b->tileX = tileX; b->tileY = tileY;
        for (int dr=0;dr<BARN_H;dr++) for(int dc=0;dc<BARN_W;dc++) {
            int tr=tileY+dr, tc=tileX+dc;
            if(tr>=0&&tr<MAP_ROWS&&tc>=0&&tc<MAP_COLS) {
                G.map[tr][tc].barnIdx = bi;
                G.map[tr][tc].owned   = true;
                G.map[tr][tc].type    = TILE_GRASS; /* cỏ dưới chuồng */
                G.map[tr][tc].cropIdx = -1;
            }
        }
        G.isMoving    = false;
        G.moveBarnIdx = -1;
        strncpy(G.message, "Đã di chuyển chuồng!", sizeof(G.message));
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        G.msgTimer = 2.0f;
        return true;
    }
}

/* ── Hủy di chuyển — đặt lại vị trí cũ ── */
void Object_CancelMove(void)
{
    if (!G.isMoving) return;
    if (G.movePlot) {
<<<<<<< HEAD
<<<<<<< HEAD
        /* Đặt lại ô đất về vị trí cũ */
        int ox = G.movePlotTileX, oy = G.movePlotTileY;
        for (int dr = 0; dr < LAND_PLOT_H; dr++)
        for (int dc = 0; dc < LAND_PLOT_W; dc++) {
            int tr = oy + dr, tc = ox + dc;
            if (tr >= 0 && tr < MAP_ROWS && tc >= 0 && tc < MAP_COLS) {
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        int ox = G.movePlotTileX, oy = G.movePlotTileY;
        int pw = G.movePlotW > 0 ? G.movePlotW : LAND_PLOT_W;
        int ph = G.movePlotH > 0 ? G.movePlotH : LAND_PLOT_H;
        for (int dr=0;dr<ph;dr++) for(int dc=0;dc<pw;dc++) {
            int tr=oy+dr, tc=ox+dc;
            if (tr>=0&&tr<MAP_ROWS&&tc>=0&&tc<MAP_COLS) {
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
                G.map[tr][tc].type  = TILE_SOIL_BOUGHT;
                G.map[tr][tc].owned = true;
            }
        }
    } else if (G.moveBarnIdx >= 0) {
        Barn *b = &G.barns[G.moveBarnIdx];
        for (int dr = 0; dr < BARN_H; dr++)
        for (int dc = 0; dc < BARN_W; dc++) {
            int tr = b->tileY+dr, tc = b->tileX+dc;
            if (tr >= 0 && tr < MAP_ROWS && tc >= 0 && tc < MAP_COLS)
                G.map[tr][tc].barnIdx = G.moveBarnIdx;
        }
    }
    G.isMoving    = false;
    G.moveBarnIdx = -1;
    G.movePlot    = false;
<<<<<<< HEAD
<<<<<<< HEAD
    strncpy(G.message, "Da huy di chuyen.", sizeof(G.message));
    G.msgTimer = 1.5f;
}

void EntityManager_UpdateCrops(float dt)
{
    bool raining = (G.weather.current == WEATHER_RAINY);
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    strncpy(G.message, "Đã hủy di chuyển.", sizeof(G.message));
    G.msgTimer = 1.5f;
}

/* ── Cập nhật barn damage flash timer ── */
void UpdateBarnDmgTimers(float dt)
{
    for (int i = 0; i < MAX_BARNS; i++)
        if (G.barnDmgTimer[i] > 0.0f) {
            G.barnDmgTimer[i] -= dt;
            if (G.barnDmgTimer[i] < 0.0f) G.barnDmgTimer[i] = 0.0f;
        }
}

void EntityManager_UpdateCrops(float dt)
{
    bool raining = (G.weather.current == WEATHER_RAINY);

    /* BUG FIX #6: Mua tuoi tat ca o dat da dao chua trong (TILE_SOIL_DUG) */
    if (raining) {
        for (int r = 0; r < MAP_ROWS; r++)
        for (int c = 0; c < MAP_COLS; c++) {
            if (G.map[r][c].type == TILE_SOIL_DUG && G.map[r][c].cropIdx < 0)
                G.map[r][c].type = TILE_SOIL_WET;
        }
    }

<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    for (int i = 0; i < MAX_CROPS; i++)
    {
        Crop *c = &G.crops[i];
        if (!c->active)
            continue;

<<<<<<< HEAD
<<<<<<< HEAD
        /* Mưa tưới đất đã đào chưa trồng */
        if (raining && c->stage == CSTAGE_DUG)
        {
            c->stage = CSTAGE_WATERED;
            G.map[c->tileY][c->tileX].type = TILE_SOIL_WET;
        }

=======
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        /* WATERED = đã trồng hạt + đã tưới → tự chuyển sang GROWING */
        if (c->stage == CSTAGE_WATERED)
        {
            /* Giu WATERED 1s de hien thi mam (frame 1), roi bat dau lon */
            c->growTimer += dt;
            if (c->growTimer >= 1.0f)
            {
                c->stage = CSTAGE_GROWING;
                c->growTimer = 0;
            }
        }

        /* GROWING → đếm thời gian → READY */
        if (c->stage == CSTAGE_GROWING)
        {
<<<<<<< HEAD
<<<<<<< HEAD
            c->growTimer += dt * (raining ? 1.5f : 1.0f);
            if (c->growTimer >= GROW_SECS_STAGE)
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            /* Thời gian lớn riêng theo từng loại cây (giây), tăng dần theo độ hiếm/giá:
               CARROT=30  BEETROOT=45  CABBAGE=40  CAULIFLOWER=70
               KALE=35    PARSNIP=55   POTATO=50   PUMPKIN=100
               RADISH=25  SUNFLOWER=80 WHEAT=20                    */
            static const float CROP_GROW_SECS[NUM_CROP_TYPES] = {
                30.0f,  /* CARROT      giá 28  */
                45.0f,  /* BEETROOT    giá 35  */
                40.0f,  /* CABBAGE     giá 25  */
                70.0f,  /* CAULIFLOWER giá 45  */
                35.0f,  /* KALE        giá 22  */
                55.0f,  /* PARSNIP     giá 32  */
                50.0f,  /* POTATO      giá 35  */
               100.0f,  /* PUMPKIN     giá 65  */
                25.0f,  /* RADISH      giá 20  */
                80.0f,  /* SUNFLOWER   giá 50  */
                20.0f,  /* WHEAT       giá 18  */
            };
            float growNeeded = (c->type >= 0 && c->type < NUM_CROP_TYPES)
                               ? CROP_GROW_SECS[c->type] : GROW_SECS_STAGE;
            c->growTimer += dt * (raining ? 1.5f : 1.0f);
            if (c->growTimer >= growNeeded)
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            {
                c->stage = CSTAGE_READY;
                c->growTimer = 0;
                G.map[c->tileY][c->tileX].type = TILE_SOIL_PLANTED;
            }
        }
    }
}

/* ── Update animals ── */
void EntityManager_UpdateAnimals(float dt)
{
    for (int i = 0; i < MAX_ANIMALS; i++)
    {
        Animal *a = &G.animals[i];
        if (!a->active)
            continue;

        /* Đếm đói */
        if (!a->hungry)
        {
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            /* Thời gian đói theo loại động vật (giây):
               CHICKEN=60  PIG=90  SHEEP=120  (tăng dần theo giá sản phẩm) */
            static const float ANIMAL_FEED_SECS[ANIMAL_COUNT] = {
                60.0f,   /* CHICKEN  sản phẩm Trứng=22  */
                90.0f,   /* PIG      sản phẩm Len=38    */
               120.0f,   /* SHEEP    sản phẩm Sữa=45    */
            };
            float feedNeeded = (a->type >= 0 && a->type < ANIMAL_COUNT)
                               ? ANIMAL_FEED_SECS[a->type] : FEED_SECS;
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            a->feedTimer -= dt;
            if (a->feedTimer <= 0.0f)
            {
                a->hungry = true;
<<<<<<< HEAD
<<<<<<< HEAD
                a->feedTimer = FEED_SECS;
                Barn *b = &G.barns[a->barnIdx];
                snprintf(G.message, sizeof(G.message),
                         "Dong vat trong chuong [%d] dang doi an!", a->barnIdx);
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
                a->feedTimer = feedNeeded;
                Barn *b = &G.barns[a->barnIdx];
                snprintf(G.message, sizeof(G.message),
                         "Động vật trong chuồng [%d] đang đợi ăn!", a->barnIdx);
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
                G.msgTimer = 3.0f;
                (void)b;
            }
        }

        /* Chỉ sản xuất khi no */
        if (!a->hungry && !a->hasProduct)
        {
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            /* Thời gian cho sản phẩm theo loại (giây):
               CHICKEN=80  PIG=120  SHEEP=160  (tăng dần theo giá sản phẩm) */
            static const float ANIMAL_PRODUCE_SECS[ANIMAL_COUNT] = {
                80.0f,   /* CHICKEN  Trứng=22  */
               120.0f,   /* PIG      Len=38    */
               160.0f,   /* SHEEP    Sữa=45    */
            };
            float produceNeeded = (a->type >= 0 && a->type < ANIMAL_COUNT)
                                  ? ANIMAL_PRODUCE_SECS[a->type] : PRODUCE_SECS;
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            a->produceTimer -= dt;
            if (a->produceTimer <= 0.0f)
            {
                a->hasProduct = true;
<<<<<<< HEAD
<<<<<<< HEAD
                a->produceTimer = PRODUCE_SECS;
=======
                a->produceTimer = produceNeeded;
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
                a->produceTimer = produceNeeded;
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            }
        }

        /* Di chuyển lang thang trong chuồng
           Đứng im khi đói hoặc đang có sản phẩm chờ thu */
        /* Di chuyển lang thang trong toàn bộ chuồng 5x5 (chừa viền 0.5 tile) */
        Barn *b = &G.barns[a->barnIdx];
        float minX = (b->tileX + 0.5f) * TILE_SIZE, maxX = (b->tileX + 4.5f) * TILE_SIZE;
        float minY = (b->tileY + 0.5f) * TILE_SIZE, maxY = (b->tileY + 4.5f) * TILE_SIZE;

        if (a->hungry || a->hasProduct)
        {
            a->moveVel = (Vector2){0, 0};
        }
        else
        {
            /* Đổi hướng ngẫu nhiên theo timer */
            a->moveTimer -= dt;
            if (a->moveTimer <= 0.0f)
            {
                a->moveTimer = 0.8f + GetRandomValue(0, 25) * 0.1f;
                if (GetRandomValue(0, 3) == 0)
                {
                    /* 25%: đứng im */
                    a->moveVel = (Vector2){0, 0};
                }
                else
                {
                    /* 75%: hướng ngẫu nhiên hoàn toàn, tốc độ 22-38 */
                    float tx = GetRandomValue((int)minX, (int)maxX);
                    float ty = GetRandomValue((int)minY, (int)maxY);

                    Vector2 dir = {
                        tx - a->pos.x,
                        ty - a->pos.y};

                    float len = sqrtf(dir.x * dir.x + dir.y * dir.y);
                    if (len > 0.01f)
                    {
                        dir.x /= len;
                        dir.y /= len;
                    }

                    float spd = 20.0f + GetRandomValue(0, 15);
                    a->moveVel = (Vector2){dir.x * spd, dir.y * spd};
                }
            }

            a->moveVel.x += (GetRandomValue(-5, 5)) * 0.3f;
            a->moveVel.y += (GetRandomValue(-5, 5)) * 0.3f;

            /* Nảy ngược khi chạm tường — đổi hướng + thêm nhiễu */
            float nx = a->pos.x + a->moveVel.x * dt;
            float ny = a->pos.y + a->moveVel.y * dt;
            if (nx < minX || nx > maxX)
            {
                a->moveVel.x = -a->moveVel.x;
                /* Xáo trộn thêm vY để không đi thẳng mãi */
                a->moveVel.y += (GetRandomValue(0, 20) - 10) * 0.8f;
                a->moveTimer = 0.3f + GetRandomValue(0, 8) * 0.1f;
            }
            if (ny < minY || ny > maxY)
            {
                a->moveVel.y = -a->moveVel.y;
                a->moveVel.x += (GetRandomValue(0, 20) - 10) * 0.8f;
                a->moveTimer = 0.3f + GetRandomValue(0, 8) * 0.1f;
            }
        }

        a->pos.x = Clamp(a->pos.x + a->moveVel.x * dt, minX, maxX);
        a->pos.y = Clamp(a->pos.y + a->moveVel.y * dt, minY, maxY);

        /* Animation */
        a->animTimer += dt;
        if (a->animTimer >= 1.0f / ANIM_FPS)
        {
            a->animTimer = 0;
            Texture2D at = T.animal[a->type];
            int fc = (at.width > 0) ? at.width / 64 : 1;
            a->animFrame = (a->animFrame + 1) % (fc > 0 ? fc : 1);
        }
    }
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
/* ── Goblin zone: col 2-18, row 2-18 (rung cay goc tren trai) ── */
#define GZONE_X1  (2  * TILE_SIZE)
#define GZONE_X2  (18 * TILE_SIZE)
#define GZONE_Y1  (2  * TILE_SIZE)
#define GZONE_Y2  (18 * TILE_SIZE)

<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
/* ── Update enemies ── */
void EntityManager_UpdateEnemies(float dt)
{
    Player *p = &G.player;
<<<<<<< HEAD
<<<<<<< HEAD
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        Enemy *e = &G.enemies[i];
        if (!e->active)
            continue;
        if (e->hurtTimer > 0)
            e->hurtTimer -= dt;
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23

    /* Kiem tra bat dau game: spawn 5 goblin ngay dau */
    /* Dung G.goblinCount==0 && G.gameTime<1.0f lam dieu kien spawn lan dau
       (tranh dung static bool de reset duoc khi logout/login trong cung session) */
    static bool firstSpawn = false;
    if (!firstSpawn) {
        firstSpawn = true;
        for (int k = 0; k < 5; k++) {
            Enemy *eg = NULL;
            for (int i = 0; i < MAX_ENEMIES; i++)
                if (!G.enemies[i].active) { eg = &G.enemies[i]; break; }
            if (!eg) break;
            memset(eg, 0, sizeof(Enemy));
            eg->pos.x = GZONE_X1 + (float)GetRandomValue(2,(int)((GZONE_X2-GZONE_X1)/TILE_SIZE)-2)*TILE_SIZE;
            eg->pos.y = GZONE_Y1 + (float)GetRandomValue(2,(int)((GZONE_Y2-GZONE_Y1)/TILE_SIZE)-2)*TILE_SIZE;
            eg->type = ENEMY_GOBLIN;
            eg->maxHp = 45; eg->hp = 45;
            eg->state = ESTATE_WALK;
            eg->active = true;
            eg->wanderTarget = eg->pos;
            eg->wanderTimer = 0;
            G.enemyCount++;
            G.goblinCount++;
        }
    }

    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        Enemy *e = &G.enemies[i];
        if (!e->active) continue;
        if (e->hurtTimer > 0) e->hurtTimer -= dt;
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23

        if (e->state == ESTATE_DEAD)
        {
            e->animTimer += dt;
            if (e->animTimer >= 1.0f / ANIM_FPS)
            {
                e->animTimer = 0;
                e->animFrame++;
<<<<<<< HEAD
<<<<<<< HEAD
                if (e->animFrame >= 10)
                    e->active = false;
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
                if (e->animFrame >= 10) {
                    e->active = false;
                    /* Chi giam goblinCount cho goblin thuong, khong giam cho boss */
                    if (e->type == ENEMY_GOBLIN && !e->isBoss) G.goblinCount--;
                }
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            }
            continue;
        }
        if (e->state == ESTATE_HURT && e->hurtTimer <= 0)
            e->state = ESTATE_WALK;

        float dist = sqrtf(powf(e->pos.x - p->pos.x, 2) + powf(e->pos.y - p->pos.y, 2));
<<<<<<< HEAD
<<<<<<< HEAD
=======

        /* --- Tan cong neu du gan --- */
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======

        /* --- Tan cong neu du gan --- */
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        if (dist < ATTACK_RANGE)
        {
            e->state = ESTATE_ATTACK;
            e->atkTimer -= dt;
            if (e->atkTimer <= 0)
            {
<<<<<<< HEAD
<<<<<<< HEAD
                e->atkTimer = ATTACK_COOLDOWN;
                p->hp -= ATTACK_DAMAGE;
                p->hurtTimer = 0.5f;
                if (p->hp <= 0)
                {
                    p->hp = p->maxHp / 2;
                    p->pos = (Vector2){MAP_PX_W * 0.5f, MAP_PX_H * 0.5f};
                    p->money = (int)(p->money * 0.9f);
                    strncpy(G.message, "Ban bi ha guc! -10% tien.", sizeof(G.message));
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
                /* Đêm: sát thương tăng 50%, boss luôn x3 */
                int dmgAmt = e->isBoss ? ATTACK_DAMAGE*3 : ATTACK_DAMAGE;
                if (G.isNight && !e->isBoss) dmgAmt = (int)(dmgAmt * 1.5f);
                e->atkTimer = ATTACK_COOLDOWN;
                p->hp -= dmgAmt;
                p->hurtTimer = 0.5f;
                if (p->hp <= 0)
                {
                    /* Mat 1 mang */
                    p->lives--;
                    p->hp = p->maxHp;
                    p->pos = (Vector2){MAP_PX_W * 0.5f, MAP_PX_H * 0.5f};
                    if (p->lives <= 0) {
                        p->lives = 0;
                        G.endGame = true; G.endWin = false;
                        strncpy(G.message, "GAME OVER! Bạn đã mất tất cả mạng!", sizeof(G.message));
                    } else {
                        snprintf(G.message, sizeof(G.message), "Bị hạ gục! Còn %d mạng!", p->lives);
                    }
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
                    G.msgTimer = 4.0f;
                }
            }
        }
        else
        {
<<<<<<< HEAD
<<<<<<< HEAD
            e->state = ESTATE_WALK;
            Vector2 dir = {p->pos.x - e->pos.x, p->pos.y - e->pos.y};
            float len = sqrtf(dir.x * dir.x + dir.y * dir.y);
            if (len > 0)
            {
                dir.x /= len;
                dir.y /= len;
            }
            e->pos.x += dir.x * ENEMY_SPEED * dt;
            e->pos.y += dir.y * ENEMY_SPEED * dt;
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            float speed;
            if (e->type == ENEMY_GOBLIN)      speed = GOBLIN_SPEED;
            else if (e->type == ENEMY_BOSS)   speed = BOSS_SPEED;
            else                               speed = SKEL_SPEED;
            if (e->isBoss) speed = BOSS_SPEED;
            /* ĐÊM: tốc độ và sát thương tăng 50% */
            if (G.isNight) speed *= 1.5f;

            if (e->type == ENEMY_GOBLIN && !e->isBoss)
            {
                /* Goblin: di chuyển tự do trong rừng, xuyên qua cây để tạo tầng lớp.
                   Đuổi theo player khi player vào zone, lang thang ngẫu nhiên khi không. */
                bool playerInZone = (p->pos.x >= GZONE_X1 && p->pos.x <= GZONE_X2 &&
                                     p->pos.y >= GZONE_Y1 && p->pos.y <= GZONE_Y2);
                Vector2 target;
                if (playerInZone) {
                    target = p->pos;
                } else {
                    e->wanderTimer -= dt;
                    if (e->wanderTimer <= 0) {
                        e->wanderTarget.x = GZONE_X1 + (float)GetRandomValue(1,(int)((GZONE_X2-GZONE_X1)/TILE_SIZE)-1)*TILE_SIZE;
                        e->wanderTarget.y = GZONE_Y1 + (float)GetRandomValue(1,(int)((GZONE_Y2-GZONE_Y1)/TILE_SIZE)-1)*TILE_SIZE;
                        e->wanderTimer = 2.5f + GetRandomValue(0,3);
                    }
                    target = e->wanderTarget;
                }
                e->state = ESTATE_WALK;
                Vector2 dir = {target.x - e->pos.x, target.y - e->pos.y};
                float len = sqrtf(dir.x*dir.x + dir.y*dir.y);
                if (len > 4.0f) {
                    dir.x /= len; dir.y /= len;
                    /* Đi xuyên cây và đất — không check collision gì cả */
                    e->pos.x += dir.x * speed * dt;
                    e->pos.y += dir.y * speed * dt;
                }
                /* Clamp giữ goblin trong zone rừng */
                e->pos.x = Clamp(e->pos.x, GZONE_X1, GZONE_X2);
                e->pos.y = Clamp(e->pos.y, GZONE_Y1, GZONE_Y2);
            }
            else
            {
                /* Skeleton + Boss: di chuyển tự do toàn map, tấn công chuồng và cây */
                e->state = ESTATE_WALK;
                Vector2 dir = {p->pos.x - e->pos.x, p->pos.y - e->pos.y};
                float len = sqrtf(dir.x*dir.x + dir.y*dir.y);
                if (len > 0) { dir.x /= len; dir.y /= len; }

                float nx = e->pos.x + dir.x * speed * dt;
                float ny = e->pos.y + dir.y * speed * dt;
                int stx = (int)(nx/TILE_SIZE), sty = (int)(ny/TILE_SIZE);
                bool inBounds = (stx>=0&&stx<MAP_COLS&&sty>=0&&sty<MAP_ROWS);
                /* Skeleton bị chặn bởi chuồng hoặc cây gỗ; đi xuyên đất trồng */
                bool skelHasBarn     = inBounds && G.map[sty][stx].barnIdx >= 0;
                bool skelBlockedOwned = inBounds && skelHasBarn;
                bool skelBlockedTree  = inBounds && Tile_IsTree(stx, sty);
                /* Crop attack: check tile hiện tại skeleton đứng trên */
                int skelTileX = (int)(e->pos.x/TILE_SIZE), skelTileY = (int)(e->pos.y/TILE_SIZE);
                bool skelOnCrop = (skelTileX>=0&&skelTileX<MAP_COLS&&skelTileY>=0&&skelTileY<MAP_ROWS)
                               && G.map[skelTileY][skelTileX].cropIdx >= 0;

                if (!skelBlockedOwned && !skelBlockedTree) {
                    e->pos.x = nx;
                    e->pos.y = ny;
                    /* Đang đi qua đất có cây trồng → phá */
                    if (skelOnCrop && !e->isBoss) {
                        e->atkTimer -= dt;
                        int ci = G.map[skelTileY][skelTileX].cropIdx;
                        if (e->atkTimer <= 0.0f && ci >= 0 && G.crops[ci].active) {
                            e->atkTimer = ATTACK_COOLDOWN * 2.0f;
                            G.crops[ci].active = false;
                            G.map[skelTileY][skelTileX].cropIdx = -1;
                            G.map[skelTileY][skelTileX].type = TILE_SOIL_BOUGHT;
                            G.cropCount--;
                            snprintf(G.message,sizeof(G.message),"Skeleton phá cây trồng!");
                            G.msgTimer = 2.0f;
                        }
                    }
                } else {
                    e->atkTimer -= dt;

                    /* Skeleton phá CÂY */
                    if (skelBlockedTree && !skelBlockedOwned) {
                        if (e->atkTimer <= 0.0f) {
                            e->atkTimer = ATTACK_COOLDOWN * 2.5f;
                            if (G.map[sty][stx].chopCount < 1) {
                                G.map[sty][stx].chopCount = 1;
                                G.map[sty][stx].chopTimer = 15.0f;
                            } else {
                                G.map[sty][stx].chopCount = 99;
                                G.map[sty][stx].chopTimer = 120.0f; /* mọc lại sau 120s */
                            }
                        }
                    }

                    /* Skeleton phá CHUỒNG */
                    if (skelBlockedOwned && !e->isBoss) {
                        int bi = inBounds ? G.map[sty][stx].barnIdx : -1;
                        if (bi >= 0 && G.barns[bi].active) {
                            if (e->atkTimer <= 0.0f) {
                                e->atkTimer = ATTACK_COOLDOWN * 2.0f;
                                G.barnHp[bi] -= BARN_GOBLIN_DMG;
                                G.barnDmgTimer[bi] = 0.4f;
                                if (G.barnHp[bi] <= 0) {
                                    G.barnHp[bi] = 0;
                                    Barn_Delete(G.barns[bi].tileX, G.barns[bi].tileY);
                                    snprintf(G.message, sizeof(G.message),
                                        "Chuồng bị Skeleton phá! Bảo vệ nông trại!");
                                    G.msgTimer = 5.0f;
                                } else if (G.barnHp[bi] < BARN_MAX_HP / 3) {
                                    snprintf(G.message, sizeof(G.message),
                                        "Skeleton tấn công chuồng! HP: %d/%d",
                                        G.barnHp[bi], BARN_MAX_HP);
                                    G.msgTimer = 2.5f;
                                }
                            }
                        }
                        /* Crop attack handled when walking through tiles */
                    }
                }
            }
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        }
        e->animTimer += dt;
        if (e->animTimer >= 1.0f / ANIM_FPS)
        {
            e->animTimer = 0;
            e->animFrame = (e->animFrame + 1) % 8;
        }
    }
}

/* ── Update weather ── */
void EntityManager_UpdateWeather(float dt)
{
    Weather *w = &G.weather;
    w->timer -= dt;
    if (w->timer <= 0.0f)
    {
        /* Xác suất: sunny 50%, cloudy 30%, rainy 20% */
        int r = GetRandomValue(0, 9);
        w->current = (r < 5) ? WEATHER_SUNNY : (r < 8) ? WEATHER_CLOUDY
                                                       : WEATHER_RAINY;
        w->duration = 60.0f + GetRandomValue(0, 120);
        w->timer = w->duration;
    }
    /* Mây di chuyển */
    for (int i = 0; i < 8; i++)
    {
        w->cloudX[i] += w->cloudSpeed[i] * dt;
        if (w->cloudX[i] > SCREEN_W + 200)
            w->cloudX[i] = -200;
    }
    /* Mưa rơi */
    if (w->current == WEATHER_RAINY)
    {
        for (int i = 0; i < 40; i++)
        {
            w->rainDropY[i] += 280.0f * dt;
            if (w->rainDropY[i] > SCREEN_H)
            {
                w->rainDropY[i] = -10;
                w->rainDropX[i] = (float)GetRandomValue(0, SCREEN_W);
            }
        }
    }
}

/* ── Draw enemies ── */
void EntityManager_DrawEnemies(void)
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        Enemy *e = &G.enemies[i];
        if (!e->active)
            continue;
        Color tint = (e->hurtTimer > 0) ? (Color){255, 80, 80, 255} : WHITE;
        Texture2D(*arr)[5] = (e->type == ENEMY_GOBLIN) ? &T.goblin : &T.skel;
        Texture2D tex;
        switch (e->state)
        {
        case ESTATE_ATTACK:
            tex = (*arr)[2];
            break;
        case ESTATE_HURT:
            tex = (*arr)[3];
            break;
        case ESTATE_DEAD:
            tex = (*arr)[4];
            break;
        default:
            tex = (*arr)[e->state == ESTATE_WALK ? 1 : 0];
            break;
        }
<<<<<<< HEAD
<<<<<<< HEAD
        DrawSprite(tex, e->animFrame, ENEMY_FRAME_W, ENEMY_FRAME_H,
                   e->pos.x, e->pos.y, 1.25f, tint, false);
=======
        float sc = e->isBoss ? 2.5f : 1.25f;
        DrawSprite(tex, e->animFrame, ENEMY_FRAME_W, ENEMY_FRAME_H,
                   e->pos.x, e->pos.y, sc, tint, false);
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
        float sc = e->isBoss ? 2.5f : 1.25f;
        DrawSprite(tex, e->animFrame, ENEMY_FRAME_W, ENEMY_FRAME_H,
                   e->pos.x, e->pos.y, sc, tint, false);
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        if (e->state != ESTATE_DEAD)
        {
            float z = G.camZoom;
            Vector2 sp = WorldToScreen(e->pos);
<<<<<<< HEAD
<<<<<<< HEAD
            float bw = 38 * z, bx2 = sp.x - bw * 0.5f, by2 = sp.y - 42 * z;
            DrawRectangle((int)bx2, (int)by2, (int)bw, (int)(4 * z), DARKGRAY);
            float r = (float)e->hp / e->maxHp;
            DrawRectangle((int)bx2, (int)by2, (int)(bw * r), (int)(4 * z), RED);
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            float bw = (e->isBoss ? 80.0f : 38.0f) * z;
            float bx2 = sp.x - bw*0.5f;
            float by2 = sp.y - (e->isBoss ? 80.0f : 42.0f)*z;
            int bh = (int)((e->isBoss ? 8.0f : 4.0f)*z);
            DrawRectangle((int)bx2, (int)by2, (int)bw, bh, DARKGRAY);
            float hr = (float)e->hp / e->maxHp;
            Color hcol = e->isBoss ? (Color){220,50,50,255} : RED;
            DrawRectangle((int)bx2, (int)by2, (int)(bw*hr), bh, hcol);
            if (e->isBoss) {
                DrawRectangleLines((int)bx2,(int)by2,(int)bw,bh,(Color){255,200,0,255});
                DrawTextEx(gameFont,"BOSS",(Vector2){bx2,by2-14*z},12*z,1,YELLOW);
            }
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        }
    }
}

<<<<<<< HEAD
<<<<<<< HEAD
/* ── Spawn enemy ── */
void EntityManager_SpawnEnemy(void)
{
    Enemy *e = NULL;
    for (int i = 0; i < MAX_ENEMIES; i++)
        if (!G.enemies[i].active)
        {
            e = &G.enemies[i];
            break;
        }
    if (!e)
        return;
    memset(e, 0, sizeof(Enemy));
    int side = GetRandomValue(0, 3);
    switch (side)
    {
    case 0:
        e->pos.x = (float)GetRandomValue(2, MAP_COLS - 2) * TILE_SIZE;
        e->pos.y = 2 * TILE_SIZE;
        break;
    case 1:
        e->pos.x = (float)GetRandomValue(2, MAP_COLS - 2) * TILE_SIZE;
        e->pos.y = (MAP_ROWS - 4) * TILE_SIZE;
        break;
    case 2:
        e->pos.x = 2 * TILE_SIZE;
        e->pos.y = (float)GetRandomValue(2, MAP_ROWS - 2) * TILE_SIZE;
        break;
    default:
        e->pos.x = (MAP_COLS - 3) * TILE_SIZE;
        e->pos.y = (float)GetRandomValue(2, MAP_ROWS - 2) * TILE_SIZE;
        break;
    }
    e->type = (G.day > 3) ? (EnemyType)GetRandomValue(0, 1) : ENEMY_GOBLIN;
    e->maxHp = (e->type == ENEMY_GOBLIN) ? 45 : 70;
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
/* ── Spawn goblin trong rung ── */
static void SpawnGoblin(void)
{
    if (G.goblinCount >= MAX_GOBLINS) return;
    Enemy *e = NULL;
    for (int i = 0; i < MAX_ENEMIES; i++)
        if (!G.enemies[i].active) { e = &G.enemies[i]; break; }
    if (!e) return;
    memset(e, 0, sizeof(Enemy));
    e->pos.x = GZONE_X1 + (float)GetRandomValue(1,(int)((GZONE_X2-GZONE_X1)/TILE_SIZE)-1)*TILE_SIZE;
    e->pos.y = GZONE_Y1 + (float)GetRandomValue(1,(int)((GZONE_Y2-GZONE_Y1)/TILE_SIZE)-1)*TILE_SIZE;
    e->type = ENEMY_GOBLIN;
    e->maxHp = 45 + G.day * 3;
    e->hp = e->maxHp;
    e->state = ESTATE_WALK;
    e->active = true;
    e->wanderTimer = 0;
    e->wanderTarget = e->pos;
    G.enemyCount++;
    G.goblinCount++;
}

/* ── Spawn skeleton ngau nhien tren map ── */
static void SpawnSkeleton(void)
{
    Enemy *e = NULL;
    for (int i = 0; i < MAX_ENEMIES; i++)
        if (!G.enemies[i].active) { e = &G.enemies[i]; break; }
    if (!e) return;
    memset(e, 0, sizeof(Enemy));
    int side = GetRandomValue(0,3);
    switch(side){
    case 0: e->pos.x=(float)GetRandomValue(5,MAP_COLS-5)*TILE_SIZE; e->pos.y=3*TILE_SIZE; break;
    case 1: e->pos.x=(float)GetRandomValue(5,MAP_COLS-5)*TILE_SIZE; e->pos.y=(MAP_ROWS-5)*TILE_SIZE; break;
    case 2: e->pos.x=3*TILE_SIZE; e->pos.y=(float)GetRandomValue(5,MAP_ROWS-5)*TILE_SIZE; break;
    default:e->pos.x=(MAP_COLS-4)*TILE_SIZE; e->pos.y=(float)GetRandomValue(5,MAP_ROWS-5)*TILE_SIZE; break;
    }
    e->type = ENEMY_SKELETON;
    e->maxHp = 70 + G.day * 5;
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    e->hp = e->maxHp;
    e->state = ESTATE_WALK;
    e->active = true;
    G.enemyCount++;
}
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23

/* ── Spawn boss goblin to ── */
void SpawnBoss(void)
{
    if (G.bossAlive) return;
    Enemy *e = NULL;
    for (int i = 0; i < MAX_ENEMIES; i++)
        if (!G.enemies[i].active) { e = &G.enemies[i]; break; }
    if (!e) return;
    memset(e, 0, sizeof(Enemy));
    /* Boss xuat hien giua rung */
    e->pos.x = (GZONE_X1 + GZONE_X2) * 0.5f;
    e->pos.y = (GZONE_Y1 + GZONE_Y2) * 0.5f;
    e->type = ENEMY_GOBLIN;
    e->isBoss = true;
    e->maxHp = 350 + G.day * 20;
    e->hp = e->maxHp;
    e->state = ESTATE_WALK;
    e->active = true;
    G.enemyCount++;
    G.bossAlive = true;
    strncpy(G.message, "BOSS GOBLIN XUẤT HIỆN! TIÊU DIỆT ĐỂ KẾT THÚC GAME!", sizeof(G.message));
    G.msgTimer = 5.0f;
}

/* Public wrapper for extern call from game_logic */
void SpawnSkeleton_Pub(void) { SpawnSkeleton(); }

/* ── Spawn enemy (goi moi frame tu game_logic spawnTimer) ── */
void EntityManager_SpawnEnemy(void)
{
    /* Đêm: spawn tích cực hơn, mục tiêu goblin x2 */
    int nightMult = G.isNight ? 2 : 1;
    int targetGoblins = (5 + G.day * 2) * nightMult;
    if (targetGoblins > MAX_GOBLINS) targetGoblins = MAX_GOBLINS;
    if (G.goblinCount < targetGoblins)
        SpawnGoblin();
    /* Đêm: còn spawn thêm 1 skeleton nhanh hơn */
    if (G.isNight && GetRandomValue(0,3) == 0)
        SpawnSkeleton();

    /* Skeleton: 1 con moi 5 phut (300 giay), xu ly o game_logic */
}
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
/* ─────────────────────────────────────────────────────────
   CÂY: nhận diện + chặt (double-click → thu gỗ)
───────────────────────────────────────────────────────── */

/* Duplicate TileRand từ draw_tile.c để dùng trong entity_manager */
<<<<<<< HEAD
<<<<<<< HEAD
static int EM_TileRand(int x, int y, int salt, int range)
{
    if (range <= 0) return 0;
    unsigned int h = (unsigned int)(x * 1619 + y * 31337 + salt * 6271);
    h ^= h >> 16; h *= 0x45d9f3b; h ^= h >> 16;
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
/* BUG FIX: Dùng đúng cùng thuật toán hash với TileRand() trong draw_tile.c
   để Tile_IsTree() và GetDecorForTile() đồng thuận về tile nào có cây */
static int EM_TileRand(int x, int y, int salt, int range)
{
    if (range <= 0) return 0;
    unsigned int h = (unsigned int)(x * 2654435761u ^ y * 2246822519u ^ salt * 374761393u);
    h ^= h >> 17; h *= 668265263u; h ^= h >> 15;
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    return (int)(h % (unsigned int)range);
}

/* Trả về true nếu tile (r,c) có cây (decor 30, 31, 32) và chưa bị chặt */
bool Tile_IsTree(int c, int r)
{
    if (r < 2 || r >= MAP_ROWS-2 || c < 3 || c >= MAP_COLS-2) return false;
    if (G.map[r][c].type != TILE_GRASS) return false;
    if (G.map[r][c].owned) return false;
    if (G.map[r][c].barnIdx >= 0) return false;
    /* Cây đã bị chặt (chopCount=99) → không còn là cây */
    if (G.map[r][c].chopCount == 99) return false;
    /* Tránh vùng buildings (copy từ GetDecorForTile) */
    if (c>=23&&c<=34&&r>=17&&r<=28) return false;
    if (c>=2 &&c<=10&&r>=13&&r<=23) return false;
    if (c>=47&&c<=56&&r>=13&&r<=23) return false;
    if (c>=23&&c<=33&&r>=3 &&r<=13) return false;
    if (c>=48&&c<=57&&r>=25&&r<=35) return false;

    int roll = EM_TileRand(c, r, 42, 100);
<<<<<<< HEAD
<<<<<<< HEAD
=======
    bool inGoblinZone = (c >= 2 && c <= 18 && r >= 2 && r <= 18);
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
    bool inGoblinZone = (c >= 2 && c <= 18 && r >= 2 && r <= 18);
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    int edgeR = r < MAP_ROWS/2 ? r : MAP_ROWS-1-r;
    int edgeC = c < MAP_COLS/2 ? c : MAP_COLS-1-c;
    int edgeDist = edgeR < edgeC ? edgeR : edgeC;
    int maxEdge = (MAP_ROWS < MAP_COLS ? MAP_ROWS : MAP_COLS) / 2;
<<<<<<< HEAD
<<<<<<< HEAD
    int threshold = 22 + (edgeDist * 10) / (maxEdge > 0 ? maxEdge : 1);
    if (roll >= threshold) return false;

    int treeChance = edgeDist < 4 ? 50 : edgeDist < 8 ? 30 : 15;
    int treeRoll = EM_TileRand(c, r, 77, 100);
    return (treeRoll < treeChance);  /* decor 30/31/32 */
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    int threshold = inGoblinZone ? 90 : 22 + (edgeDist * 10) / (maxEdge > 0 ? maxEdge : 1);
    if (roll >= threshold) return false;
    /* Cây chỉ tồn tại trong rừng goblin */
    int treeChance = inGoblinZone ? 85 : 0;
    int treeRoll = EM_TileRand(c, r, 77, 100);
    return (treeRoll < treeChance);
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
}

/* Gọi mỗi frame để decay chopTimer */
void Tree_UpdateTimers(float dt)
{
    for (int r = 0; r < MAP_ROWS; r++)
    for (int c = 0; c < MAP_COLS; c++) {
        Tile *t = &G.map[r][c];
        if (t->chopTimer > 0.0f) {
            t->chopTimer -= dt;
            if (t->chopTimer <= 0.0f) {
                t->chopTimer = 0.0f;
<<<<<<< HEAD
<<<<<<< HEAD
                /* Chỉ reset về 0 nếu chưa bị chặt hẳn (99=đã chặt, giữ nguyên) */
                if (t->chopCount != 99) t->chopCount = 0;
=======
                /* Reset chopCount: nếu =1 (lần 1) về 0, nếu =99 (chặt hẳn) → cây mọc lại */
                t->chopCount = 0;
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
                /* Reset chopCount: nếu =1 (lần 1) về 0, nếu =99 (chặt hẳn) → cây mọc lại */
                t->chopCount = 0;
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            }
        }
    }
}

/* Click vào tile cây: click 1 → báo cần thêm 1 lần; click 2 → chặt */
bool Tree_Click(int tileX, int tileY)
{
    if (!Tile_IsTree(tileX, tileY)) return false;
    Tile *tile = &G.map[tileY][tileX];

    if (tile->chopCount == 0) {
        /* Lần đầu: set timer 10 giây, báo cho người chơi */
        tile->chopCount = 1;
        tile->chopTimer = 10.0f;
<<<<<<< HEAD
<<<<<<< HEAD
        strncpy(G.message, "Click them 1 lan nua de chat cay! (-10s)", sizeof(G.message));
=======
        strncpy(G.message, "Click thêm 1 lần nữa để chặt cây! (-10s)", sizeof(G.message));
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
        strncpy(G.message, "Click thêm 1 lần nữa để chặt cây! (-10s)", sizeof(G.message));
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        G.msgTimer = 3.0f;
        return true;
    } else {
        /* Lần hai: chặt cây — đánh dấu đã chặt (chopCount=99), thêm gỗ vào kho */
        tile->chopCount = 99;  /* 99 = đã chặt, cây không render nữa */
        tile->chopTimer = 0.0f;
        int wood = 2 + EM_TileRand(tileX, tileY, GetRandomValue(0,99), 3); /* 2-4 gỗ */
        Inv_Add(ITEM_WOOD, wood);
<<<<<<< HEAD
<<<<<<< HEAD
        snprintf(G.message, sizeof(G.message), "Chat cay! +%d Go", wood);
        G.msgTimer = 2.5f;
        return true;
    }
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        snprintf(G.message, sizeof(G.message), "Chặt cây! +%d gỗ", wood);
        G.msgTimer = 2.5f;
        return true;
    }
}

/* BUG FIX #5: reset firstSpawn khi game moi bat dau / login lai */
bool Entity_ResetFirstSpawn(void)
{
    /* Loi dung viec ham nay duoc goi tu ben ngoai de reset static */
    /* Thuc te: dat lai gia tri bang cach spawn truc tiep khi gameTime reset */
    return true;
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
}