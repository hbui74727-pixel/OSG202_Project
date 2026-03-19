#include "renderer.h"
#include "font_manager.h"

Vector2 WorldToScreen(Vector2 world)
{
    return (Vector2){
        (world.x - G.camX) * G.camZoom,
        (world.y - G.camY) * G.camZoom
    };
}

Vector2 ScreenToWorld(Vector2 screen)
{
    return (Vector2){
        screen.x / G.camZoom + G.camX,
        screen.y / G.camZoom + G.camY
    };
}

// Vẽ một frame từ horizontal spritesheet tại tọa độ world (căn giữa ngang)
void DrawSprite(Texture2D tex, int frame, int frameW, int frameH,
                float worldX, float worldY, float scale,
                Color tint, bool flipX)
{
    if (tex.width == 0) return;

    int totalFrames = tex.width / frameW;
    if (totalFrames < 1) totalFrames = 1;
    frame = frame % totalFrames;

    float srcW = (float)(flipX ? -frameW : frameW);
    Rectangle src = { (float)(frame * frameW), 0.0f, srcW, (float)frameH };

    float dw = frameW  * scale * G.camZoom;
    float dh = frameH  * scale * G.camZoom;

    Vector2 sp = WorldToScreen((Vector2){ worldX, worldY });
    Rectangle dst = { sp.x - dw * 0.5f, sp.y - dh * 0.75f, dw, dh };

    DrawTexturePro(tex, src, dst, (Vector2){0,0}, 0.0f, tint);
}

// Tileset SunnyWorld: mỗi cell 16×16 px, 64 cột
#define TS_CELL   16
void DrawTilesetCell(int col, int row, float worldX, float worldY)
{
    Rectangle src = { (float)(col * TS_CELL), (float)(row * TS_CELL),
                      (float)TS_CELL, (float)TS_CELL };
    Vector2 sp = WorldToScreen((Vector2){ worldX, worldY });
    float   z  = G.camZoom;
    Rectangle dst = { sp.x, sp.y, (float)TILE_SIZE * z, (float)TILE_SIZE * z };
    DrawTexturePro(T.tileset, src, dst, (Vector2){0,0}, 0.0f, WHITE);
}

void DrawTextCentered(const char *text, int cx, int y, int fontSize, Color color)
{
    DrawTextCenteredShort(text, cx, y, fontSize, color);
}

// Color ColorLerp(Color a, Color b, float t)
// {
//     return (Color){
//         (unsigned char)(a.r + (b.r - a.r) * t),
//         (unsigned char)(a.g + (b.g - a.g) * t),
//         (unsigned char)(a.b + (b.b - a.b) * t),
//         255
//     };
// }
int WorldToTileX(float wx)
{
    return (int)(wx / TILE_SIZE);
}

int WorldToTileY(float wy)
{
    return (int)(wy / TILE_SIZE);
}

float Dist(Vector2 a, Vector2 b)
{
    float dx = a.x - b.x, dy = a.y - b.y;
    return sqrtf(dx * dx + dy * dy);
}
