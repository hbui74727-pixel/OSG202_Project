#include "draw_admin_panel.h"

#ifndef KEY_K
#define KEY_K 75
#endif
#ifndef KEY_G
#define KEY_G 71
#endif
#ifndef KEY_GRAVE
#define KEY_GRAVE 96
#endif

void DrawAdminPanel_Badge(void)
{
    if (G.player.role != ROLE_ADMIN) return;

}

void DrawAdminPanel_All(void)
{
    if (G.player.role != ROLE_ADMIN) return;

    int px = 10, py = 74, pw = 200, ph = 200;
    DrawRectangle(px, py, pw, ph, (Color){50, 0, 0, 180});
    DrawRectangleLines(px, py, pw, ph, RED);
    DrawTextCentered("ADMIN PANEL", px + pw / 2, py + 5, 13, RED);

    // Định nghĩa các nút admin
    static const struct {
        const char *label;
        int         key;
    } cmds[] = {
        { "[M] +500 tiền",       KEY_M },
        { "[H] Phục hồi HP",     KEY_H },
        { "[K] Giết quái",       KEY_K },
        { "[F6] Thay đổi thời tiết", KEY_F6 },
        { "[F8] Chế độ bất tử", KEY_F8 },
        { "[P] Di chuyển", KEY_P },

    };
    int n = 6;

    for (int i = 0; i < n; i++) {
        int bx = px + 6;
        int by = py + 24 + i * 28;
        int bw = pw - 12, bh = 22;

        Rectangle btn = { (float)bx, (float)by, (float)bw, (float)bh };
        bool hover = CheckCollisionPointRec(GetMousePosition(), btn);

        DrawRectangleRec(btn, hover ? (Color){150, 30, 30, 220} : (Color){80, 10, 10, 200});
        DrawRectangleLinesEx(btn, 1, (Color){200, 60, 60, 200});
        DrawTextCentered(cmds[i].label, bx + bw / 2, by + 5, 12, WHITE);

        bool clicked = (hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    || IsKeyPressed(cmds[i].key);

        if (clicked) {
            switch (i) {
                case 0: Admin_GiveMoney(500);                         break;
                case 1: Admin_FullHeal();                             break;
                case 2: Admin_FastGrow();                             break;
                case 3: Admin_KillAllEnemies();                       break;
                case 4:
                    for (int s = ITEM_SEED_CARROT; s <= ITEM_SEED_WHEAT; s++)
                        Admin_SpawnItem((ItemType)s, 5);
                    break;
            }
        }
    }
}


