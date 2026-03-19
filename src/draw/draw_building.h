// file: src/draw/draw_building.h
#ifndef DRAW_BUILDING_H
#define DRAW_BUILDING_H

#include "../types.h"
#include "../renderer.h"

// Vẽ các công trình trang trại cố định:
// nhà kho, chuồng trại, hàng rào, cổng, giếng nước
void DrawBuilding_All(void);
void DrawBuilding_Home(int mapTileX, int mapTileY, int homeVariant);
void DrawBuilding_HomeAll(void);

// THÊM HÀM NÀY ĐỂ XỬ LÝ CLICK
bool DrawBuilding_HandleClick(Vector2 worldPos);

// Vẽ một object trang trí từ tileset tại vị trí world
void DrawBuilding_TileObject(int tileCol, int tileRow,
                              int tileSpanW, int tileSpanH,
                              float worldX, float worldY,
                              float scale);

#endif