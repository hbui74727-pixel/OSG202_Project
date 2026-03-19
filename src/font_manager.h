#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "raylib.h"
#include "types.h"

extern Font gameFont;

// Khởi tạo và giải phóng font
void Font_Load(void);
void Font_Unload(void);

// Text cố định trên màn hình (UI) - KHÔNG ZOOM
void DrawTextShort(const char *text, int posX, int posY, int fontSize, Color color);
void DrawTextCenteredShort(const char *text, int centerX, int y, int fontSize, Color color);

// Text trong game world - CÓ ZOOM (tọa độ world)
void DrawTextZoom(const char *text, float worldX, float worldY, int baseFontSize, Color color);
void DrawTextCenteredZoom(const char *text, float worldX, float worldY, int baseFontSize, Color color);

// Text có outline (nổi bật)
void DrawTextWithOutline(const char *text, int posX, int posY, int fontSize, Color textColor, Color outlineColor);
void DrawTextCenteredWithOutline(const char *text, int centerX, int y, int fontSize, Color textColor, Color outlineColor);

// Hàm tiện ích
int MeasureTextShort(const char *text, int fontSize);

#endif