#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>

#define MAP_SIZE 5
#define TILE_SIZE 80
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 500

// Giữ nguyên logic trạng thái từ các ngày trước
typedef enum { GRASS, TILLED, PLANTED, GROWN } TileState;

typedef struct {
    TileState state;
    float growTime;
} Tile;

int main() {
    // 1. Khởi tạo cửa sổ đồ họa
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "FARM GAME - NGAY 5 GRAPHICS");
    SetTargetFPS(60);

    // Khởi tạo dữ liệu game
    Tile map[MAP_SIZE][MAP_SIZE] = {0};
    int pX = 2, pY = 2; // Vị trí Player
    int money = 1000;
    int day = 1;

    while (!WindowShouldClose()) {
        // --- XỬ LÝ LOGIC (UPDATE) ---
        
        // Di chuyển bằng phím W-A-S-D (Ngày 5 logic)
        if (IsKeyPressed(KEY_W) && pY > 0) pY--;
        if (IsKeyPressed(KEY_S) && pY < MAP_SIZE - 1) pY++;
        if (IsKeyPressed(KEY_A) && pX > 0) pX--;
        if (IsKeyPressed(KEY_D) && pX < MAP_SIZE - 1) pX++;

        // Tương tác chuột (Click để cuốc đất/trồng cây)
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();
            int x = mouse.x / TILE_SIZE;
            int y = mouse.y / TILE_SIZE;

            if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) {
                Tile *t = &map[y][x];
                if (t->state == GRASS) t->state = TILLED;
                else if (t->state == TILLED) {
                    t->state = PLANTED;
                    t->growTime = 0;
                }
            }
        }

        // Cập nhật thời gian cây lớn (Thay thế hàm Sleep)
        for (int i = 0; i < MAP_SIZE; i++) {
            for (int j = 0; j < MAP_SIZE; j++) {
                if (map[i][j].state == PLANTED) {
                    map[i][j].growTime += GetFrameTime();
                    if (map[i][j].growTime >= 5.0f) map[i][j].state = GROWN;
                }
            }
        }

        // --- VẼ GIAO DIỆN (DRAW) ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Vẽ bản đồ ô vuông (Texture màu)
        for (int i = 0; i < MAP_SIZE; i++) {
            for (int j = 0; j < MAP_SIZE; j++) {
                Color tileColor = GREEN;
                if (map[i][j].state == TILLED) tileColor = BROWN;
                if (map[i][j].state == PLANTED) tileColor = DARKGREEN;
                if (map[i][j].state == GROWN) tileColor = GOLD;

                DrawRectangle(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE - 2, TILE_SIZE - 2, tileColor);
                
                // Vẽ thanh tiến trình nhỏ nếu đang lớn (Sleep trực quan)
                if (map[i][j].state == PLANTED) {
                    float prog = map[i][j].growTime / 5.0f;
                    DrawRectangle(j * TILE_SIZE + 10, i * TILE_SIZE + 65, (TILE_SIZE - 20) * prog, 5, WHITE);
                }
            }
        }
// Vẽ Player 'P' (Hình tròn đại diện)
        DrawCircle(pX * TILE_SIZE + TILE_SIZE/2, pY * TILE_SIZE + TILE_SIZE/2, 20, BLUE);
        DrawText("P", pX * TILE_SIZE + 32, pY * TILE_SIZE + 25, 30, WHITE);

        // Vẽ Menu thông tin bên phải
        DrawText(TextFormat("NGAY: %d", day), 420, 20, 20, BLACK);
        DrawText(TextFormat("TIEN: %d $", money), 420, 50, 20, GREEN);
        DrawText("W-A-S-D: Di chuyen", 420, 150, 15, DARKGRAY);
        DrawText("CHUOT: Tuong tac", 420, 180, 15, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

//day la comment cua thao
