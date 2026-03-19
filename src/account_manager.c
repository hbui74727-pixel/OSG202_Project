#include "account_manager.h"
#include "data_manager.h"
#include "entity_manager.h"
#include "quest_system.h"

void Account_LoadAll(void)
{
    MakeDirectory("saves");
    FILE *f = fopen(ACCOUNTS_FILE, "rb");
    if (!f) return;
    fread(&G.accountCount, sizeof(int), 1, f);
    fread(G.accounts, sizeof(Account), G.accountCount, f);
    fclose(f);
    /* Đảm bảo luôn có ADMIN */
bool found = false;
for (int i = 0; i < G.accountCount; i++) {
    if (strcmp(G.accounts[i].username, "ADMIN") == 0) {
        found = true;
        break;
    }
}

if (!found && G.accountCount < MAX_ACCOUNTS) {
    Account *a = &G.accounts[G.accountCount++];
    memset(a, 0, sizeof(Account));
    strcpy(a->username, "ADMIN");
    strcpy(a->password, "1234");
    a->role = ROLE_ADMIN;
    a->active = true;
}
}

void Account_SaveAll(void)
{
    MakeDirectory("saves");
    FILE *f = fopen(ACCOUNTS_FILE, "wb");
    if (!f) return;
    fwrite(&G.accountCount, sizeof(int), 1, f);
    fwrite(G.accounts, sizeof(Account), G.accountCount, f);
    fclose(f);
}

bool Account_Register(const char *user, const char *pass, PlayerRole role, char *errOut)
{
    if (strcmp(user, "ADMIN") == 0) {
    strcpy(errOut, "Tên này bị khóa!");
    return false;
}
    if (strlen(user) < 3) { strcpy(errOut, "Tên đăng nhập >= 3 ký tự!"); return false; }
    if (strlen(pass) < 4) { strcpy(errOut, "Mật khẩu >= 4 ký tự!");      return false; }
    if (G.accountCount >= MAX_ACCOUNTS) { strcpy(errOut, "Server đầy!"); return false; }

    for (int i = 0; i < G.accountCount; i++) {
        if (G.accounts[i].active &&
            strcmp(G.accounts[i].username, user) == 0) {
            strcpy(errOut, "Tên tài khoản đã tồn tại!");
            return false;
        }
    }

    Account *a = &G.accounts[G.accountCount++];
    strncpy(a->username, user, MAX_NAME_LEN - 1);
    strncpy(a->password, pass, MAX_PASS_LEN - 1);
    a->role   = role;
    a->active = true;
    Account_SaveAll();
    errOut[0] = '\0';
    return true;
}

bool Account_Login(const char *user, const char *pass, char *errOut)
{
    for (int i = 0; i < G.accountCount; i++) {
        Account *a = &G.accounts[i];
        if (!a->active) continue;
        if (strcmp(a->username, user) == 0 && strcmp(a->password, pass) == 0) {
            /* Gán thông tin player */
            strncpy(G.player.username, a->username, MAX_NAME_LEN - 1);
            G.player.role = a->role;
            errOut[0] = '\0';

            /* Load save của tài khoản này */
            char savePath[128];
            snprintf(savePath, sizeof(savePath), "saves/%s.dat", user);
            Game_LoadPlayer(savePath);
            return true;
        }
    }
    strcpy(errOut, "Sai tên đăng nhập hoặc mật khẩu!");
    return false;
}

void Account_Logout(void)
{
    /* Lưu save tài khoản hiện tại trước khi thoát */
    char savePath[128];
    snprintf(savePath, sizeof(savePath), "saves/%s.dat", G.player.username);
    Game_SavePlayer(savePath);

    /* ── Reset toàn bộ game world để tài khoản mới đăng nhập sạch ── */
    /* Xóa map về trạng thái ban đầu */
    EntityManager_InitMap();

    /* Xóa crops */
    for (int i = 0; i < MAX_CROPS; i++)   G.crops[i].active   = false;
    G.cropCount = 0;

    /* Xóa barns + animals */
    for (int i = 0; i < MAX_BARNS;   i++) G.barns[i].active   = false;
    for (int i = 0; i < MAX_ANIMALS; i++) G.animals[i].active = false;
    G.barnCount   = 0;
    G.animalCount = 0;

    /* Xóa enemies */
    for (int i = 0; i < MAX_ENEMIES; i++) G.enemies[i].active = false;
    G.enemyCount  = 0;
    G.goblinCount = 0;

    /* Reset counters */
    G.gemCount    = 0;
    G.bossAlive   = false;
    G.day         = 1;
    G.dayTimer    = 0.0f;
    G.gameTime    = 0.0f;
    G.spawnTimer  = 30.0f;
    G.skeletonTimer = 300.0f;
    G.endGame     = false;
    G.endWin      = false;
    G.isNight     = false;
    G.nightOverlay = 0.0f;
    G.lastBossDay = 0;

    /* Reset barn HP */
    for (int i = 0; i < MAX_BARNS; i++) {
        G.barnHp[i]       = BARN_MAX_HP;
        G.barnDmgTimer[i] = 0.0f;
    }

    /* Reset UI state */
    G.showInventory    = false;
    G.showStore        = false;
    G.showBarnUI       = false;
    G.showHelp         = false;
    G.showQuest        = false;
    G.showAchievements = false;

    G.editMode         = false;
    G.isMoving         = false;
    G.paused           = false;
    G.hbarPlacing      = false;
    G.hbarSel          = -1;
    G.msgTimer         = 0.0f;

    /* Reset player (giữ trống để GameLogic_Init + Game_LoadPlayer điền lại) */
    memset(&G.player, 0, sizeof(Player));

    /* Reset quests cho tài khoản mới */
    extern void Quest_Init(void);
    Quest_Init();

    /* Reset achievement counters + trang thai cho tai khoan moi */
    extern int achTotalHarvested, achTotalKills, achTotalPlanted, achTotalCollected, achTotalEarned;
    achTotalHarvested = 0;
    achTotalKills     = 0;
    achTotalPlanted   = 0;
    achTotalCollected = 0;
    achTotalEarned    = 0;
    extern void Achievement_Init(void);
    Achievement_Init();

    /* Reset login form */
    G.screen      = SCR_LOGIN;
    memset(G.loginUser, 0, sizeof(G.loginUser));
    memset(G.loginPass, 0, sizeof(G.loginPass));
    G.loginField  = 0;
    G.loginError[0] = '\0';
}

void Account_ToggleAdmin(void)
{
    if (G.player.role == ROLE_ADMIN) {
        G.player.role = ROLE_PLAYER;
        strncpy(G.message, "Đã thoát chế độ Admin", sizeof(G.message));
    } else {
        G.player.role = ROLE_ADMIN;
        strncpy(G.message, "Admin: M=+$5000 | H=Full HP | T=Cây chín | K=Kill all", sizeof(G.message));
    }
    G.msgTimer = 4.0f;
}

/* ─── Xử lý nhập liệu đăng nhập ── */
static void AppendChar(char *buf, int maxLen, int key)
{
    if (key < 32) return;
    int len = (int)strlen(buf);
    /* Encode Unicode codepoint sang UTF-8 */
    char utf8[5] = {0};
    int bytes = 0;
    if (key <= 0x7F) {
        utf8[0] = (char)key; bytes = 1;
    } else if (key <= 0x7FF) {
        utf8[0] = (char)(0xC0 | (key >> 6));
        utf8[1] = (char)(0x80 | (key & 0x3F));
        bytes = 2;
    } else if (key <= 0xFFFF) {
        utf8[0] = (char)(0xE0 | (key >> 12));
        utf8[1] = (char)(0x80 | ((key >> 6) & 0x3F));
        utf8[2] = (char)(0x80 | (key & 0x3F));
        bytes = 3;
    } else {
        utf8[0] = (char)(0xF0 | (key >> 18));
        utf8[1] = (char)(0x80 | ((key >> 12) & 0x3F));
        utf8[2] = (char)(0x80 | ((key >> 6) & 0x3F));
        utf8[3] = (char)(0x80 | (key & 0x3F));
        bytes = 4;
    }
    if (len + bytes >= maxLen) return;
    for (int i = 0; i < bytes; i++) buf[len + i] = utf8[i];
    buf[len + bytes] = '\0';
}
static void DeleteChar(char *buf)
{
    int len = (int)strlen(buf);
    if (len == 0) return;
    /* Xóa ký tự UTF-8 cuối (lùi qua các byte continuation 0x80-0xBF) */
    int i = len - 1;
    while (i > 0 && ((unsigned char)buf[i] & 0xC0) == 0x80) i--;
    buf[i] = '\0';
}

void Account_HandleLoginInput(void)
{
    /* Tab / Click chuyển field */
    if (IsKeyPressed(KEY_TAB))
        G.loginField = (G.loginField + 1) % 2;

    /* Backspace */
    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (G.loginField == 0) DeleteChar(G.loginUser);
        else                   DeleteChar(G.loginPass);
    }

    /* Nhập ký tự */
    int key = GetCharPressed();
    while (key > 0) {
        if (G.loginField == 0) AppendChar(G.loginUser, MAX_NAME_LEN, key);
        else                   AppendChar(G.loginPass, MAX_PASS_LEN, key);
        key = GetCharPressed();
    }

    /* Enter = đăng nhập */
    if (IsKeyPressed(KEY_ENTER)) {
        if (Account_Login(G.loginUser, G.loginPass, G.loginError)) {
            G.screen = SCR_GAME;
        }
    }
}

void Account_HandleRegisterInput(void)
{
    if (IsKeyPressed(KEY_TAB))
        G.regField = (G.regField + 1) % 3;

    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (G.regField == 0)      DeleteChar(G.regUser);
        else if (G.regField == 1) DeleteChar(G.regPass);
        else                      DeleteChar(G.regPass2);
    }

    int key = GetCharPressed();
    while (key > 0) {
        if (G.regField == 0)      AppendChar(G.regUser,  MAX_NAME_LEN, key);
        else if (G.regField == 1) AppendChar(G.regPass,  MAX_PASS_LEN, key);
        else                      AppendChar(G.regPass2, MAX_PASS_LEN, key);
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (strcmp(G.regPass, G.regPass2) != 0) {
            strcpy(G.regError, "Mật khẩu xác nhận không khớp!");
            return;
        }
        if (Account_Register(G.regUser, G.regPass, G.regRole, G.regError)) {
            /* Đăng ký xong → về login */
            G.screen = SCR_LOGIN;
            strncpy(G.loginUser, G.regUser, MAX_NAME_LEN - 1);
            memset(G.loginPass, 0, sizeof(G.loginPass));
            strncpy(G.loginError, "Đăng ký thành công! Hãy đăng nhập.", sizeof(G.loginError));
        }
    }
}