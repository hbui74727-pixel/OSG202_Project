#ifndef DRAW_DEBUG_H
#define DRAW_DEBUG_H

#include "../types.h"
#include "../renderer.h"

// Bật/tắt toàn bộ debug overlay
extern bool debugMode;

// Vẽ grid tile + tọa độ
void DrawDebug_Grid(void);

// Vẽ hitbox / attack range của player và enemies
void DrawDebug_Hitboxes(void);

// Vẽ thông tin trạng thái từng entity (pos, hp, state)
void DrawDebug_EntityInfo(void);

// Vẽ FPS và thống kê game (entities, crops, day)
void DrawDebug_Stats(void);

// Gọi tất cả (chỉ khi debugMode == true)
void DrawDebug_All(void);

#endif
