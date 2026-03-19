#include "draw_debug.h"
#include "../font_manager.h"

bool debugMode = false;

// ─────────────────────────────────────────────────────────
void DrawDebug_Grid(void)
{
    float z = G.camZoom;

    int c0 = (int)(G.camX / TILE_SIZE);
    int r0 = (int)(G.camY / TILE_SIZE);
    int c1 = c0 + (int)((float)SCREEN_W  / ((float)TILE_SIZE * z)) + 2;
    int r1 = r0 + (int)((float)SCREEN_H  / ((float)TILE_SIZE * z)) + 2;
    if (c0 < 0) c0 = 0;
    if (r0 < 0) r0 = 0;
    if (c1 > MAP_COLS) c1 = MAP_COLS;
    if (r1 > MAP_ROWS) r1 = MAP_ROWS;

    for (int r = r0; r < r1; r++) {
        for (int c = c0; c < c1; c++) {
            Vector2 sp = WorldToScreen((Vector2){
                (float)(c * TILE_SIZE), (float)(r * TILE_SIZE)
            });
            float tw = (float)TILE_SIZE * z;

            DrawRectangleLines((int)sp.x, (int)sp.y,
                               (int)tw, (int)tw,
                               (Color){60, 60, 60, 80});

            // Tọa độ tile nhỏ
            DrawTextCenteredShort(TextFormat("%d,%d", c, r),
                     (int)(sp.x + 2), (int)(sp.y + 2),
                     (int)(7.0f * z),
                     (Color){120, 120, 120, 100});

            // Màu tile type
            TileType tt = G.map[r][c].type;
            if (tt == TILE_SOIL_DUG || tt == TILE_SOIL_WET) {
                DrawRectangle((int)sp.x, (int)sp.y,
                              (int)tw, (int)tw,
                              (Color){120, 80, 20, 30});
            }
        }
    }
}

// ─────────────────────────────────────────────────────────
void DrawDebug_Hitboxes(void)
{
    float z = G.camZoom;

    // Player hitbox + reach circle
    Vector2 psp = WorldToScreen(G.player.pos);
    DrawCircle((int)psp.x, (int)psp.y,
                    (int)(20.0f * z), GREEN);
    DrawCircle((int)psp.x, (int)psp.y,
                    (int)(PLAYER_REACH * z), (Color){0, 255, 0, 60});

    // Enemy hitboxes + attack range
    for (int i = 0; i < MAX_ENEMIES; i++) {
        Enemy *e = &G.enemies[i];
        if (!e->active) continue;
        Vector2 esp = WorldToScreen(e->pos);
        DrawCircle((int)esp.x, (int)esp.y,
                        (int)(22.0f * z), RED);
        DrawCircle((int)esp.x, (int)esp.y,
                        (int)(ATTACK_RANGE * z), (Color){255, 0, 0, 50});
    }

    // Animal collect range
    for (int i = 0; i < G.animalCount; i++) {
        Animal *a = &G.animals[i];
        if (!a->active) continue;
        Vector2 asp = WorldToScreen(a->pos);
        DrawCircle((int)asp.x, (int)asp.y,
                        (int)(TILE_SIZE * 1.8f * z), (Color){255, 255, 0, 60});
    }
}

// ─────────────────────────────────────────────────────────
void DrawDebug_EntityInfo(void)
{
    float z = G.camZoom;

    // Enemies: vị trí + HP + state
    static const char *stateNames[] = { "Di chuyển", "Tấn công", "Bị thương", "Chết" };
    for (int i = 0; i < MAX_ENEMIES; i++) {
        Enemy *e = &G.enemies[i];
        if (!e->active) continue;
        Vector2 sp = WorldToScreen(e->pos);
        DrawTextCenteredShort(
            TextFormat("hp:%d st:%s", e->hp, stateNames[e->state]),
            (int)(sp.x - 28), (int)(sp.y - 52.0f * z),
            (int)(9.0f * z),
            (Color){255, 150, 150, 220}
        );
    }

    // Crops: stage + watered
    for (int i = 0; i < MAX_CROPS; i++) {
        Crop *c = &G.crops[i];
        if (!c->active) continue;
        float wx = (c->tileX + 0.5f) * TILE_SIZE;
        float wy = (c->tileY + 0.5f) * TILE_SIZE;
        Vector2 sp = WorldToScreen((Vector2){wx, wy});
        DrawTextCenteredShort(
            TextFormat("s%d%s", c->stage, c->stage==CSTAGE_WATERED?"~":""),
            (int)(sp.x - 8), (int)(sp.y - 36.0f * z),
            (int)(8.0f * z),
            (Color){150, 255, 150, 200}
        );
    }
}

// ─────────────────────────────────────────────────────────
void DrawDebug_Stats(void)
{
    // Nền panel nhỏ góc trên trái
    int px = 4, py = 54, pw = 260, ph = 110;
    DrawRectangle(px, py, pw, ph, (Color){0, 0, 0, 160});
    DrawRectangleLines(px, py, pw, ph, RED);

    DrawTextCenteredShort("=== DEBUG ===", px + 6, py + 4, 12, RED);

    Player *p = &G.player;
    DrawTextCenteredShort(TextFormat("FPS:      %d",     GetFPS()),        px+6, py+20, 11, WHITE);
    DrawTextCenteredShort(TextFormat("Pos:      %.0f,%.0f", p->pos.x, p->pos.y), px+6, py+33, 11, WHITE);
    DrawTextCenteredShort(TextFormat("Cam:      %.0f,%.0f z=%.2f", G.camX, G.camY, G.camZoom), px+6, py+46, 11, WHITE);
    DrawTextCenteredShort(TextFormat("Cây:    %d / %d", G.cropCount, MAX_CROPS),    px+6, py+59, 11, WHITE);
    DrawTextCenteredShort(TextFormat("Kẻ thù:  %d / %d", G.enemyCount, MAX_ENEMIES), px+6, py+72, 11, WHITE);
    DrawTextCenteredShort(TextFormat("Ngày:      %d  timer=%.0f", G.day, G.dayTimer),  px+6, py+85, 11, WHITE);
    DrawTextCenteredShort(TextFormat("Tiền:    $%d", p->money),                       px+6, py+98, 11, GOLD);

    // Tile hover info
    Vector2 mw = ScreenToWorld(GetMousePosition());
    int tx = WorldToTileX(mw.x), ty = WorldToTileY(mw.y);
    if (tx >= 0 && tx < MAP_COLS && ty >= 0 && ty < MAP_ROWS) {
        Tile *t = &G.map[ty][tx];
        static const char *tNames[] = {"Cỏ","Đất khô","Đất ẩm","Đường","Nước","Đá"};
        DrawTextCenteredShort(
            TextFormat("Tile [%d,%d] type=%s cropIdx=%d",
                       tx, ty, tNames[t->type], t->cropIdx),
            px + 6, py + 111, 10, (Color){0, 255, 255, 255}
        );
    }
}

// ─────────────────────────────────────────────────────────
void DrawDebug_All(void)
{
    if (!debugMode) return;
    DrawDebug_Grid();
    DrawDebug_Hitboxes();
    DrawDebug_EntityInfo();
    DrawDebug_Stats();
}
