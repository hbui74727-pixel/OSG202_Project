#include "textures.h"

// Load texture, fallback về ô hồng 8x8 nếu file không tồn tại
static Texture2D SafeLoad(const char *path)
{
    if (FileExists(path))
        return LoadTexture(path);

    TraceLog(LOG_WARNING, "TEXTURE: Missing file: %s", path);
    Image img = GenImageColor(8, 8, MAGENTA);
    Texture2D t = LoadTextureFromImage(img);
    UnloadImage(img);
    return t;
}

void Textures_Load(void)
{
    //LOGIN
    T.loginBg = LoadTexture("assets/backgrounds/login_bg.jpg");

    // ── Player ────────────────────────────────────────────
    T.pIdle             = SafeLoad("assets/characters/player/idle_strip.png");
    T.pWalk[DIR_DOWN]   = SafeLoad("assets/characters/player/walk_down_strip.png");
    T.pWalk[DIR_UP]     = SafeLoad("assets/characters/player/walk_up_strip.png");
    T.pWalk[DIR_LEFT]   = SafeLoad("assets/characters/player/walk_left_strip.png");
    T.pWalk[DIR_RIGHT]  = SafeLoad("assets/characters/player/walk_right_strip.png");
    T.pRun[DIR_DOWN]    = SafeLoad("assets/characters/player/run_down_strip.png");
    T.pRun[DIR_UP]      = SafeLoad("assets/characters/player/run_up_strip.png");
    T.pRun[DIR_LEFT]    = SafeLoad("assets/characters/player/run_left_strip.png");
    T.pRun[DIR_RIGHT]   = SafeLoad("assets/characters/player/run_right_strip.png");
    T.pDig              = SafeLoad("assets/characters/player/dig_strip.png");
    T.pWater            = SafeLoad("assets/characters/player/water_strip.png");
    T.pHurt             = SafeLoad("assets/characters/player/hurt_strip.png");

    // ── Goblin  [0]idle [1]walk [2]attack [3]hurt [4]death ─
    T.goblin[0] = SafeLoad("assets/characters/goblin/goblin_idle_strip8.png");
    T.goblin[1] = SafeLoad("assets/characters/goblin/goblin_walk_strip8.png");
    T.goblin[2] = SafeLoad("assets/characters/goblin/goblin_attack_strip8.png");
    T.goblin[3] = SafeLoad("assets/characters/goblin/goblin_hurt_strip8.png");
    T.goblin[4] = SafeLoad("assets/characters/goblin/goblin_death_strip10.png");

    // ── Skeleton ─────────────────────────────────────────
    T.skel[0] = SafeLoad("assets/characters/SKELETON/skeleton_idle_strip6.png");
    T.skel[1] = SafeLoad("assets/characters/SKELETON/skeleton_walk_strip8.png");
    T.skel[2] = SafeLoad("assets/characters/SKELETON/skeleton_attack_strip7.png");
    T.skel[3] = SafeLoad("assets/characters/SKELETON/skeleton_hurt_strip7.png");
    T.skel[4] = SafeLoad("assets/characters/SKELETON/skeleton_death_strip10.png");

    // ── Crops ────────────────────────────────────────────
    T.crop[CROP_CARROT]      = SafeLoad("assets/crops/carrot_strip.png");
    T.crop[CROP_BEETROOT]    = SafeLoad("assets/crops/beetroot_strip.png");
    T.crop[CROP_CABBAGE]     = SafeLoad("assets/crops/cabbage_strip.png");
    T.crop[CROP_CAULIFLOWER] = SafeLoad("assets/crops/cauliflower_strip.png");
    T.crop[CROP_KALE]        = SafeLoad("assets/crops/kale_strip.png");
    T.crop[CROP_PARSNIP]     = SafeLoad("assets/crops/parsnip_strip.png");
    T.crop[CROP_POTATO]      = SafeLoad("assets/crops/potato_strip.png");
    T.crop[CROP_PUMPKIN]     = SafeLoad("assets/crops/pumpkin_strip.png");
    T.crop[CROP_RADISH]      = SafeLoad("assets/crops/radish_strip.png");
    T.crop[CROP_SUNFLOWER]   = SafeLoad("assets/crops/sunflower_strip.png");
    T.crop[CROP_WHEAT]       = SafeLoad("assets/crops/wheat_strip.png");

    // ── Animals ──────────────────────────────────────────
    T.animal[ANIMAL_CHICKEN] = SafeLoad("assets/animal/chicken_strip.png");
    T.animal[ANIMAL_PIG]     = SafeLoad("assets/animal/pig_strip.png");
    T.animal[ANIMAL_SHEEP]   = SafeLoad("assets/animal/sheep_strip.png");

    // ── Tileset ──────────────────────────────────────────
    T.tileset = SafeLoad("assets/spr_tileset_sunnysideworld.png");
    SetTextureFilter(T.tileset, TEXTURE_FILTER_POINT);

    // ── Item icons ───────────────────────────────────────
    T.iEgg  = SafeLoad("assets/crops/egg.png");
    T.iMilk = SafeLoad("assets/crops/milk.png");
    T.iWood = SafeLoad("assets/crops/wood.png");
    T.iRock = SafeLoad("assets/crops/rock.png");
    T.iSeed = SafeLoad("assets/crops/seeds_generic.png");
    T.iFeed = SafeLoad("assets/crops/fish.png");

    // ── Tree ─────────────────────────────────────────────
    T.tree = SafeLoad("assets/backgrounds/tree.png");
    SetTextureFilter(T.tree, TEXTURE_FILTER_POINT);

    // ── Ground tileset (160x16, 10 tiles 16x16) ──────────
    // Tile 0-5: cỏ xanh, Tile 6-8: đất đào, Tile 9: đất nhạt/ướt
    T.ground = SafeLoad("assets/backgrounds/ground.png");
    SetTextureFilter(T.ground, TEXTURE_FILTER_POINT);

    // ── Home / objects spritesheet (240x320, 48x48) ──────
    T.home = SafeLoad("assets/objects/home.png");
    SetTextureFilter(T.home, TEXTURE_FILTER_POINT);

    // ── Chuồng fence tileset (96x112, 16x16 per tile) ─────
    T.chuong = SafeLoad("assets/objects/chuong.png");
    T.animal_fence = SafeLoad("assets/objects/animal.png");
    SetTextureFilter(T.animal_fence, TEXTURE_FILTER_POINT);
    SetTextureFilter(T.chuong, TEXTURE_FILTER_POINT);
}

void Textures_Unload(void)
{
    UnloadTexture(T.pIdle);
    for (int i = 0; i < 4; i++) {
        UnloadTexture(T.pWalk[i]);
        UnloadTexture(T.pRun[i]);
    }
    UnloadTexture(T.pDig);
    UnloadTexture(T.pWater);
    UnloadTexture(T.pHurt);

    for (int i = 0; i < 5; i++) {
        UnloadTexture(T.goblin[i]);
        UnloadTexture(T.skel[i]);
    }
    for (int i = 0; i < NUM_CROP_TYPES; i++) UnloadTexture(T.crop[i]);
    for (int i = 0; i < ANIMAL_COUNT; i++)   UnloadTexture(T.animal[i]);

    UnloadTexture(T.tileset);
    UnloadTexture(T.iEgg);
    UnloadTexture(T.iMilk);
    UnloadTexture(T.iWood);
    UnloadTexture(T.iRock);
    UnloadTexture(T.iSeed);
    UnloadTexture(T.iFeed);
    UnloadTexture(T.tree);
    UnloadTexture(T.loginBg);
    UnloadTexture(T.ground);
    UnloadTexture(T.home);
    UnloadTexture(T.chuong);
    UnloadTexture(T.animal_fence);
}
