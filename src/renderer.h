#ifndef RENDERER_H
#define RENDERER_H

#include "types.h"

// Chuyển đổi tọa độ world ↔ screen
Vector2 WorldToScreen(Vector2 world);
Vector2 ScreenToWorld(Vector2 screen);

// Vẽ một frame từ spritesheet theo tọa độ world
void DrawSprite(Texture2D tex, int frame, int frameW, int frameH,
                float worldX, float worldY, float scale,
                Color tint, bool flipX);

// Vẽ một tile từ tileset SunnyWorld (tile 16×16 px)
void DrawTilesetCell(int col, int row, float worldX, float worldY);

// Tiện ích text căn giữa
void DrawTextCentered(const char *text, int cx, int y, int fontSize, Color color);

// Fade màu theo t [0..1]
Color ColorLerp(Color a, Color b, float t);

// Đổi world pos sang tile index
int WorldToTileX(float wx);
int WorldToTileY(float wy);

// Khoảng cách 2 điểm
float Dist(Vector2 a, Vector2 b);

#endif
