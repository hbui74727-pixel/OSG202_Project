#include "draw_tile.h"
#include "tree_system.h"
<<<<<<< HEAD
<<<<<<< HEAD
=======
#include "font_manager.h" 
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
#include "font_manager.h" 
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
/* ─────────────────────────────────────────────────────────
   GROUND TILE HELPER
   ground.png: 160x16, 10 tiles 16x16
     tile 0-5: cỏ (6 biến thể sáng tối xen kẽ)
     tile 6-8: đất đào (nâu đậm, 3 biến thể)
     tile 9  : đất ướt
───────────────────────────────────────────────────────── */
static void DrawGroundTile(int idx, float wx, float wy)
{
    if (T.ground.width < 16) return;
    float z = G.camZoom;
    Vector2 sp = WorldToScreen((Vector2){wx, wy});
    Rectangle src = {(float)(idx * 16), 0, 16, 16};
    Rectangle dst = {sp.x, sp.y, (float)TILE_SIZE * z, (float)TILE_SIZE * z};
    DrawTexturePro(T.ground, src, dst, (Vector2){0,0}, 0, WHITE);
}

/* ─────────────────────────────────────────────────────────
   TREE.PNG SPRITE HELPER
   tree.png: 240x176
   DrawTreeSprite(srcX, srcY, srcW, srcH, worldX, worldY, scale)
   - worldX/Y là gốc dưới-giữa của sprite
───────────────────────────────────────────────────────── */
static void DrawTreeSprite(int sx, int sy, int sw, int sh,
                            float wx, float wy, float scale, Color tint)
{
    if (T.tree.width < 16) return;
    float z = G.camZoom * scale;
    Vector2 sp = WorldToScreen((Vector2){wx, wy});
    float dw = (float)sw * z;
    float dh = (float)sh * z;
    Rectangle src = {(float)sx, (float)sy, (float)sw, (float)sh};
    /* Anchor: gốc dưới-giữa */
    Rectangle dst = {sp.x - dw * 0.5f, sp.y - dh, dw, dh};
    DrawTexturePro(T.tree, src, dst, (Vector2){0,0}, 0, tint);
}

/* ─────────────────────────────────────────────────────────
   RANDOM SCATTER — các đồ vật trang trí ngẫu nhiên trên toàn map
   Dùng seed cố định (tileX*1000+tileY) để giống nhau mỗi frame
───────────────────────────────────────────────────────── */

/* Pseudo-random nhanh: hash của (x, y, salt) → 0..range-1 */
static int TileRand(int x, int y, int salt, int range)
{
    unsigned int h = (unsigned int)(x * 2654435761u ^ y * 2246822519u ^ salt * 374761393u);
    h ^= h >> 17; h *= 668265263u; h ^= h >> 15;
    return (int)(h % (unsigned int)range);
}

typedef struct {
    int  srcX, srcY, srcW, srcH;
    float scale;
} DecorDef;


/* Bảng decor từ tree.png — đã verify từng sprite pixel (240x176, grid 16px)
   Căn chỉnh đúng: mỗi sprite 16px aligned, đen→transparent đã xử lý */
#define DECOR_COUNT 35
static const DecorDef DECORS[DECOR_COUNT] = {
    /* ── Hoa nhỏ (16x16) ── */
    /*  0 */ { 32, 48, 16,16, 1.4f}, 
    /*  1 */ { 48, 48, 16,16, 1.5f}, 
    /*  2 */ { 64, 48, 16,16, 1.6f}, 
    /*  3 */ { 80, 48, 16,16, 1.7f}, 
    /*  4 */ { 32, 64, 16,16, 1.4f}, 
    /*  5 */ { 48, 64, 16,16, 1.5f}, 
    /*  6 */ { 64, 64, 16,16, 1.6f}, 
    /*  7 */ { 80, 64, 16,16, 1.7f}, 
    /*  8 */ { 32, 80, 16,16, 1.4f}, 
    /*  9 */ { 48, 80, 16,16, 1.5f}, 
    /* 10 */ { 64, 80, 16,16, 1.6f}, 
    /* 11 */ { 80, 80, 16,16, 1.7f}, 
    /* 12 */ { 96, 80, 16,16, 1.8f}, 
    /* 13 */ { 96, 80, 16,16, 1.9f}, 
    /* 14 */ { 32,112, 16,16, 1.5f}, 

    /* ── Đá (16x16) ── */
    /* 15 */ { 32, 96, 16,16, 1.5f}, 
    /* 16 */ { 48, 96, 16,16, 1.7f}, 
    /* 17 */ { 64, 96, 16,16, 1.9f}, 
    /* 18 */ { 80, 96, 16,16, 2.1f}, 

    /* ── Hoa lớn/chậu (16x32) ── */
    /* 19 */ { 48,128, 16,32, 1.3f}, 
    /* 20 */ { 64,128, 16,32, 1.4f}, 
    /* 21 */ { 80,128, 16,32, 1.3f}, 
    /* 22 */ { 96,128, 16,32, 1.2f}, 
    /* 23 */ {112,128, 16,32, 1.1f}, 

    /* ── Sparkle ── */
    /* 24 */ { 32,144, 16,16, 1.2f}, 
    /* 25 */ { 32,160, 16,16, 1.1f}, 

    /* ── Bụi cây ── */
    /* 26 */ {  0, 48, 32,32, 1.6f}, 
    /* 27 */ {  0, 80, 32,32, 1.7f}, 
    /* 28 */ {  0,112, 32,32, 1.7f}, 

    /* ── gốc cây ── */
    /* 29 */ { 80, 16, 32,16, 1.8f}, 

    /* ── Cây ── */
    /* 30 */ {  0,  0, 16,48, 2.4f}, 
    /* 31 */ { 16,  0, 32,48, 2.5f}, 
    /* 32 */ { 48, 16, 32,32, 2.6f}, 
};
/* Xác suất xuất hiện trang trí tại tile (r,c)
   Trả về index vào DECORS hoặc -1 nếu không có gì */
static int GetDecorForTile(int r, int c)
{
    /* Chỉ vẽ decor trên tile cỏ chưa owned */
    if (r < 2 || r >= MAP_ROWS-2 || c < 3 || c >= MAP_COLS-2) return -1;
    if (G.map[r][c].type != TILE_GRASS) return -1;
    if (G.map[r][c].owned) return -1;
    if (G.map[r][c].barnIdx >= 0) return -1;
    /* Cây đã bị chặt → không vẽ */
    if (G.map[r][c].chopCount == 99) return -1;
    /* Tránh vùng buildings */
    if (c>=23&&c<=34&&r>=17&&r<=28) return -1;
    if (c>=2 &&c<=10&&r>=13&&r<=23) return -1;
    if (c>=47&&c<=56&&r>=13&&r<=23) return -1;
    if (c>=23&&c<=33&&r>=3 &&r<=13) return -1;
    if (c>=48&&c<=57&&r>=25&&r<=35) return -1;

    /* Tính khoảng cách đến rìa map (0=rìa, 1=xa rìa nhất) */
    int edgeR = r < MAP_ROWS/2 ? r : MAP_ROWS-1-r;
    int edgeC = c < MAP_COLS/2 ? c : MAP_COLS-1-c;
    int edgeDist = edgeR < edgeC ? edgeR : edgeC;  /* min */
    /* Chuẩn hóa: 0=rìa → 1=giữa map */
    int maxEdge = (MAP_ROWS < MAP_COLS ? MAP_ROWS : MAP_COLS) / 2;
    /* edgeDist: 0=rìa, maxEdge=giữa */

<<<<<<< HEAD
<<<<<<< HEAD
    /* Roll cơ bản: giảm từ 40% xuống 22% cho nội thất map */
    int roll = TileRand(c, r, 42, 100);
    /* Càng vào giữa map → ngưỡng xuất hiện càng thấp (thưa hơn) */
    int threshold = 22 + (edgeDist * 10) / (maxEdge > 0 ? maxEdge : 1);
    /* rìa (edgeDist=0): threshold~22 → 22% có decor
       giữa (edgeDist=maxEdge): threshold~32 → 32% không có = 68% trống */
    if (roll >= threshold) return -1;

    /* Tỉ lệ cây cao hơn ở rìa, thấp hơn ở giữa */
    /* Chia roll thành nhóm cây / hoa-đá */
    /* Rìa (edgeDist<4): ~50% cây, ~50% còn lại
       Giữa (edgeDist>=8): ~15% cây */
    int treeChance = edgeDist < 4  ? 50 :
                     edgeDist < 8  ? 30 : 15;
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    /* Khu rung goblin (goc tren trai): mat do cay rat cao */
    bool inGoblinZone = (c >= 2 && c <= 18 && r >= 2 && r <= 18);
    int roll = TileRand(c, r, 42, 100);
    int threshold;
    if (inGoblinZone) {
        threshold = 90; /* 90% o co decor trong rung */
    } else {
        threshold = 22 + (edgeDist * 10) / (maxEdge > 0 ? maxEdge : 1);
    }
    if (roll >= threshold) return -1;

    /* Cây chỉ mọc trong rừng goblin (góc trên trái) */
    int treeChance = inGoblinZone ? 85 : 0;
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    int treeRoll = TileRand(c, r, 77, 100);
    if (treeRoll < treeChance) {
        /* Chọn loại cây */
        int tv = TileRand(c, r, 88, 5);
        if (tv < 2) return 30;               /* cây thông */
        if (tv < 4) return 31;               /* cây tròn */
        return 32;                            /* cây tròn lớn */
    }
    /* Còn lại: hoa, đá, bụi — nhưng chỉ xuất hiện rải rác */
    int decorRoll = TileRand(c, r, 55, 100);
    if (decorRoll < 12) return 26 + TileRand(c,r,1,3);   /* bụi (26-28) */
    if (decorRoll < 18) return 29;                         /* gốc cây */
    if (decorRoll < 28) return TileRand(c,r,4,4);         /* hoa xanh 0-3 */
    if (decorRoll < 38) return 4 + TileRand(c,r,5,4);     /* hoa cam 4-7 */
    if (decorRoll < 45) return 8 + TileRand(c,r,6,2);     /* hoa trắng 8-9 */
    if (decorRoll < 55) return 10 + TileRand(c,r,7,4);    /* hoa cúc 10-13 */
    if (decorRoll < 60) return 14;                         /* hoa đỏ */
    if (decorRoll < 72) return 15 + TileRand(c,r,8,4);    /* đá 15-18 */
    if (decorRoll < 80) return 19 + TileRand(c,r,9,2);    /* hoa vàng 19-20 */
    if (decorRoll < 90) return 21 + TileRand(c,r,10,2);   /* hoa chậu 21-22 */
    return 24 + TileRand(c,r,11,2);                        /* sparkle 24-25 */
}

/* ─────────────────────────────────────────────────────────
   BORDER TREES (cây viền map = vùng bị khóa)
───────────────────────────────────────────────────────── */
static void DrawBorderTrees(void)
{
    if (T.tree.width < 16) return;
    float z = G.camZoom;

    /* Cây tròn to từ cluster (32x32 px tại src 144,16) */
    /* Dùng cây thông (0,0,32,48) và tròn nhỏ (32,0,32,48) xen kẽ */
    int bigSrcs[3][4] = {
        {0,  0, 16, 48},   /* pine */
        {16, 0, 32, 48},   /* round */
        {48,16,32, 32},   /* big round */
    };

    /* Vẽ viền trên (row 0-1) */
    for (int c = -1; c <= MAP_COLS+1; c++) {
        int v = TileRand(c, 0, 77, 3);
        int *s = bigSrcs[v];
        float wx = (float)(c * TILE_SIZE) + TILE_SIZE * 0.5f;
        float wy = (float)(1 * TILE_SIZE);
        float sc = 1.2f + TileRand(c,0,99,3)*0.12f;
        DrawTreeSprite(s[0],s[1],s[2],s[3], wx,wy, sc, WHITE);
    }
    /* Viền dưới (row MAP_ROWS-2) */
    for (int c = -1; c <= MAP_COLS+1; c++) {
        int v = TileRand(c, MAP_ROWS, 55, 3);
        int *s = bigSrcs[v];
        float wx = (float)(c * TILE_SIZE) + TILE_SIZE * 0.5f;
        float wy = (float)((MAP_ROWS-1) * TILE_SIZE);
        float sc = 1.2f + TileRand(c,MAP_ROWS,88,3)*0.12f;
        DrawTreeSprite(s[0],s[1],s[2],s[3], wx,wy, sc, WHITE);
    }
    /* Viền trái (col 0-1) */
    for (int r = 2; r < MAP_ROWS-2; r++) {
        int v = TileRand(0, r, 33, 3);
        int *s = bigSrcs[v];
        float wx = (float)(1 * TILE_SIZE) + TILE_SIZE * 0.5f;
        float wy = (float)((r+1) * TILE_SIZE);
        float sc = 1.1f + TileRand(0,r,66,3)*0.12f;
        DrawTreeSprite(s[0],s[1],s[2],s[3], wx,wy, sc, WHITE);
    }
    /* Viền phải (col MAP_COLS-2) */
    for (int r = 2; r < MAP_ROWS-2; r++) {
        int v = TileRand(MAP_COLS, r, 44, 3);
        int *s = bigSrcs[v];
        float wx = (float)((MAP_COLS-2) * TILE_SIZE) + TILE_SIZE * 0.5f;
        float wy = (float)((r+1) * TILE_SIZE);
        float sc = 1.1f + TileRand(MAP_COLS,r,77,3)*0.12f;
        DrawTreeSprite(s[0],s[1],s[2],s[3], wx,wy, sc, WHITE);
    }

    (void)z;
}

/* ─────────────────────────────────────────────────────────
   DrawTile_All — render toàn bộ map tiles + decor
───────────────────────────────────────────────────────── */
void DrawTile_All(void)
{
    float z = G.camZoom;
    int c0 = (int)(G.camX / TILE_SIZE) - 1;
    int r0 = (int)(G.camY / TILE_SIZE) - 1;
    int c1 = c0 + (int)((float)SCREEN_W  / ((float)TILE_SIZE * z)) + 3;
    int r1 = r0 + (int)((float)SCREEN_H  / ((float)TILE_SIZE * z)) + 3;
    if (c0 < 0) c0 = 0; if (r0 < 0) r0 = 0;
    if (c1 > MAP_COLS) c1 = MAP_COLS;
    if (r1 > MAP_ROWS) r1 = MAP_ROWS;

    bool hasGround = (T.ground.width >= 160);

    /* ── Pass 1: vẽ ground tiles ── */
    for (int r = r0; r < r1; r++)
    for (int c = c0; c < c1; c++) {
      float wx = (float)(c * TILE_SIZE);
      float wy = (float)(r * TILE_SIZE);
        TileType t = G.map[r][c].type;

        switch (t) {
            case TILE_GRASS:
                if (hasGround) {
                    /* Pattern caro 2 màu giống game mẫu:
                       tile sáng (0,1,2) và tối (3,4,5) xen kẽ theo (c+r)%2
                       thêm micro-variation để không đều quá */
                    int light = (c + r) % 2;  /* 0=sáng, 1=tối */
                    int v;
                    /* 80% tile caro thuần, 20% biến thể */
                    if (TileRand(c,r,11,5) < 4) {
                        /* Caro thuần: tile 0 (sáng) hoặc tile 3 (tối) */
                        v = light ? 3 : 0;
                    } else {
                        /* Biến thể: sáng→{0,1,2}, tối→{3,4,5} */
                        v = light ? (3 + TileRand(c,r,22,3))
                                  : TileRand(c,r,22,3);
                    }
                    DrawGroundTile(v, wx, wy);
                } else {
                    DrawTilesetCell((c+r)%4, 0, wx, wy);
                }
                break;

            case TILE_SOIL_BOUGHT: {
                /* Đất mua: nâu nhạt đục */
                Vector2 sp = WorldToScreen((Vector2){wx, wy});
                int tsz = (int)((float)TILE_SIZE * z);
                DrawRectangle((int)sp.x, (int)sp.y, tsz, tsz, (Color){192,158,112,255});
                if (hasGround) {
                    DrawTexturePro(T.ground,
                        (Rectangle){9*16.0f,0,16,16},
                        (Rectangle){sp.x,sp.y,(float)tsz,(float)tsz},
                        (Vector2){0,0}, 0, (Color){255,240,210,100});
                }
                DrawRectangleLines((int)sp.x,(int)sp.y,tsz,tsz,(Color){150,115,70,180});
                break;
            }

            case TILE_SOIL_DUG:
                if (hasGround) {
                    int v = 6 + (c + r) % 3;
                    DrawGroundTile(v, wx, wy);
                } else DrawTilesetCell(4, 2, wx, wy);
                break;

            case TILE_SOIL_WET:
            case TILE_SOIL_PLANTED:
                if (hasGround) {
                    DrawGroundTile(9, wx, wy);
                    Vector2 sp = WorldToScreen((Vector2){wx, wy});
                    DrawRectangle((int)sp.x,(int)sp.y,
                        (int)((float)TILE_SIZE*z),(int)((float)TILE_SIZE*z),
                        (Color){30,100,200,35});
                } else DrawTilesetCell(5, 2, wx, wy);
                break;

            case TILE_PATH:
                if (T.tileset.width > 0) {
                    DrawTilesetCell(8, 4, wx, wy);
                } else {
                    Vector2 sp3=WorldToScreen((Vector2){wx,wy});
                    int tsz3=(int)((float)TILE_SIZE*z);
                    DrawRectangle((int)sp3.x,(int)sp3.y,tsz3,tsz3,(Color){180,150,110,255});
                }
                break;

            case TILE_WATER_TILE: {
                /* Vẽ nước: màu xanh dương với animation */
                Vector2 sp = WorldToScreen((Vector2){wx, wy});
                int tsz = (int)((float)TILE_SIZE * z);
                float wt = G.gameTime * 1.5f;
                unsigned char wa = (unsigned char)(200 + sinf(wt + wx*0.1f + wy*0.07f)*40.0f);
                DrawRectangle((int)sp.x,(int)sp.y,tsz,tsz,(Color){40,120,200,255});
                /* Sóng nhỏ */
                DrawRectangle((int)sp.x+2,(int)(sp.y+tsz*0.3f+sinf(wt)*2),(int)(tsz*0.6f),2,(Color){100,180,255,wa});
                DrawRectangle((int)(sp.x+tsz*0.3f)+2,(int)(sp.y+tsz*0.65f+cosf(wt)*2),(int)(tsz*0.5f),2,(Color){100,180,255,wa});
                break;
            }

            case TILE_STONE:
                /* Stone = viền map, đã có cây phủ lên - vẽ nền cỏ tối */
                if (hasGround) {
                    DrawGroundTile(5, wx, wy); /* cỏ tối nhất */
                } else {
                    Vector2 sp2=WorldToScreen((Vector2){wx,wy});
                    int tsz2=(int)((float)TILE_SIZE*z);
                    DrawRectangle((int)sp2.x,(int)sp2.y,tsz2,tsz2,(Color){60,110,45,255});
                }
                break;

            default:
                if (hasGround) DrawGroundTile(0, wx, wy);
                else           DrawTilesetCell(0, 0, wx, wy);
                break;
        }
    }

    /* ── Pass 2: decor (cây, hoa, đá…) trên cỏ ── */
    /* Vẽ theo thứ tự từ trên xuống (row tăng dần) để depth đúng */
    if (T.tree.width >= 16) {
        for (int r = r0; r < r1; r++)
        for (int c = c0; c < c1; c++) {
            int di = GetDecorForTile(r, c);
            if (di < 0) continue;

            const DecorDef *d = &DECORS[di];
            float wx = (float)(c * TILE_SIZE) + TILE_SIZE * 0.5f;
            /* Anchor: chân decor = tâm dưới tile, dịch lên 1 tile */
            float wy = (float)((r + 1) * TILE_SIZE);

            /* Micro offset để trông tự nhiên hơn */
            float ox = (TileRand(c,r,111,9) - 4) * 1.5f;
            float oy = (TileRand(c,r,222,5) - 2) * 1.5f;

            float sc = d->scale;
            /* Không scale thêm — scale đã được set trong DECORS */

            DrawTreeSprite(d->srcX, d->srcY, d->srcW, d->srcH,
                           wx + ox, wy + oy, sc, WHITE);
        }
    }

    for(int i=0;i<treeCount;i++)
{
    Tree *t=&trees[i];
    if(!t->alive) continue;

    float wx = t->tileX*TILE_SIZE + TILE_SIZE*0.5f;
    float wy = (t->tileY+1)*TILE_SIZE - TILE_SIZE*0.5f;

    DrawTreeSprite(16,0,32,48,wx,wy,2.4f,WHITE);
}

    /* ── Pass 3: border trees (vùng khóa) ── */
    DrawBorderTrees();
}

/* ─────────────────────────────────────────────────────────
   DrawTile_Highlight
───────────────────────────────────────────────────────── */
void DrawTile_Highlight(void)
{
    if (G.showInventory || G.showStore || G.showBarnUI) return;
    if (G.hbarPlacing) return;

    Vector2 mw = ScreenToWorld(GetMousePosition());
    int hx = WorldToTileX(mw.x), hy = WorldToTileY(mw.y);
    if (hx < 0 || hx >= MAP_COLS || hy < 0 || hy >= MAP_ROWS) return;

    Vector2 sp = WorldToScreen((Vector2){(float)(hx*TILE_SIZE),(float)(hy*TILE_SIZE)});
    float z = G.camZoom;

    Color hcol = {255,255,100,130};
    switch (G.player.tool) {
        case TOOL_HOE:          hcol=(Color){180,120,60,150}; break;
        case TOOL_WATERING_CAN: hcol=(Color){80,180,255,150}; break;
        case TOOL_SEED:         hcol=(Color){80,200,80,150};  break;
        case TOOL_SCYTHE:       hcol=(Color){220,220,60,150}; break;
        case TOOL_SWORD:        hcol=(Color){220,60,60,150};  break;
        case TOOL_FEED:         hcol=(Color){255,180,60,150}; break;
        default: break;
    }
    DrawRectangleLinesEx(
        (Rectangle){sp.x, sp.y, (float)TILE_SIZE*z, (float)TILE_SIZE*z},
        2.0f, hcol);

    Tile *tile = &G.map[hy][hx];
    const char *info = NULL;
    switch (tile->type) {
<<<<<<< HEAD
<<<<<<< HEAD
        case TILE_GRASS:        info="Cỏ xanh - mua đất từ hotbar"; break;
        case TILE_SOIL_BOUGHT:  info="[1]Cuốc để đào"; break;
        case TILE_SOIL_DUG:     info="[2]Tưới nước"; break;
        case TILE_SOIL_WET:     info="[3]Trồng hạt"; break;
        case TILE_SOIL_PLANTED: info="Cho cây chín rồi [4]Thu hoạch"; break;
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        case TILE_GRASS:        info="Cỏ xanh"; break;
        case TILE_SOIL_BOUGHT:  info="[1]Cày để đào"; break;
        case TILE_SOIL_DUG:     info="[2]Tưới nước"; break;
        case TILE_SOIL_WET:     info="[3]Trồng hạt"; break;
        case TILE_SOIL_PLANTED: info="Cho cây chín rồi [4]cắt"; break;
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        default: break;
    }
    if (info) {
        int tw = MeasureText(info, 10);
        DrawRectangle((int)sp.x, (int)(sp.y-16), tw+8, 14, (Color){0,0,0,150});
<<<<<<< HEAD
<<<<<<< HEAD
        DrawText(info, (int)sp.x+4, (int)(sp.y-14), 10, WHITE);
    }
}
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        DrawTextShort(info, (int)sp.x+4, (int)(sp.y-14), 10, WHITE);
    }
}
/* Public wrapper: tra ve decor index cua tile (r,c), -1 neu khong co */
<<<<<<< HEAD
int GetDecorTypeForTile(int r, int c) { return GetDecorForTile(r, c); }
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
int GetDecorTypeForTile(int r, int c) { return GetDecorForTile(r, c); }
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
