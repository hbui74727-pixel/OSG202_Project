#ifndef DRAW_TILE_H
#define DRAW_TILE_H

#include "../types.h"
#include "../renderer.h"

void DrawTile_All(void);   // vẽ toàn bộ bản đồ tile
void DrawTile_Highlight(void); // highlight tile đang hover

int GetDecorTypeForTile(int r, int c); /* public: tra ve decor index (15-18=da, 30-32=cay) */

#endif
