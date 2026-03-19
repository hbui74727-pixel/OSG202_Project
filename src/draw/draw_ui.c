#include "draw_ui.h"
#include "../data_manager.h"
#include "../entity_manager.h"
#include "../quest_system.h"
#include "../achievement_system.h"
#include "../account_manager.h"
#include "../font_manager.h"
<<<<<<< HEAD

=======
#include "../game_logic.h"
#include "../admin_commands.h"
#include "../audio_manager.h"
#include "types.h" 
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
#define PBGC (Color){18, 22, 36, 218}
#define PEDGC (Color){70, 95, 160, 255}

/* ── Helper: nút bấm trả về true nếu được click ── */
static bool Button(int x, int y, int w, int h, const char *label, Color bg, Color hoverBg)
{
    Rectangle r = {(float)x, (float)y, (float)w, (float)h};
    bool hov = CheckCollisionPointRec(GetMousePosition(), r);
    DrawRectangleRec(r, hov ? hoverBg : bg);
    DrawRectangleLinesEx(r, 1, hov ? (Color){255, 220, 50, 255} : PEDGC);
    DrawTextCenteredShort(label, x + w / 2, y + (h - 16) / 2, 16, WHITE);
    return hov && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

/* ── Field nhập liệu ── */
static void DrawInputField(int x, int y, int w, int h, const char *label,
                           const char *value, bool active, bool password)
{
    DrawTextShort(label, x, y - 20, 16, LIGHTGRAY);
    DrawRectangle(x, y, w, h, active ? (Color){30, 40, 60, 240} : (Color){20, 25, 40, 220});
    DrawRectangleLines(x, y, w, h, active ? GOLD : PEDGC);
    /* Hiển thị *** nếu password */
    char display[MAX_PASS_LEN + 1] = {0};
    if (password)
    {
        for (int i = 0; i < (int)strlen(value); i++)
            display[i] = '*';
    }
    else
        strncpy(display, value, sizeof(display) - 1);
    DrawTextShort(display, x + 8, y + h / 2 - 10, 18, WHITE);
    if (active && (int)(GetTime() * 2) % 2 == 0)
    {
        int cw = MeasureTextShort(display, 18);
        DrawRectangle(x + 8 + cw, y + h / 2 - 9, 2, 18, (Color){255, 255, 255, 220});
    }
}

/* ── LOGIN / REGISTER screens ── */
void DrawUI_LoginScreen(void)
{
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    float scaleX = (float)sw / T.loginBg.width;
    float scaleY = (float)sh / T.loginBg.height;
    float scale = scaleX > scaleY ? scaleX : scaleY;

    float w = T.loginBg.width * scale;
    float h = T.loginBg.height * scale;

    float x = (sw - w) * 0.5f;
    float y = (sh - h) * 0.5f;

    DrawTextureEx(T.loginBg, (Vector2){x, y}, 0, scale, WHITE);

    // overlay tối giúp text dễ đọc
    DrawRectangle(0, 0, sw, sh, (Color){0, 0, 0, 120});

    /* Background gradient */
    DrawRectangleGradientV(0, 0, SCREEN_W, SCREEN_H, (Color){20, 40, 80, 80}, (Color){10, 20, 40, 80});

    /* Logo */
    DrawTextCenteredShort("SUNNY WORLD", SCREEN_W / 2 + 3, 103, 64, (Color){180, 130, 0, 255});
    DrawTextCenteredShort("SUNNY WORLD", SCREEN_W / 2, 100, 64, GOLD);
<<<<<<< HEAD
    DrawTextCenteredShort("Farm Simulator", SCREEN_W / 2, 170, 28, (Color){220, 200, 120, 200});
=======
    DrawTextCenteredShort("Cóc Không Biết Code Team", SCREEN_W / 2, 170, 28, (Color){220, 200, 120, 200});
    
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
    /* Panel */
    int pw = 380, ph = 320, px = SCREEN_W / 2 - pw / 2, py = SCREEN_H / 2 - ph / 2 + 20;
    DrawRectangle(px, py, pw, ph, PBGC);
    DrawRectangleLines(px, py, pw, ph, PEDGC);
    DrawTextCenteredShort("ĐĂNG NHẬP", px + pw / 2, py + 12, 22, GOLD);
<<<<<<< HEAD
=======
    
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
    int fx = px + 24, fw = pw - 48;
    DrawInputField(fx, py + 52, fw, 36, "Tên đăng nhập:", G.loginUser, G.loginField == 0, false);
    DrawInputField(fx, py + 120, fw, 36, "Mật khẩu:", G.loginPass, G.loginField == 1, true);

    /* Hint */
    DrawTextShort("Tab: chuyển ô  |  Enter: đăng nhập", fx, py + 170, 14, (Color){140, 140, 140, 200});

    /* Click chọn field */
    Rectangle r0 = {(float)fx, (float)(py + 52), (float)fw, 36};
    Rectangle r1 = {(float)fx, (float)(py + 120), (float)fw, 36};
    if (CheckCollisionPointRec(GetMousePosition(), r0) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        G.loginField = 0;
    if (CheckCollisionPointRec(GetMousePosition(), r1) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        G.loginField = 1;

    /* Nút Đăng nhập */
    if (Button(fx, py + 192, fw, 40, "ĐĂNG NHẬP", (Color){40, 100, 50, 255}, (Color){60, 150, 70, 255}))
    {
        Account_Login(G.loginUser, G.loginPass, G.loginError);
        if (G.loginError[0] == '\0')
            G.screen = SCR_GAME;
    }
<<<<<<< HEAD
    if (G.loginError[0])
        DrawTextCenteredShort(G.loginError, px + pw / 2, py + 240, 12, RED);

    /* Nút chuyển sang đăng ký */
    if (Button(fx, py + 248, fw, 34, "TẠO TÀI KHOẢN MỚI", (Color){30, 50, 100, 255}, (Color){50, 80, 140, 255}))
=======
    
    /* THÔNG BÁO LỖI - ĐẶT DƯỚI NÚT ĐĂNG NHẬP */
    if (G.loginError[0])
    {
        int errorY = py + 242;  // Giữ nguyên vị trí cũ nhưng đảm bảo không bị che
        DrawTextCenteredShort(G.loginError, px + pw / 2, errorY, 14, RED);
    }

    /* Nút chuyển sang đăng ký */
    if (Button(fx, py + 260, fw, 34, "TẠO TÀI KHOẢN MỚI", (Color){30, 50, 100, 255}, (Color){50, 80, 140, 255}))
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
        G.screen = SCR_REGISTER;
}

void DrawUI_RegisterScreen(void)
{
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    float scaleX = (float)sw / T.loginBg.width;
    float scaleY = (float)sh / T.loginBg.height;
    float scale = scaleX > scaleY ? scaleX : scaleY;

    DrawTextureEx(T.loginBg, (Vector2){0, 0}, 0, scale, WHITE);

    DrawRectangle(0, 0, sw, sh, (Color){0, 0, 0, 120});

    DrawRectangleGradientV(0, 0, SCREEN_W, SCREEN_H, (Color){20, 40, 80, 80}, (Color){10, 20, 40, 80});
<<<<<<< HEAD
    DrawTextCenteredShort("SUNNY WORLD", SCREEN_W / 2, 60, 40, GOLD);

    int pw = 400, ph = 420;
    int px = SCREEN_W / 2 - pw / 2;
    int py = SCREEN_H / 2 - ph / 2 + 20;
    DrawRectangle(px, py, pw, ph, PBGC);
    DrawRectangleLines(px, py, pw, ph, PEDGC);
    DrawTextCenteredShort("TẠO TÀI KHOẢN", px + pw / 2, py + 12, 22, GOLD);
    int fx = px + 24, fw = pw - 48;
    DrawInputField(fx, py + 46, fw, 34, "Tên đăng nhập (>=3 ký tự):", G.regUser, G.regField == 0, false);
=======
    DrawTextCenteredShort("SUNNY WORLD", SCREEN_W / 2 + 3, 103, 64, (Color){180, 130, 0, 255});
    DrawTextCenteredShort("SUNNY WORLD", SCREEN_W / 2, 100, 64, GOLD);

    int pw = 400, ph = 420;
    int px = SCREEN_W / 2 - pw / 2;
    int py = SCREEN_H / 2 - ph / 2 + 40;
    DrawRectangle(px, py, pw, ph, PBGC);
    DrawRectangleLines(px, py, pw, ph, PEDGC);
    DrawTextCenteredShort("TẠO TÀI KHOẢN", px + pw / 2, py + 10, 22, GOLD);
    
    int fx = px + 24, fw = pw - 48;
    py = py  + 10;
    DrawInputField(fx, py + 40, fw, 34, "Tên đăng nhập (>=3 ký tự):", G.regUser, G.regField == 0, false);
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
    DrawInputField(fx, py + 104, fw, 34, "Mật khẩu (>=4 ký tự):", G.regPass, G.regField == 1, true);
    DrawInputField(fx, py + 162, fw, 34, "Xác nhận mật khẩu:", G.regPass2, G.regField == 2, true);

    /* Click chọn field */
    for (int i = 0; i < 3; i++)
    {
        int fy = py + 46 + i * 58;
        Rectangle rf = {(float)fx, (float)fy, (float)fw, 34};
        if (CheckCollisionPointRec(GetMousePosition(), rf) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            G.regField = i;
    }

    /* Chọn role */
    DrawTextShort("Loại tài khoản:", fx, py + 210, 16, LIGHTGRAY);
    static const char *roleLabels[] = {"Player", "Tester"};
    for (int i = 0; i < 2; i++)
    {
        bool sel = (G.regRole == (PlayerRole)i);
        int bx = fx + i * 120;
        Rectangle rb = {(float)bx, (float)(py + 228), (float)110, 30};
        bool hov = CheckCollisionPointRec(GetMousePosition(), rb);
        DrawRectangleRec(rb, sel ? (Color){50, 120, 50, 255} : hov ? (Color){40, 70, 40, 200}
                                                                   : (Color){25, 40, 25, 200});
        DrawRectangleLines((int)rb.x, (int)rb.y, (int)rb.width, (int)rb.height, sel ? GREEN : DARKGRAY);
        DrawTextCenteredShort(roleLabels[i], bx + 55, py + 236, 16, WHITE);
        if (hov && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            G.regRole = (PlayerRole)i;
    }

<<<<<<< HEAD
    DrawTextShort("Tab: chuyển ô  |  Enter: tạo tài khoản", fx, py + 268, 14, (Color){130, 130, 130, 200});
=======
    DrawTextShort("Tab: chuyển ô  |  Enter: tạo tài khoản", fx, py + 265, 14, (Color){130, 130, 130, 200});
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc

    if (Button(fx, py + 280, fw, 40, "TẠO TÀI KHOẢN", (Color){40, 100, 50, 255}, (Color){60, 150, 70, 255}))
    {
        if (strcmp(G.regPass, G.regPass2) != 0)
        {
            strcpy(G.regError, "Mật khẩu xác nhận không khớp!");
        }
        else if (Account_Register(G.regUser, G.regPass, G.regRole, G.regError))
        {
            G.screen = SCR_LOGIN;
            strncpy(G.loginUser, G.regUser, MAX_NAME_LEN - 1);
            strncpy(G.loginError, "Đăng ký thành công! Hãy đăng nhập.", sizeof(G.loginError) - 1);
        }
    }
<<<<<<< HEAD
    if (G.regError[0])
        DrawTextCenteredShort(G.regError, px + pw / 2, py + 334, 12, RED);
=======
    
    /* THÔNG BÁO LỖI - ĐẶT GIỮA NÚT TẠO TÀI KHOẢN VÀ NÚT QUAY LẠI */
    if (G.regError[0])
    {
        int errorY = py + 325;  // Điều chỉnh vị trí
        DrawTextCenteredShort(G.regError, px + pw / 2, errorY, 14, RED);
    }
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc

    if (Button(fx, py + 342, fw, 34, "QUAY LẠI ĐĂNG NHẬP", (Color){30, 30, 60, 255}, (Color){50, 50, 100, 255}))
        G.screen = SCR_LOGIN;
}

/* ── SIDE PANEL ── */
void DrawUI_SidePanel(void)
{
<<<<<<< HEAD
    int pw = 160, ph = 390, px = SCREEN_W - pw - 4, py = 58;
    DrawRectangle(px, py, pw, ph, PBGC);
    DrawRectangleLines(px, py, pw, ph, PEDGC);
    /* Tiêu đề căn giữa */
    DrawTextCenteredShort("MENU", px + pw / 2, py + 8, 20, GOLD);
    DrawRectangle(px + 6, py + 28, pw - 12, 1, PEDGC);

    struct
    {
        const char *lbl;
    } btns[] = {
        {"[I] Túi đồ"}, {"[B] Cửa hàng"}, {"[N] Chuồng"}, {"[Q] Nhiệm vụ"}, {"[F2] Thàn Tựu"}, {"[C] Trợ giúp"}, {"[F5] Lưu"}, {"Đăng xuất"}};
    int nb = 8;
    for (int i = 0; i < nb; i++)
    {
        int bx = px + 6, by = py + 34 + i * 42, bw = pw - 12, bh = 36;
        if (by + bh > py + ph - 24)
            break;
        if (Button(bx, by, bw, bh, btns[i].lbl, (Color){28, 40, 28, 210}, (Color){50, 90, 50, 230}))
        {
            switch (i)
            {
            case 0:
                G.showInventory = !G.showInventory;
                G.showStore = false;
                G.showBarnUI = false;
                G.showAchievements = false;
                break;
            case 1:
                G.showStore = !G.showStore;
                G.showInventory = false;
                G.showBarnUI = false;
                G.showAchievements = false;
                break;
            case 2:
                G.showBarnUI = !G.showBarnUI;
                G.showInventory = false;
                G.showStore = false;
                G.showAchievements = false;
                break;
            case 3:
                G.showQuest = !G.showQuest;
                break;
            case 4:
                G.showAchievements = !G.showAchievements;
                G.showInventory = false;
                G.showStore = false;
                break;
            case 5:
                G.showHelp = !G.showHelp;
                break;
            case 6:
            {
                char sp[128];
                snprintf(sp, sizeof(sp), "saves/%s.dat", G.player.username);
                Game_SavePlayer(sp);
                strncpy(G.message, "Đã lưu!", sizeof(G.message));
                G.msgTimer = 2.0f;
                break;
            }
            case 7:
                Account_Logout();
                break;
            }
        }
    }
    /* Role badge */
    const char *rs = (G.player.role == ROLE_ADMIN) ? "ADMIN" : (G.player.role == ROLE_TESTER) ? "TESTER"
                                                                                              : "PLAYER";
    Color rc = (G.player.role == ROLE_ADMIN) ? RED : (G.player.role == ROLE_TESTER) ? ORANGE
                                                                                    : SKYBLUE;
    DrawTextCenteredShort(rs, px + pw / 2, py + ph - 18, 16, rc);
}

/* ── QUEST PANEL ── */
void DrawUI_QuestPanel(void)
{
    if (!G.showQuest)
        return;
    int pw = 250, ph = 190;
    int px = SCREEN_W / 2 - pw / 2;
    int py = SCREEN_H / 2 - ph / 2;
    DrawRectangle(px, py, pw, ph, PBGC);
    DrawRectangleLines(px, py, pw, ph, PEDGC);
    DrawTextCenteredShort("NHIỆM VỤ", px + pw / 2, py + 6, 20, GOLD);
    for (int i = 0; i < MAX_QUESTS; i++)
    {
        Quest *q = &G.quests[i];
        Color col = q->done ? GREEN : WHITE;
        DrawTextShort(TextFormat("%s %s", q->done ? "[v]" : "[ ]", q->desc), px + 8, py + 26 + i * 30, 13, col);
        DrawTextCenteredShort(TextFormat("%d/%d", q->progress, q->target), px + pw - 30, py + 26 + i * 30, 13, YELLOW);
    }
=======
    static int activeTab   = -1;
    static int subScroll   = 0;   /* scroll offset cho sub-menu */

    int pw = 190, px = SCREEN_W - pw - 4, py = 68;

    bool isAdmin  = (G.player.role == ROLE_ADMIN);
    bool isTester = (G.player.role == ROLE_TESTER);

    typedef struct { const char *name; Color col; int count; } TabDef;
    static const TabDef tabs[5] = {
        { "TRANG TRẠI", {50, 160,  50, 255}, 3 },
        { "XÃ HỘI",     {50, 100, 180, 255}, 3 },
        { "HỆ THỐNG",   {150, 110, 20, 255}, 3 },
        { "TESTER",     {200, 110,  0, 255}, 4 },
        { "ADMIN",      {200,  30,  30, 255}, 10 },
    };
    int nTabs = isAdmin ? 5 : isTester ? 4 : 3;

    int tabH = 48, tabGap = 5;
    int subItemH = 38, subGap = 3;

    /* Giới hạn chiều cao để không che minimap (mmY = SCREEN_H-170) */
    int maxPH = SCREEN_H - 170 - py - 6;

    int rawSubH = (activeTab >= 0 && activeTab < nTabs)
        ? tabs[activeTab].count * (subItemH + subGap) + 14
        : 0;
    int tabsH   = 10 + nTabs * (tabH + tabGap);
    /* Chiều cao phần sub thực sự hiển thị */
    int visSubH = rawSubH;
    if (tabsH + visSubH + 26 > maxPH)
        visSubH = maxPH - tabsH - 26;
    if (visSubH < 0) visSubH = 0;

    int ph = tabsH + (visSubH > 0 ? visSubH + 4 : 0) + 26;

    DrawRectangle(px, py, pw, ph, (Color){14, 18, 32, 240});
    DrawRectangleLines(px, py, pw, ph, (Color){60, 80, 140, 255});

    /* ── Tabs ── */
    int ty = py + 10;
    for (int t = 0; t < nTabs; t++) {
        bool active = (activeTab == t);
        Rectangle tr = {(float)(px+4),(float)ty,(float)(pw-8),(float)tabH};
        bool hov = CheckCollisionPointRec(GetMousePosition(), tr);

        Color col = tabs[t].col;
        Color bg  = active ? col
                  : hov    ? (Color){col.r/2+15, col.g/2+15, col.b/2+15, 230}
                           : (Color){22, 28, 44, 215};
        Color edge = active ? (Color){255,220,80,255}
                            : (Color){col.r/2, col.g/2, col.b/2, 200};

        DrawRectangleRec(tr, bg);
        DrawRectangleLinesEx(tr, 1.5f, edge);
        if (active) DrawRectangle(px+4, ty, 4, tabH, (Color){255,220,80,255});

        DrawTextCenteredShort(tabs[t].name, px+pw/2, ty+(tabH-16)/2, 16,
                              active ? WHITE : (Color){200,200,200,230});
        DrawTextShort(active?"v":">", px+pw-18, ty+(tabH-14)/2, 14,
                      active ? GOLD : (Color){140,140,140,200});

        if (hov && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (activeTab == t) { activeTab = -1; }
            else { activeTab = t; subScroll = 0; }
        }
        ty += tabH + tabGap;
    }

    /* ── Sub-menu với scissor + scroll ── */
    if (activeTab >= 0 && activeTab < nTabs && visSubH > 0) {
        int subAreaY = ty + 5;
        int bx = px + 6, bw = pw - 12;
        Color sc = tabs[activeTab].col;
        DrawLine(px+8, subAreaY-3, px+pw-8, subAreaY-3, (Color){sc.r,sc.g,sc.b,120});

        typedef struct { const char *lbl; int action; } SubItem;
        static const SubItem farm[3]   = {{"[I] TÚI ĐỒ",0},{"[B] CỬA HÀNG",1},{"[N] CHUỒNG",2}};
        static const SubItem social[3] = {{"[Q] NHIỆM VỤ",3},{"[F2] THÀNH TỰU",5},{"[C] TRỢ GIÚP",6}};
        static const SubItem sys[3]    = {{"[F5] LƯU",7},{"CÀI ĐẶT",18},{"ĐĂNG XUẤT",8}};
        static const SubItem tester[4] = {{"[T] CÂY CHÍN",12},{"[G] THÊM HẠT",14},{"[H] PHỤC HỒI HP",11},{"[F6] THỜI TIẾT",15}};
        static const SubItem adm[10]   = {{"[M] +5000 TIỀN",10},{"[H] FULL HP",11},{"[T] CÂY CHÍN",12},{"[K] GIẾT QUÁI",13},{"[V] ĐÀO TẤT CẢ",21},{"[G] THÊM HẠT",14},{"[F6] THỜI TIẾT",15},{"[F8] BUFF NGỌC",16},{"[F10] NGÀY/ĐÊM",19},{"[F11] NGÀY MỚI",20}};

        const SubItem *items;
        switch (activeTab) {
            case 0: items=farm;   break;
            case 1: items=social; break;
            case 2: items=sys;    break;
            case 3: items=tester; break;
            default: items=adm;   break;
        }
        int n = tabs[activeTab].count;

        /* Scroll bằng mousewheel khi hover panel */
        int totalSubPx = n * (subItemH + subGap);
        int maxScroll  = totalSubPx - visSubH;
        if (maxScroll < 0) maxScroll = 0;

        Vector2 mp = GetMousePosition();
        if (CheckCollisionPointRec(mp,(Rectangle){(float)px,(float)subAreaY,(float)pw,(float)visSubH})) {
            int wheel = GetMouseWheelMove();
            if (wheel != 0) {
                subScroll -= wheel * (subItemH + subGap);
                if (subScroll < 0) subScroll = 0;
                if (subScroll > maxScroll) subScroll = maxScroll;
            }
        }

        /* Clip vùng sub */
        BeginScissorMode(px, subAreaY, pw, visSubH);

        int action = -1;
        int subY = subAreaY - subScroll;
        for (int s = 0; s < n; s++) {
            Rectangle sr = {(float)bx,(float)subY,(float)bw,(float)subItemH};
            bool sh = CheckCollisionPointRec(mp, sr)
                   && mp.y >= subAreaY
                   && mp.y <= subAreaY + visSubH;
            DrawRectangle(bx,subY,bw,subItemH,
                sh?(Color){sc.r/2+25,sc.g/2+25,sc.b/2+25,235}:(Color){20,26,42,215});
            DrawRectangleLinesEx(sr,1.5f,sh?GOLD:(Color){sc.r/2,sc.g/2,sc.b/2,190});
            DrawTextCenteredShort(items[s].lbl,bx+bw/2,subY+(subItemH-16)/2,15,sh?GOLD:WHITE);
            if (sh && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) action = items[s].action;
            subY += subItemH + subGap;
        }
        EndScissorMode();

        /* Scrollbar nhỏ nếu cần scroll */
        if (maxScroll > 0) {
            int sbX=px+pw-6, sbY2=subAreaY, sbH=visSubH, sbW=4;
            DrawRectangle(sbX,sbY2,sbW,sbH,(Color){30,30,40,200});
            float thumbH=(float)visSubH/totalSubPx*sbH;
            if(thumbH<16) thumbH=16;
            float thumbPos=(float)subScroll/maxScroll*(sbH-thumbH);
            DrawRectangle(sbX,(int)(sbY2+thumbPos),sbW,(int)thumbH,(Color){sc.r,sc.g,sc.b,220});
        }

        /* Xử lý action */
        switch (action) {
        case 0: G.showInventory=!G.showInventory; G.showStore=false; G.showBarnUI=false; G.showAchievements=false; break;
        case 1: G.showStore=!G.showStore; G.showInventory=false; G.showBarnUI=false; G.showAchievements=false; break;
        case 2: G.showBarnUI=!G.showBarnUI; G.showInventory=false; G.showStore=false; G.showAchievements=false; break;
        case 3: G.showQuest=!G.showQuest; break;
        case 5: G.showAchievements=!G.showAchievements; G.showInventory=false; G.showStore=false; break;
        case 6: G.showHelp=!G.showHelp; break;
        case 7: { char sp[128]; snprintf(sp,sizeof(sp),"saves/%s.dat",G.player.username); Game_SavePlayer(sp); strncpy(G.message,"Đã lưu game!",sizeof(G.message)); G.msgTimer=2.0f; break; }
        case 8: Account_Logout(); break;
        case 10: Admin_GiveMoney(5000); break;
        case 11: Admin_FullHeal(); break;
        case 12: { for(int _i=0;_i<MAX_CROPS;_i++) if(G.crops[_i].active) G.crops[_i].stage=CSTAGE_READY; strncpy(G.message,"Tất cả cây đã chín!",sizeof(G.message)); G.msgTimer=1.5f; break; }
        case 13: { for(int _i=0;_i<MAX_ENEMIES;_i++) if(G.enemies[_i].active){G.enemies[_i].state=ESTATE_DEAD;G.enemies[_i].hp=0;G.enemyCount--;} strncpy(G.message,"Đã giết hết quái!",sizeof(G.message)); G.msgTimer=1.5f; break; }
        case 14: { for(int _s2=ITEM_SEED_CARROT;_s2<=ITEM_SEED_WHEAT;_s2++) Admin_SpawnItem((ItemType)_s2,5); strncpy(G.message,"Thêm hạt giống!",sizeof(G.message)); G.msgTimer=1.5f; break; }
        case 15: { G.weather.current=(WeatherType)((G.weather.current+1)%WEATHER_COUNT); G.weather.timer=300.0f; const char *wn[]={"Nắng","Mây","Mưa"}; snprintf(G.message,sizeof(G.message),"Thời tiết: %s",wn[G.weather.current]); G.msgTimer=2.0f; break; }
        case 16: { for(int _k=0;_k<3;_k++){Inv_Add(ITEM_GEM,1);G.gemCount++;} snprintf(G.message,sizeof(G.message),"+3 Ngọc! Tổng: %d/3",G.gemCount); G.msgTimer=2.0f; if(G.gemCount>=3&&!G.bossAlive){extern void SpawnBoss(void);SpawnBoss();} break; }
        case 17 : {G.player.maxHp = 99999; G.player.hp = 99999;strncpy(G.message, "Admin: God Mode ON", sizeof(G.message));G.msgTimer = 1.5f; break; }
        case 18: { G.showSettings=!G.showSettings; G.showInventory=false; G.showStore=false; G.showBarnUI=false; break; }
        case 19: { if(!G.isNight){G.dayTimer=DAY_DURATION*NIGHT_START_RATIO+1.0f;G.isNight=true;G.nightOverlay=1.0f;strncpy(G.message,"Admin: ĐÊM",sizeof(G.message));}else{G.dayTimer=0.0f;G.isNight=false;G.nightOverlay=0.0f;strncpy(G.message,"Admin: NGÀY",sizeof(G.message));}G.msgTimer=2.0f;break; }
        case 20: { G.dayTimer=0;G.day++;G.isNight=false;G.nightOverlay=0.0f;snprintf(G.message,sizeof(G.message),"Admin: Ngày %d!",G.day);G.msgTimer=2.0f;break; }
        case 21: {
            int _dug=0;
            for(int _r=0;_r<MAP_ROWS;_r++) for(int _c=0;_c<MAP_COLS;_c++){
                Tile *_t=&G.map[_r][_c];
                if(_t->type==TILE_SOIL_BOUGHT&&_t->cropIdx<0){_t->type=TILE_SOIL_DUG;_dug++;}
            }
            snprintf(G.message,sizeof(G.message),"Admin: Đào %d ô đất!",_dug); G.msgTimer=2.0f; break; }
        default: break;
        }
    }

    /* Role badge */
    const char *rs = isAdmin?"ADMIN":isTester?"TESTER":"PLAYER";
    Color rc = isAdmin?RED:isTester?ORANGE:SKYBLUE;
    DrawTextCenteredShort(rs, px+pw/2, py+ph-16, 15, rc);
}


void DrawUI_QuestPanel(void)
{
    if (!G.showQuest) return;
    
    /* Panel */
    int pw = 400, ph = 280;
    int px = SCREEN_W / 2 - pw / 2;
    int py = SCREEN_H / 2 - ph / 2;
    
    /* Nền panel */
    DrawRectangle(px, py, pw, ph, (Color){18, 22, 36, 240});
    DrawRectangleLines(px, py, pw, ph, (Color){70, 95, 160, 255});
    
    /* Tiêu đề */
    DrawTextCenteredShort("NHIỆM VỤ", px + pw / 2, py + 15, 28, GOLD);
    
    /* Đường kẻ */
    DrawLine(px + 20, py + 45, px + pw - 20, py + 45, (Color){70, 95, 160, 200});
    
    /* Danh sách nhiệm vụ */
    int startY = py + 55;
    int lineHeight = 35;
    
    for (int i = 0; i < MAX_QUESTS; i++)
    {
        Quest *q = &G.quests[i];
        
        /* Màu sắc dựa trên trạng thái */
        Color textColor = q->done ? (Color){100, 255, 100, 255} : WHITE;
        
        /* Dấu hiệu hoàn thành - dùng chữ [X] thay vì ký tự đặc biệt */
        if (q->done)
        {
            DrawTextShort("[X]", px + 20, startY + i * lineHeight + 8, 16, GREEN);
        }
        else
        {
            DrawTextShort("[ ]", px + 20, startY + i * lineHeight + 8, 16, (Color){150, 150, 150, 255});
        }
        
        /* Tên nhiệm vụ */
        DrawTextShort(q->desc, px + 55, startY + i * lineHeight + 8, 16, textColor);
        
        /* Tiến độ */
        char progressText[32];
        snprintf(progressText, sizeof(progressText), "%d/%d", q->progress, q->target);
        
        int progressWidth = MeasureTextShort(progressText, 16);
        DrawTextShort(progressText, px + pw - 35 - progressWidth, 
                     startY + i * lineHeight + 8, 16, 
                     q->progress >= q->target ? YELLOW : (Color){150, 150, 150, 255});
    }
    
    /* Đường kẻ cuối */
    DrawLine(px + 20, py + ph - 45, px + pw - 20, py + ph - 45, (Color){70, 95, 160, 200});
    
    /* Thống kê */
    int completedCount = 0;
    for (int i = 0; i < MAX_QUESTS; i++) {
        if (G.quests[i].done) completedCount++;
    }
    
    char summaryText[64];
    snprintf(summaryText, sizeof(summaryText), "Hoàn thành: %d/%d", completedCount, MAX_QUESTS);
    DrawTextCenteredShort(summaryText, px + pw / 2, py + ph - 30, 16, 
                         completedCount == MAX_QUESTS ? YELLOW : LIGHTGRAY);
    
    /* Nút Đóng */
    Rectangle closeBtn = {(float)(px + pw - 60), (float)(py + 10), 45, 25};
    bool closeHover = CheckCollisionPointRec(GetMousePosition(), closeBtn);
    DrawRectangleRec(closeBtn, closeHover ? (Color){150, 50, 50, 255} : (Color){80, 30, 30, 220});
    DrawRectangleLinesEx(closeBtn, 1, (Color){150, 150, 150, 200});
    DrawTextCenteredShort("ĐÓNG", px + pw - 60 + 22, py + 15, 14, WHITE);
    
    if (closeHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        G.showQuest = false;
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
}

/* ── INVENTORY ── */
void DrawUI_Inventory(void)
{
<<<<<<< HEAD
    if (!G.showInventory)
        return;
    int pw = 560, ph = 400, px = SCREEN_W / 2 - pw / 2, py = SCREEN_H / 2 - ph / 2;
    DrawRectangle(px, py, pw, ph, PBGC);
    DrawRectangleLines(px, py, pw, ph, PEDGC);
    DrawTextCenteredShort("TÚI ĐỒ", px + pw / 2, py + 8, 22, GOLD);
    DrawTextCenteredShort("RClick=Bán | LClick=Chọn hotbar", px + pw / 2, py + 32, 13, (Color){150, 150, 150, 255});
    if (Button(px + pw - 70, py + 6, 62, 22, "Đóng", (Color){80, 30, 30, 220}, (Color){150, 50, 50, 255}))
        G.showInventory = false;

    int cols = 8, sw = 60, sh = 60, oy = py + 56;
    int gridW = cols * sw + (cols - 1) * 4;
    int ox = px + (pw - gridW) / 2;

    for (int i = 0; i < INV_SLOTS; i++)
    {
        int col = i % cols, row = i / cols;
        int x = ox + col * (sw + 4), y = oy + row * (sh + 22);
        bool sel = (i == G.player.hotbarIdx);
        DrawRectangle(x, y, sw, sh, sel ? (Color){70, 60, 20, 230} : (Color){25, 32, 25, 210});
        DrawRectangleLines(x, y, sw, sh, sel ? GOLD : (Color){55, 70, 55, 255});
=======
    if (!G.showInventory) return;
    
    // Kích thước panel to hơn để chứa chữ lớn và ô to
    int pw = 720, ph = 500;
    int px = SCREEN_W / 2 - pw / 2;
    int py = SCREEN_H / 2 - ph / 2;
    
    // Vẽ panel nền
    DrawRectangle(px, py, pw, ph, (Color){18, 22, 36, 240});
    DrawRectangleLines(px, py, pw, ph, (Color){70, 95, 160, 255});
    
    // Tiêu đề - TIẾNG VIỆT CÓ DẤU
    DrawTextCenteredShort("TÚI ĐỒ", px + pw / 2, py + 15, 32, GOLD);
    
    // Hướng dẫn - TIẾNG VIỆT CÓ DẤU
    DrawTextCenteredShort("CHUỘT PHẢI = BÁN  |  CHUỘT TRÁI = CHỌN THANH CÔNG CỤ", 
                          px + pw / 2, py + 50, 16, (Color){150, 150, 150, 255});
    
    // Nút Đóng
    if (Button(px + pw - 90, py + 12, 75, 30, "ĐÓNG", 
               (Color){80, 30, 30, 220}, (Color){150, 50, 50, 255}))
        G.showInventory = false;

    // Grid inventory - 8 cột
    int cols = 8;
    int slotSize = 72;
    int slotPadding = 8;
    
    int gridW = cols * slotSize + (cols - 1) * slotPadding;
    int startX = px + (pw - gridW) / 2;
    int startY = py + 80;

    for (int i = 0; i < INV_SLOTS; i++) {
        int col = i % cols;
        int row = i / cols;
        int x = startX + col * (slotSize + slotPadding);
        int y = startY + row * (slotSize + 25);

        // Vẽ ô
        bool selected = (i == G.player.hotbarIdx);
        DrawRectangle(x, y, slotSize, slotSize, 
                     selected ? (Color){70, 60, 20, 230} : (Color){25, 32, 25, 210});
        DrawRectangleLines(x, y, slotSize, slotSize, 
                          selected ? GOLD : (Color){55, 70, 55, 255});
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc

        InvSlot *s = &G.player.inv[i];
        if (s->type == ITEM_NONE || s->quantity == 0)
            continue;

<<<<<<< HEAD
        if (s->type >= ITEM_SEED_CARROT && s->type <= ITEM_SEED_WHEAT)
        {
            int ct = s->type - ITEM_SEED_CARROT;
            if (T.crop[ct].width > 0)
            {
                int fw = T.crop[ct].width / 6;
                Rectangle src = {(float)(5 * fw), 0, (float)fw, (float)T.crop[ct].height};
                DrawTexturePro(T.crop[ct], src, (Rectangle){(float)(x + 4), (float)(y + 4), (float)(sw - 8), (float)(sh - 8)}, (Vector2){0, 0}, 0, WHITE);
            }
        }
        else if (s->type >= ITEM_CARROT && s->type <= ITEM_WHEAT)
        {
            int ct = s->type - ITEM_CARROT;
            if (T.crop[ct].width > 0)
            {
                int fw = T.crop[ct].width / 6;
                Rectangle src = {(float)(5 * fw), 0, (float)fw, (float)T.crop[ct].height};
                Rectangle dst = {
                    x + sw / 2,
                    y + sh / 2,
                    sw - 8,
                    sh - 8};

                Vector2 origin = {(sw - 8) / 2.0f, (sh - 8) / 2.0f};

                DrawTexturePro(T.crop[ct], src, dst, origin, 0, WHITE);
            }
        }
        else
        {
            const char *t = TextFormat("%c", GetItemName(s->type)[0]);
            int tw = MeasureText(t, 20);

            DrawTextShort(
                t,
                x + sw / 2 - tw / 2,
                y + sh / 2 - 10,
                20,
                WHITE);
        }
        const char *name = GetItemName(s->type);
        int tw = MeasureText(name, 11);

        DrawTextShort(
            name,
            x + sw / 2 - tw / 2,
            y + sh + 2,
            11,
            LIGHTGRAY);

        if (s->quantity > 1)
            DrawTextCenteredShort(TextFormat("x%d", s->quantity), x + sw - 18, y + sh - 13, 15, YELLOW);

        Rectangle sr = {(float)x, (float)y, (float)sw, (float)sh};
        if (CheckCollisionPointRec(GetMousePosition(), sr))
        {
=======
        // Vẽ icon item
        if (s->type >= ITEM_SEED_CARROT && s->type <= ITEM_SEED_WHEAT) {
            int ct = s->type - ITEM_SEED_CARROT;
            if (T.crop[ct].width > 0) {
                int fw = T.crop[ct].width / 6;
                Rectangle src = {(float)(5 * fw), 0, (float)fw, (float)T.crop[ct].height};
                DrawTexturePro(T.crop[ct], src, 
                    (Rectangle){(float)(x + 6), (float)(y + 6), 
                                (float)(slotSize - 12), (float)(slotSize - 12)}, 
                    (Vector2){0, 0}, 0, WHITE);
            }
        }
        else if (s->type >= ITEM_CARROT && s->type <= ITEM_WHEAT) {
            int ct = s->type - ITEM_CARROT;
            if (T.crop[ct].width > 0) {
                int fw = T.crop[ct].width / 6;
                Rectangle src = {(float)(5 * fw), 0, (float)fw, (float)T.crop[ct].height};
                DrawTexturePro(T.crop[ct], src, 
                    (Rectangle){(float)(x + 6), (float)(y + 6), 
                                (float)(slotSize - 12), (float)(slotSize - 12)}, 
                    (Vector2){0, 0}, 0, WHITE);
            }
        }
        else {
            // Vẽ icon mặc định
            DrawRectangle(x + 6, y + 6, slotSize - 12, slotSize - 12, (Color){60, 45, 25, 230});
            const char *firstChar = TextFormat("%c", GetItemName(s->type)[0]);
            DrawTextCenteredShort(firstChar, x + slotSize/2, y + slotSize/2 - 10, 24, GOLD);
        }

        // TÊN ITEM - DÙNG GetItemName (đã có tiếng Việt)
        const char *itemName = GetItemName(s->type);
        int nameWidth = MeasureTextShort(itemName, 14);
        int nameX = x + (slotSize - nameWidth) / 2;
        DrawTextShort(itemName, nameX, y + slotSize + 4, 14, LIGHTGRAY);

        // SỐ LƯỢNG
        if (s->quantity > 0) {
            char qtyStr[16];
            snprintf(qtyStr, sizeof(qtyStr), "x%d", s->quantity);
            int qtyWidth = MeasureTextShort(qtyStr, 17);
            DrawTextShort(qtyStr, x + slotSize - qtyWidth - 6, 
                         y + slotSize - 22, 17, YELLOW);
        }

        // Xử lý click chuột
        Rectangle slotRect = {(float)x, (float)y, (float)slotSize, (float)slotSize};
        if (CheckCollisionPointRec(GetMousePosition(), slotRect)) {
            DrawRectangleLinesEx(slotRect, 2, (Color){255, 255, 100, 200});
            
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
                Economy_SellSlot(i);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                G.player.hotbarIdx = i;
        }
    }
<<<<<<< HEAD
=======
    
    // // Hiển thị tổng số slot đã dùng
    // int usedSlots = 0;
    // for (int i = 0; i < INV_SLOTS; i++) {
    //     if (G.player.inv[i].type != ITEM_NONE && G.player.inv[i].quantity > 0)
    //         usedSlots++;
    // }
    // DrawTextShort(TextFormat("Đã dùng: %d/%d ô", usedSlots, INV_SLOTS), 
    //               px + 25, py + ph - 35, 14, (Color){180, 180, 180, 255});
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
}

/* ── STORE ── */
/* ── Helper: vẽ icon item (crop hoặc animal product) ── */
static void DrawItemIcon(ItemType type, int x, int y, int sz)
{
    if (type >= ITEM_SEED_CARROT && type <= ITEM_SEED_WHEAT)
    {
        int ct = type - ITEM_SEED_CARROT;
        if (T.crop[ct].width > 0)
        {
            int fw = T.crop[ct].width / 6;
            Rectangle src = {(float)(5 * fw), 0, (float)fw, (float)T.crop[ct].height};
            DrawTexturePro(T.crop[ct], src, (Rectangle){(float)x, (float)y, (float)sz, (float)sz}, (Vector2){0, 0}, 0, WHITE);
            return;
        }
    }
    else if (type >= ITEM_CARROT && type <= ITEM_WHEAT)
    {
        int ct = type - ITEM_CARROT;
        if (T.crop[ct].width > 0)
        {
            int fw = T.crop[ct].width / 6;
            Rectangle src = {(float)(5 * fw), 0, (float)fw, (float)T.crop[ct].height};
            DrawTexturePro(T.crop[ct], src, (Rectangle){(float)x, (float)y, (float)sz, (float)sz}, (Vector2){0, 0}, 0, WHITE);
            return;
        }
    }
    else if (type == ITEM_EGG && T.iEgg.width > 0)
    {
        DrawTexturePro(T.iEgg, (Rectangle){0, 0, (float)T.iEgg.width, (float)T.iEgg.height},
                       (Rectangle){(float)x, (float)y, (float)sz, (float)sz}, (Vector2){0, 0}, 0, WHITE);
        return;
    }
    else if (type == ITEM_MILK && T.iMilk.width > 0)
    {
        DrawTexturePro(T.iMilk, (Rectangle){0, 0, (float)T.iMilk.width, (float)T.iMilk.height},
                       (Rectangle){(float)x, (float)y, (float)sz, (float)sz}, (Vector2){0, 0}, 0, WHITE);
        return;
    }
    else if (type == ITEM_FEED && T.iFeed.width > 0)
    {
        DrawTexturePro(T.iFeed, (Rectangle){0, 0, (float)T.iFeed.width, (float)T.iFeed.height},
                       (Rectangle){(float)x, (float)y, (float)sz, (float)sz}, (Vector2){0, 0}, 0, WHITE);
        return;
    }
    /* Fallback: ký tự đầu tên */
    DrawRectangle(x, y, sz, sz, (Color){50, 40, 20, 200});
    DrawTextCenteredShort(TextFormat("%c", GetItemName(type)[0]), x + sz / 2, y + sz / 2 - 7, 14, GOLD);
}

/* ── Helper: dãy nút chọn số lượng, trả về qty hiện tại ── */
/* Bố cục: [-] [số] [+] [x5] [x10]  tổng rộng ~158px */
static int DrawQtySelector(int x, int y, int qty, int maxQty,
                           Color minusBg, Color plusBg, Color presetBg)
{
<<<<<<< HEAD
    int btnH = 22, numW = 34;
    /* [-] */
    if (Button(x, y, 22, btnH, "-", minusBg, (Color){minusBg.r + 40, minusBg.g + 20, minusBg.b + 10, 255}))
        if (qty > 1)
            qty--;
    /* [num] */
    DrawRectangle(x + 24, y, numW, btnH, (Color){10, 12, 22, 230});
    DrawRectangleLines(x + 24, y, numW, btnH, (Color){70, 90, 130, 200});
    DrawTextCenteredShort(TextFormat("%d", qty), x + 24 + numW / 2, y + 4, 12, WHITE);
    /* [+] */
    if (Button(x + 60, y, 22, btnH, "+", plusBg, (Color){plusBg.r + 40, plusBg.g + 20, plusBg.b + 10, 255}))
        if (qty < maxQty)
            qty++;
    /* [x5] */
    if (Button(x + 86, y, 30, btnH, "x5", presetBg, (Color){presetBg.r + 30, presetBg.g + 20, presetBg.b + 30, 255}))
        qty = (5 < maxQty) ? 5 : maxQty;
    /* [x10] */
    if (Button(x + 120, y, 34, btnH, "x10", presetBg, (Color){presetBg.r + 30, presetBg.g + 20, presetBg.b + 30, 255}))
=======
    /* Kích thước lớn hơn để dễ bấm */
    int btnH = 32, numW = 50;
    /* [-] */
    if (Button(x, y, 32, btnH, "-", minusBg,
        (Color){(unsigned char)(minusBg.r+40),(unsigned char)(minusBg.g+20),(unsigned char)(minusBg.b+10),255}))
        if (qty > 1) qty--;
    /* [number display] */
    DrawRectangle(x + 36, y, numW, btnH, (Color){10, 12, 22, 230});
    DrawRectangleLines(x + 36, y, numW, btnH, (Color){70, 90, 130, 200});
    DrawTextCenteredShort(TextFormat("%d", qty), x + 36 + numW / 2, y + (btnH - 18) / 2, 18, WHITE);
    /* [+] */
    if (Button(x + 90, y, 32, btnH, "+", plusBg,
        (Color){(unsigned char)(plusBg.r+40),(unsigned char)(plusBg.g+20),(unsigned char)(plusBg.b+10),255}))
        if (qty < maxQty) qty++;
    /* [x5] */
    if (Button(x + 128, y, 38, btnH, "x5", presetBg,
        (Color){(unsigned char)(presetBg.r+30),(unsigned char)(presetBg.g+20),(unsigned char)(presetBg.b+30),255}))
        qty = (5 < maxQty) ? 5 : maxQty;
    /* [x10] */
    if (Button(x + 170, y, 42, btnH, "x10", presetBg,
        (Color){(unsigned char)(presetBg.r+30),(unsigned char)(presetBg.g+20),(unsigned char)(presetBg.b+30),255}))
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
        qty = (10 < maxQty) ? 10 : maxQty;
    return qty;
}

<<<<<<< HEAD
void DrawUI_Store(void)
{
    if (!G.showStore)
        return;

    /* ── State tĩnh cho quantity ── */
    static int storeTab = 0;
    static int buyQty[12] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    static int sellQty[INV_SLOTS];
    static bool sqInit = false;
=======
/* ── STORE ── */
void DrawUI_Store(void)
{
    if (!G.showStore) return;

    /* ── State tĩnh cho quantity và scroll ── */
    static int storeTab = 0;
    static int buyQty[12] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    static int sellQty[INV_SLOTS];
    static int scrollOffset = 0;
    static int maxScroll = 0;
    static bool sqInit = false;
    
    /* LƯU LẠI CAMERA ZOOM TEMPORARY */
    float savedCamZoom = G.camZoom;
    G.camZoom = 1.0f;  // Tạm thời set zoom = 1 khi mở store
    
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
    if (!sqInit)
    {
        for (int i = 0; i < INV_SLOTS; i++)
            sellQty[i] = 1;
        sqInit = true;
    }

<<<<<<< HEAD
    /* ── Cửa sổ chính: 760x580 ── */
    int pw = 760, ph = 580, px = SCREEN_W / 2 - pw / 2, py = SCREEN_H / 2 - ph / 2;
    DrawRectangle(px, py, pw, ph, PBGC);
    DrawRectangleLines(px, py, pw, ph, (Color){100, 150, 220, 255});

    /* Header */
    DrawTextCenteredShort("CỬA HÀNG", px + pw / 2, py + 8, 24, GOLD);
    DrawTextCenteredShort(TextFormat("Tiền: $%d", G.player.money), px + 36, py + 10, 18, YELLOW);
    if (Button(px + pw - 76, py + 6, 68, 26, "[X] Đóng", (Color){80, 30, 30, 220}, (Color){150, 50, 50, 255}))
        G.showStore = false;

    /* ── Tabs ── */
    int tabY = py + 40, tabH = 28;
    Color tBuyN = (Color){28, 45, 80, 210}, tBuyA = (Color){55, 100, 185, 245};
    Color tSellN = (Color){50, 28, 12, 210}, tSellA = (Color){130, 65, 18, 245};
    if (Button(px + 10, tabY, 150, tabH, "  MUA HÀNG", storeTab == 0 ? tBuyA : tBuyN, tBuyA))
        storeTab = 0;
    if (Button(px + 168, tabY, 150, tabH, "  BÁN HÀNG", storeTab == 1 ? tSellA : tSellN, tSellA))
        storeTab = 1;
    DrawLine(px, tabY + tabH, px + pw, tabY + tabH, (Color){70, 95, 160, 200});

    int contentY = tabY + tabH + 6; /* Y bắt đầu nội dung */
    int contentH = py + ph - contentY - 6;

    /* ════════════════════════════════════════════════
       TAB MUA HANG
       Layout: 3 cột, mỗi card 238x108
=======
    /* ── Cửa sổ chính ── */
    int pw = 900, ph = 650;  // Tăng kích thước
    int px = SCREEN_W / 2 - pw / 2;
    int py = SCREEN_H / 2 - ph / 2;
    
    // Vẽ overlay mờ để tách biệt với game
    DrawRectangle(0, 0, SCREEN_W, SCREEN_H, (Color){0, 0, 0, 120});
    
    DrawRectangle(px, py, pw, ph, (Color){18, 22, 36, 250});
    DrawRectangleLines(px, py, pw, ph, (Color){100, 150, 220, 255});

    /* Header */
    DrawTextCenteredShort("CỬA HÀNG", px + pw / 2, py + 15, 36, GOLD);
    DrawTextShort(TextFormat("Tiền: $%d", G.player.money), px + 30, py + 22, 24, YELLOW);
    
    if (Button(px + pw - 100, py + 12, 85, 35, "ĐÓNG", 
               (Color){80, 30, 30, 220}, (Color){150, 50, 50, 255}))
    {
        G.showStore = false;
        G.camZoom = savedCamZoom;  // Khôi phục zoom khi đóng store
    }

    /* Tabs */
    int tabY = py + 60, tabH = 40;
    
    if (Button(px + 25, tabY, 170, tabH, "MUA HÀNG", 
               storeTab == 0 ? (Color){55, 100, 185, 245} : (Color){28, 45, 80, 210},
               (Color){70, 130, 220, 255}))
    {
        storeTab = 0;
        scrollOffset = 0;
    }
        
    if (Button(px + 205, tabY, 170, tabH, "BÁN HÀNG", 
               storeTab == 1 ? (Color){130, 65, 18, 245} : (Color){50, 28, 12, 210},
               (Color){180, 95, 30, 255}))
    {
        storeTab = 1;
        scrollOffset = 0;
    }
        
    DrawLine(px, tabY + tabH, px + pw, tabY + tabH, (Color){70, 95, 160, 200});

    // Vùng cuộn được
    int contentX = px + 15;
    int contentY = tabY + tabH + 15;
    int contentW = pw - 60;      // Chừa chỗ cho scrollbar
    int contentH = ph - (contentY - py) - 35;
    
    // Giới hạn vùng vẽ
    BeginScissorMode(contentX, contentY, contentW, contentH);

    /* ════════════════════════════════════════════════
       TAB MUA HÀNG
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
    ════════════════════════════════════════════════ */
    if (storeTab == 0)
    {
        static const ItemType buyItems[] = {
            ITEM_SEED_CARROT, ITEM_SEED_BEETROOT, ITEM_SEED_CABBAGE,
            ITEM_SEED_CAULIFLOWER, ITEM_SEED_KALE, ITEM_SEED_PARSNIP,
            ITEM_SEED_POTATO, ITEM_SEED_PUMPKIN, ITEM_SEED_RADISH,
            ITEM_SEED_SUNFLOWER, ITEM_SEED_WHEAT, ITEM_FEED};
<<<<<<< HEAD
        int nb = 12, cols = 3;
        int iw = 246, ih = 96, gap = 5;
        int ox = px + 8, oy = contentY + 2;
=======
            
        int nb = 12, cols = 2;
        int iw = 380, ih = 170;
        int gap = 15;
        int startY = contentY - scrollOffset;

        // Tính max scroll
        int totalRows = (nb + cols - 1) / cols;
        int totalHeight = totalRows * (ih + gap);
        maxScroll = (totalHeight > contentH) ? totalHeight - contentH + 20 : 0;
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc

        for (int i = 0; i < nb; i++)
        {
            int col = i % cols, row = i / cols;
<<<<<<< HEAD
            int cx = ox + col * (iw + gap), cy = oy + row * (ih + gap);
=======
            int cx = contentX + 5 + col * (iw + gap);
            int cy = startY + row * (ih + gap);

            // Chỉ vẽ nếu nằm trong vùng nhìn thấy
            if (cy + ih < contentY || cy > contentY + contentH)
                continue;
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc

            ItemType it = buyItems[i];
            int price = GetItemPrice(it);
            int totalCost = price * buyQty[i];
            bool canAfford = (G.player.money >= totalCost);

<<<<<<< HEAD
            /* ── Nền card ── */
            bool hov = CheckCollisionPointRec(GetMousePosition(),
                                              (Rectangle){(float)cx, (float)cy, (float)iw, (float)ih});
            DrawRectangle(cx, cy, iw, ih, hov ? (Color){26, 50, 88, 245} : (Color){16, 28, 50, 225});
            DrawRectangleLinesEx((Rectangle){(float)cx, (float)cy, (float)iw, (float)ih},
                                 1.5f, hov ? GOLD : (Color){50, 80, 125, 210});

            /* ── Icon 40x40 ── */
            DrawItemIcon(it, cx + 4, cy + 4, 40);

            /* ── Tên item + giá ── */
            DrawTextCenteredShort(GetItemName(it), cx + 50 + (iw - 50) / 2, cy + 4, 12, WHITE);
            DrawTextCenteredShort(TextFormat("$%d/cái", price), cx + 50 + (iw - 50) / 2, cy + 20, 11, YELLOW);

            /* ── Separator ── */
            DrawLine(cx + 4, cy + 38, cx + iw - 4, cy + 38, (Color){50, 70, 110, 160});

            /* ── Qty selector tại y=cy+43 ── */
            DrawTextShort("SL:", cx + 4, cy + 46, 10, (Color){150, 150, 150, 255});
            buyQty[i] = DrawQtySelector(
                cx + 26, cy + 43, buyQty[i], 99,
                (Color){50, 30, 20, 220}, (Color){30, 60, 20, 220}, (Color){25, 45, 80, 220});

            /* ── Tổng tiền + nút MUA ── */
            Color cstCol = canAfford ? LIME : RED;
            DrawTextShort(TextFormat("= $%d", totalCost), cx + 4, cy + 72, 11, cstCol);

            Color buyBg = canAfford ? (Color){25, 75, 130, 230} : (Color){38, 38, 38, 180};
            Color buyHov = canAfford ? (Color){45, 125, 200, 255} : (Color){48, 48, 48, 200};
            if (Button(cx + iw - 62, cy + 66, 56, 24, "MUA", buyBg, buyHov))
                if (canAfford)
                    Economy_BuyItem(it, buyQty[i]);
        }

        /* Hint hotbar ở dưới cùng */
        int hy = py + ph - 36;
        DrawRectangle(px + 6, hy, pw - 12, 30, (Color){10, 20, 10, 200});
        DrawRectangleLines(px + 6, hy, pw - 12, 30, (Color){60, 100, 50, 180});

        /* ════════════════════════════════════════════════
           TAB BAN HANG
           Layout: 3 cột, mỗi card 246x130
        ════════════════════════════════════════════════ */
    }
    else
    {
        int cols = 3;
        int iw = 246, ih = 130, gap = 5;
        int ox = px + 8, oy = contentY + 2;
        int row2 = 0, col2 = 0;
        int di = 0; /* display index – dùng làm key cho sellQty */
        bool anyItem = false;

=======
            /* Nền card */
            bool hov = CheckCollisionPointRec(GetMousePosition(),
                                              (Rectangle){(float)cx, (float)cy, (float)iw, (float)ih});
            DrawRectangle(cx, cy, iw, ih, hov ? (Color){30, 55, 95, 250} : (Color){20, 32, 55, 245});
            DrawRectangleLinesEx((Rectangle){(float)cx, (float)cy, (float)iw, (float)ih},
                                 2.0f, hov ? GOLD : (Color){60, 90, 135, 230});

            /* Icon 70x70 */
            DrawItemIcon(it, cx + 15, cy + 15, 70);

            /* Tên item */
            const char *itemName = GetItemName(it);
            DrawTextCenteredShort(itemName, cx + 100 + (iw - 100) / 2, cy + 20, 22, WHITE);
            
            /* Giá */
            DrawTextCenteredShort(TextFormat("$%d / cái", price), cx + 100 + (iw - 100) / 2, cy + 50, 20, YELLOW);

            /* Separator */
            DrawLine(cx + 15, cy + 90, cx + iw - 15, cy + 90, (Color){60, 80, 120, 220});

            /* Số lượng */
            DrawTextShort("Số lượng:", cx + 15, cy + 105, 17, (Color){210, 210, 210, 255});
            buyQty[i] = DrawQtySelector(
                cx + 110, cy + 100, buyQty[i], 99,
                (Color){65, 38, 22, 235}, (Color){38, 75, 28, 235}, (Color){32, 55, 95, 235});

            /* Thành tiền */
            DrawTextShort(TextFormat("Thành tiền: $%d", totalCost), cx + 15, cy + 140, 18, 
                         canAfford ? LIME : RED);

            /* Nút MUA */
            if (Button(cx + iw - 110, cy + 130, 95, 32, "MUA", 
                       canAfford ? (Color){28, 90, 150, 245} : (Color){50, 50, 50, 220},
                       canAfford ? (Color){45, 140, 220, 255} : (Color){70, 70, 70, 230}))
                if (canAfford)
                    Economy_BuyItem(it, buyQty[i]);
        }
    }
    /* ════════════════════════════════════════════════
       TAB BÁN HÀNG
    ════════════════════════════════════════════════ */
    else
    {
        int cols = 2;
        int iw = 380, ih = 200;
        int gap = 15;
        int startY = contentY - scrollOffset;
        int di = 0;
        bool anyItem = false;

        // Đếm số item có thể bán
        int sellableCount = 0;
        for (int i = 0; i < INV_SLOTS; i++) {
            if (G.player.inv[i].type != ITEM_NONE && 
                G.player.inv[i].quantity > 0 && 
                GetItemPrice(G.player.inv[i].type) > 0)
                sellableCount++;
        }
        
        int totalRows = (sellableCount + cols - 1) / cols;
        int totalHeight = totalRows * (ih + gap);
        maxScroll = (totalHeight > contentH) ? totalHeight - contentH + 20 : 0;

>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
        for (int i = 0; i < INV_SLOTS; i++)
        {
            InvSlot *s = &G.player.inv[i];
            if (s->type == ITEM_NONE || s->quantity == 0)
                continue;
<<<<<<< HEAD
            /* Bán tất cả item có trong kho (trừ item rỗng và item không có giá) */
            int price = GetItemPrice(s->type);
            if (price <= 0)
                continue;
            anyItem = true;

            /* Clamp sellQty dùng display-index */
=======
                
            int price = GetItemPrice(s->type);
            if (price <= 0)
                continue;
                
            anyItem = true;

>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
            if (sellQty[di] < 1)
                sellQty[di] = 1;
            if (sellQty[di] > s->quantity)
                sellQty[di] = s->quantity;

<<<<<<< HEAD
            int cx = ox + col2 * (iw + gap), cy = oy + row2 * (ih + gap);
            if (cy + ih > py + ph - 10)
                break;

            /* ── Nền card ── */
            bool hov = CheckCollisionPointRec(GetMousePosition(),
                                              (Rectangle){(float)cx, (float)cy, (float)iw, (float)ih});
            DrawRectangle(cx, cy, iw, ih, hov ? (Color){65, 42, 12, 245} : (Color){36, 22, 8, 225});
            DrawRectangleLinesEx((Rectangle){(float)cx, (float)cy, (float)iw, (float)ih},
                                 1.5f, hov ? GOLD : (Color){115, 85, 35, 210});

            /* ── Dòng 1: Icon 40x40 + Tên + Kho + Giá ── */
            DrawItemIcon(s->type, cx + 4, cy + 4, 40);
            DrawTextCenteredShort(GetItemName(s->type), cx + 50 + (iw - 50) / 2, cy + 4, 13, WHITE);
            DrawTextCenteredShort(TextFormat("Kho: x%d", s->quantity), cx + 50 + (iw - 50) / 2, cy + 22, 11, (Color){180, 180, 180, 255});
            DrawTextCenteredShort(TextFormat("Giá: $%d/cái", price), cx + 50 + (iw - 50) / 2, cy + 38, 11, YELLOW);

            /* ── Separator ── */
            DrawLine(cx + 4, cy + 52, cx + iw - 4, cy + 52, (Color){90, 65, 20, 160});

            /* ── Dòng 2: Qty selector ── */
            DrawTextShort("Bán:", cx + 4, cy + 59, 10, (Color){150, 150, 150, 255});
            sellQty[di] = DrawQtySelector(
                cx + 32, cy + 56, sellQty[di], s->quantity,
                (Color){65, 30, 10, 220}, (Color){50, 70, 15, 220}, (Color){60, 40, 10, 220});

            /* ── Dòng 3: Thu nhập ── */
            int earned = price * sellQty[di];
            DrawTextShort(TextFormat("Thu được: +$%d", earned), cx + 4, cy + 83, 11, LIME);

            /* ── Dòng 4: Nút BAN / BAN HET ── */
            int btnY = cy + ih - 26;
            int hw = (iw - 14) / 2;
            if (Button(cx + 4, btnY, hw, 22, "BÁN", (Color){75, 38, 8, 230}, (Color){140, 75, 18, 255}))
            {
                Economy_SellPartial(i, sellQty[di]);
                /* Sau compact, reset toàn bộ sellQty về 1 */
                for (int k = 0; k < INV_SLOTS; k++)
                    sellQty[k] = 1;
                break; /* thoát loop, frame sau vẽ lại */
            }
            if (Button(cx + 8 + hw, btnY, hw, 22, "BÁN HẾT", (Color){110, 28, 8, 230}, (Color){180, 55, 18, 255}))
=======
            int col = di % cols, row = di / cols;
            int cx = contentX + 5 + col * (iw + gap);
            int cy = startY + row * (ih + gap);

            // Chỉ vẽ nếu nằm trong vùng nhìn thấy
            if (cy + ih < contentY || cy > contentY + contentH)
            {
                di++;
                continue;
            }

            /* Nền card */
            bool hov = CheckCollisionPointRec(GetMousePosition(),
                                              (Rectangle){(float)cx, (float)cy, (float)iw, (float)ih});
            DrawRectangle(cx, cy, iw, ih, hov ? (Color){85, 55, 18, 250} : (Color){50, 32, 12, 245});
            DrawRectangleLinesEx((Rectangle){(float)cx, (float)cy, (float)iw, (float)ih},
                                 2.0f, hov ? GOLD : (Color){135, 95, 40, 230});

            /* Icon 70x70 */
            DrawItemIcon(s->type, cx + 15, cy + 15, 70);
            
            /* Tên item */
            const char *itemName = GetItemName(s->type);
            DrawTextCenteredShort(itemName, cx + 100 + (iw - 100) / 2, cy + 20, 22, WHITE);
            
            /* Kho và giá */
            DrawTextShort(TextFormat("Kho: x%d", s->quantity), cx + 100, cy + 52, 17, (Color){230, 230, 230, 255});
            DrawTextShort(TextFormat("Giá: $%d/cái", price), cx + 100, cy + 75, 17, YELLOW);

            /* Separator */
            DrawLine(cx + 15, cy + 105, cx + iw - 15, cy + 105, (Color){110, 75, 28, 220});

            /* Qty selector */
            DrawTextShort("Bán:", cx + 15, cy + 118, 17, (Color){230, 230, 230, 255});
            sellQty[di] = DrawQtySelector(
                cx + 70, cy + 113, sellQty[di], s->quantity,
                (Color){85, 40, 15, 235}, (Color){60, 85, 20, 235}, (Color){75, 50, 15, 235});

            /* Thu nhập */
            int earned = price * sellQty[di];
            DrawTextShort(TextFormat("Thu được: +$%d", earned), cx + 15, cy + 155, 18, LIME);

            /* Nút BÁN / BÁN HẾT */
            if (Button(cx + 15, cy + 175, 100, 30, "BÁN", 
                       (Color){95, 50, 15, 240}, (Color){160, 85, 22, 255}))
            {
                Economy_SellPartial(i, sellQty[di]);
                for (int k = 0; k < INV_SLOTS; k++)
                    sellQty[k] = 1;
                break;
            }
            
            if (Button(cx + 125, cy + 175, 100, 30, "BÁN HẾT", 
                       (Color){130, 40, 15, 240}, (Color){200, 65, 22, 255}))
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
            {
                Economy_SellSlot(i);
                for (int k = 0; k < INV_SLOTS; k++)
                    sellQty[k] = 1;
                break;
            }

            di++;
<<<<<<< HEAD
            col2++;
            if (col2 >= cols)
            {
                col2 = 0;
                row2++;
            }
=======
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
        }

        if (!anyItem)
        {
<<<<<<< HEAD
            DrawTextCenteredShort("Không có hàng hóa để bán.", px + pw / 2, contentY + 60, 15, GRAY);
            DrawTextCenteredShort("Thu hoạch cây trồng và sản phẩm động vật trước!", px + pw / 2, contentY + 88, 12, DARKGRAY);
        }
    }
}

/* ── BARN UI ── */
void DrawUI_BarnPanel(void)
{
    if (!G.showBarnUI)
        return;
    int pw = 480, ph = 440, px = SCREEN_W / 2 - pw / 2, py = SCREEN_H / 2 - ph / 2;
    DrawRectangle(px, py, pw, ph, PBGC);
    DrawRectangleLines(px, py, pw, ph, (Color){180, 140, 60, 255});
    DrawTextCenteredShort("QUẢN LÝ CHUỒNG", px + pw / 2, py + 8, 16, GOLD);
    if (Button(px + pw - 72, py + 6, 64, 22, "[X] Đóng", (Color){80, 30, 30, 220}, (Color){150, 50, 50, 255}))
        G.showBarnUI = false;

    int feedInv = Inv_Count(ITEM_FEED);
    DrawTextCenteredShort(TextFormat("Thức ăn trong túi: x%d", feedInv), px + 60, py + 14, 11,
                          feedInv > 0 ? YELLOW : (Color){200, 80, 80, 255});

    if (G.barnCount == 0)
    {
        DrawTextCenteredShort("Chưa có chuồng nào.", px + pw / 2, py + ph / 2, 14, LIGHTGRAY);
        DrawTextCenteredShort("Mua chuồng tại Cửa Hàng.", px + pw / 2, py + ph / 2 + 24, 12, GRAY);
        return;
    }

    static const char *aname[] = {"Gà (Trứng)", "Lợn (Sữa)", "Cừu (Len)"};
    static const Color acolor[] = {{255, 240, 160, 255}, {255, 200, 140, 255}, {220, 230, 210, 255}};
    int oy = py + 38;

    for (int i = 0; i < G.barnCount; i++)
    {
        Barn *b = &G.barns[i];
        if (!b->active)
            continue;

=======
            DrawTextCenteredShort("KHÔNG CÓ HÀNG HÓA ĐỂ BÁN", 
                                 px + pw / 2, contentY + 100, 26, GRAY);
            DrawTextCenteredShort("Thu hoạch cây trồng và sản phẩm động vật trước!", 
                                 px + pw / 2, contentY + 140, 18, DARKGRAY);
        }
    }

    EndScissorMode();

    /* ── THANH CUỘN (SCROLLBAR) VỚI CHỨC NĂNG KÉO ── */
static bool isDraggingScroll = false;
static int dragStartY = 0;
static float dragStartOffset = 0;

if (maxScroll > 0)
{
    int scrollBarX = px + pw - 30;
    int scrollBarY = contentY;
    int scrollBarH = contentH;
    int scrollBarW = 14;
    
    // Vẽ thanh cuộn nền
    DrawRectangle(scrollBarX, scrollBarY, scrollBarW, scrollBarH, (Color){45, 45, 55, 220});
    DrawRectangleLines(scrollBarX, scrollBarY, scrollBarW, scrollBarH, (Color){90, 90, 110, 220});
    
    // Tính kích thước thanh trượt
    float thumbHeight = (float)contentH / (float)(contentH + maxScroll) * scrollBarH;
    if (thumbHeight < 35) thumbHeight = 35;  // Thanh trượt tối thiểu 35px
    
    float thumbPos = (float)scrollOffset / (float)maxScroll * (scrollBarH - thumbHeight);
    
    // Vùng thanh trượt
    Rectangle thumbRect = {
        (float)scrollBarX,
        scrollBarY + thumbPos,
        (float)scrollBarW,
        thumbHeight
    };
    
    // Màu thanh trượt
    Color thumbColor = (Color){170, 170, 200, 240};
    Color thumbBorder = (Color){220, 220, 255, 220};
    
    // Highlight khi hover
    if (CheckCollisionPointRec(GetMousePosition(), thumbRect))
    {
        thumbColor = (Color){200, 200, 230, 255};
        thumbBorder = (Color){255, 255, 255, 255};
    }
    
    // Vẽ thanh trượt
    DrawRectangleRec(thumbRect, thumbColor);
    DrawRectangleLinesEx(thumbRect, 1, thumbBorder);
    
    // XỬ LÝ CLICK VÀ KÉO THANH SCROLL
    Vector2 mousePos = GetMousePosition();
    
    // Bắt đầu kéo khi click vào thanh trượt
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
        CheckCollisionPointRec(mousePos, thumbRect))
    {
        isDraggingScroll = true;
        dragStartY = mousePos.y;
        dragStartOffset = scrollOffset;
    }
    
    // Kết thúc kéo khi thả chuột
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        isDraggingScroll = false;
    }
    
    // Xử lý kéo
    if (isDraggingScroll)
    {
        int mouseDeltaY = mousePos.y - dragStartY;
        float scrollDelta = (float)mouseDeltaY / (scrollBarH - thumbHeight) * maxScroll;
        scrollOffset = dragStartOffset + scrollDelta;
        
        // Giới hạn scrollOffset
        if (scrollOffset < 0) scrollOffset = 0;
        if (scrollOffset > maxScroll) scrollOffset = maxScroll;
        
        // Vẽ hiệu ứng khi đang kéo
        DrawRectangleRec(thumbRect, (Color){220, 220, 250, 255});
    }
    
    // Xử lý click vào vùng thanh cuộn (nhảy đến vị trí)
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
        CheckCollisionPointRec(mousePos, 
            (Rectangle){(float)scrollBarX, (float)scrollBarY, (float)scrollBarW, (float)scrollBarH}) &&
        !CheckCollisionPointRec(mousePos, thumbRect))
    {
        // Click vào vùng trống của thanh cuộn - nhảy đến vị trí đó
        float clickPos = mousePos.y - scrollBarY;
        float targetOffset = (clickPos - thumbHeight/2) / (scrollBarH - thumbHeight) * maxScroll;
        
        if (targetOffset < 0) targetOffset = 0;
        if (targetOffset > maxScroll) targetOffset = maxScroll;
        
        scrollOffset = targetOffset;
    }
    
    // Xử lý cuộn bằng chuột (bánh xe) - CHỈ TRONG VÙNG CỬA HÀNG
    if (CheckCollisionPointRec(mousePos, (Rectangle){(float)contentX, (float)contentY, 
                                                     (float)contentW, (float)contentH}))
    {
        int wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            scrollOffset -= wheel * 30;
            if (scrollOffset < 0) scrollOffset = 0;
            if (scrollOffset > maxScroll) scrollOffset = maxScroll;
        }
    }
}
else
{
    scrollOffset = 0;
    isDraggingScroll = false;  // Reset trạng thái kéo
}
    
    // Khôi phục camera zoom khi đóng store
    if (!G.showStore)
        G.camZoom = savedCamZoom;
}
/* ── BARN UI ── */
void DrawUI_BarnPanel(void)
{
    if (!G.showBarnUI) return;
    
    /* State tĩnh cho scroll */
    static int barnScrollOffset = 0;
    static int barnMaxScroll = 0;
    static bool isDraggingBarnScroll = false;
    static int dragBarnStartY = 0;
    static float dragBarnStartOffset = 0;
    
    /* Lưu camera zoom */
    float savedCamZoom = G.camZoom;
    G.camZoom = 1.0f;
    
    /* Overlay mờ */
    DrawRectangle(0, 0, SCREEN_W, SCREEN_H, (Color){0, 0, 0, 120});
    
    /* Panel chính */
    int pw = 820, ph = 620;
    int px = SCREEN_W / 2 - pw / 2;
    int py = SCREEN_H / 2 - ph / 2;
    
    DrawRectangle(px, py, pw, ph, (Color){18, 22, 36, 250});
    DrawRectangleLines(px, py, pw, ph, (Color){180, 140, 60, 255});
    
    /* Tiêu đề */
    DrawTextCenteredShort("QUẢN LÝ CHUỒNG", px + pw / 2, py + 18, 32, GOLD);
    
    /* Thức ăn trong túi */
    int feedCount = Inv_Count(ITEM_FEED);
    DrawTextShort(TextFormat("Thức ăn: x%d", feedCount), 
                  px + 25, py + 60, 22, feedCount > 0 ? YELLOW : RED);
    
    /* Nút Đóng */
    Rectangle closeBtn = {(float)(px + pw - 90), (float)(py + 15), 75, 32};
    bool closeHover = CheckCollisionPointRec(GetMousePosition(), closeBtn);
    DrawRectangleRec(closeBtn, closeHover ? (Color){150, 50, 50, 255} : (Color){80, 30, 30, 220});
    DrawRectangleLinesEx(closeBtn, 1, (Color){150, 150, 150, 200});
    DrawTextCenteredShort("ĐÓNG", px + pw - 90 + 37, py + 15 + 8, 16, WHITE);
    
    if (closeHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        G.showBarnUI = false;
        G.camZoom = savedCamZoom;
    }

    /* Kiểm tra có chuồng không */
    if (G.barnCount == 0)
    {
        DrawTextCenteredShort("CHƯA CÓ CHUỒNG NÀO", px + pw / 2, py + ph / 2, 28, LIGHTGRAY);
        DrawTextCenteredShort("Mua chuồng tại Cửa Hàng", px + pw / 2, py + ph / 2 + 45, 20, GRAY);
        return;
    }

    /* Vùng cuộn được */
    int contentX = px + 20;
    int contentY = py + 95;
    int contentW = pw - 70;
    int contentH = ph - (contentY - py) - 35;
    
    /* Tính chiều cao tổng dựa trên số chuồng active */
    int activeBarnCount = 0;
    for (int i = 0; i < G.barnCount; i++) {
        if (G.barns[i].active) activeBarnCount++;
    }
    
    int barnItemHeight = 150;
    int totalBarnHeight = activeBarnCount * barnItemHeight;
    barnMaxScroll = (totalBarnHeight > contentH) ? totalBarnHeight - contentH + 20 : 0;
    
    /* Giới hạn vùng vẽ */
    BeginScissorMode(contentX, contentY, contentW, contentH);
    
    int startY = contentY - barnScrollOffset;
    int displayIndex = 1;  // Thứ tự hiển thị
    
    for (int i = 0; i < G.barnCount; i++)
    {
        Barn *b = &G.barns[i];
        if (!b->active) continue;  // Bỏ qua chuồng không active
        
        int cy = startY + (displayIndex - 1) * barnItemHeight;
        
        /* Chỉ vẽ nếu trong vùng nhìn thấy */
        if (cy + barnItemHeight < contentY || cy > contentY + contentH)
        {
            displayIndex++;
            continue;
        }

        /* Thống kê động vật */
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
        int hungry = 0, hasProduct = 0, total = 0;
        for (int j = 0; j < MAX_ANIMALS; j++)
        {
            Animal *a = &G.animals[j];
<<<<<<< HEAD
            if (!a->active || a->barnIdx != i)
                continue;
            total++;
            if (a->hungry)
                hungry++;
            if (a->hasProduct)
                hasProduct++;
        }

        int bh = 84;
        DrawRectangle(px + 6, oy, pw - 12, bh, (Color){22, 35, 15, 225});
        DrawRectangleLinesEx((Rectangle){(float)(px + 6), (float)oy, (float)(pw - 12), (float)bh},
                             1.5f, (Color){100, 130, 60, 200});

        DrawTextShort(TextFormat("Chuồng %d — %s", i + 1, aname[b->type]), px + 14, oy + 5, 13, acolor[b->type]);
        DrawTextShort(TextFormat("%d/%d con", total, MAX_ANIMALS_PER_BARN), px + 14, oy + 22, 11,
                      total >= MAX_ANIMALS_PER_BARN ? RED : LIGHTGRAY);
        if (hungry > 0)
            DrawText(TextFormat("| Đói: %d", hungry), px + 70, oy + 22, 11, RED);
        if (hasProduct > 0)
            DrawText(TextFormat("| Sản phẩm: %d", hasProduct), px + 130, oy + 22, 11, LIME);

        int btnX = px + pw - 130, btnW = 118, btnH = 20;

        /* Mua */
        bool canBuy = (total < MAX_ANIMALS_PER_BARN && G.player.money >= ANIMAL_PRICE);
        if (Button(btnX, oy + 4, btnW, btnH, TextFormat("MUA ($%d)", ANIMAL_PRICE),
                   canBuy ? (Color){30, 70, 130, 230} : (Color){30, 30, 30, 180},
                   canBuy ? (Color){50, 110, 200, 255} : (Color){40, 40, 40, 200}))
            if (canBuy)
                Barn_BuyAnimal(i);

        /* Cho ăn */
        bool canFeed = (hungry > 0 && feedInv > 0);
        if (Button(btnX, oy + 28, btnW, btnH, TextFormat("CHO ĂN (%d đói)", hungry),
                   hungry > 0 ? (Color){120, 70, 10, 230} : (Color){30, 30, 30, 180},
                   canFeed ? (Color){190, 110, 20, 255} : (Color){40, 40, 40, 200}))
        {
            if (canFeed)
            {
                int fed = 0;
                for (int j = 0; j < MAX_ANIMALS; j++)
                {
                    Animal *a = &G.animals[j];
                    if (!a->active || a->barnIdx != i || !a->hungry)
                        continue;
                    if (!Inv_Remove(ITEM_FEED, 1))
                        break;
                    a->hungry = false;
                    a->feedTimer = FEED_SECS;
                    fed++;
                }
                feedInv = Inv_Count(ITEM_FEED);
                snprintf(G.message, sizeof(G.message), "Cho %d con ăn!", fed);
                G.msgTimer = 1.5f;
            }
            else if (!hungry)
            {
                strncpy(G.message, "Không con nào đang đói.", sizeof(G.message));
                G.msgTimer = 1.5f;
            }
            else
            {
                strncpy(G.message, "Hết thức ăn!", sizeof(G.message));
                G.msgTimer = 1.5f;
            }
        }

        /* Thu hoạch */
        bool canHarv = (hasProduct > 0);
        if (Button(btnX, oy + 52, btnW, btnH, TextFormat("THU HOẠCH (%d)", hasProduct),
                   canHarv ? (Color){20, 90, 30, 230} : (Color){30, 30, 30, 180},
                   canHarv ? (Color){35, 150, 50, 255} : (Color){40, 40, 40, 200}))
        {
            if (canHarv)
            {
                int got = 0;
                for (int j = 0; j < MAX_ANIMALS; j++)
                {
                    Animal *a = &G.animals[j];
                    if (!a->active || a->barnIdx != i || !a->hasProduct)
                        continue;
                    ItemType prod = (a->type == ANIMAL_CHICKEN) ? ITEM_EGG : (a->type == ANIMAL_PIG) ? ITEM_MILK
                                                                                                     : ITEM_WOOL;
                    if (Inv_Add(prod, 1))
                    {
                        a->hasProduct = false;
                        got++;
                    }
                }
                snprintf(G.message, sizeof(G.message), "Thu %d sản phẩm!", got);
                G.msgTimer = 2.0f;
            }
        }

        oy += bh + 5;
        if (oy > py + ph - 10)
            break;
    }
=======
            if (!a->active || a->barnIdx != i) continue;
            total++;
            if (a->hungry) hungry++;
            if (a->hasProduct) hasProduct++;
        }

        /* Tên động vật theo loại */
        const char *animalTypeName;
        Color animalColor;
        switch(b->type) {
            case ANIMAL_CHICKEN: 
                animalTypeName = "GÀ (TRỨNG)"; 
                animalColor = (Color){255, 240, 160, 255};
                break;
            case ANIMAL_PIG: 
                animalTypeName = "LỢN (SỮA)"; 
                animalColor = (Color){255, 200, 140, 255};
                break;
            case ANIMAL_SHEEP: 
                animalTypeName = "CỪU (LEN)"; 
                animalColor = (Color){220, 230, 210, 255};
                break;
            default: 
                animalTypeName = "???";
                animalColor = WHITE;
        }

        /* Vẽ nền chuồng */
        DrawRectangle(contentX + 5, cy, contentW - 25, barnItemHeight - 10, 
                     (Color){25, 38, 18, 240});
        DrawRectangleLines(contentX + 5, cy, contentW - 25, barnItemHeight - 10, 
                          (Color){140, 110, 50, 220});

        /* Dòng 1: Số thứ tự chuồng */
        DrawTextShort(TextFormat("CHUỒNG %d", displayIndex), 
                     contentX + 20, cy + 10, 20, GOLD);
        
        /* Dòng 2: Loại động vật */
        DrawTextShort(animalTypeName, 
                     contentX + 20, cy + 35, 18, animalColor);

        /* Dòng 3: Số lượng và trạng thái */
        char statusText[64];
        if (hungry > 0 && hasProduct > 0)
            snprintf(statusText, sizeof(statusText), "%d/%d con  |  ĐÓI: %d  |  SP: %d", 
                     total, MAX_ANIMALS_PER_BARN, hungry, hasProduct);
        else if (hungry > 0)
            snprintf(statusText, sizeof(statusText), "%d/%d con  |  ĐÓI: %d", 
                     total, MAX_ANIMALS_PER_BARN, hungry);
        else if (hasProduct > 0)
            snprintf(statusText, sizeof(statusText), "%d/%d con  |  SP: %d", 
                     total, MAX_ANIMALS_PER_BARN, hasProduct);
        else
            snprintf(statusText, sizeof(statusText), "%d/%d con", 
                     total, MAX_ANIMALS_PER_BARN);

        DrawTextShort(statusText, contentX + 20, cy + 60, 16, LIGHTGRAY);

        /* ── 3 NÚT BẤM ── */
        int btnY = cy + 95;
        int btnW = 90;
        int btnH = 32;
        int spacing = 12;
        
        int totalBtnWidth = btnW * 3 + spacing * 2;
        int startBtnX = contentX + (contentW - totalBtnWidth) / 2 - 5;
        
        Vector2 mousePos = GetMousePosition();
        
        /* NÚT 1: MUA */
        bool canBuy = (total < MAX_ANIMALS_PER_BARN && G.player.money >= ANIMAL_PRICE);
        Rectangle buyRect = {
            (float)startBtnX,
            (float)btnY,
            (float)btnW,
            (float)btnH
        };
        
        bool buyHover = CheckCollisionPointRec(mousePos, buyRect);
        Color buyColor;
        if (!canBuy) buyColor = (Color){50, 50, 50, 220};
        else buyColor = buyHover ? (Color){50, 120, 200, 255} : (Color){30, 80, 140, 240};
        
        DrawRectangleRec(buyRect, buyColor);
        DrawRectangleLinesEx(buyRect, 1, canBuy ? (Color){100, 180, 255, 200} : (Color){80, 80, 80, 200});
        DrawTextCenteredShort(TextFormat("MUA $%d", ANIMAL_PRICE), 
                              startBtnX + btnW/2, btnY + 8, 14, WHITE);
        
        if (buyHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && canBuy)
        {
            Barn_BuyAnimal(i);
            feedCount = Inv_Count(ITEM_FEED);
        }
        
        /* NÚT 2: CHO ĂN */
        bool canFeed = (hungry > 0 && feedCount > 0);
        Rectangle feedRect = {
            (float)(startBtnX + btnW + spacing),
            (float)btnY,
            (float)btnW,
            (float)btnH
        };
        
        bool feedHover = CheckCollisionPointRec(mousePos, feedRect);
        Color feedColor;
        if (!canFeed) feedColor = (Color){60, 55, 45, 220};
        else feedColor = feedHover ? (Color){200, 130, 30, 255} : (Color){160, 100, 20, 240};
        
        DrawRectangleRec(feedRect, feedColor);
        DrawRectangleLinesEx(feedRect, 1, canFeed ? (Color){255, 180, 50, 200} : (Color){90, 80, 60, 200});
        DrawTextCenteredShort(TextFormat("CHO ĂN (%d)", hungry), 
                              startBtnX + btnW + spacing + btnW/2, btnY + 8, 14, WHITE);
        
        if (feedHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && canFeed)
        {
            int fed = 0;
            for (int j = 0; j < MAX_ANIMALS; j++)
            {
                Animal *a = &G.animals[j];
                if (!a->active || a->barnIdx != i || !a->hungry) continue;
                if (!Inv_Remove(ITEM_FEED, 1)) break;
                a->hungry = false;
                a->feedTimer = FEED_SECS;
                fed++;
            }
            feedCount = Inv_Count(ITEM_FEED);
            snprintf(G.message, sizeof(G.message), "Đã cho %d con ăn!", fed);
            G.msgTimer = 2.0f;
        }
        
        /* NÚT 3: THU HOẠCH */
        bool canHarvest = (hasProduct > 0);
        Rectangle harvestRect = {
            (float)(startBtnX + (btnW + spacing) * 2),
            (float)btnY,
            (float)btnW,
            (float)btnH
        };
        
        bool harvestHover = CheckCollisionPointRec(mousePos, harvestRect);
        Color harvestColor;
        if (!canHarvest) harvestColor = (Color){50, 60, 50, 220};
        else harvestColor = harvestHover ? (Color){40, 160, 50, 255} : (Color){30, 120, 40, 240};
        
        DrawRectangleRec(harvestRect, harvestColor);
        DrawRectangleLinesEx(harvestRect, 1, canHarvest ? (Color){80, 220, 80, 200} : (Color){70, 80, 70, 200});
        DrawTextCenteredShort(TextFormat("THU HOẠCH (%d)", hasProduct), 
                              startBtnX + (btnW + spacing) * 2 + btnW/2, btnY + 8, 14, WHITE);
        
        if (harvestHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && canHarvest)
        {
            int collected = 0;
            for (int j = 0; j < MAX_ANIMALS; j++)
            {
                Animal *a = &G.animals[j];
                if (!a->active || a->barnIdx != i || !a->hasProduct) continue;
                
                ItemType product;
                switch(a->type) {
                    case ANIMAL_CHICKEN: product = ITEM_EGG; break;
                    case ANIMAL_PIG: product = ITEM_WOOL; break;
                    case ANIMAL_SHEEP: product = ITEM_WOOL; break;
                    default: continue;
                }
                
                if (Inv_Add(product, 1))
                {
                    a->hasProduct = false;
                    a->produceTimer = PRODUCE_SECS;
                    collected++;
                }
            }
            snprintf(G.message, sizeof(G.message), "Thu hoạch %d sản phẩm!", collected);
            G.msgTimer = 2.0f;
        }
        
        displayIndex++;
    }
    
    EndScissorMode();

    /* ── THANH CUỘN (SCROLLBAR) ── */
    if (barnMaxScroll > 0)
    {
        int scrollBarX = px + pw - 30;
        int scrollBarY = contentY;
        int scrollBarH = contentH;
        int scrollBarW = 14;
        
        DrawRectangle(scrollBarX, scrollBarY, scrollBarW, scrollBarH, (Color){45, 45, 55, 220});
        DrawRectangleLines(scrollBarX, scrollBarY, scrollBarW, scrollBarH, (Color){90, 90, 110, 220});
        
        float thumbHeight = (float)contentH / (float)(contentH + barnMaxScroll) * scrollBarH;
        if (thumbHeight < 40) thumbHeight = 40;
        
        float thumbPos = (float)barnScrollOffset / (float)barnMaxScroll * (scrollBarH - thumbHeight);
        
        Rectangle thumbRect = {
            (float)scrollBarX,
            scrollBarY + thumbPos,
            (float)scrollBarW,
            thumbHeight
        };
        
        Vector2 mousePos = GetMousePosition();
        bool thumbHover = CheckCollisionPointRec(mousePos, thumbRect);
        Color thumbColor = thumbHover ? (Color){200, 200, 230, 255} : (Color){170, 170, 200, 240};
        
        DrawRectangleRec(thumbRect, thumbColor);
        DrawRectangleLinesEx(thumbRect, 1, (Color){220, 220, 255, 220});
        
        /* Xử lý kéo scroll */
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && thumbHover)
        {
            isDraggingBarnScroll = true;
            dragBarnStartY = mousePos.y;
            dragBarnStartOffset = barnScrollOffset;
        }
        
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            isDraggingBarnScroll = false;
        
        if (isDraggingBarnScroll)
        {
            int mouseDeltaY = mousePos.y - dragBarnStartY;
            float scrollDelta = (float)mouseDeltaY / (scrollBarH - thumbHeight) * barnMaxScroll;
            barnScrollOffset = dragBarnStartOffset + scrollDelta;
            
            if (barnScrollOffset < 0) barnScrollOffset = 0;
            if (barnScrollOffset > barnMaxScroll) barnScrollOffset = barnMaxScroll;
        }
        
        /* Click vào vùng trống của thanh cuộn */
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
            CheckCollisionPointRec(mousePos, 
                (Rectangle){(float)scrollBarX, (float)scrollBarY, (float)scrollBarW, (float)scrollBarH}) &&
            !thumbHover)
        {
            float clickPos = mousePos.y - scrollBarY;
            float targetOffset = (clickPos - thumbHeight/2) / (scrollBarH - thumbHeight) * barnMaxScroll;
            
            if (targetOffset < 0) targetOffset = 0;
            if (targetOffset > barnMaxScroll) targetOffset = barnMaxScroll;
            
            barnScrollOffset = targetOffset;
        }
        
        /* Cuộn bằng bánh xe chuột */
        if (CheckCollisionPointRec(mousePos, (Rectangle){(float)contentX, (float)contentY, 
                                                         (float)contentW, (float)contentH}))
        {
            int wheel = GetMouseWheelMove();
            if (wheel != 0)
            {
                barnScrollOffset -= wheel * 40;
                if (barnScrollOffset < 0) barnScrollOffset = 0;
                if (barnScrollOffset > barnMaxScroll) barnScrollOffset = barnMaxScroll;
            }
        }
    }
    else
    {
        barnScrollOffset = 0;
        isDraggingBarnScroll = false;
    }
    
    /* Khôi phục camera khi đóng */
    if (!G.showBarnUI)
        G.camZoom = savedCamZoom;
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
}

/* ── HELP ── */
void DrawUI_Help(void)
{
<<<<<<< HEAD
    if (!G.showHelp)
        return;
=======
    if (!G.showHelp) return;
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
    int pw = 440, ph = 500;
    int px = SCREEN_W / 2 - pw / 2;
    int py = SCREEN_H / 2 - ph / 2;
    DrawRectangle(px, py, pw, ph, (Color){8, 10, 22, 248});
    DrawRectangleLines(px, py, pw, ph, GOLD);
    DrawTextCenteredShort("HƯỚNG DẪN", px + pw / 2, py + 8, 22, GOLD);
    if (Button(px + pw - 70, py + 6, 62, 22, "Đóng", (Color){80, 30, 30, 220}, (Color){150, 50, 50, 255}))
        G.showHelp = false;

    static const char *lines[] = {
        "WASD / Arrow   - Di chuyển",
        "Shift          - Chạy nhanh",
        "I - Túi đồ     B - Cửa hàng   N - Chuồng",
        "Q - Nhiệm vụ   c - Trợ giúp   F5 - Lưu",
        "ESC - Tạm dừng",
        " ",
        "TRỒNG TRỌT (4 BƯỚC):",
        "  1. Mua đất ở Cửa Hàng → click vị trí",
        "  2. [1]Cuốc → click đất đã mua (SOIL_BOUGHT)",
        "  3. [2]Bình tưới → click đất đã đào",
        "  4. [3]Chọn hạt + click đất đã tưới",
        "  5. [4]Thu Hoạch khi cây đã chín (READY)",
        " ",
        "CHĂN NUÔI:",
        "  Mua chuồng ở Cửa Hàng (chọn loại)",
        "  Mua động vật vào chuồng (Quản lý Chuồng)",
        "  Mua Thức Ăn → [6] click chuồng khi đói",
        "  Hoặc click [Cho ăn Tất Cả] trong panel",
        "  RClick lên chuồng để thu sản phẩm",
        " ",
        "THỜI TIẾT: Mưa → cây tự được tưới nước",
        "LEVEL: Thu hoạch/Trồng/Đánh quái/Thu sp → EXP",
    };
    int n = sizeof(lines) / sizeof(lines[0]);
    for (int i = 0; i < n; i++)
        DrawTextShort(lines[i], px + 24, py + 36 + i * 18, 16, WHITE);
}

/* ── PAUSE ── */
<<<<<<< HEAD
=======

>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
void DrawUI_PauseScreen(void)
{
    DrawRectangle(0, 0, SCREEN_W, SCREEN_H, (Color){0, 0, 0, 140});
    DrawTextCenteredShort("GAME PAUSED", SCREEN_W / 2, SCREEN_H / 2 - 56, 56, WHITE);
    DrawTextCenteredShort("ESC ĐỂ TIẾP TỤC", SCREEN_W / 2, SCREEN_H / 2 + 18, 24, LIGHTGRAY);
    DrawTextCenteredShort("F5 ĐỂ LƯU GAME", SCREEN_W / 2, SCREEN_H / 2 + 50, 20, GRAY);
}

/* ── ACHIEVEMENTS PANEL ── */
void DrawUI_Achievements(void)
{
<<<<<<< HEAD
    if (!G.showAchievements)
        return;

    int pw = 600, ph = 500, px = SCREEN_W / 2 - pw / 2, py = SCREEN_H / 2 - ph / 2;
    DrawRectangle(px, py, pw, ph, (Color){12, 14, 28, 248});
    DrawRectangleLines(px, py, pw, ph, (Color){200, 160, 50, 255});
    DrawTextCenteredShort("THÀNH TỰU", px + pw / 2, py + 8, 24, GOLD);

    /* Đếm đã mở */
=======
    if (!G.showAchievements) return;
    
    /* State tĩnh cho scroll */
    static int achScrollOffset = 0;
    static int achMaxScroll = 0;
    static bool isDraggingAchScroll = false;
    static int dragAchStartY = 0;
    static float dragAchStartOffset = 0;
    
    /* Lưu camera zoom */
    float savedCamZoom = G.camZoom;
    G.camZoom = 1.0f;
    
    /* Overlay mờ */
    DrawRectangle(0, 0, SCREEN_W, SCREEN_H, (Color){0, 0, 0, 140});
    
    /* Panel chính */
    int pw = 900, ph = 650;
    int px = SCREEN_W / 2 - pw / 2;
    int py = SCREEN_H / 2 - ph / 2;
    
    /* Nền panel với hiệu ứng */
    DrawRectangleGradientV(px, py, pw, ph, (Color){25, 30, 45, 250}, (Color){15, 18, 30, 250});
    DrawRectangleLines(px, py, pw, ph, (Color){220, 180, 60, 255});
    
    /* BỎ: Trang trí góc - DrawTextShort("★", ...) */
    
    /* Tiêu đề */
    DrawTextCenteredShort("THÀNH TỰU", px + pw / 2, py + 25, 42, GOLD);
    
    /* Đếm số đã mở khóa */
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
    int unlocked = 0;
    for (int i = 0; i < MAX_ACHIEVEMENTS; i++)
        if (achievements[i].unlocked)
            unlocked++;
<<<<<<< HEAD
    // DrawTextCenteredShort(TextFormat("%d / %d da mo khoa", unlocked, MAX_ACHIEVEMENTS),
    //                       px + 24, py + 34, 16, (Color){180, 180, 180, 255});

    if (Button(px + pw - 70, py + 6, 62, 22, "Đóng", (Color){80, 30, 30, 220}, (Color){150, 50, 50, 255}))
        G.showAchievements = false;

    /* Thanh tiến trình tổng */
    int bw = pw - 100, bx2 = px + 50, by2 = py + 52;
    DrawRectangle(bx2, by2, bw, 10, (Color){30, 30, 30, 200});
    DrawRectangle(bx2, by2, (int)(bw * (float)unlocked / MAX_ACHIEVEMENTS), 10, GOLD);
    DrawRectangleLines(bx2, by2, bw, 10, DARKGRAY);

    /* Grid thành tựu: 2 cột */
    int cols = 2;
    int padding = 12;
    int iw = (pw - padding * 2) / cols;
    int ih = 54;
    int ox = px + 8, oy = py + 72;
    for (int i = 0; i < MAX_ACHIEVEMENTS; i++)
    {
        Achievement *a = &achievements[i];
        int col = i % cols, row = i / cols;
        int x = ox + col * iw, y = oy + row * (ih + 4);
        if (y + ih > py + ph - 10)
            break;

        Color bg = a->unlocked ? (Color){40, 70, 30, 230} : (Color){22, 28, 22, 210};
        Color edge = a->unlocked ? (Color){120, 200, 60, 255} : (Color){50, 60, 50, 200};
        DrawRectangle(x, y, iw - 4, ih, bg);
        DrawRectangleLines(x, y, iw - 4, ih, edge);

        /* Icon */
        Color iconCol = a->unlocked ? GOLD : (Color){80, 80, 80, 200};
        DrawRectangle(x + 4, y + 4, 34, ih - 8, a->unlocked ? (Color){60, 50, 10, 200} : (Color){30, 30, 30, 200});
        DrawTextCenteredShort(a->icon, x + 21, y + (ih - 12) / 2, 11, iconCol);

        /* Tên + mô tả */
        Color nameCol = a->unlocked ? WHITE : (Color){100, 100, 100, 255};
        DrawTextShort(a->name,
                      x + 42,
                      y + 6,
                      13,
                      nameCol);

        DrawTextShort(a->desc,
                      x + 42,
                      y + 22,
                      10,
                      a->unlocked ? (Color){180, 220, 150, 255} : (Color){80, 90, 80, 255});
        /* Progress bar */
        if (!a->unlocked)
        {
            int pbx = x + 44;
            int pby = y + 36;
            int pbw = iw - 110;
            int cur = a->progress, tgt = a->threshold;
            float ratio = (tgt > 0) ? (float)cur / tgt : 0;
            if (ratio > 1)
                ratio = 1;
            DrawRectangle(pbx - 2, pby, pbw, 6, (Color){25, 25, 25, 200});
            DrawRectangle(pbx, pby, (int)(pbw * ratio), 6, (Color){80, 150, 80, 255});
            DrawRectangleLines(pbx - 4, pby - 1, pbw, 6, WHITE);
            DrawTextShort(TextFormat("%d/%d", cur, tgt),
                          pbx + pbw + 6,
                          pby - 2,
                          9,
                          (Color){140, 140, 140, 255});
        }
        else
        {
            DrawTextShort(TextFormat("%d / %d đã mở khóa", unlocked, MAX_ACHIEVEMENTS),
                          px + 20,
                          py + 34,
                          16,
                          (Color){180, 180, 180, 255});
=======
    
    /* Thanh tiến trình tổng - TO */
    int barX = px + 150, barY = py + 80, barW = pw - 300, barH = 25;
    
    // Nền
    DrawRectangle(barX, barY, barW, barH, (Color){30, 30, 45, 230});
    DrawRectangleLines(barX, barY, barW, barH, (Color){100, 100, 130, 200});
    
    // Phần đã đạt
    float totalRatio = (float)unlocked / MAX_ACHIEVEMENTS;
    DrawRectangleGradientH(barX, barY, (int)(barW * totalRatio), barH, 
                          (Color){255, 215, 0, 255}, (Color){255, 165, 0, 255});
    
    // Hiệu ứng sáng
    DrawRectangleGradientH(barX, barY, (int)(barW * totalRatio), barH/3, 
                          (Color){255, 255, 255, 120}, (Color){255, 255, 255, 20});
    
    /* BỎ: Icon hai bên thanh - DrawTextShort("🏆", ...) */
    
    /* Text tiến trình */
    char progressText[64];
    snprintf(progressText, sizeof(progressText), "%d / %d  %d%%", 
             unlocked, MAX_ACHIEVEMENTS, (int)(totalRatio * 100));
    DrawTextCenteredShort(progressText, px + pw / 2, barY + barH + 10, 20, 
                         unlocked == MAX_ACHIEVEMENTS ? GOLD : LIGHTGRAY);
    
    /* Nút Đóng */
    Rectangle closeBtn = {(float)(px + pw - 80), (float)(py + 18), 60, 32};
    bool closeHover = CheckCollisionPointRec(GetMousePosition(), closeBtn);
    
    Color closeColor = closeHover ? (Color){180, 60, 60, 255} : (Color){100, 35, 35, 230};
    DrawRectangleRec(closeBtn, closeColor);
    DrawRectangleLinesEx(closeBtn, 1, (Color){200, 150, 150, 200});
    /* ĐỔI: ✕ thành "X" */
    DrawTextCenteredShort("X", px + pw - 80 + 30, py + 18 + 6, 20, WHITE);
    
    if (closeHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        G.showAchievements = false;
        G.camZoom = savedCamZoom;
    }

    /* Vùng cuộn được */
    int contentX = px + 30;
    int contentY = py + 140;
    int contentW = pw - 90;
    int contentH = ph - (contentY - py) - 50;
    
    /* Tính chiều cao tổng */
    int itemHeight = 100;
    int totalItems = MAX_ACHIEVEMENTS;
    int totalHeight = totalItems * itemHeight;
    achMaxScroll = (totalHeight > contentH) ? totalHeight - contentH + 20 : 0;
    
    /* Giới hạn vùng vẽ */
    BeginScissorMode(contentX, contentY, contentW, contentH);
    
    int startY = contentY - achScrollOffset;
    
    for (int i = 0; i < MAX_ACHIEVEMENTS; i++)
    {
        Achievement *a = &achievements[i];
        int cy = startY + i * itemHeight;
        
        if (cy + itemHeight < contentY || cy > contentY + contentH)
            continue;

        bool isUnlocked = a->unlocked;
        
        /* Nền item với gradient */
        Color bgStart = isUnlocked ? (Color){45, 70, 45, 250} : (Color){28, 32, 28, 250};
        Color bgEnd = isUnlocked ? (Color){35, 55, 35, 250} : (Color){20, 24, 20, 250};
        DrawRectangleGradientV(contentX, cy, contentW - 25, itemHeight - 8, bgStart, bgEnd);
        
        /* Viền */
        Color borderColor = isUnlocked ? (Color){140, 220, 80, 255} : (Color){80, 90, 80, 200};
        DrawRectangleLines(contentX, cy, contentW - 25, itemHeight - 8, borderColor);
        
        /* Icon với hiệu ứng */
        DrawRectangle(contentX + 12, cy + 12, 55, 55, 
                     isUnlocked ? (Color){100, 75, 25, 255} : (Color){40, 40, 40, 220});
        DrawRectangleLines(contentX + 12, cy + 12, 55, 55, 
                          isUnlocked ? GOLD : (Color){100, 100, 100, 200});
        
        /* BỎ: Icon chính - DrawTextCenteredShort(a->icon, ...) */
        
        /* BỎ: Nếu đã mở khóa, thêm hiệu ứng sao - DrawTextShort("✦", ...) */
        
        /* Tên thành tựu */
        DrawTextShort(a->name, contentX + 80, cy + 15, 20, 
                     isUnlocked ? GOLD : (Color){200, 200, 200, 255});
        
        /* Mô tả */
        DrawTextShort(a->desc, contentX + 80, cy + 42, 16, 
                     isUnlocked ? (Color){220, 255, 220, 255} : (Color){150, 150, 150, 255});
        
        /* Progress bar TO */
        if (!isUnlocked)
        {
            int pbx = contentX + contentW - 260;
            int pby = cy + 25;
            int pbw = 240;
            int pbh = 28;
            
            float ratio = (a->threshold > 0) ? (float)a->progress / a->threshold : 0;
            if (ratio > 1) ratio = 1;
            
            // Nền
            DrawRectangle(pbx, pby, pbw, pbh, (Color){20, 20, 28, 240});
            DrawRectangleLines(pbx, pby, pbw, pbh, (Color){70, 70, 90, 200});
            
            // Màu theo tiến độ
            Color progressColor;
            if (ratio < 0.25f) progressColor = (Color){220, 80, 80, 255};
            else if (ratio < 0.5f) progressColor = (Color){240, 180, 50, 255};
            else if (ratio < 0.75f) progressColor = (Color){120, 200, 80, 255};
            else progressColor = (Color){80, 240, 80, 255};
            
            DrawRectangleGradientH(pbx, pby, (int)(pbw * ratio), pbh, 
                                  progressColor, (Color){progressColor.r, progressColor.g, progressColor.b, 200});
            
            // Hiệu ứng sáng
            DrawRectangleGradientH(pbx, pby, (int)(pbw * ratio), pbh/3, 
                                  (Color){255, 255, 255, 100}, (Color){255, 255, 255, 10});
            
            // Phần trăm ở giữa thanh
            char pctText[16];
            snprintf(pctText, sizeof(pctText), "%d%%", (int)(ratio * 100));
            DrawTextCenteredShort(pctText, pbx + pbw/2, pby + 6, 18, WHITE);
            
            // Số lượng DƯỚI thanh (không bị tràn ra ngoài menu)
            char numText[24];
            snprintf(numText, sizeof(numText), "%d / %d", a->progress, a->threshold);
            DrawTextCenteredShort(numText, pbx + pbw/2, pby + pbh + 4, 14,
                         a->progress >= a->threshold ? GOLD : (Color){160,160,160,255});
        }
        else
        {
            /* Đã mở khóa - hiển thị đẹp */
            int ubx = contentX + contentW - 220;
            int uby = cy + 25;
            
            DrawRectangleGradientH(ubx, uby, 180, 38, 
                                  (Color){50, 100, 50, 240}, (Color){35, 70, 35, 240});
            DrawRectangleLines(ubx, uby, 180, 38, (Color){100, 220, 100, 220});
            
            /* ĐỔI: ✓ thành "DA MO KHOA" */
            DrawTextCenteredShort("ĐÃ MỞ KHÓA", ubx + 90, uby + 8, 20, GREEN);
            /* BỎ: DrawTextShort("🏆", ...) và DrawTextShort("✨", ...) */
        }
    }
    
    EndScissorMode();

    /* THANH CUỘN (SCROLLBAR) */
    if (achMaxScroll > 0)
    {
        int scrollBarX = px + pw - 35;
        int scrollBarY = contentY;
        int scrollBarH = contentH;
        int scrollBarW = 16;
        
        // Nền thanh cuộn
        DrawRectangleRounded((Rectangle){(float)scrollBarX, (float)scrollBarY, 
                            (float)scrollBarW, (float)scrollBarH}, 0.5f, 8, 
                            (Color){45, 45, 60, 220});
        
        float thumbHeight = (float)contentH / (float)(contentH + achMaxScroll) * scrollBarH;
        if (thumbHeight < 50) thumbHeight = 50;
        
        float thumbPos = (float)achScrollOffset / (float)achMaxScroll * (scrollBarH - thumbHeight);
        
        Rectangle thumbRect = {
            (float)scrollBarX,
            scrollBarY + thumbPos,
            (float)scrollBarW,
            thumbHeight
        };
        
        Vector2 mousePos = GetMousePosition();
        bool thumbHover = CheckCollisionPointRec(mousePos, thumbRect);
        
        // Màu thanh trượt
        Color thumbColor = thumbHover ? (Color){220, 220, 250, 255} : (Color){180, 180, 220, 240};
        DrawRectangleRounded(thumbRect, 0.5f, 8, thumbColor);
        
        // Xử lý kéo scroll
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && thumbHover)
        {
            isDraggingAchScroll = true;
            dragAchStartY = mousePos.y;
            dragAchStartOffset = achScrollOffset;
        }
        
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            isDraggingAchScroll = false;
        
        if (isDraggingAchScroll)
        {
            int mouseDeltaY = mousePos.y - dragAchStartY;
            float scrollDelta = (float)mouseDeltaY / (scrollBarH - thumbHeight) * achMaxScroll;
            achScrollOffset = dragAchStartOffset + scrollDelta;
            
            if (achScrollOffset < 0) achScrollOffset = 0;
            if (achScrollOffset > achMaxScroll) achScrollOffset = achMaxScroll;
        }
        
        // Click vào vùng trống
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
            CheckCollisionPointRec(mousePos, 
                (Rectangle){(float)scrollBarX, (float)scrollBarY, (float)scrollBarW, (float)scrollBarH}) &&
            !thumbHover)
        {
            float clickPos = mousePos.y - scrollBarY;
            float targetOffset = (clickPos - thumbHeight/2) / (scrollBarH - thumbHeight) * achMaxScroll;
            
            if (targetOffset < 0) targetOffset = 0;
            if (targetOffset > achMaxScroll) targetOffset = achMaxScroll;
            
            achScrollOffset = targetOffset;
        }
        
        // Cuộn bằng bánh xe
        if (CheckCollisionPointRec(mousePos, (Rectangle){(float)contentX, (float)contentY, 
                                                         (float)contentW, (float)contentH}))
        {
            int wheel = GetMouseWheelMove();
            if (wheel != 0)
            {
                achScrollOffset -= wheel * 55;
                if (achScrollOffset < 0) achScrollOffset = 0;
                if (achScrollOffset > achMaxScroll) achScrollOffset = achMaxScroll;
            }
        }
    }
    else
    {
        achScrollOffset = 0;
        isDraggingAchScroll = false;
    }
    
    /* BỎ: Footer với icon - DrawTextCenteredShort("✦ ... ✦", ...) */
    /* THÊM: Footer đơn giản */
    DrawTextCenteredShort("TÍCH LŨY THÀNH TỰU ĐỂ NHẬN THƯỞNG", 
                          px + pw / 2, py + ph - 30, 18, (Color){180, 160, 100, 255});
    
    /* Khôi phục camera */
    if (!G.showAchievements)
        G.camZoom = savedCamZoom;
}
void DrawUI_BarnHpBars(void)
{
    float z = G.camZoom;

    for (int i = 0; i < MAX_BARNS; i++) {
        if (!G.barns[i].active) continue;

        /* Chỉ vẽ khi HP bị tổn thương hoặc đang flash damage */
        if (G.barnHp[i] >= BARN_MAX_HP && G.barnDmgTimer[i] <= 0.0f) continue;

        Barn *b = &G.barns[i];

        /* Vị trí: phía trên chuồng, căn giữa theo chiều ngang 5 tile */
        Vector2 worldTop = {
            (b->tileX + 2.5f) * TILE_SIZE,
            (float)(b->tileY * TILE_SIZE) - 6.0f
        };
        Vector2 sp = WorldToScreen(worldTop);

        float bw = 80.0f * z;
        float bh =  8.0f * z;
        float bx = sp.x - bw * 0.5f;
        float by = sp.y - bh;

        /* Nền thanh */
        DrawRectangle((int)bx, (int)by, (int)bw, (int)bh, (Color){20, 20, 20, 210});

        /* Thanh HP — màu thay đổi theo mức HP */
        float ratio = (float)G.barnHp[i] / (float)BARN_MAX_HP;
        Color hpCol = ratio > 0.6f ? (Color){ 60, 200,  60, 255}
                    : ratio > 0.3f ? (Color){220, 180,  30, 255}
                                   : (Color){220,  50,  50, 255};
        DrawRectangle((int)bx, (int)by, (int)(bw * ratio), (int)bh, hpCol);
        DrawRectangleLines((int)bx, (int)by, (int)bw, (int)bh, DARKGRAY);

        /* Flash đỏ khi vừa nhận damage */
        if (G.barnDmgTimer[i] > 0.0f) {
            unsigned char alpha = (unsigned char)(G.barnDmgTimer[i] / 0.4f * 140);
            DrawRectangle((int)bx - 2, (int)by - 2,
                          (int)bw + 4, (int)bh + 4,
                          (Color){255, 50, 50, alpha});
        }

        /* Text HP nhỏ phía trên thanh */
        DrawTextEx(gameFont,
                   TextFormat("HP %d/%d", G.barnHp[i], BARN_MAX_HP),
                   (Vector2){bx, by - 13.0f * z},
                   11.0f * z, 1,
                   (Color){220, 220, 220, 220});
    }
}

/* ─────────────────────────────────────────────────────────
   DrawUI_Settings — menu cài đặt (âm thanh + thông tin)
───────────────────────────────────────────────────────── */

/* Volume được lưu ở global để tránh reset mỗi lần mở panel */
static float g_masterVol = 1.0f;   /* 0.0 -> 1.0, bước 0.1 */

void DrawUI_Settings(void)
{
    if (!G.showSettings) return;

    int pw = 500, ph = 420;
    int px = SCREEN_W/2 - pw/2;
    int py = SCREEN_H/2 - ph/2;

    DrawRectangle(0, 0, SCREEN_W, SCREEN_H, (Color){0,0,0,120});
    DrawRectangle(px, py, pw, ph, (Color){14,18,34,252});
    DrawRectangleLines(px, py, pw, ph, (Color){100,150,220,255});
    DrawRectangle(px+2, py+2, pw-4, 40, (Color){30,50,100,200});
    DrawTextCenteredShort("CÀI ĐẶT", px+pw/2, py+10, 24, GOLD);

    if (Button(px+pw-88, py+7, 80, 28, "ĐÓNG",
               (Color){80,30,30,220}, (Color){150,50,50,255}))
        G.showSettings = false;

    int cx = px + 20;
    int cy = py + 56;

    /* ── Thông tin người chơi ── */
    DrawRectangle(px+6, cy-4, pw-12, 108, (Color){20,30,55,200});
    DrawRectangleLines(px+6, cy-4, pw-12, 108, (Color){60,90,160,220});
    DrawTextShort("THÔNG TIN NGƯỜI CHƠI", cx+4, cy+2, 16, (Color){160,200,255,255});
    cy += 24;

    const char *roleStr = "Người chơi";
    Color roleCol = (Color){180,220,255,255};
    if (G.player.role == ROLE_ADMIN)
        { roleStr = "Quản trị viên"; roleCol = (Color){255,100,100,255}; }
    else if (G.player.role == ROLE_TESTER)
        { roleStr = "Kiểm thử viên"; roleCol = (Color){255,210,60,255}; }

    DrawTextShort(TextFormat("Tên:      %s", G.player.username),
                  cx+8, cy, 15, WHITE); cy += 20;
    DrawTextShort("Vai trò:", cx+8, cy, 15, LIGHTGRAY);
    DrawTextShort(roleStr, cx+90, cy, 15, roleCol); cy += 20;
    DrawTextShort(TextFormat("Cấp: %d     Tiền: $%d     HP: %d / %d",
                  G.player.lvl.level, G.player.money,
                  G.player.hp, G.player.maxHp),
                  cx+8, cy, 14, (Color){190,215,255,255});
    cy += 30;

    /* ── Âm thanh ── */
    DrawRectangle(px+6, cy-4, pw-12, 96, (Color){20,30,55,200});
    DrawRectangleLines(px+6, cy-4, pw-12, 96, (Color){60,90,160,220});
    DrawTextShort("AM THANH", cx+4, cy+2, 16, (Color){160,200,255,255});
    cy += 26;

    /* Hiển thị mức âm lượng bằng thanh ô vuông — không dùng chuột kéo */
    DrawTextShort("Am luong:", cx+8, cy+4, 15, WHITE);
    int barX = cx + 110;
    int steps = 10;
    int bw = 22, bh = 22, bgap = 4;
    int filled = (int)(g_masterVol * steps + 0.5f);
    for (int i = 0; i < steps; i++) {
        int bx = barX + i*(bw+bgap);
        Color bc = (i < filled) ? (Color){80,180,255,255} : (Color){40,40,60,220};
        DrawRectangle(bx, cy, bw, bh, bc);
        DrawRectangleLines(bx, cy, bw, bh, (Color){70,110,180,180});
    }
    DrawTextShort(TextFormat("%d%%", filled*10), barX+steps*(bw+bgap)+6, cy+4, 14, LIGHTGRAY);
    cy += 32;

    /* Nút [-] [+] điều chỉnh âm lượng — CHỈ dùng Button(), không dùng IsMouseButtonDown */
    if (Button(cx+8, cy, 46, 28, "  -  ",
               (Color){60,60,100,220}, (Color){90,90,150,255})) {
        if (g_masterVol > 0.0f) {
            g_masterVol -= 0.1f;
            if (g_masterVol < 0.0f) g_masterVol = 0.0f;
            Audio_SetVolume(g_masterVol);
        }
    }
    DrawTextCenteredShort(TextFormat("%d%%", (int)(g_masterVol*100+0.5f)),
                          cx+90, cy+6, 16, WHITE);
    if (Button(cx+130, cy, 46, 28, "  +  ",
               (Color){60,60,100,220}, (Color){90,90,150,255})) {
        if (g_masterVol < 1.0f) {
            g_masterVol += 0.1f;
            if (g_masterVol > 1.0f) g_masterVol = 1.0f;
            Audio_SetVolume(g_masterVol);
        }
    }
    /* Nút tắt hẳn / khôi phục */
    if (g_masterVol > 0.0f) {
        if (Button(cx+200, cy, 110, 28, "TAT TIENG",
                   (Color){140,40,40,220}, (Color){200,60,60,255})) {
            g_masterVol = 0.0f;
            Audio_SetVolume(0.0f);
        }
    } else {
        if (Button(cx+200, cy, 110, 28, "BAT TIENG",
                   (Color){40,120,60,220}, (Color){60,180,90,255})) {
            g_masterVol = 0.5f;
            Audio_SetVolume(0.5f);
        }
    }
    cy += 44;

    /* ── Phím tắt ── */
    if (G.player.role == ROLE_ADMIN || G.player.role == ROLE_TESTER) {
        int bxH = (G.player.role == ROLE_ADMIN) ? 110 : 60;
        DrawRectangle(px+6, cy-4, pw-12, bxH, (Color){38,16,16,200});
        DrawRectangleLines(px+6, cy-4, pw-12, bxH, (Color){150,55,55,220});
        const char *title = (G.player.role==ROLE_ADMIN) ? "PHIM TAT ADMIN" : "PHIM TAT TESTER";
        DrawTextShort(title, cx+4, cy+2, 16, (Color){255,140,140,255}); cy += 24;
        if (G.player.role == ROLE_ADMIN) {
            DrawTextShort("F9=GodMode  F10=Ngay/Dem  F11=Ngay moi",  cx+8, cy, 14, (Color){220,180,180,255}); cy+=19;
            DrawTextShort("F6=ThoiTiet  F8=+Ngoc  M=+Tien  K=GietQuai", cx+8, cy, 14, (Color){220,180,180,255}); cy+=19;
            DrawTextShort("H=FullHP  T=CayChin  G=ThemHat  D=DaoTatCaDat", cx+8, cy, 14, (Color){220,180,180,255});
        } else {
            DrawTextShort("T=CayChin  H=PhucHoiHP  F6=ThoiTiet",       cx+8, cy, 14, (Color){220,180,180,255});
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
        }
    }
}