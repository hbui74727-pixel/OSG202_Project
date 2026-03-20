#include "types.h"
#include "textures.h"
#include "renderer.h"
#include "game_logic.h"
#include "entity_manager.h"
#include "data_manager.h"
#include "quest_system.h"
#include "account_manager.h"
#include "achievement_system.h"
#include "event_system.h"
#include "admin_commands.h"
#include "access_control.h"
#include "draw/draw_tile.h"
#include "draw/draw_player.h"
#include "draw/draw_crop.h"
#include "draw/draw_animal.h"
#include "draw/draw_hud.h"
#include "draw/draw_building.h"
#include "draw/draw_debug.h"
#include "draw/draw_ui.h"
#include "font_manager.h"
#include "audio_manager.h"

GameState G;
Textures T;

static void DrawGame(void)
{
    /* ── Vẽ world trước ── */
    DrawTile_All();
    DrawTile_Highlight();
    DrawBuilding_All();
    DrawBuilding_HomeAll();
    DrawAnimal_Barns();
    DrawCrop_All();
    DrawAnimal_All();
    EntityManager_DrawEnemies();
    DrawPlayer_Character();

    /* ── Hiệu ứng thời tiết + đêm SAU world, TRƯỚC HUD ──
       Phủ lên cảnh vật nhưng không bị tile map che mất   */
    DrawHUD_Weather();
    DrawHUD_NightOverlay();

    DrawDebug_All();

    DrawHUD_TopBar();
    DrawHUD_PlacementGhost();    /* ghost preview trước UI */
    DrawHUD_PlacementBar();      /* hotbar mới */
    DrawUI_SidePanel();
    DrawUI_QuestPanel();
    DrawHUD_Minimap();
    DrawHUD_Message();
    DrawHUD_LevelUp();

    DrawUI_Inventory();
    DrawUI_Store();
    DrawUI_BarnPanel();
    DrawUI_Help();
    DrawUI_Achievements();
    DrawUI_Settings();
    DrawUI_BarnHpBars();     /* HP bar chuồng trên map */

    if (G.paused)
        DrawUI_PauseScreen();

    DrawTextCenteredShort(TextFormat("FPS:%d", GetFPS()), 20, SCREEN_H - 26, 10, (Color){90, 90, 90, 180});
}

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(SCREEN_W, SCREEN_H, GAME_TITLE);
    SetTargetFPS(TARGET_FPS);

    SetExitKey(KEY_NULL);
    Audio_Init();
    Font_Load();
    RenderTexture2D target = LoadRenderTexture(SCREEN_W, SCREEN_H);

    memset(&G, 0, sizeof(GameState));
    memset(&T, 0, sizeof(Textures));

    G.screen = SCR_LOGIN;
    G.camZoom = 1.0f;
    G.day = 1;
    G.selectedBarn = -1;
    G.regRole = ROLE_PLAYER;

    MakeDirectory("saves");
    MakeDirectory("logs");

    Textures_Load();
    EntityManager_InitMap();
    EntityManager_InitAnimals();
    Quest_Init();
    Achievement_Init();
    Account_LoadAll();

    Game_Log("=== SUNNY WORLD started ===");

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F11))
            ToggleFullscreen();

        float dt = GetFrameTime();
        Audio_Update();
        if (dt > 0.1f)
            dt = 0.1f;

        switch (G.screen)
        {
        case SCR_LOGIN:
            G.gameTime += dt;
            Account_HandleLoginInput();
            if (G.screen == SCR_GAME)
                GameLogic_Init();
            break;

        case SCR_REGISTER:
            G.gameTime += dt;
            Account_HandleRegisterInput();
            break;

        case SCR_GAME:
            if (!G.paused)
            {
                GameLogic_Update(dt);
                Event_FlushAll();
                Achievement_Check();
            }
            if (IsKeyPressed(KEY_ESCAPE)) {
                G.paused = !G.paused;
                if (G.paused) Audio_Pause(); else Audio_Resume();
            }
            break;

        case SCR_PAUSE:
            if (IsKeyPressed(KEY_ESCAPE))
                G.screen = SCR_GAME;
            break;

        default:
            break;
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 w = ScreenToWorld(GetMousePosition());
        Player_UseTool(w);
    }
        BeginTextureMode(target);
        ClearBackground((Color){34, 90, 34, 255});

        switch (G.screen)
        {
        case SCR_LOGIN:
            DrawUI_LoginScreen();
            break;
        case SCR_REGISTER:
            DrawUI_RegisterScreen();
            break;
        case SCR_GAME:
        case SCR_PAUSE:
            DrawGame();
            break;
        default:
            break;
        }
        /* End game overlay — chỉ vẽ khi đang trong game */
        if (G.screen == SCR_GAME || G.screen == SCR_PAUSE)
            DrawHUD_EndGame();
        EndTextureMode();
        BeginDrawing();
        ClearBackground(BLACK);

        // float scale = fminf(
        //     (float)GetScreenWidth() / SCREEN_W,
        //     (float)GetScreenHeight() / SCREEN_H);

        // Rectangle src = {0, 0, SCREEN_W, -SCREEN_H};
        // Rectangle dst = {
        //     (GetScreenWidth() - SCREEN_W * scale) * 0.5f,
        //     (GetScreenHeight() - SCREEN_H * scale) * 0.5f,
        //     SCREEN_W * scale,
        //     SCREEN_H * scale};

        //DrawTexturePro(target.texture, src, dst, (Vector2){0, 0}, 0, WHITE);
        float sw = (float)GetScreenWidth();
       float sh = (float)GetScreenHeight();
       float scale = fminf(sw / SCREEN_W, sh / SCREEN_H);


       Rectangle src = { 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height };
       Rectangle dst = {
           (sw - (float)SCREEN_W * scale) * 0.5f,
           (sh - (float)SCREEN_H * scale) * 0.5f,
           (float)SCREEN_W * scale,
           (float)SCREEN_H * scale
       };


       DrawTexturePro(target.texture, src, dst, (Vector2){ 0, 0 }, 0.0f, WHITE);
       /* --- [KET THUC PHAN SUA: TINH TOAN CAN GIUA HOAN HAO] --- */



        EndDrawing();
    }

    /* Auto-save khi thoát */
    if (G.screen == SCR_GAME || G.screen == SCR_PAUSE)
    {
        char sp[128];
        snprintf(sp, sizeof(sp), "saves/%s.dat", G.player.username);
        Game_SavePlayer(sp);
    }
    Account_SaveAll();
    Game_Log("=== SUNNY WORLD closed ===");
    Textures_Unload();
    Font_Unload();
    Audio_Unload();
    CloseWindow();
    return 0;
}