#ifndef STRUCTS_H
#define STRUCTS_H

// 1. Quản lý Thời gian (Ngày 2)
typedef struct {
    int hour;
    int day;
    int season; 
} GameTime;

// 2. Quản lý Ô đất và Cây trồng (Ngày 2)
typedef struct {
    int plant_type;   // 0: Trống, 1: Lúa, 2: Ngô...
    int growth_stage; // 0-3
    int water_level;
} Tile;

// 3. Quản lý Người chơi (Ngày 2)
typedef struct {
    char name[50];
    long money;
} Player;

// 4. GameState tổng quản lý (Ngày 2)
typedef struct {
    Player player;
    GameTime time;
    Tile map[5][5]; // Bản đồ 5x5
} GameState;

#endif