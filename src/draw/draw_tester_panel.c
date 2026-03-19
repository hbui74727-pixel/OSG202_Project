#include "draw_tester_panel.h"
#include "../entity_manager.h"
#include "../quest_system.h"
#include "../data_manager.h"

// Định nghĩa các phím tắt
#ifndef KEY_M
#define KEY_M 77
#endif
#ifndef KEY_T
#define KEY_T 84
#endif
#ifndef KEY_L
#define KEY_L 76
#endif
#ifndef KEY_I
#define KEY_I 73
#endif
#ifndef KEY_H
#define KEY_H 72
#endif
#ifndef KEY_F7
#define KEY_F7 0
#endif
#ifndef KEY_F9
#define KEY_F9 0
#endif

// Biến debug mode (khai báo ở nơi khác trong project)
extern bool debugMode;

void DrawTesterPanel_Badge(void)
{
    if (G.player.role != ROLE_TESTER) return;
    
    const char *text = "TESTER MODE";
    int fontSize = 16;
    int textWidth = MeasureText(text, fontSize);
    int padding = 8;
    
    Rectangle bg = {
        SCREEN_W - textWidth - padding * 2 - 10,
        10,
        (float)(textWidth + padding * 2),
        (float)(fontSize + padding)
    };
    
    DrawRectangleRounded(bg, 0.3f, 8, (Color){106, 13, 173, 200});
DrawRectangleLines(bg.x, bg.y, bg.width, bg.height, (Color){170, 85, 255, 255});
    DrawText(text, (int)bg.x + padding, (int)bg.y + padding/2, fontSize, WHITE);
}

void DrawTesterPanel_All(void)
{
    if (G.player.role != ROLE_TESTER) return;

    // Tăng kích thước panel để chứa 7 nút
    int px = 10, py = 74, pw = 220, ph = 280;
    
    // Vẽ nền panel
    DrawRectangle(px, py, pw, ph, (Color){106, 13, 173, 215});
    DrawRectangleLines(px, py, pw, ph, (Color){170, 85, 255, 255});
    DrawTextCentered("TESTER PANEL", px + pw / 2, py + 5, 13, (Color){220, 180, 255, 255});

    // Định nghĩa các nút tester - 7 nút theo yêu cầu
    static const struct {
        const char *label;
        int         key;
    } cmds[] = {
        { "[M] +500 tien",        KEY_M },      // Nút 1: Cộng tiền
        { "[T] Cay chin ngay",    KEY_T },      // Nút 2: Làm chín cây
        { "[L] +500 EXP",         KEY_L },      // Nút 3: Tăng EXP
        { "[I] Nhan vat pham",    KEY_I },      // Nút 4: Nhận vật phẩm
        { "[F7] Sang ngay moi",   KEY_F7 },     // Nút 5: Tua ngày
        { "[F9] Debug",           KEY_F9 },     // Nút 6: Bật/tắt debug
        { "[H] Hoi day mau",      KEY_H },      // Nút 7: Hồi máu
    };
    
    int n = sizeof(cmds) / sizeof(cmds[0]); // = 7

    // Vẽ các nút
    for (int i = 0; i < n; i++) {
        int bx = px + 6;
        int by = py + 24 + i * 28; // Mỗi nút cách nhau 28px
        int bw = pw - 12, bh = 22;

        Rectangle btn = { (float)bx, (float)by, (float)bw, (float)bh };
        bool hover = CheckCollisionPointRec(GetMousePosition(), btn);

        // Màu tím đậm/nhạt khi hover
        DrawRectangleRec(btn, hover ? (Color){140, 50, 200, 220} : (Color){80, 20, 120, 200});
        DrawRectangleLinesEx(btn, 1, (Color){170, 85, 255, 200});
        DrawTextCentered(cmds[i].label, bx + bw / 2, by + 4, 11, WHITE);

        bool clicked = (hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    || IsKeyPressed(cmds[i].key);

        if (clicked) {
            switch (i) {
                case 0: // [M] +500 tien
                    G.player.money += 500;
                    snprintf(G.message, sizeof(G.message), "Tester: +$500");
                    break;
                    
                case 1: // [T] Cay chin ngay
                    for (int j = 0; j < MAX_CROPS; j++) {
                        if (G.crops[j].active) G.crops[j].stage = CSTAGE_READY;
                    }
                    strncpy(G.message, "Tester: Cay da chin!", sizeof(G.message));
                    break;
                    
                case 2: // [L] +500 EXP
                    Level_AddExp(500);
                    snprintf(G.message, sizeof(G.message), "Tester: +500 EXP");
                    break;
                    
                case 3: // [I] Nhan vat pham
                    // Thêm các vật phẩm test
                    if (Inv_Add) { // Kiểm tra hàm Inv_Add có tồn tại không
                        Inv_Add(ITEM_SEED_CARROT, 20);
                        Inv_Add(ITEM_SEED_WHEAT, 20);
                        Inv_Add(ITEM_WOOD, 100);
                        Inv_Add(ITEM_FEED, 20);
                        strncpy(G.message, "Tester: Da nhan vat pham", sizeof(G.message));
                    } else {
                        strncpy(G.message, "Tester: Inventory not available", sizeof(G.message));
                    }
                    break;
                    
                case 4: // [F7] Sang ngay moi
                    G.dayTimer = DAY_DURATION; // Kích hoạt chuyển ngày
                    strncpy(G.message, "Tester: Sang ngay moi", sizeof(G.message));
                    break;
                    
                case 5: // [F9] Debug
                    debugMode = !debugMode;
                    snprintf(G.message, sizeof(G.message), "Tester: Debug %s", debugMode ? "BAT" : "TAT");
                    break;
                    
                case 6: // [H] Hoi day mau
                    G.player.hp = G.player.maxHp;
                    strncpy(G.message, "Tester: Hoi day mau", sizeof(G.message));
                    break;
            }
            G.msgTimer = 1.5f;
        }
    }
    
    // Hiển thị thông tin thêm ở cuối panel
    int infoY = py + ph - 45;
    DrawText(TextFormat("Level: %d", G.player.lvl.level), px + 10, infoY, 12, WHITE);
    DrawText(TextFormat("Exp: %d/%d", G.player.lvl.exp, G.player.lvl.expToNext), px + 10, infoY + 18, 12, WHITE);
}