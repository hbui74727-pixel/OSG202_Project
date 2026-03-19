#ifndef DRAW_CROP_H
#define DRAW_CROP_H

#include "../types.h"
#include "../renderer.h"

// Vẽ tất cả cây trồng theo stage phát triển
void DrawCrop_All(void);

// Vẽ badge "READY" nhấp nháy trên cây đã chín
void DrawCrop_ReadyBadge(float screenX, float screenY, float zoom);

// Vẽ chấm xanh "đã tưới" trên tile
void DrawCrop_WateredDot(float screenX, float screenY, float zoom);

#endif
