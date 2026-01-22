#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

// Định nghĩa các trạng thái của ô đất
typedef enum {
    GRASS = 0,  // Cỏ dại
    SOIL,       // Đất đã cuốc
    PLANTED,    // Đất đã gieo hạt
    READY       // Cây đã chín, có thể thu hoạch
} TileStatus;

// Cấu trúc một ô đất (Đây là Bước 2.2 quan trọng nhất)
typedef struct {
    Rectangle bounds;   // Vị trí (x, y) và kích thước ô đất
    TileStatus status;  // Trạng thái hiện tại của ô
    float growthTimer;  // Thời gian cây đang lớn (dùng cho Ngày 3)
} Tile;

#endif