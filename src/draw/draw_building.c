// file: src/draw/draw_building.c
// GIỮ NGUYÊN VỊ TRÍ NHÀ Ở GÓC PHẢI TRÊN MAP - DÙNG home.png

#include "draw_building.h"
#include "../game_logic.h"
#include "../font_manager.h"

/* home.png: 240x320, mode RGBA
   15 cols x 20 rows @ 16px/tile
   5 ngôi nhà, mỗi nhà = col*48 x row, kích thước 48x64 (3 tile rộng x 4 tile cao)
   Col 0=xanh(NHA), 1=xanh lá(KHO), 2=cam(CỬAHÀNG), 3=đỏ(QUEST), 4=tím(GUILD) */

void DrawBuilding_TileObject(int tileCol, int tileRow, int spanW, int spanH,
                              float worldX, float worldY, float scale)
{
    (void)tileCol; (void)tileRow; (void)spanW; (void)spanH;
    (void)worldX; (void)worldY; (void)scale;
}
// === HÀM VẼ NHÀ TỪ home.png ===
static void DrawHomeFromTileset(int col, int tileX, int tileY, const char *label)
{
    if (T.home.width < 48) return;
    
    float z = G.camZoom;
    float worldX = tileX * TILE_SIZE;
    float worldY = tileY * TILE_SIZE;
    
    // Vẽ 3 tile ngang cho mỗi nhà (48px = 3 tile * 16px)
    for (int i = 0; i < 3; i++) {
        Rectangle src = {
            (float)(col * 48 + i * 16),  // Mỗi tile 16px
            0,                            // Hàng 0 (mái nhà)
            16, 64                         // 16x64
        };
        
        Vector2 sp = WorldToScreen((Vector2){
            worldX + i * TILE_SIZE,
            worldY
        });
        
        Rectangle dst = {
            sp.x,
            sp.y - TILE_SIZE * z * 1.8f,  // Điều chỉnh độ cao
            TILE_SIZE * z,
            TILE_SIZE * z * 2.0f
        };
        
        DrawTexturePro(T.home, src, dst, (Vector2){0,0}, 0, WHITE);
    }
    
    // Vẽ tên nhà phía trên - TĂNG KÍCH THƯỚC FONT
    if (label) {
        Vector2 sp = WorldToScreen((Vector2){
            worldX + TILE_SIZE * 1.5f,
            worldY - TILE_SIZE * 1.5f
        });
        int fontSize = (int)(12 * z);  // Tăng từ 12 lên 16
        int tw = MeasureText(label, fontSize);
        DrawRectangle((int)(sp.x - tw/2 - 6), (int)(sp.y - 40 * z),
                     tw + 12, (int)(24 * z), (Color){0,0,0,200});
        DrawTextCenteredShort(label, (int)sp.x, (int)(sp.y - 38 * z),
                        fontSize, WHITE);
    }
}

// === CẤU TRÚC BUILDING - ĐÃ CĂN CHỈNH LẠI VỊ TRÍ ===
typedef struct {
    int tileX, tileY;      // Vị trí tile gốc
    int width, height;     // Kích thước tính bằng tile
    const char *name;      // Tên hiển thị
    const char *key;       // Phím tắt
    int tileCol;           // Màu sắc trong tileset (0-4)
    void (*onClick)(void); // Hàm xử lý khi click
} Building;

// Hàm xử lý click - THÊM THÔNG BÁO RÕ HƠN
static void OnClickHome(void) {
    G.showInventory = !G.showInventory;
    G.showStore = false;
    G.showBarnUI = false;
    G.showAchievements = false;
    G.showQuest = false;
    strncpy(G.message, "NHÀ CỦA BẠN - Bấm I để mở túi đồ", sizeof(G.message));
    G.msgTimer = 2.5f;
}

static void OnClickStore(void) {
    G.showStore = !G.showStore;
    G.showInventory = false;
    G.showBarnUI = false;
    G.showAchievements = false;
    G.showQuest = false;
    strncpy(G.message, "CỬA HÀNG - Mua hạt giống và vật tư", sizeof(G.message));
    G.msgTimer = 2.5f;
}
static void OnClickStorage(void) {
    G.showInventory = !G.showInventory;
    G.showStore = false;
    G.showBarnUI = false;
    G.showAchievements = false;
    G.showQuest = false;
    strncpy(G.message, "KHO ĐỒ - Kiểm tra vật phẩm của bạn", sizeof(G.message));
    G.msgTimer = 2.5f;
}

static void OnClickQuest(void) {
    G.showQuest = !G.showQuest;
    G.showInventory = false;
    G.showStore = false;
    G.showAchievements = false;
    G.showBarnUI = false;
    strncpy(G.message, "NHIỆM VỤ - Nhận thưởng khi hoàn thành", sizeof(G.message));
    G.msgTimer = 2.5f;
}

static void OnClickGuild(void) {
    G.showAchievements = !G.showAchievements;
    G.showInventory = false;
    G.showStore = false;
    G.showQuest = false;
    G.showBarnUI = false;
    strncpy(G.message, "THÀNH TỰU - Các thành tựu đã đạt được", sizeof(G.message));
    G.msgTimer = 2.5f;
}

static void OnClickBarn(void) {
    G.showBarnUI = !G.showBarnUI;
    G.showInventory = false;
    G.showStore = false;
    G.showAchievements = false;
    G.showQuest = false;
    strncpy(G.message, "QUẢN LÝ CHUỒNG - Mua và chăm sóc động vật", sizeof(G.message));
    G.msgTimer = 2.5f;
}

// === DANH SÁCH NHÀ MỚI - ĐƯA HOME RA GIỮA MAP ===
static Building buildings[] = {
    // Hàng trên - ĐƯA HOME VÀO GIỮA
    {30, 10, 3, 2, "NHÀ", "[I]", 0, OnClickHome},           // HOME ở giữa
    
    // Hàng dưới - Các công trình khác
    {18, 15, 3, 2, "CỬA HÀNG", "[B]", 2, OnClickStore},      // Bên trái
    {24, 15, 3, 2, "KHO ĐỒ", "[I]", 1, OnClickStorage},      // Giữa trái
    {30, 15, 3, 2, "NHIỆM VỤ", "[Q]", 3, OnClickQuest},      // Giữa phải
    {36, 15, 3, 2, "THÀNH TỰU", "[F2]", 4, OnClickGuild},    // Phải
    {42, 15, 3, 2, "CHUỒNG", "[N]", 0, OnClickBarn},         // Xa phải
};
static const int buildingCount = sizeof(buildings) / sizeof(buildings[0]);

// === XỬ LÝ CLICK - KIỂM TRA CHÍNH XÁC HƠN ===
// === XỬ LÝ CLICK - KIỂM TRA CHÍNH XÁC HƠN ===
bool DrawBuilding_HandleClick(Vector2 worldPos)
{
    int tx = WorldToTileX(worldPos.x);
    int ty = WorldToTileY(worldPos.y) +2;
    
    float distToPlayer = Dist(G.player.pos, worldPos);
    if (distToPlayer > PLAYER_REACH * 2.0f) {
        strncpy(G.message, "Đến gần công trình hơn để sử dụng!", sizeof(G.message));
        G.msgTimer = 1.5f;
        return false;
    }
    
    for (int i = 0; i < buildingCount; i++) {
        Building *b = &buildings[i];
        /* Mở rộng vùng click lên trên 2 tile (nhà vẽ cao hơn tile gốc) */
        if (tx >= b->tileX && tx < b->tileX + b->width &&
            ty >= b->tileY - 2 && ty < b->tileY + b->height + 1) {
            
            if (b->onClick) {
                b->onClick();
                G.player.animState = ANIM_DIG;
                G.player.isActing = true;
                G.player.actTimer = 0.3f;
            }
            return true;
        }
    }
    return false;
}

// === VẼ TẤT CẢ NHÀ ===
void DrawBuilding_HomeAll(void)
{
    for (int i = 0; i < buildingCount; i++) {
        Building *b = &buildings[i];
        char label[64];
        snprintf(label, sizeof(label), "%s %s", b->name, b->key);
        DrawHomeFromTileset(b->tileCol, b->tileX, b->tileY, label);
    }
    
    // Vẽ thêm vùng highlight khi hover
    Vector2 mw = ScreenToWorld(GetMousePosition());
    int tx = WorldToTileX(mw.x);
    int ty = WorldToTileY(mw.y);
    
    for (int i = 0; i < buildingCount; i++) {
        Building *b = &buildings[i];
        if (tx >= b->tileX && tx < b->tileX + b->width &&
            ty >= b->tileY && ty < b->tileY + b->height) {
            
            float z = G.camZoom;
            Vector2 sp = WorldToScreen((Vector2){
                (float)(b->tileX * TILE_SIZE),
                (float)(b->tileY * TILE_SIZE)
            });
            
            // Vẽ viền sáng xung quanh building khi hover
            DrawRectangleLinesEx(
                (Rectangle){sp.x, sp.y-80,
                           b->width * TILE_SIZE * z, 
                           b->height * TILE_SIZE * z},
                3.0f * z, (Color){255, 255, 100, 200}
            );
            
            // Vẽ thông báo "Click to use"
            const char *hint = "Click để sử dụng";
            int fontSize = (int)(12 * z);
            int tw = MeasureText(hint, fontSize);
            DrawRectangle((int)(sp.x + (b->width * TILE_SIZE * z)/2 - tw/2 - 4),
                         (int)(sp.y - 30 * z), tw + 8, (int)(20 * z),
                         (Color){0,0,0,200});
            DrawTextCenteredShort(hint, 
                           (int)(sp.x + (b->width * TILE_SIZE * z)/2),
                           (int)(sp.y - 28 * z), fontSize, YELLOW);
            break;
        }
    }
}

// === CÁC HÀM GIỮ NGUYÊN ===
void DrawBuilding_All(void)
{
    DrawBuilding_HomeAll();
}

void DrawBuilding_Home(int mapTileX, int mapTileY, int homeVariant)
{
    DrawHomeFromTileset(homeVariant, mapTileX, mapTileY, NULL);
}