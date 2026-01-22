#include "raylib.h"
#include <stdio.h>

#define MAP_SIZE 5
#define TILE_SIZE 80

typedef enum {
    GRASS,
    TILLED,
    PLANTED,
    GROWN
} TileState;

typedef struct {
    TileState state;
    float growTime; // thời gian cây đã lớn
} Tile;

int main() {
    InitWindow(500, 500, "Farm Game - C Demo");
    SetTargetFPS(60);

    Tile map[MAP_SIZE][MAP_SIZE] = {0};
    int money = 0;

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int x = mouse.x / TILE_SIZE;
            int y = mouse.y / TILE_SIZE;

            if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) {
                Tile *t = &map[y][x];

                if (t->state == GRASS) {
                    t->state = TILLED;
                }
                else if (t->state == TILLED) {
                    t->state = PLANTED;
                    t->growTime = 0;
                }
                else if (t->state == GROWN) {
                    t->state = GRASS;
                    money += 10; // bán nông sản
                }
            }
        }

        // Cây lớn theo thời gian
        for (int i = 0; i < MAP_SIZE; i++) {
            for (int j = 0; j < MAP_SIZE; j++) {
                Tile *t = &map[i][j];
                if (t->state == PLANTED) {
                    t->growTime += GetFrameTime();
                    if (t->growTime >= 5.0f) {
                        t->state = GROWN;
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < MAP_SIZE; i++) {
            for (int j = 0; j < MAP_SIZE; j++) {
                Color color;
                switch (map[i][j].state) {
                    case GRASS:   color = GREEN; break;
                    case TILLED:  color = BROWN; break;
                    case PLANTED: color = DARKGREEN; break;
                    case GROWN:   color = GOLD; break;
                }

                DrawRectangle(
                    j * TILE_SIZE,
                    i * TILE_SIZE,
                    TILE_SIZE - 2,
                    TILE_SIZE - 2,
                    color
                );
            }
        }

        DrawText(TextFormat("Money: %d", money), 10, 420, 20, BLACK);
        DrawText("Click: Dao -> Trong -> Thu hoach", 10, 450, 18, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
