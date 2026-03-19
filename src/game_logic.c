#include "game_logic.h"
#include "entity_manager.h"
<<<<<<< HEAD
<<<<<<< HEAD
=======
#include "draw/draw_tile.h"
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
#include "draw/draw_tile.h"
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
#include "data_manager.h"
#include "quest_system.h"
#include "account_manager.h"
#include "achievement_system.h"
#include "draw/draw_hud.h"
#include "draw/draw_building.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include <math.h> 
#include <stdbool.h> 


// Định nghĩa các hằng số thời tiết nếu chưa có
#ifndef WEATHER_SUNNY
#define WEATHER_SUNNY 0
#endif
#ifndef WEATHER_CLOUDY
#define WEATHER_CLOUDY 1
#endif
#ifndef WEATHER_RAIN
#define WEATHER_RAIN 2
#endif
#ifndef WEATHER_COUNT
#define WEATHER_COUNT 3
#endif

// Khai báo hàm
void GameLogic_DrawWeatherEffects(void);
void GameLogic_UpdateRain(float dt);

=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
#include <math.h>
#include <stdbool.h>

/* Forward declaration — định nghĩa ở phía dưới */
static bool MouseOverUI(void);
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
/* ── Init ── */
void GameLogic_Init(void)
{
    Player *p=&G.player;
    /* Chỉ set nếu chưa load từ file */
    if (p->maxHp == 0) {
        p->hp=p->maxHp=PLAYER_MAX_HP;
        p->money=STARTING_MONEY;
    }
    if (p->pos.x == 0 && p->pos.y == 0)
        p->pos=(Vector2){MAP_PX_W*0.5f, MAP_PX_H*0.55f};
    if (p->lvl.level == 0) {
        p->lvl.level=1; p->lvl.exp=0;
        p->lvl.expToNext=Level_ExpNeeded(1);
    }
    p->dir=DIR_DOWN; p->tool=TOOL_HOE;
    HotbarPlacement_Init();

<<<<<<< HEAD
<<<<<<< HEAD
    G.camZoom=1.0f; G.spawnTimer=SPAWN_INTERVAL;
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    G.player.lives = 3;
    G.goblinCount = 0;
    G.gemCount = 0;
    G.bossAlive = false;
    /* BUG FIX #5: Reset firstSpawn flag khi vao game moi / login lai */
    extern bool Entity_ResetFirstSpawn(void);
    Entity_ResetFirstSpawn();
    G.endGame = false; G.endWin = false;
    /* Hệ thống ngày/đêm */
    G.isNight      = false;
    G.nightOverlay = 0.0f;
    G.lastBossDay  = 0;
    /* Khởi tạo HP chuồng */
    for (int _i = 0; _i < MAX_BARNS; _i++) {
        G.barnHp[_i]       = BARN_MAX_HP;
        G.barnDmgTimer[_i] = 0.0f;
    }
    /* Khởi tạo kho đồ */
    for (int _i = 0; _i < STORAGE_SLOTS; _i++) {
        G.storage[_i].type     = ITEM_NONE;
        G.storage[_i].quantity = 0;
    }
    G.camZoom=1.0f; G.spawnTimer=30.0f;
    G.skeletonTimer=300.0f;
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    if (G.day==0) G.day=1;

    /* Init weather */
    G.weather.current=WEATHER_SUNNY;
    G.weather.timer=G.weather.duration=120.0f;
    for (int i=0;i<8;i++){
        G.weather.cloudX[i]=(float)GetRandomValue(-200,SCREEN_W);
        G.weather.cloudY[i]=(float)GetRandomValue(30,200);
        G.weather.cloudSpeed[i]=10.0f+GetRandomValue(0,20);
    }
    for (int i=0;i<40;i++){
        G.weather.rainDropX[i]=(float)GetRandomValue(0,SCREEN_W);
        G.weather.rainDropY[i]=(float)GetRandomValue(-SCREEN_H,0);
    }
}

<<<<<<< HEAD
<<<<<<< HEAD
/* ================= TREE SYSTEM ================= */

// #define MAX_TREES 128

// typedef struct {
//     int tx, ty;
//     int hp;
//     float regenTimer;
//     bool active;
// } Tree;

// static Tree trees[MAX_TREES];

// /* kiểm tra tile có phải cây decor 30/31/32 */
// bool Tile_IsTree(int tx,int ty)
// {
//     if(tx<0 || ty<0 || tx>=MAP_COLS || ty>=MAP_ROWS)
//         return false;

//     int id = G.map[ty][tx].decor;
//     return (id==30 || id==31 || id==32);
// }

// /* tìm tree trong mảng */
// static Tree* FindTree(int tx,int ty)
// {
//     for(int i=0;i<MAX_TREES;i++)
//         if(trees[i].active && trees[i].tx==tx && trees[i].ty==ty)
//             return &trees[i];
//     return NULL;
// }

// /* tạo tree entry nếu chưa có */
// static Tree* GetOrCreateTree(int tx,int ty)
// {
//     Tree* t=FindTree(tx,ty);
//     if(t) return t;

//     for(int i=0;i<MAX_TREES;i++){
//         if(!trees[i].active){
//             trees[i].active=true;
//             trees[i].tx=tx;
//             trees[i].ty=ty;
//             trees[i].hp=2;            // cần 2 lần chặt
//             trees[i].regenTimer=0;
//             return &trees[i];
//         }
//     }
//     return NULL;
// }
//click chặt c
// bool Tree_Click(int tx,int ty)
// {
//     Tree *t = GetOrCreateTree(tx,ty);
//     if(!t) return false;

//     t->hp--;

//     G.player.animState = ANIM_DIG;
//     G.player.isActing = true;
//     G.player.actTimer = 0.35f;

//     if(t->hp <= 0)
//     {
//         G.map[ty][tx].decor = 0;
//         t->regenTimer = 120.0f;

//         Inv_Add(ITEM_WOOD,1);

//         strncpy(G.message,"Da chat cay +1 go",sizeof(G.message));
//         G.msgTimer = 1.5f;
//     }
//     else
//     {
//         strncpy(G.message,"Dang chat cay...",sizeof(G.message));
//         G.msgTimer = 0.8f;
//     }

//     return true;
// }

// /* update mọc lại */
// void Tree_UpdateTimers(float dt)
// {
//     for(int i=0;i<MAX_TREES;i++)
//     {
//         Tree *t=&trees[i];
//         if(!t->active) continue;

//         if(t->regenTimer>0)
//         {
//             t->regenTimer-=dt;
//             if(t->regenTimer<=0)
//             {
//                 G.map[t->ty][t->tx].decor=30;  // mọc lại
//                 t->hp=2;
//             }
//         }
//     }
// }

=======
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
/* ── Camera ── */
void GameLogic_UpdateCamera(void)
{
    float z=G.camZoom;
    float tx=G.player.pos.x-(float)SCREEN_W*0.5f/z;
    float ty=G.player.pos.y-(float)SCREEN_H*0.5f/z;
    G.camX+=(tx-G.camX)*0.12f;
    G.camY+=(ty-G.camY)*0.12f;

    float maxX=MAP_PX_W-(float)SCREEN_W/z;
    float maxY=MAP_PX_H-(float)SCREEN_H/z;
    if (G.camX<0)G.camX=0;
    if (G.camY<0)G.camY=0;
    if (maxX>0&&G.camX>maxX)G.camX=maxX;
    if (maxY>0&&G.camY>maxY)G.camY=maxY;

<<<<<<< HEAD
<<<<<<< HEAD
    /* Scroll chuột để zoom */
    float wheel=GetMouseWheelMove();
    if (wheel!=0) {
=======
    /* Scroll chuột để zoom — chỉ khi không có UI panel đang mở */
    float wheel=GetMouseWheelMove();
    if (wheel!=0 && !MouseOverUI()) {
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
    /* Scroll chuột để zoom — chỉ khi không có UI panel đang mở */
    float wheel=GetMouseWheelMove();
    if (wheel!=0 && !MouseOverUI()) {
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        G.camZoom+=wheel*0.12f;
        if (G.camZoom<0.35f)G.camZoom=0.35f;
        if (G.camZoom>3.0f)G.camZoom=3.0f;
    }
    /* Phím += */
    if (IsKeyDown(KEY_EQUAL))   G.camZoom=Clamp(G.camZoom+0.02f,0.35f,3.0f);
    if (IsKeyDown(KEY_MINUS))   G.camZoom=Clamp(G.camZoom-0.02f,0.35f,3.0f);
}
static bool MouseOverUI(void)
{
    /* Khi mo UI panels -> moi click deu la UI, khong di chuyen player */
    if (G.showStore||G.showInventory||G.showBarnUI||G.showHelp||G.showAchievements) return true;

    Vector2 m = GetMousePosition();

    /* TopBar */
<<<<<<< HEAD
<<<<<<< HEAD
    if (m.y < 54) return true;
=======
    if (m.y < 66) return true;
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
    if (m.y < 66) return true;
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23

    /* Side panel (minimap, buttons) */
    if (m.x > SCREEN_W - 252) return true;

    /* Hotbar zone: 17 slots x 53px = 901px, startY = SCREEN_H-68 */
    if (m.y > SCREEN_H - 100) return true;

    /* Admin / Tester panels */
    if (CheckCollisionPointRec(m,(Rectangle){10,74,200,170})) return true;
    if (CheckCollisionPointRec(m,(Rectangle){10,96,180,100})) return true;

    return false;
}
/* ── Tile click – toàn bộ tương tác bằng chuột trái ── */
void GameLogic_HandleTileClick(Vector2 wPos)
{
    if (DrawBuilding_HandleClick(wPos)) return;
    Player *p=&G.player;
    int tx=WorldToTileX(wPos.x), ty=WorldToTileY(wPos.y);
    if (tx<0||tx>=MAP_COLS||ty<0||ty>=MAP_ROWS) return;

    Vector2 tc={(tx+0.5f)*TILE_SIZE,(ty+0.5f)*TILE_SIZE};
    if (Dist(p->pos,tc)>PLAYER_REACH) {
        strncpy(G.message,"Qua xa! Lai gan hon.",sizeof(G.message));
        G.msgTimer=1.2f; return;
    }
    

    Tile *tile=&G.map[ty][tx];

    /* Click vao chuong voi bat ky tool nao -> mo BarnUI (tru TOOL_FEED) */
    if (tile->barnIdx >= 0) {
        Barn *cb = &G.barns[tile->barnIdx];
        Vector2 barnCenter = {(cb->tileX + 2.5f)*TILE_SIZE, (cb->tileY + 2.5f)*TILE_SIZE};
        if (Dist(p->pos, barnCenter) > PLAYER_REACH * 3.0f) {
<<<<<<< HEAD
<<<<<<< HEAD
            strncpy(G.message, "Qua xa! Lai gan chuong hon.", sizeof(G.message));
=======
            strncpy(G.message, "Quá xa! Lại gần chuồng hơn.", sizeof(G.message));
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
            strncpy(G.message, "Quá xa! Lại gần chuồng hơn.", sizeof(G.message));
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            G.msgTimer = 1.2f; return;
        }
        if (p->tool != TOOL_FEED) {
            G.showBarnUI = !G.showBarnUI;
            G.showInventory = false; G.showStore = false;
<<<<<<< HEAD
<<<<<<< HEAD
            strncpy(G.message, "QUAN LY CHUONG - [N] de mo/dong", sizeof(G.message));
=======
            strncpy(G.message, "QUẢN LÝ CHUỒNG - [N] để mở/đóng", sizeof(G.message));
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
            strncpy(G.message, "QUẢN LÝ CHUỒNG - [N] để mở/đóng", sizeof(G.message));
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            G.msgTimer = 1.5f; return;
        }
    }

    switch(p->tool) {

    /* ── 1: HOE – đào đất (đất đã mua → đã đào) ── */
    case TOOL_HOE:
        if (tile->type==TILE_SOIL_BOUGHT && tile->cropIdx<0) {
            tile->type=TILE_SOIL_DUG;
            p->animState=ANIM_DIG; p->isActing=true; p->actTimer=0.6f;
<<<<<<< HEAD
<<<<<<< HEAD
            strncpy(G.message,"Da dao dat! Hay tuoi nuoc.",sizeof(G.message));
            G.msgTimer=1.5f;
        } else if (tile->type==TILE_GRASS) {
            strncpy(G.message,"Hay mua dat truoc! (click [Mua Dat])",sizeof(G.message));
            G.msgTimer=2.0f;
        } else {
            strncpy(G.message,"Khong the dao o nay.",sizeof(G.message));
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            strncpy(G.message,"Đã đào đất! Hay tưới nước.",sizeof(G.message));
            G.msgTimer=1.5f;
        } else if (tile->type==TILE_GRASS) {
            strncpy(G.message,"Hay mua đất trước! (click [Mua Đất])",sizeof(G.message));
            G.msgTimer=2.0f;
        } else {
            strncpy(G.message,"Không thể đào ở đây.",sizeof(G.message));
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            G.msgTimer=1.5f;
        }
        break;

    /* ── 2: WATERING CAN – tưới đất đã đào ── */
    case TOOL_WATERING_CAN:
        if (tile->type==TILE_SOIL_DUG && tile->cropIdx<0) {
            tile->type=TILE_SOIL_WET;
            p->animState=ANIM_WATER; p->isActing=true; p->actTimer=0.8f;
<<<<<<< HEAD
<<<<<<< HEAD
            strncpy(G.message,"Da tuoi nuoc! Hay trong cay.",sizeof(G.message));
            G.msgTimer=1.5f;
        } else {
            strncpy(G.message,"Phai dao dat truoc roi moi tuoi!",sizeof(G.message));
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            strncpy(G.message,"Đã tưới nước! Hay trồng cây.",sizeof(G.message));
            G.msgTimer=1.5f;
        } else {
            strncpy(G.message,"Phải đào đất trước rồi mới tưới!",sizeof(G.message));
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            G.msgTimer=1.5f;
        }
        break;

    /* ── 3: SEED – trồng cây vào đất đã tưới ── */
    case TOOL_SEED: {
        if (tile->type!=TILE_SOIL_WET||tile->cropIdx>=0) {
<<<<<<< HEAD
<<<<<<< HEAD
            strncpy(G.message,"Phai tuoi dat truoc roi moi trong!",sizeof(G.message));
=======
            strncpy(G.message,"Phải tưới đất trước rồi mới trồng!",sizeof(G.message));
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
            strncpy(G.message,"Phải tưới đất trước rồi mới trồng!",sizeof(G.message));
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            G.msgTimer=1.5f; break;
        }
        InvSlot *sel=&p->inv[p->hotbarIdx];
        if (sel->type<ITEM_SEED_CARROT||sel->type>ITEM_SEED_WHEAT) {
<<<<<<< HEAD
<<<<<<< HEAD
            strncpy(G.message,"Chon hat giong trong hotbar!",sizeof(G.message));
            G.msgTimer=1.5f; break;
        }
        if (!Inv_Remove(sel->type,1)) {
            strncpy(G.message,"Het hat giong!",sizeof(G.message));
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            strncpy(G.message,"Chọn hạt giống trong hotbar!",sizeof(G.message));
            G.msgTimer=1.5f; break;
        }
        if (!Inv_Remove(sel->type,1)) {
            strncpy(G.message,"Hết hạt giống!",sizeof(G.message));
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            G.msgTimer=1.5f; break;
        }
        int idx=-1;
        for (int i=0;i<MAX_CROPS;i++) if (!G.crops[i].active){idx=i;break;}
        if (idx<0) break;
        CropType ct=(CropType)(sel->type-ITEM_SEED_CARROT);
        G.crops[idx]=(Crop){ct,CSTAGE_WATERED,0,true,tx,ty};
        tile->cropIdx=idx; tile->type=TILE_SOIL_WET;
        G.cropCount++;
        p->animState=ANIM_DIG; p->isActing=true; p->actTimer=0.5f;
        Quest_Progress(1,1);
        Level_AddExp(EXP_PER_PLANT); Achievement_AddPlant(1);
<<<<<<< HEAD
<<<<<<< HEAD
        strncpy(G.message,"Da trong cay! Cho cay lon.",sizeof(G.message));
=======
        strncpy(G.message,"Đã trồng cây! Chờ cây lớn.",sizeof(G.message));
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
        strncpy(G.message,"Đã trồng cây! Chờ cây lớn.",sizeof(G.message));
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        G.msgTimer=1.5f;
        break;
    }

    /* ── 4: SCYTHE – thu hoạch cây chín ── */
    case TOOL_SCYTHE: {
        if (tile->cropIdx<0) {
<<<<<<< HEAD
<<<<<<< HEAD
            strncpy(G.message,"Khong co cay de thu hoach.",sizeof(G.message));
=======
            strncpy(G.message,"Không có cây để thu hoạch.",sizeof(G.message));
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
            strncpy(G.message,"Không có cây để thu hoạch.",sizeof(G.message));
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            G.msgTimer=1.5f; break;
        }
        Crop *c=&G.crops[tile->cropIdx];
        if (c->stage!=CSTAGE_READY) {
<<<<<<< HEAD
<<<<<<< HEAD
            strncpy(G.message,"Cay chua chin! Cho them.",sizeof(G.message));
=======
            strncpy(G.message,"Cây chưa chín! Cho thêm thời gian.",sizeof(G.message));
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
            strncpy(G.message,"Cây chưa chín! Cho thêm thời gian.",sizeof(G.message));
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            G.msgTimer=1.5f; break;
        }
        ItemType harvest=(ItemType)(ITEM_CARROT+c->type);
        int qty=1+GetRandomValue(0,2)+(G.player.lvl.level/5);
        Inv_Add(harvest,qty);
        c->active=false; tile->cropIdx=-1;
        tile->type=TILE_SOIL_BOUGHT; /* đất về bought để dùng lại */
        G.cropCount--;
        p->animState=ANIM_DIG; p->isActing=true; p->actTimer=0.4f;
        Quest_Progress(0,1); Level_AddExp(EXP_PER_HARVEST); Achievement_AddHarvest(1);
<<<<<<< HEAD
<<<<<<< HEAD
        snprintf(G.message,sizeof(G.message),"Thu hoach %s x%d!",GetItemName(harvest),qty);
=======
        snprintf(G.message,sizeof(G.message),"Thu hoạch %s x%d!",GetItemName(harvest),qty);
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
        snprintf(G.message,sizeof(G.message),"Thu hoạch %s x%d!",GetItemName(harvest),qty);
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        G.msgTimer=2.0f;
        break;
    }

    /* ── 5: SWORD – tấn công kẻ thù ── */
    case TOOL_SWORD: {
        bool hit=false;
        for (int i=0;i<MAX_ENEMIES;i++) {
            Enemy *e=&G.enemies[i];
            if (!e->active||e->state==ESTATE_DEAD) continue;
            Vector2 ep=e->pos;
            if (Dist(p->pos,ep)<TILE_SIZE*2.2f) {
                int dmg=15+GetRandomValue(0,15)+(G.player.lvl.level*2);
                e->hp-=dmg; e->state=ESTATE_HURT; e->hurtTimer=0.3f; hit=true;
                if (e->hp<=0){
                    e->hp=0; e->state=ESTATE_DEAD; e->animFrame=0; G.enemyCount--;
<<<<<<< HEAD
<<<<<<< HEAD
                    int coins=10+GetRandomValue(0,25)+(G.day*2);
                    p->money+=coins;
                    Quest_Progress(3,1); Level_AddExp(EXP_PER_KILL); Achievement_AddKill(1);
                    snprintf(G.message,sizeof(G.message),"Ha guc quai! +$%d",coins);
                } else {
                    snprintf(G.message,sizeof(G.message),"Tan cong -%d HP",dmg);
                }
                G.msgTimer=1.0f;
            }
        }
        if (!hit){strncpy(G.message,"Khong co quai trong tam!",sizeof(G.message));G.msgTimer=1.2f;}
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
                    Quest_Progress(3,1); Level_AddExp(EXP_PER_KILL); Achievement_AddKill(1);
                    char dropMsg[128]="";
                    int coins=0;
                    if (e->isBoss) {
                        coins=300+GetRandomValue(0,200)+G.day*10;
                        Inv_Add(ITEM_GEM,1); G.gemCount++;
                        Inv_Add(ITEM_FISH,3);
                        snprintf(dropMsg,sizeof(dropMsg),"BOSS HẠ! +$%d +1 Ngọc ",coins);
                        G.bossAlive=false;
                        G.endGame=true; G.endWin=true;
                    } else if (e->type==ENEMY_GOBLIN) {
                        coins=8+GetRandomValue(0,12)+(G.day*2);
                        if(GetRandomValue(0,9)<7){int w=1+GetRandomValue(0,1);Inv_Add(ITEM_WOOD,w);snprintf(dropMsg,sizeof(dropMsg),"+$%d +%dGo",coins,w);}
                        else snprintf(dropMsg,sizeof(dropMsg),"+$%d",coins);
                        if(GetRandomValue(0,9)<3){Inv_Add(ITEM_FISH,1);strncat(dropMsg," +1Ca",sizeof(dropMsg)-strlen(dropMsg)-1);}
                        if(GetRandomValue(0,4)==0){ItemType sd=(ItemType)(ITEM_SEED_CARROT+GetRandomValue(0,10));Inv_Add(sd,1);strncat(dropMsg," +Hat",sizeof(dropMsg)-strlen(dropMsg)-1);}
                        /* Tỉ lệ rớt ngọc: 5% (1/20) */
                        if(GetRandomValue(0,19)==0){Inv_Add(ITEM_GEM,1);G.gemCount++;strncat(dropMsg," +NGỌC!",sizeof(dropMsg)-strlen(dropMsg)-1);
                            if(G.gemCount>=3&&!G.bossAlive){ SpawnBoss(); }}
                    } else {
                        coins=18+GetRandomValue(0,22)+(G.day*3);
                        if(GetRandomValue(0,9)<6){int rk=1+GetRandomValue(0,1);Inv_Add(ITEM_ROCK,rk);snprintf(dropMsg,sizeof(dropMsg),"+$%d +%dDa",coins,rk);}
                        else snprintf(dropMsg,sizeof(dropMsg),"+$%d",coins);
                        if(GetRandomValue(0,9)<3){Inv_Add(ITEM_FISH,1);strncat(dropMsg," +1Ca",sizeof(dropMsg)-strlen(dropMsg)-1);}
                        if(GetRandomValue(0,9)==0){Inv_Add(ITEM_GEM,1);G.gemCount++;strncat(dropMsg," +NGỌC!",sizeof(dropMsg)-strlen(dropMsg)-1);}
                    }
                    p->money+=coins;
                    if(!e->isBoss) snprintf(G.message,sizeof(G.message),"Hạ %s! %s",e->type==ENEMY_GOBLIN?"Goblin":"Skel",dropMsg);
                    G.msgTimer=2.5f;
                } else {
                    snprintf(G.message,sizeof(G.message),"Tấn công -%d HP",dmg);
                    G.msgTimer=1.0f;
                }
            }
        }
        if (!hit){strncpy(G.message,"Không có quái trong tầm!",sizeof(G.message));G.msgTimer=1.2f;}
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        p->animState=ANIM_DIG; p->isActing=true; p->actTimer=0.3f;
        break;
    }

    /* ── 6: FEED – cho động vật ăn (click vào chuồng) ── */
    case TOOL_FEED: {
        if (tile->barnIdx<0) {
<<<<<<< HEAD
<<<<<<< HEAD
            strncpy(G.message,"Click vao chuong de cho an!",sizeof(G.message));
=======
            strncpy(G.message,"Click vào chuồng để cho ăn!",sizeof(G.message));
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
            strncpy(G.message,"Click vào chuồng để cho ăn!",sizeof(G.message));
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            G.msgTimer=1.5f; break;
        }
        int bi=tile->barnIdx;
        if (Inv_Count(ITEM_FEED)==0) {
<<<<<<< HEAD
<<<<<<< HEAD
            strncpy(G.message,"Khong co thuc an! Mua tai cua hang.",sizeof(G.message));
=======
            strncpy(G.message,"Không có thức ăn! Mua tại cửa hàng.",sizeof(G.message));
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
            strncpy(G.message,"Không có thức ăn! Mua tại cửa hàng.",sizeof(G.message));
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            G.msgTimer=2.0f; break;
        }
        int fed=0;
        for (int i=0;i<MAX_ANIMALS;i++) {
            Animal *a=&G.animals[i];
            if (!a->active||a->barnIdx!=bi||!a->hungry) continue;
            if (!Inv_Remove(ITEM_FEED,1)) break;
            a->hungry=false; a->feedTimer=FEED_SECS; fed++;
        }
        if (fed>0) {
<<<<<<< HEAD
<<<<<<< HEAD
            snprintf(G.message,sizeof(G.message),"Cho %d con an!",fed);
        } else {
            strncpy(G.message,"Dong vat chua doi.",sizeof(G.message));
=======
            snprintf(G.message,sizeof(G.message),"Cho %d con ăn!",fed);
        } else {
            strncpy(G.message,"Động vật chưa đói.",sizeof(G.message));
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
            snprintf(G.message,sizeof(G.message),"Cho %d con ăn!",fed);
        } else {
            strncpy(G.message,"Động vật chưa đói.",sizeof(G.message));
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        }
        G.msgTimer=1.5f;
        break;
    }
    default: break;
    }
}

/* ── Chuột phải – thu sản phẩm động vật ── */
static void HandleRightClick(void)
{
    if (G.showInventory||G.showStore||G.showBarnUI) return;
    Vector2 mw=ScreenToWorld(GetMousePosition());
    int tx=WorldToTileX(mw.x), ty=WorldToTileY(mw.y);
    if (tx<0||tx>=MAP_COLS||ty<0||ty>=MAP_ROWS) return;
    int bi=G.map[ty][tx].barnIdx;
    if (bi<0) return;

    int collected=0;
    for (int i=0;i<MAX_ANIMALS;i++) {
        Animal *a=&G.animals[i];
        if (!a->active||a->barnIdx!=bi||!a->hasProduct) continue;
<<<<<<< HEAD
<<<<<<< HEAD
        ItemType prod=(a->type==ANIMAL_CHICKEN)?ITEM_EGG:
                      (a->type==ANIMAL_PIG)?ITEM_MILK:ITEM_WOOL;
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        /* BUG FIX #9: Lon (Pig) san xuat Len (WOOL), Cuu (Sheep) san xuat Sua (MILK)
           Ga (Chicken) → Trung (EGG), Lon (Pig) → Len/Tho (WOOL), Cuu (Sheep) → Sua (MILK) */
        ItemType prod=(a->type==ANIMAL_CHICKEN)?ITEM_EGG:
                      (a->type==ANIMAL_PIG)?ITEM_WOOL:ITEM_MILK;
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        Inv_Add(prod,1);
        a->hasProduct=false;
        Quest_Progress(4,1); Level_AddExp(EXP_PER_COLLECT); Achievement_AddCollect(1);
        collected++;
    }
    if (collected>0) {
<<<<<<< HEAD
<<<<<<< HEAD
        snprintf(G.message,sizeof(G.message),"Thu %d san pham!",collected);
=======
        snprintf(G.message,sizeof(G.message),"Thu %d sản phẩm!",collected);
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
        snprintf(G.message,sizeof(G.message),"Thu %d sản phẩm!",collected);
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        G.msgTimer=1.5f;
    }
}

/* ── Input tổng hợp ── */
void GameLogic_HandleInput(void)
{
    Player *p=&G.player;

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    /* ── Phím UI: luôn hoạt động dù panel nào đang mở ── */
    if (IsKeyPressed(KEY_I)){G.showInventory=!G.showInventory;G.showStore=false;G.showBarnUI=false;}
    if (IsKeyPressed(KEY_B)){G.showStore=!G.showStore;G.showInventory=false;G.showBarnUI=false;}
    if (IsKeyPressed(KEY_N)){G.showBarnUI=!G.showBarnUI;G.showInventory=false;G.showStore=false;}
    if (IsKeyPressed(KEY_Q)) G.showQuest=!G.showQuest;
    
    if (IsKeyPressed(KEY_C)) G.showHelp=!G.showHelp;
    if (IsKeyPressed(KEY_F2)) G.showAchievements=!G.showAchievements;
    if (IsKeyPressed(KEY_F5)){
        char sp[128]; snprintf(sp,sizeof(sp),"saves/%s.dat",p->username);
        Game_SavePlayer(sp);
        strncpy(G.message,"Đã lưu game!",sizeof(G.message)); G.msgTimer=2.0f;
    }
    if (IsKeyPressed(KEY_F3)){ extern bool debugMode; debugMode=!debugMode; }
    if (IsKeyPressed(KEY_F11)) {
        if (G.player.role == ROLE_ADMIN) {
            /* Admin F11: sang ngày mới */
            G.dayTimer = 0;
            G.day++;
            G.isNight = false;
            G.nightOverlay = 0.0f;
            snprintf(G.message, sizeof(G.message), "Admin: Sang Ngày %d!", G.day);
            G.msgTimer = 2.0f;
        } else {
            if (!IsWindowFullscreen()) strncpy(G.message,"Chế độ Toàn màn hình",sizeof(G.message));
            else                       strncpy(G.message,"Chế độ Cửa sổ",sizeof(G.message));
            G.msgTimer=2.0f;
        }
    }
    if (IsKeyPressed(KEY_F10) && G.player.role == ROLE_ADMIN) {
        /* Admin F10: chuyển ngày/đêm */
        if (!G.isNight) {
            G.dayTimer = DAY_DURATION * NIGHT_START_RATIO + 1.0f;
            G.isNight = true;
            G.nightOverlay = 1.0f;
            strncpy(G.message, "Admin: Chuyển sang ĐÊM", sizeof(G.message));
        } else {
            G.dayTimer = 0.0f;
            G.isNight = false;
            G.nightOverlay = 0.0f;
            strncpy(G.message, "Admin: Chuyển sang NGÀY", sizeof(G.message));
        }
        G.msgTimer = 2.0f;
    }
    if (IsKeyPressed(KEY_F9) && G.player.role == ROLE_ADMIN) {
        /* Admin F9: God Mode — toggle */
        if (G.player.maxHp == 99999) {
            G.player.maxHp = PLAYER_MAX_HP;
            G.player.hp    = PLAYER_MAX_HP;
            strncpy(G.message, "Admin: God Mode OFF", sizeof(G.message));
        } else {
            G.player.maxHp = 99999;
            G.player.hp    = 99999;
            strncpy(G.message, "Admin: God Mode ON", sizeof(G.message));
        }
        G.msgTimer = 2.0f;
    }
    /* ESC thoát edit mode (luôn xử lý) */
    if (IsKeyPressed(KEY_ESCAPE)) {
        if (G.editMode) G.editMode=false;
    }

    /* ── Khi bất kỳ panel nào đang mở: không xử lý game keys ── */
    if (G.showInventory||G.showStore||G.showBarnUI||G.showHelp||
        G.showAchievements||G.showQuest||G.showSettings) return;

    /* ── Game keys: chỉ hoạt động khi không có panel ── */

<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    /* Tool keys */
    if (IsKeyPressed(KEY_ONE))   p->tool=TOOL_HOE;
    if (IsKeyPressed(KEY_TWO))   p->tool=TOOL_WATERING_CAN;
    if (IsKeyPressed(KEY_THREE)) p->tool=TOOL_SEED;
    if (IsKeyPressed(KEY_FOUR))  p->tool=TOOL_SCYTHE;
    if (IsKeyPressed(KEY_FIVE))  p->tool=TOOL_SWORD;
    if (IsKeyPressed(KEY_SIX))   p->tool=TOOL_FEED;

    /* Hotbar scroll */
<<<<<<< HEAD
<<<<<<< HEAD
    /* (scroll zoom đã ở camera, chuyển bằng Q/E) */
    if (IsKeyPressed(KEY_LEFT_BRACKET))  p->hotbarIdx=(p->hotbarIdx-1+HOTBAR_SIZE)%HOTBAR_SIZE;
    if (IsKeyPressed(KEY_RIGHT_BRACKET)) p->hotbarIdx=(p->hotbarIdx+1)%HOTBAR_SIZE;

    /* UI */
    if (IsKeyPressed(KEY_I)){G.showInventory=!G.showInventory;G.showStore=false;G.showBarnUI=false;}
    if (IsKeyPressed(KEY_B)){G.showStore=!G.showStore;G.showInventory=false;G.showBarnUI=false;}
    if (IsKeyPressed(KEY_N)){G.showBarnUI=!G.showBarnUI;G.showInventory=false;G.showStore=false;}
    if (IsKeyPressed(KEY_Q)) G.showQuest=!G.showQuest;
    if (IsKeyPressed(KEY_C)) G.showHelp=!G.showHelp;
    if (IsKeyPressed(KEY_F2)) G.showAchievements=!G.showAchievements;
    if (IsKeyPressed(KEY_F5)){
        char sp[128]; snprintf(sp,sizeof(sp),"saves/%s.dat",p->username);
        Game_SavePlayer(sp);
        strncpy(G.message,"Da luu game!",sizeof(G.message)); G.msgTimer=2.0f;
    }
    if (IsKeyPressed(KEY_F3)){ extern bool debugMode; debugMode=!debugMode; }
    
   /* --- [BAT DAU PHAN THEM: THONG BAO F11] --- */
   if (IsKeyPressed(KEY_F11)) {
       if (!IsWindowFullscreen()) strncpy(G.message, "Che do Toan man hinh", sizeof(G.message));
       else strncpy(G.message, "Che do Cua so", sizeof(G.message));
       G.msgTimer = 2.0f;
   }
   /* --- [KET THUC PHAN THEM: THONG BAO F11] --- */




    /* --- CHUYỂN ĐỔI ROLE (SHIFT + ENTER) --- */
if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_ENTER)) {
    // Khởi tạo role nếu đang là PLAYER
    if (p->role != ROLE_ADMIN && p->role != ROLE_TESTER) {
        p->role = ROLE_TESTER; // Mặc định vào TESTER
    } else {
        // Chuyển qua lại giữa ADMIN và TESTER
        p->role = (p->role == ROLE_ADMIN) ? ROLE_TESTER : ROLE_ADMIN;
    }
    
    const char* roleName = (p->role == ROLE_ADMIN) ? "ADMIN" : "TESTER";
    snprintf(G.message, sizeof(G.message), "Role: %s", roleName);
    G.msgTimer = 2.0f;
}

    /* --- LOGIC RIÊNG CHO ADMIN --- */
    if (p->role == ROLE_ADMIN) {
        // M: Tiền +$5000 (Admin nhận nhiều hơn)
        if (IsKeyPressed(KEY_M)) {
            p->money += 5000;
            strncpy(G.message, "Admin: +$5000", sizeof(G.message));
            G.msgTimer = 1.5f;
        }
        // K: Diệt sạch kẻ địch
        if (IsKeyPressed(KEY_K)) {
            for (int i = 0; i < MAX_ENEMIES; i++) {
                if (G.enemies[i].active) {
                    G.enemies[i].state = ESTATE_DEAD;
                    G.enemies[i].hp = 0;
                    G.enemyCount--;
                }
            }
            strncpy(G.message, "Admin: Kill all enemies!", sizeof(G.message));
            G.msgTimer = 1.5f;
        }
        // F6: Đổi thời tiết
        if (IsKeyPressed(KEY_F6)) {
            G.weather.current = (G.weather.current + 1) % WEATHER_COUNT;
            G.weather.timer = 300.0f;
            const char *weatherNames[] = {"NANG", "NHIEU MAY", "MUA"};
            snprintf(G.message, sizeof(G.message), "Admin: Weather -> %s", weatherNames[G.weather.current]);
            G.msgTimer = 2.0f;
        }
        // F8: God Mode
        if (IsKeyPressed(KEY_F8)) {
            p->maxHp = 99999; p->hp = 99999;
            strncpy(G.message, "Admin: God Mode ON", sizeof(G.message));
            G.msgTimer = 2.0f;
        }
        // P: Teleport trung tâm
        if (IsKeyPressed(KEY_P)) {
            p->pos = (Vector2){MAP_PX_W * 0.5f, MAP_PX_H * 0.5f};
            p->hasClickTarget = false;
            strncpy(G.message, "Admin: Teleported to Center", sizeof(G.message));
            G.msgTimer = 1.5f;
        }
    }

    /* --- LOGIC RIÊNG CHO TESTER --- */
    if (p->role == ROLE_TESTER) {
        // M: Tiền +$500
        if (IsKeyPressed(KEY_M)) {
            p->money += 500;
            strncpy(G.message, "Tester: +$500", sizeof(G.message));
            G.msgTimer = 1.5f;
        }
        // T: Chín cây ngay
        if (IsKeyPressed(KEY_T)) {
            for (int i = 0; i < MAX_CROPS; i++) {
                if (G.crops[i].active) G.crops[i].stage = CSTAGE_READY;
            }
            strncpy(G.message, "Tester: Crops Ready!", sizeof(G.message));
            G.msgTimer = 1.5f;
        }
        // L: Tăng cấp (+500 EXP)
        if (IsKeyPressed(KEY_L)) {
            Level_AddExp(500);
            strncpy(G.message, "Tester: +500 EXP", sizeof(G.message));
            G.msgTimer = 1.5f;
        }
        // I: Nhận vật phẩm test
        if (IsKeyPressed(KEY_I)) {
            Inv_Add(ITEM_SEED_CARROT, 20); Inv_Add(ITEM_SEED_WHEAT, 20);
            Inv_Add(ITEM_WOOD, 100); Inv_Add(ITEM_FEED, 20);
            strncpy(G.message, "Tester: Received Test Items", sizeof(G.message));
            G.msgTimer = 1.5f;
        }
        // F7: Sang ngày mới
        if (IsKeyPressed(KEY_F7)) {
            G.dayTimer = DAY_DURATION;
            strncpy(G.message, "Tester: Fast Forward Day", sizeof(G.message));
            G.msgTimer = 1.5f;
        }
        // F9: Debug Mode
        if (IsKeyPressed(KEY_F9)) {
            extern bool debugMode; debugMode = !debugMode;
            snprintf(G.message, sizeof(G.message), "Tester: Debug %s", debugMode ? "ON" : "OFF");
            G.msgTimer = 1.5f;
        }
    }

    /* --- CHUNG CHO ADMIN & TESTER --- */
    if (p->role == ROLE_ADMIN || p->role == ROLE_TESTER) {
        // H: Full HP
        if (IsKeyPressed(KEY_H)) {
            p->hp = p->maxHp;
            strncpy(G.message, "Refilled HP", sizeof(G.message));
            G.msgTimer = 1.5f;
        }
    }

=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    if (IsKeyPressed(KEY_LEFT_BRACKET))  p->hotbarIdx=(p->hotbarIdx-1+HOTBAR_SIZE)%HOTBAR_SIZE;
    if (IsKeyPressed(KEY_RIGHT_BRACKET)) p->hotbarIdx=(p->hotbarIdx+1)%HOTBAR_SIZE;

    /* Admin + Tester keys */
    if (p->role==ROLE_ADMIN||p->role==ROLE_TESTER) {
        if (IsKeyPressed(KEY_M)&&p->role==ROLE_ADMIN){p->money+=5000;strncpy(G.message,"Admin:+$5000",sizeof(G.message));G.msgTimer=1.5f;}
        if (IsKeyPressed(KEY_H)){p->hp=p->maxHp;strncpy(G.message,"Phục hồi HP!",sizeof(G.message));G.msgTimer=1.5f;}
        if (IsKeyPressed(KEY_T)){
            for(int i=0;i<MAX_CROPS;i++) if(G.crops[i].active) G.crops[i].stage=CSTAGE_READY;
            strncpy(G.message,"Cây đã chín!",sizeof(G.message));G.msgTimer=1.5f;
        }
        if (IsKeyPressed(KEY_K)&&p->role==ROLE_ADMIN){
            for(int i=0;i<MAX_ENEMIES;i++) if(G.enemies[i].active){G.enemies[i].state=ESTATE_DEAD;G.enemies[i].hp=0;G.enemyCount--;}
            strncpy(G.message,"Admin:Kill all!",sizeof(G.message));G.msgTimer=1.5f;
        }
        if (IsKeyPressed(KEY_V)&&p->role==ROLE_ADMIN){
            /* Đào tất cả đất SOIL_BOUGHT thành SOIL_DUG (bỏ qua ô có cây) */
            int dug=0;
            for(int r=0;r<MAP_ROWS;r++)
            for(int c=0;c<MAP_COLS;c++){
                Tile *t=&G.map[r][c];
                if(t->type==TILE_SOIL_BOUGHT && t->cropIdx<0){
                    t->type=TILE_SOIL_DUG;
                    dug++;
                }
            }
            snprintf(G.message,sizeof(G.message),"Admin: Đào %d ô đất!",dug);
            G.msgTimer=2.0f;
        }
    }

    /* [F6] Doi thoi tiet — Admin + Tester */
    if (IsKeyPressed(KEY_F6) && (p->role==ROLE_ADMIN||p->role==ROLE_TESTER)) {
        G.weather.current = (WeatherType)((G.weather.current + 1) % WEATHER_COUNT);
        G.weather.timer   = 300.0f;
        const char *wNames[] = {"Nắng","Nhiều Mây","Mưa"};
        snprintf(G.message, sizeof(G.message), "Thời tiết: %s", wNames[G.weather.current]);
        G.msgTimer = 2.5f;
    }

    /* [F8] Buff ngọc — Admin only */
    if (IsKeyPressed(KEY_F8) && p->role==ROLE_ADMIN) {
        for (int k=0;k<3;k++){Inv_Add(ITEM_GEM,1);G.gemCount++;}
        snprintf(G.message,sizeof(G.message),"+3 Ngọc! Tổng: %d/3",G.gemCount);
        G.msgTimer=2.5f;
        if (G.gemCount>=3&&!G.bossAlive){extern void SpawnBoss(void);SpawnBoss();}
    }
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    /* Phím E: bật/tắt edit mode */
    if (IsKeyPressed(KEY_E) && !G.showInventory && !G.showStore && !G.showBarnUI) {
        G.editMode = !G.editMode;
        if (G.editMode) { G.hbarSel=-1; G.hbarPlacing=false; G.editSubMode=0; }
    }
<<<<<<< HEAD
<<<<<<< HEAD
    /* ESC thoát edit mode */
    if (IsKeyPressed(KEY_ESCAPE)) {
        if (G.editMode) { G.editMode=false; }
    }
=======
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23

    /* ── Hotbar placement system ── */
    HotbarPlacement_HandleInput();

    /* ── Edit mode click handler ── */
    if (G.editMode && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !MouseOverUI()) {
        Vector2 mw = ScreenToWorld(GetMousePosition());
        int tx2=WorldToTileX(mw.x), ty2=WorldToTileY(mw.y);
        if (tx2>=0&&tx2<MAP_COLS&&ty2>=0&&ty2<MAP_ROWS) {
            if (G.isMoving) {
                /* Đang di chuyển → đặt xuống vị trí mới */
                Object_PlaceAtTile(tx2, ty2);
            } else if (G.editSubMode == 1) {
                /* Sub-mode MOVE */
                if (G.map[ty2][tx2].barnIdx >= 0)
                    Barn_StartMove(tx2, ty2);
                else if (G.map[ty2][tx2].owned)
                    Plot_StartMove(tx2, ty2);
<<<<<<< HEAD
<<<<<<< HEAD
                else { strncpy(G.message,"Khong co gi de di chuyen.",sizeof(G.message)); G.msgTimer=1.5f; }
=======
                else { strncpy(G.message,"Không có gì để di chuyển.",sizeof(G.message)); G.msgTimer=1.5f; }
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
                else { strncpy(G.message,"Không có gì để di chuyển.",sizeof(G.message)); G.msgTimer=1.5f; }
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            } else {
                /* Sub-mode DELETE (0) */
                if (G.map[ty2][tx2].barnIdx>=0)  Barn_Delete(tx2,ty2);
                else if (G.map[ty2][tx2].owned)   Plot_Delete(tx2,ty2);
<<<<<<< HEAD
<<<<<<< HEAD
                else { strncpy(G.message,"Khong co gi de xoa.",sizeof(G.message)); G.msgTimer=1.5f; }
=======
                else { strncpy(G.message,"Không có gì để xóa.",sizeof(G.message)); G.msgTimer=1.5f; }
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
                else { strncpy(G.message,"Không có gì để xóa.",sizeof(G.message)); G.msgTimer=1.5f; }
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            }
        }
        return;
    }

    /* Phải click trong edit mode → hủy di chuyển */
    if (G.editMode && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && G.isMoving) {
        Object_CancelMove();
        return;
    }

    /* Click TRÁI:
       - Nếu đang mở UI → bỏ qua (UI tự xử lý)
       - Nếu đang placing → đã xử lý bởi HotbarPlacement_HandleInput
       - Nếu tool là SWORD → tấn công tại chỗ
       - Nếu tile trong tầm → dùng tool
       - Nếu tile ngoài tầm → di chuyển đến gần rồi tự dùng (set clickTarget) */
   if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !MouseOverUI() && !G.hbarPlacing && !G.player.isActing && !G.editMode && !G.isMoving)
    {
        Vector2 mw = ScreenToWorld(GetMousePosition());

        /* Ưu tiên click vào nhà/công trình làng */
        if (DrawBuilding_HandleClick(mw)) return;

        int tx2 = WorldToTileX(mw.x), ty2 = WorldToTileY(mw.y);
        if (tx2>=0 && tx2<MAP_COLS && ty2>=0 && ty2<MAP_ROWS) {
            Vector2 tc = {(tx2+0.5f)*TILE_SIZE, (ty2+0.5f)*TILE_SIZE};
            float dist = Dist(p->pos, tc);

<<<<<<< HEAD
<<<<<<< HEAD
            /* Nhận diện cây (decor 30/31/32): click 2 lần với Cuốc → chặt */
            if (Tile_IsTree(tx2, ty2)) {
                if (dist <= PLAYER_REACH * 1.5f) {
                    if (p->tool == TOOL_HOE) {
                        Tree_Click(tx2, ty2);
                    } else {
                        strncpy(G.message, "Dung Cuoc [1] de chat cay!", sizeof(G.message));
                        G.msgTimer = 1.5f;
                    }
                } else {
                    p->hasClickTarget = true;
                    p->clickTarget    = tc;
                }
                return;
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            /* Dao da: HOE tren tile co decor da (15-18) */
            {
                int di = GetDecorTypeForTile(ty2, tx2);
                if (di >= 15 && di <= 18 && p->tool == TOOL_HOE && dist <= PLAYER_REACH*1.5f) {
                    int rockAmt = 1 + GetRandomValue(0,2);
                    Inv_Add(ITEM_ROCK, rockAmt);
                    char rm[64]; snprintf(rm,sizeof(rm),"Đào đá! +%d Đá",rockAmt);
                    /* 5% ro ngoc */
                    if(GetRandomValue(0,19)==0){ Inv_Add(ITEM_GEM,1); G.gemCount++; strncat(rm," +NGỌC!",sizeof(rm)-strlen(rm)-1); }
                    strncpy(G.message,rm,sizeof(G.message)); G.msgTimer=2.0f;
                    p->animState=ANIM_DIG; p->isActing=true; p->actTimer=0.4f;
                    return;
                }
            }
            /* Nhận diện cây (decor 30/31/32): tìm cây gần nhất quanh điểm click
               Scan rộng hơn vì cây cao 2-3 tile, anchor ở đáy tile gốc.
               Khi click vào thân cây, tile click thường DƯỚI tile gốc. */
            {
                bool foundTree=false;
                int bestTx=-1, bestTy=-1;
                float bestDist=999999;

                /* Scan 7×5 tile quanh điểm click (rộng hơn để bắt cây cao) */
                for(int dy2=-4; dy2<=2; dy2++)
                for(int dx2=-3; dx2<=3; dx2++) {
                    int cx2=tx2+dx2, cy2=ty2+dy2;
                    if(cx2<0||cx2>=MAP_COLS||cy2<0||cy2>=MAP_ROWS) continue;
                    if(!Tile_IsTree(cx2,cy2)) continue;

                    /* Lấy decor index để tính kích thước sprite thực tế */
                    int di = GetDecorTypeForTile(cy2, cx2);

                    /* Kích thước sprite theo DECORS[]:
                       30=>{srcW=16,srcH=48,scale=2.4}
                       31=>{srcW=32,srcH=48,scale=2.5}
                       32=>{srcW=32,srcH=32,scale=2.6} */
                    float srcW, srcH, sc;
                    if      (di==30) { srcW=16; srcH=48; sc=2.4f; }
                    else if (di==31) { srcW=32; srcH=48; sc=2.5f; }
                    else if (di==32) { srcW=32; srcH=32; sc=2.6f; }
                    else             { srcW=16; srcH=48; sc=2.4f; } /* fallback */

                    float dw = srcW * sc;
                    float dh = srcH * sc;

                    /* Vị trí render thực (anchor bottom-center, giữa tile) */
                    float wx = (cx2 + 0.5f) * TILE_SIZE;
                    float wy = (cy2 + 1)    * TILE_SIZE;

                    /* Bounding box trong world coords */
                    float bx1 = wx - dw * 0.5f;
                    float bx2 = wx + dw * 0.5f;
                    float by1 = wy - dh;
                    float by2 = wy;

                    /* Điểm click có nằm trong bbox không? */
                    bool inBox = (mw.x >= bx1 && mw.x <= bx2 &&
                                  mw.y >= by1 && mw.y <= by2);

                    /* Khoảng cách từ player đến trung tâm bbox */
                    float bcx = wx;
                    float bcy = wy - dh * 0.5f;
                    float d2  = Dist(p->pos, (Vector2){bcx, bcy});

                    /* Ưu tiên cây mà click trúng bbox; nếu không thì lấy gần nhất */
                    if (inBox) {
                        if (!foundTree || d2 < bestDist) {
                            bestDist = d2; bestTx = cx2; bestTy = cy2;
                            foundTree = true;
                        }
                    } else if (!foundTree && d2 < bestDist) {
                        bestDist = d2; bestTx = cx2; bestTy = cy2;
                    }
                }

                if(foundTree && bestTx >= 0) {
                    /* Tâm bbox để player đi đến */
                    int di2 = GetDecorTypeForTile(bestTy, bestTx);
                    float srcH2 = (di2==32) ? 32.0f : 48.0f;
                    float sc2   = (di2==30) ? 2.4f : (di2==31) ? 2.5f : 2.6f;
                    float dh2   = srcH2 * sc2;
                    Vector2 treeCenter = {
                        (bestTx + 0.5f) * TILE_SIZE,
                        (bestTy + 1)    * TILE_SIZE - dh2 * 0.5f
                    };

                    if(Dist(p->pos, treeCenter) <= PLAYER_REACH * 3.0f) {
                        if(p->tool == TOOL_HOE) {
                            Tree_Click(bestTx, bestTy);
                        } else {
                            strncpy(G.message,"Dùng Cuốc [1] để chặt cây!",sizeof(G.message));
                            G.msgTimer=1.5f;
                        }
                    } else {
                        /* Đi đến gần cây rồi tự chặt */
                        p->hasClickTarget = true;
                        p->clickTarget    = treeCenter;
                    }
                    return;
                }
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            }

            if (dist <= PLAYER_REACH) {
                /* Trong tầm → thực hiện ngay */
                GameLogic_HandleTileClick(mw);
            } else {
                /* Ngoài tầm → đi đến tile đó trước */
                p->hasClickTarget = true;
                p->clickTarget    = tc;
            }
        }
    }

    /* Click PHẢI = di chuyển đến vị trí đó (không dùng tool) */
   if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && !MouseOverUI() && !G.hbarPlacing)
    {
        Vector2 mw = ScreenToWorld(GetMousePosition());
        /* Thu sản phẩm nếu click vào chuồng */
        int tx2=WorldToTileX(mw.x), ty2=WorldToTileY(mw.y);
        if (tx2>=0&&tx2<MAP_COLS&&ty2>=0&&ty2<MAP_ROWS && G.map[ty2][tx2].barnIdx>=0) {
            HandleRightClick();
        } else {
            /* Di chuyển đến điểm click */
            p->hasClickTarget = true;
            p->clickTarget    = mw;
        }
    }
}

/* ── Update player ── */
void GameLogic_UpdatePlayer(float dt)
{
    if (MouseOverUI()) return;
    Player *p=&G.player;
    if (p->hurtTimer>0) p->hurtTimer-=dt;

    /* Đang thực hiện hành động (cuốc, tưới...) */
    if (p->isActing){
        p->actTimer-=dt;
        if (p->actTimer<=0){p->isActing=false;p->animState=ANIM_IDLE;}
        p->animTimer+=dt;
        if (p->animTimer>=1.0f/ANIM_FPS){
            p->animTimer=0;
            Texture2D tex=(p->animState==ANIM_DIG)?T.pDig:T.pWater;
            int fc=(tex.width>0)?tex.width/PLAYER_FRAME_W:1;
            p->animFrame=(p->animFrame+1)%(fc>0?fc:1);
        }
        return;
    }

    /* ── Di chuyển WASD (ưu tiên hơn click) ── */
    Vector2 vel={0,0};
    p->isRunning=IsKeyDown(KEY_LEFT_SHIFT);
    if(IsKeyDown(KEY_W)||IsKeyDown(KEY_UP))    {vel.y=-1; p->dir=DIR_UP;    p->hasClickTarget=false;}
    if(IsKeyDown(KEY_S)||IsKeyDown(KEY_DOWN))  {vel.y= 1; p->dir=DIR_DOWN;  p->hasClickTarget=false;}
    if(IsKeyDown(KEY_A)||IsKeyDown(KEY_LEFT))  {vel.x=-1; p->dir=DIR_LEFT;  p->hasClickTarget=false;}
    if(IsKeyDown(KEY_D)||IsKeyDown(KEY_RIGHT)) {vel.x= 1; p->dir=DIR_RIGHT; p->hasClickTarget=false;}

    bool wasdMoving=(vel.x!=0||vel.y!=0);

    /* ── Di chuyển theo click chuột phải ── */
    if (!wasdMoving && p->hasClickTarget) {
        float dx=p->clickTarget.x-p->pos.x;
        float dy=p->clickTarget.y-p->pos.y;
        float dist=sqrtf(dx*dx+dy*dy);
        if (dist < 6.0f) {
            /* Đã đến nơi - tự dùng tool nếu có tile đích */
            p->hasClickTarget=false;
            p->animState=ANIM_IDLE;
            GameLogic_HandleTileClick(p->clickTarget);
        } else {
            vel.x=dx/dist; vel.y=dy/dist;
            /* Xác định hướng nhìn */
            if (fabsf(dx)>fabsf(dy)) p->dir=(dx>0)?DIR_RIGHT:DIR_LEFT;
            else                      p->dir=(dy>0)?DIR_DOWN:DIR_UP;
        }
    }

    bool moving=(vel.x!=0||vel.y!=0);
    if (moving){
        float len=sqrtf(vel.x*vel.x+vel.y*vel.y);
        if(len>0){vel.x/=len;vel.y/=len;}
        float spd=p->isRunning?PLAYER_RUN_SPEED:PLAYER_SPEED;
        float nx=p->pos.x+vel.x*spd*dt;
        float ny=p->pos.y+vel.y*spd*dt;
        if(nx>TILE_SIZE&&nx<MAP_PX_W-TILE_SIZE) p->pos.x=nx;
        if(ny>TILE_SIZE&&ny<MAP_PX_H-TILE_SIZE) p->pos.y=ny;
        p->animState=p->isRunning?ANIM_RUN:ANIM_WALK;
    } else {
        p->animState=ANIM_IDLE;
    }

    p->animTimer+=dt;
    if(p->animTimer>=1.0f/ANIM_FPS){
        p->animTimer=0;
        Texture2D tex;
        switch(p->animState){
            case ANIM_WALK: tex=T.pWalk[p->dir]; break;
            case ANIM_RUN:  tex=T.pRun[p->dir];  break;
            default:        tex=T.pIdle;           break;
        }
        int fc=(tex.width>0)?tex.width/PLAYER_FRAME_W:1;
        if(fc<1)fc=1;
        p->animFrame=(p->animFrame+1)%fc;
    }
}

/* ── Main update ── */
void GameLogic_Update(float dt)
{
    G.gameTime+=dt;
    G.dayTimer+=dt;
<<<<<<< HEAD
<<<<<<< HEAD
    if (G.dayTimer>=DAY_DURATION){
        G.dayTimer=0; G.day++;
        snprintf(G.message,sizeof(G.message),"Ngay moi! Ngay %d bat dau.",G.day);
        G.msgTimer=3.0f;
        Game_Log(TextFormat("New day %d",G.day));
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    if (G.dayTimer >= DAY_DURATION) {
        G.dayTimer = 0; G.day++;
        snprintf(G.message, sizeof(G.message), "Ngày mới! Ngày %d bắt đầu.", G.day);
        G.msgTimer = 3.5f;
        Game_Log(TextFormat("New day %d", G.day));
        /* Auto-save mỗi ngày */
        char autoSavePath[128];
        snprintf(autoSavePath, sizeof(autoSavePath), "saves/%s.dat", G.player.username);
        Game_SavePlayer(autoSavePath);
        extern void Achievement_Check(void);
        Achievement_Check();
        /* Hồi HP chuồng một phần vào đầu ngày mới */
        for (int _i = 0; _i < MAX_BARNS; _i++)
            if (G.barns[_i].active && G.barnHp[_i] < BARN_MAX_HP)
                G.barnHp[_i] = Clamp(G.barnHp[_i] + 20, 0, BARN_MAX_HP);
    }

    /* ── NGÀY/ĐÊM: tính toán isNight và nightOverlay ── */
    {
        float ratio = G.dayTimer / DAY_DURATION;
        bool shouldBeNight = (ratio >= NIGHT_START_RATIO);
        if (shouldBeNight != G.isNight) {
            G.isNight = shouldBeNight;
            if (G.isNight) {
                strncpy(G.message, " Trời tối! Quái vật nguy hiểm hơn về đêm!", sizeof(G.message));
                G.msgTimer = 4.0f;
            }
        }
        float targetOverlay = G.isNight ? 1.0f : 0.0f;
        float lerpSpeed = 0.4f * dt;  /* ~2.5 giây để chuyển */
        if (G.nightOverlay < targetOverlay) G.nightOverlay = Clamp(G.nightOverlay + lerpSpeed, 0.0f, targetOverlay);
        else                                G.nightOverlay = Clamp(G.nightOverlay - lerpSpeed, targetOverlay, 1.0f);
    }

    /* ── MULTI-BOSS: spawn boss mỗi 10 ngày ── */
    if (G.day >= 10 && (G.day % 10 == 0) && G.day > G.lastBossDay && !G.bossAlive && G.dayTimer < 5.0f) {
        G.lastBossDay = G.day;
        SpawnBoss();
        snprintf(G.message, sizeof(G.message), "NGÀY %d: BOSS XUẤT HIỆN! Hãy chuẩn bị chiến đấu!", G.day);
        G.msgTimer = 6.0f;
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    }
    if (G.msgTimer>0) G.msgTimer-=dt;
    if (G.levelUpTimer>0){G.levelUpTimer-=dt;if(G.levelUpTimer<=0)G.levelUpAnim=false;}

    GameLogic_HandleInput();
    GameLogic_UpdatePlayer(dt);
    EntityManager_UpdateCrops(dt);
    EntityManager_UpdateAnimals(dt);
    EntityManager_UpdateEnemies(dt);
    EntityManager_UpdateWeather(dt);
    Tree_UpdateTimers(dt);
<<<<<<< HEAD
<<<<<<< HEAD
=======
    UpdateBarnDmgTimers(dt);
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
    UpdateBarnDmgTimers(dt);
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    GameLogic_UpdateCamera();

    G.spawnTimer-=dt;
    if (G.spawnTimer<=0){
<<<<<<< HEAD
<<<<<<< HEAD
        /* Tang cham: giam 0.5s moi ngay, toi thieu 30s */
        G.spawnTimer=SPAWN_INTERVAL-(float)G.day*0.5f;
        if(G.spawnTimer<30.0f)G.spawnTimer=30.0f;
        EntityManager_SpawnEnemy();
    }
}

/* --- [BAT DAU PHAN THEM: HIEU UNG THOI TIET] --- */

/* Vẽ hiệu ứng thời tiết lên màn hình */
void GameLogic_DrawWeatherEffects(void)
{
    // 1. Nắng
    if (G.weather.current == WEATHER_SUNNY) {
        DrawRectangle(0, 0, SCREEN_W, SCREEN_H, (Color){ 255, 255, 200, 20 });
    }
    
    // 2. Mây - XÁM ĐẬM
    else if (G.weather.current == WEATHER_CLOUDY) {
        DrawRectangle(0, 0, SCREEN_W, SCREEN_H, (Color){ 40, 40, 60, 150 });
    }
    
    // 3. Mưa - ZÍC ZẮC
    else if (G.weather.current == WEATHER_RAIN) {
        // Lớp phủ tối
        DrawRectangle(0, 0, SCREEN_W, SCREEN_H, (Color){ 10, 10, 25, 90 });
        
        for (int i = 0; i < 40; i++) {
            // Mỗi giọt mưa là 3 đoạn thẳng tạo đường zíc zắc
            float x = G.weather.rainDropX[i];
            float y = G.weather.rainDropY[i];
            
            // Đoạn 1: xuống phải
            DrawLineEx(
                (Vector2){ x, y },
                (Vector2){ x + 6, y + 10 },
                2.5f,
                (Color){ 210, 235, 255, 200 }
            );
            
            // Đoạn 2: xuống trái
            DrawLineEx(
                (Vector2){ x + 6, y + 10 },
                (Vector2){ x - 4, y + 22 },
                2.5f,
                (Color){ 210, 235, 255, 200 }
            );
            
            // Đoạn 3: xuống phải
            DrawLineEx(
                (Vector2){ x - 4, y + 22 },
                (Vector2){ x + 8, y + 35 },
                2.5f,
                (Color){ 210, 235, 255, 180 }
            );
            
            // Thêm giọt phụ lệch vị trí
            if (i % 3 == 0) {
                float x2 = x + 30;
                float y2 = y - 10;
                DrawLineEx(
                    (Vector2){ x2, y2 },
                    (Vector2){ x2 - 8, y2 + 18 },
                    2.0f,
                    (Color){ 170, 200, 230, 150 }
                );
            }
        }
    }
}

//hàm update vị trí giọt mưa, gọi trong GameLogic_Update
void GameLogic_UpdateRain(float dt)
{
    if (G.weather.current != WEATHER_RAIN) return;
    
    for (int i = 0; i < 40; i++) {
        // Mỗi giọt có hướng rơi khác nhau - tạo zíc zắc tự nhiên
        float speed = 800.0f + (i * 10); // Tốc độ khác nhau
        float wind = 300.0f + sinf(G.gameTime + i) * 150; // Gió thay đổi
        
        G.weather.rainDropY[i] += speed * dt;
        G.weather.rainDropX[i] -= wind * dt;
        
        // Reset với vị trí ngẫu nhiên
        if (G.weather.rainDropY[i] > SCREEN_H + 100) {
            G.weather.rainDropY[i] = (float)GetRandomValue(-300, -50);
            G.weather.rainDropX[i] = (float)GetRandomValue(-100, SCREEN_W + 200);
        }
    }
}

/* --- [KET THUC PHAN THEM: HIEU UNG THOI TIET] --- */
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        G.spawnTimer=30.0f;
        EntityManager_SpawnEnemy();
    }
    /* Skeleton: 1 con moi 5 phut */
    G.skeletonTimer-=dt;
    if (G.skeletonTimer<=0 && G.day>=1){
        G.skeletonTimer=300.0f;
        SpawnSkeleton_Pub();
    }
<<<<<<< HEAD
}
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
}
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
