#ifndef DRAW_ADMIN_PANEL_H
#define DRAW_ADMIN_PANEL_H

#include "../types.h"
#include "../renderer.h"
#include "../admin_commands.h"

// Vẽ panel Admin (chỉ hiện khi role == ROLE_ADMIN)
// Panel liệt kê các lệnh admin có thể bấm trực tiếp
void DrawAdminPanel_All(void);

// Badge "ADMIN MODE" nhỏ ở góc trên trái
void DrawAdminPanel_Badge(void);

#endif
