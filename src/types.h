#ifndef TYPES_H
#define TYPES_H

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define SCREEN_W        1280
#define SCREEN_H        720
#define TARGET_FPS      60
#define GAME_TITLE      "SUNNY WORLD"

#define MAP_COLS        60
#define MAP_ROWS        45
#define TILE_SIZE       48
#define MAP_PX_W        (MAP_COLS * TILE_SIZE)
#define MAP_PX_H        (MAP_ROWS * TILE_SIZE)

#define PLAYER_SPEED        200.0f
#define PLAYER_RUN_SPEED    320.0f
#define PLAYER_MAX_HP       100
#define PLAYER_FRAME_W      96
#define PLAYER_FRAME_H      64
#define PLAYER_REACH        (TILE_SIZE * 2.5f)

#define MAX_LEVEL           30
#define EXP_PER_HARVEST     20
#define EXP_PER_PLANT       5
#define EXP_PER_KILL        15
#define EXP_PER_COLLECT     8
#define EXP_BASE            100     // exp cần cho level 1->2

#define MAX_LAND_PLOTS      60
#define LAND_PLOT_W         5
#define LAND_PLOT_H         5
#define LAND_PRICE_BASE     150

#define MAX_CROPS           600
#define GROW_SECS_STAGE     55.0f
#define NUM_CROP_TYPES      11

#define MAX_BARNS           12
#define MAX_ANIMALS_PER_BARN 5
#define MAX_ANIMALS         (MAX_BARNS * MAX_ANIMALS_PER_BARN)
#define BARN_PRICE          500
#define ANIMAL_PRICE        150
#define FEED_PRICE          20
#define FEED_SECS           50.0f
#define PRODUCE_SECS        70.0f

#define MAX_ENEMIES         55
#define MAX_GOBLINS         50
#define GOBLIN_SPEED        32.0f
#define SKEL_SPEED          28.0f
#define BOSS_SPEED          22.0f
#define ENEMY_SPEED         32.0f
#define ENEMY_FRAME_W       96
#define ENEMY_FRAME_H       64
#define ATTACK_RANGE        54.0f
#define ATTACK_DAMAGE       8
#define ATTACK_COOLDOWN     1.8f
#define SPAWN_INTERVAL      60.0f

#define INV_SLOTS           32
#define HOTBAR_SIZE         8
#define STARTING_MONEY      5000

#define MAX_QUESTS          5
#define ANIM_FPS            10.0f
#define DAY_DURATION        300.0f

#define MAX_ACCOUNTS        20
#define BARN_MAX_HP         100     /* HP tối đa của mỗi chuồng */
#define BARN_GOBLIN_DMG     12      /* damage goblin gây cho chuồng mỗi lần */
#define NIGHT_START_RATIO   0.65f   /* đêm bắt đầu khi dayTimer > 65% DAY_DURATION */
#define STORAGE_SLOTS       64      /* số slot kho đồ */
#define MAX_NAME_LEN        32
#define MAX_PASS_LEN        32
#define ACCOUNTS_FILE       "saves/accounts.dat"
#define LOG_FILE            "logs/history.log"

#ifndef Clamp
#define Clamp(v,mn,mx) ((v)<(mn)?(mn):((v)>(mx)?(mx):(v)))
#endif

#define KEY_F2 291

#ifndef KEY_GRAVE
#define KEY_GRAVE 96
#endif
#ifndef KEY_K
#define KEY_K 75
#endif
#ifndef KEY_G
#define KEY_G 71
#endif
#ifndef KEY_F3
#define KEY_F3 292
#endif
#define BARN_W      5
#define BARN_H      5



/* ── Hotbar placement item types (explicit values to avoid enum offset bugs) ── */
typedef enum {
    HBAR_NONE        = 0,
    HBAR_SOIL        = 1,   /* Đặt ô đất 3x3 (vô hạn)          */
    HBAR_WATER       = 2,   /* Tưới nước (vô hạn)               */
    HBAR_BARN        = 3,   /* Đặt chuồng trống 3x3             */
    /* Hạt giống: HBAR_SEED_0 + CropType (0..10) = 11 loại */
    HBAR_SEED_0      = 10,
    HBAR_SEED_LAST   = 20,  /* = HBAR_SEED_0 + NUM_CROP_TYPES-1 */
    /* Động vật: HBAR_ANIMAL_0 + AnimalType (0..2) = 3 loại */
    HBAR_ANIMAL_0    = 30,
    HBAR_ANIMAL_LAST = 32,  /* = HBAR_ANIMAL_0 + ANIMAL_COUNT-1 */
} HotbarItemKind;

/* slot: 0=Dat, 1=Nuoc, 2=Chuong, 3-13=11 cay, 14-16=3 thu */
#define HBAR_SLOT_COUNT  17

typedef struct {
    HotbarItemKind kind;
} HotbarSlot;

/* ── Enums ── */
typedef enum { SCR_LOGIN=0, SCR_REGISTER, SCR_MENU, SCR_GAME, SCR_PAUSE } GameScreen;
typedef enum { DIR_DOWN=0, DIR_UP, DIR_LEFT, DIR_RIGHT } Direction;
typedef enum { ANIM_IDLE=0, ANIM_WALK, ANIM_RUN, ANIM_DIG, ANIM_WATER, ANIM_HURT } AnimState;

typedef enum {
    TOOL_HOE=0,         /* 1: Cuốc – đào đất      */
    TOOL_WATERING_CAN,  /* 2: Bình tưới            */
    TOOL_SEED,          /* 3: Trồng hạt giống      */
    TOOL_SCYTHE,        /* 4: Liềm – thu hoạch     */
    TOOL_SWORD,         /* 5: Kiếm – chiến đấu     */
    TOOL_FEED,          /* 6: Cho ăn động vật      */
    TOOL_COUNT,
    TOOL_AXE
} ToolType;

typedef enum {
    TILE_GRASS=0,
    TILE_SOIL_BOUGHT,   /* đã mua, chưa đào    */
    TILE_SOIL_DUG,      /* đã đào              */
    TILE_SOIL_WET,      /* đã tưới             */
    TILE_SOIL_PLANTED,  /* đã trồng            */
    TILE_PATH,
    TILE_WATER_TILE,
    TILE_STONE
} TileType;

typedef enum {
    ITEM_SEED_CARROT=0, ITEM_SEED_BEETROOT, ITEM_SEED_CABBAGE,
    ITEM_SEED_CAULIFLOWER, ITEM_SEED_KALE, ITEM_SEED_PARSNIP,
    ITEM_SEED_POTATO, ITEM_SEED_PUMPKIN, ITEM_SEED_RADISH,
    ITEM_SEED_SUNFLOWER, ITEM_SEED_WHEAT,
    ITEM_CARROT, ITEM_BEETROOT, ITEM_CABBAGE, ITEM_CAULIFLOWER,
    ITEM_KALE, ITEM_PARSNIP, ITEM_POTATO, ITEM_PUMPKIN,
    ITEM_RADISH, ITEM_SUNFLOWER, ITEM_WHEAT,
    ITEM_EGG, ITEM_MILK, ITEM_WOOL,
    ITEM_WOOD, ITEM_ROCK, ITEM_FISH,
    ITEM_FEED,
    ITEM_GEM,
    ITEM_COUNT,
    ITEM_NONE = -1
} ItemType;

typedef enum {
    CROP_CARROT=0, CROP_BEETROOT, CROP_CABBAGE, CROP_CAULIFLOWER,
    CROP_KALE, CROP_PARSNIP, CROP_POTATO, CROP_PUMPKIN,
    CROP_RADISH, CROP_SUNFLOWER, CROP_WHEAT
} CropType;

typedef enum { ANIMAL_CHICKEN=0, ANIMAL_PIG, ANIMAL_SHEEP, ANIMAL_COUNT } AnimalType;
typedef enum { ENEMY_GOBLIN=0, ENEMY_SKELETON, ENEMY_BOSS, ENEMY_COUNT } EnemyType;
typedef enum { ESTATE_WALK=0, ESTATE_ATTACK, ESTATE_HURT, ESTATE_DEAD } EnemyState;
typedef enum { ROLE_PLAYER=0, ROLE_TESTER, ROLE_ADMIN } PlayerRole;
typedef enum { WEATHER_SUNNY=0, WEATHER_CLOUDY, WEATHER_RAINY, WEATHER_COUNT } WeatherType;

/* ── Crop stage enum (ý nghĩa từng stage) ── */
typedef enum {
    CSTAGE_DUG=0,       /* vừa đào xong        */
    CSTAGE_WATERED,     /* đã tưới             */
    CSTAGE_GROWING,     /* đang lớn            */
    CSTAGE_READY        /* chín, sẵn thu hoạch */
} CropStage;

/* ── Structs ── */
typedef struct {
    char       username[MAX_NAME_LEN];
    char       password[MAX_PASS_LEN];
    PlayerRole role;
    bool       active;
} Account;

typedef struct { ItemType type; int quantity; } InvSlot;

typedef struct {
    CropType type;
    CropStage stage;
    float    growTimer;
    bool     active;
    int      tileX, tileY;
} Crop;


typedef struct {
    AnimalType type;
    int        tileX, tileY;   /* góc trên-trái chuồng */
    int        animalCount;
    bool       active;
} Barn;

typedef struct {
    AnimalType type;
    Vector2    pos;
    float      feedTimer;
    bool       hungry;
    bool       hasProduct;
    float      produceTimer;
    bool       active;
    int        barnIdx;
    float      moveTimer;
    Vector2    moveVel;
    int        animFrame;
    float      animTimer;
} Animal;

typedef struct {
    EnemyType  type;
    Vector2    pos;
    int        hp, maxHp;
    EnemyState state;
    int        animFrame;
    float      animTimer;
    float      atkTimer;
    float      hurtTimer;
    bool       active;
    Vector2    wanderTarget;
    float      wanderTimer;
    bool       isBoss;
} Enemy;

typedef struct {
    char desc[64];
    int  target, progress, reward;
    bool done;
    int  qtype;
} Quest;

typedef struct {
    TileType type;
    int      decor;
    int      cropIdx;   /* -1 = trống */
    int      barnIdx;   /* -1 = không có chuồng */
    bool     owned;     /* đã mua đất */
    int      chopCount; /* số lần đã click để chặt cây (0→1→2=chặt) */
    float    chopTimer; /* thời gian chờ reset chopCount (giây) */
} Tile;

typedef struct {
    int level, exp, expToNext;
} LevelData;

typedef struct {
    char       username[MAX_NAME_LEN];
    PlayerRole role;
    Vector2    pos;
    int        hp, maxHp;
    Direction  dir;
    AnimState  animState;
    float      animTimer;
    int        animFrame;
    ToolType   tool;
    InvSlot    inv[INV_SLOTS];
    int        hotbarIdx;
    int        money;
    bool       isActing;
    float      actTimer;
    bool       isRunning;
    float      hurtTimer;
    int        lives;      /* so mang (0-3) */
    LevelData  lvl;
    /* Di chuyển bằng click chuột */
    bool       hasClickTarget;
    Vector2    clickTarget;
} Player;

typedef struct {
    WeatherType current;
    float       timer;
    float       duration;
    float       rainTimer;
    float       cloudX[8], cloudY[8], cloudSpeed[8];
    float       rainDropX[40], rainDropY[40];
} Weather;

typedef struct {
    Texture2D pIdle, pWalk[4], pRun[4], pDig, pWater, pHurt;
    Texture2D goblin[5], skel[5];
    Texture2D crop[NUM_CROP_TYPES];
    Texture2D animal[ANIMAL_COUNT];
    Texture2D tileset;
    Texture2D iEgg, iMilk, iWood, iRock, iSeed, iFeed;
    Texture2D tree;
    Texture2D loginBg;
    Texture2D ground;   /* assets/backgrounds/ground.png  – 160x16, 10 tiles 16x16 */
    Texture2D chuong;  /* assets/objects/chuong.png – 96x112, fence tileset 16x16 */
    Texture2D animal_fence; 
    Texture2D home;     /* assets/objects/home.png        – 240x320, 48x48 sprites */
} Textures;

typedef struct {
    GameScreen screen;

    /* Đăng nhập / đăng ký */
    Account accounts[MAX_ACCOUNTS];
    int     accountCount;
    char    loginUser[MAX_NAME_LEN];
    char    loginPass[MAX_PASS_LEN];
    int     loginField;     /* 0=username 1=password */
    char    loginError[64];
    /* form đăng ký */
    char    regUser[MAX_NAME_LEN];
    char    regPass[MAX_PASS_LEN];
    char    regPass2[MAX_PASS_LEN];
    int     regField;       /* 0=user 1=pass 2=pass2 */
    char    regError[64];
    /* chọn role khi đăng ký */
    PlayerRole regRole;

    Player  player;
    Tile    map[MAP_ROWS][MAP_COLS];

    Crop    crops[MAX_CROPS];
    int     cropCount;

    Barn    barns[MAX_BARNS];
    int     barnCount;

    Animal  animals[MAX_ANIMALS];
    int     animalCount;

    Enemy   enemies[MAX_ENEMIES];
    int     enemyCount;

    Quest   quests[MAX_QUESTS];

    float   camX, camY, camZoom;
    float   gameTime;
    float   dayTimer;
    int     day;
    float   spawnTimer;
    float   skeletonTimer;   /* dem 5 phut spawn 1 skel */
    int     goblinCount;     /* so goblin hien tai */
    int     gemCount;        /* so ngoc da co */
    bool    bossAlive;       /* boss dang song */
    bool    endGame;         /* game over / win */
    bool    endWin;          /* true=win, false=lose */

    Weather weather;

    bool    paused;
    bool    showInventory;
    bool    showStore;
    bool    showHelp;
    bool    showQuest;
    bool    showBarnUI;
    bool    showLandUI;     /* UI mua đất */
    bool    showAchievements;
    int     selectedBarn;

    /* ── Edit mode: xóa / di chuyển object ── */
    bool    editMode;           /* đang ở chế độ chỉnh sửa farm */
    int     editSubMode;        /* 0=xoa, 1=di chuyen */
    /* Moving object state */
    bool    isMoving;           /* đang di chuyển object */
    int     moveBarnIdx;        /* >= 0: đang di chuyển chuồng */
    bool    movePlot;           /* đang di chuyển ô đất */
    int     movePlotTileX, movePlotTileY;   /* góc TL ô đất đang di chuyển */
    HotbarSlot  hbar[HBAR_SLOT_COUNT];
    int         hbarSel;        /* -1 = không chọn gì */
    bool        hbarPlacing;    /* đang ở chế độ đặt */

    char    message[128];
    float   msgTimer;
    bool    levelUpAnim;
    float   levelUpTimer;

    /* ── Hệ thống ngày/đêm ── */
    bool    isNight;            /* true khi dayTimer > DAY_DURATION*0.65f */
    float   nightOverlay;       /* 0.0→1.0: alpha của màn đêm (lerp mượt) */

    /* ── Multi-boss theo ngày ── */
    int     lastBossDay;        /* ngày cuối cùng đã spawn boss theo schedule */

    /* ── Barn HP (damage từ goblin) ── */
    int     barnHp[MAX_BARNS];  /* HP từng chuồng, max = BARN_MAX_HP */
    float   barnDmgTimer[MAX_BARNS]; /* cooldown damage flash */

    /* ── Kho đồ (storage chest) ── */
    bool    showStorage;
    bool    showSettings;
    InvSlot storage[64];        /* kho 64 slot riêng biệt */

    int movePlotW, movePlotH;  /* kích thước thực của plot đang move */
} GameState;

extern GameState G;
extern Textures  T;
extern Font gameFont;

#endif /* TYPES_H */