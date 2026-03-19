#include "draw_hud.h"
<<<<<<< HEAD
=======
#include "types.h"  
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
#include "../data_manager.h"
#include "../entity_manager.h"
#include "../quest_system.h"
#include "../achievement_system.h"
<<<<<<< HEAD
#include "../font_manager.h" 
=======
#include "../font_manager.h"
#include "../game_logic.h"
#include "../account_manager.h"
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc

static const char *toolLabel[TOOL_COUNT]={
    "[1]Cuốc","[2]Tưới","[3]Trồng","[4]Liềm","[5]Kiếm","[6]Cho Ăn"
};
static const Color toolColor[TOOL_COUNT]={
    {180,120,60,255},{80,180,255,255},{80,200,80,255},
    {220,220,60,255},{220,60,60,255},{255,180,60,255}
};

static const char *s_cropName[NUM_CROP_TYPES]={
    "cà rốt","Beetroot","Cabbage","Caulifl","Kale",
    "Parsnip","Potato","Pumpkin","Radish","Sunflwr","Wheat"
};
static const char *s_animalName[ANIMAL_COUNT]={"Ga","Lon","Cuu"};

/* ── Crop icon frame 5 (chín) helper ── */
static void DrawCropIcon(int ct, Rectangle dst)
{
    if (ct<0||ct>=NUM_CROP_TYPES||T.crop[ct].width==0) return;
    int fw = T.crop[ct].width / 6;  /* 6 frames */
    Rectangle src = {(float)(5*fw), 0, (float)fw, (float)T.crop[ct].height};
    DrawTexturePro(T.crop[ct], src, dst, (Vector2){0,0}, 0, WHITE);
}

/* ── Crop growing stages 1-4 (frame 1..4) helper ── */
static void DrawCropStage(int ct, int frame, Rectangle dst)
{
    if (ct<0||ct>=NUM_CROP_TYPES||T.crop[ct].width==0) return;
    if (frame<0) frame=0; if (frame>5) frame=5;
    int fw = T.crop[ct].width / 6;
    Rectangle src = {(float)(frame*fw), 0, (float)fw, (float)T.crop[ct].height};
    DrawTexturePro(T.crop[ct], src, dst, (Vector2){0,0}, 0, WHITE);
}

/* ── Barn fill count helper (đếm tổng con trong chuồng idx) ── */
static int BarnAnimalCount(int barnIdx)
{
    if (barnIdx<0||barnIdx>=G.barnCount) return 0;
    return G.barns[barnIdx].animalCount;
}

/* ── Tìm chuồng trống gần nhất chấp nhận loại thú at ── */
static int FindBarnForAnimal(AnimalType at)
{
    /* Ưu tiên chuồng đúng loại còn chỗ */
    for (int i=0;i<G.barnCount;i++){
        Barn *b=&G.barns[i];
        if (b->active && b->type==at && b->animalCount<MAX_ANIMALS_PER_BARN)
            return i;
    }
    return -1;
}

/* ─────────────────────────────────────────────────────────
   Labels / quantities
───────────────────────────────────────────────────────── */
static const char *SlotLabel(HotbarItemKind kind)
{
<<<<<<< HEAD
    if (kind==HBAR_SOIL)  return "Đất 3x3";
=======
    if (kind==HBAR_SOIL)  return "Đất 5X5";
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
    if (kind==HBAR_WATER) return "Tưới";
    if (kind==HBAR_BARN)  return "Chuồng";
    if (kind>=HBAR_SEED_0&&kind<=HBAR_SEED_LAST)
        return s_cropName[kind-HBAR_SEED_0];
    if (kind>=HBAR_ANIMAL_0&&kind<=HBAR_ANIMAL_LAST)
        return s_animalName[kind-HBAR_ANIMAL_0];
    return "";
}

static int SlotQuantity(HotbarItemKind kind)
{
    if (kind==HBAR_SOIL||kind==HBAR_WATER||kind==HBAR_BARN) return -1; /* inf */
    if (kind>=HBAR_SEED_0&&kind<=HBAR_SEED_LAST)
        return Inv_Count((ItemType)(ITEM_SEED_CARROT+kind-HBAR_SEED_0));
    if (kind>=HBAR_ANIMAL_0&&kind<=HBAR_ANIMAL_LAST) {
        /* số tiền / giá mỗi con */
        return G.player.money / ANIMAL_PRICE;
    }
    return 0;
}

/* ─────────────────────────────────────────────────────────
   DrawSlotIcon
───────────────────────────────────────────────────────── */
static void DrawSlotIcon(HotbarItemKind kind, int x, int y, int sz)
{
    int p=5, isz=sz-p*2;
    Rectangle dst={(float)(x+p),(float)(y+p),(float)isz,(float)isz};

<<<<<<< HEAD
    /* ── Đất 3x3 ── */
=======
    /* ── Đất 5X5 ── */
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
    if (kind==HBAR_SOIL) {
        if (T.ground.width>=160) {
            int half=isz/2;
            for(int rr=0;rr<2;rr++) for(int cc=0;cc<2;cc++){
                int ti=6+(rr+cc)%3;
                DrawTexturePro(T.ground,(Rectangle){(float)(ti*16),0,16,16},
                    (Rectangle){(float)(x+p+cc*half),(float)(y+p+rr*half),(float)half,(float)half},
                    (Vector2){0,0},0,WHITE);
            }
            DrawLine(x+p+half,y+p,    x+p+half,y+p+isz,(Color){40,40,40,140});
            DrawLine(x+p,    y+p+half,x+p+isz,y+p+half,(Color){40,40,40,140});
        } else {
            DrawRectangleRec(dst,(Color){150,100,50,200});
        }
        DrawRectangleLines(x+p,y+p,isz,isz,(Color){200,160,80,200});
<<<<<<< HEAD
        DrawTextCenteredShort("3x3",x+sz/2-10,y+sz-15,9,(Color){255,230,100,230});
=======
        DrawTextCenteredShort("5X5",x+sz/2-10,y+sz-15,9,(Color){255,230,100,230});
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
        return;
    }

    /* ── Tưới nước ── */
    if (kind==HBAR_WATER) {
        if (T.ground.width>=160) {
            DrawTexturePro(T.ground,(Rectangle){9*16.0f,0,16,16},dst,(Vector2){0,0},0,WHITE);
        } else {
            DrawRectangleRec(dst,(Color){40,80,180,200});
        }
        DrawCircle(x+sz/2,y+sz/2-1,(float)(isz/3),(Color){60,150,255,155});
        DrawCircle(x+sz/2,y+p+4,   (float)(isz/5),(Color){100,190,255,130});
        DrawTextCenteredShort("~",x+sz/2-5,y+sz/2-6,15,(Color){200,235,255,255});
        return;
    }

    /* ── Chuồng trống ── */
    if (kind==HBAR_BARN) {
        /* Dùng home.png hàng 1 để lấy icon chuồng nhỏ (48x48 tại col=0,row=1) */
        if (T.home.width>=48 && T.home.height>=96) {
            Rectangle src={(float)(0*48),(float)(0*48),48,48}; /* hàng nhà row0 col0 */
            DrawTexturePro(T.home,src,dst,(Vector2){0,0},0,WHITE);
        } else {
            DrawRectangleRec(dst,(Color){120,80,40,250});
            DrawTextCentered("H",x+sz/2-5,y+sz/2-8,18,WHITE);
        }
        /* Hiển thị số con / 5 của chuồng đang active nhất */
        int total=0, cap=0;
        for(int i=0;i<G.barnCount;i++) if(G.barns[i].active){
            total+=G.barns[i].animalCount; cap+=MAX_ANIMALS_PER_BARN;
        }
        if (cap>0) {
            char buf[16]; snprintf(buf,sizeof(buf),"%d/%d",total,cap);
            int tw=MeasureText(buf,9);
            DrawRectangle(x+sz-tw-6,y+sz-14,tw+4,12,(Color){0,0,0,160});
            DrawTextCenteredShort(buf,x+sz-tw-4,y+sz-13,9,(Color){255,220,100,255});
        }
        return;
    }

    /* ── Hạt giống: frame CHÍN (5) ── */
    if (kind>=HBAR_SEED_0&&kind<=HBAR_SEED_LAST) {
        int ct=kind-HBAR_SEED_0;
        DrawCropIcon(ct,dst);
        return;
    }

    /* ── Động vật ── */
    if (kind>=HBAR_ANIMAL_0&&kind<=HBAR_ANIMAL_LAST) {
        int at=kind-HBAR_ANIMAL_0;
        if (at<ANIMAL_COUNT && T.animal[at].width>0) {            
            Rectangle src={0,0,(float)T.animal[at].width,(float)T.animal[at].height};
            DrawTexturePro(T.animal[at],src,dst,(Vector2){0,0},0,WHITE);
        } else {
            static Color fallback[3]={{255,220,100,220},{255,160,100,220},{200,220,160,220}};
            int a2=at<3?at:0;
            DrawRectangleRec(dst,fallback[a2]);
            DrawTextCenteredShort(s_animalName[at],x+sz/2-10,y+sz/2-7,12,WHITE);
        }
        return;
    }
}

/* ─────────────────────────────────────────────────────────
   HotbarPlacement_Init
   Layout: Dat | Nuoc | Chuong | 11 cay | 3 thu
───────────────────────────────────────────────────────── */
void HotbarPlacement_Init(void)
{
    G.hbar[0].kind = HBAR_SOIL;
    G.hbar[1].kind = HBAR_WATER;
    G.hbar[2].kind = HBAR_BARN;
    for (int i=0;i<NUM_CROP_TYPES;i++)   /* slot 3..13 = 11 cây */
        G.hbar[3+i].kind = (HotbarItemKind)(HBAR_SEED_0+i);
    for (int i=0;i<ANIMAL_COUNT;i++)     /* slot 14..16 = 3 thú */
        G.hbar[14+i].kind = (HotbarItemKind)(HBAR_ANIMAL_0+i);
    G.hbarSel     = -1;
    G.hbarPlacing = false;
}

/* ─────────────────────────────────────────────────────────
   HotbarPlacement_HandleInput
───────────────────────────────────────────────────────── */
void HotbarPlacement_HandleInput(void)
{
    if (G.showInventory||G.showStore||G.showBarnUI||G.showHelp) return;

    Vector2 mp = GetMousePosition();
    bool overHUD = (mp.y > SCREEN_H - 90);

    if (G.hbarPlacing && G.hbarSel>=0
        && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !overHUD)
    {
        Vector2 mw = ScreenToWorld(mp);
        int tx = WorldToTileX(mw.x);
        int ty = WorldToTileY(mw.y);
        if (tx<0||tx>=MAP_COLS||ty<0||ty>=MAP_ROWS) return;

        HotbarItemKind kind = G.hbar[G.hbarSel].kind;

<<<<<<< HEAD
        /* ── Đặt đất 3x3 ── */
        if (kind==HBAR_SOIL) {
            bool ok=true;
            for(int dr=0;dr<3&&ok;dr++)
            for(int dc=0;dc<3&&ok;dc++){
                int r=ty+dr,c=tx+dc;
                if(r<1||r>=MAP_ROWS-1||c<1||c>=MAP_COLS-1){ok=false;break;}
                TileType tt=G.map[r][c].type;
                if(tt==TILE_WATER_TILE||tt==TILE_STONE){ok=false;break;}
=======
        /* ── Đặt đất 5x5 [BUG FIX #7: 3x3→5x5, trừ tiền] ── */
        if (kind==HBAR_SOIL) {
            /* Tính giá theo số ô đất đã mua */
            int plotTiles=0;
            for(int _r=0;_r<MAP_ROWS;_r++) for(int _c=0;_c<MAP_COLS;_c++)
                if(G.map[_r][_c].owned) plotTiles++;
            int ownedPlots=plotTiles/(LAND_PLOT_W*LAND_PLOT_H);
            int plotPrice=LAND_PRICE_BASE+ownedPlots*50;
            if(G.player.money < plotPrice){
                snprintf(G.message,sizeof(G.message),"Cần $%d để mua đất!",plotPrice);
                G.msgTimer=2.0f; return;
            }
            bool ok=true;
            for(int dr=0;dr<LAND_PLOT_H&&ok;dr++)
            for(int dc=0;dc<LAND_PLOT_W&&ok;dc++){
                int r=ty+dr,c=tx+dc;
                if(r<1||r>=MAP_ROWS-1||c<2||c>=MAP_COLS-1){ok=false;break;}
                TileType tt=G.map[r][c].type;
                if(tt==TILE_WATER_TILE||tt==TILE_STONE||G.map[r][c].owned){ok=false;break;}
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
                if(Tile_IsTree(c,r)){
                    strncpy(G.message,"Phải dọn cây trước khi đặt đất!",sizeof(G.message));
                    G.msgTimer=2.5f; return;
                }
            }
            if (!ok){
<<<<<<< HEAD
                strncpy(G.message,"Vị trí không hợp lệ!",sizeof(G.message));
                G.msgTimer=1.5f; return;
            }
            for(int dr=0;dr<3;dr++)
            for(int dc=0;dc<3;dc++){
                int r=ty+dr,c=tx+dc;
                if(G.map[r][c].type==TILE_GRASS){
                    G.map[r][c].type=TILE_SOIL_BOUGHT;
                    G.map[r][c].owned=true;
                    G.map[r][c].cropIdx=-1;
                    G.map[r][c].barnIdx=-1;
                }
            }
            strncpy(G.message,"Đã đặt đất 3x3!",sizeof(G.message));
            G.msgTimer=1.2f;
=======
                strncpy(G.message,"Vị trí không hợp lệ hoặc đã được sử dụng!",sizeof(G.message));
                G.msgTimer=1.5f; return;
            }
            G.player.money -= plotPrice;
            for(int dr=0;dr<LAND_PLOT_H;dr++)
            for(int dc=0;dc<LAND_PLOT_W;dc++){
                int r=ty+dr,c=tx+dc;
                G.map[r][c].type=TILE_SOIL_BOUGHT;
                G.map[r][c].owned=true;
                G.map[r][c].cropIdx=-1;
                G.map[r][c].barnIdx=-1;
            }
            snprintf(G.message,sizeof(G.message),"Đã mua đất 5x5! (-$%d)",plotPrice);
            G.msgTimer=1.5f;
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
        }
        /* ── Tưới nước ── */
        else if (kind==HBAR_WATER) {
            Tile *tile=&G.map[ty][tx];
            if(tile->type==TILE_SOIL_DUG&&tile->cropIdx<0){
                tile->type=TILE_SOIL_WET;
                strncpy(G.message,"Đã tưới nước!",sizeof(G.message));
                G.msgTimer=1.0f;
            } else {
                strncpy(G.message,"Cần đất đã đào để tưới!",sizeof(G.message));
                G.msgTimer=1.2f;
            }
        }
<<<<<<< HEAD
        /* ── Đặt chuồng mới (mọi loại dùng chung slot này) ── */
        else if (kind==HBAR_BARN) {
            /* Chuồng cần chọn loại → mở popup nhỏ? Tạm thời: thông báo chọn loại thú trước */
=======
        /* ── Đặt chuồng: nhắc chọn loại thú (3 ô cuối hotbar) ── */
        else if (kind==HBAR_BARN) {
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
            strncpy(G.message,"Chọn loại thú (3 ô cuối hotbar) rồi đặt chuồng!",sizeof(G.message));
            G.msgTimer=2.5f;
            G.hbarSel=-1; G.hbarPlacing=false;
        }
        /* ── Trồng cây ── */
        else if (kind>=HBAR_SEED_0&&kind<=HBAR_SEED_LAST) {
            int ct=kind-HBAR_SEED_0;
            ItemType seedItem=(ItemType)(ITEM_SEED_CARROT+ct);
            Tile *tile=&G.map[ty][tx];
            if(tile->type!=TILE_SOIL_WET||tile->cropIdx>=0){
                strncpy(G.message,"Cần đất đã tưới để trồng!",sizeof(G.message));
                G.msgTimer=1.2f; return;
            }
            if(Inv_Count(seedItem)<=0){
                strncpy(G.message,"Hết hạt giống!",sizeof(G.message));
                G.msgTimer=1.5f; return;
            }
            int idx=-1;
            for(int i=0;i<MAX_CROPS;i++) if(!G.crops[i].active){idx=i;break;}
            if(idx<0) return;
            Inv_Remove(seedItem,1);
            G.crops[idx]=(Crop){(CropType)ct,CSTAGE_WATERED,0,true,tx,ty};
            tile->cropIdx=idx; tile->type=TILE_SOIL_WET;
            G.cropCount++;
            Quest_Progress(1,1);
            Level_AddExp(EXP_PER_PLANT);
            Achievement_AddPlant(1);
            strncpy(G.message,"Đã trồng cây!",sizeof(G.message));
            G.msgTimer=1.0f;
        }
<<<<<<< HEAD
        /* ── Đặt con vật vào chuồng ── */
        else if (kind>=HBAR_ANIMAL_0&&kind<=HBAR_ANIMAL_LAST) {
            int at=kind-HBAR_ANIMAL_0;
            /* Tìm chuồng đúng loại còn trống */
            int barnIdx=FindBarnForAnimal((AnimalType)at);
            if (barnIdx<0) {
                /* Không có chuồng phù hợp → đặt chuồng mới tại vị trí click */
                bool canPlace=true;
                for(int dr=0;dr<BARN_H&&canPlace;dr++)
                for(int dc=0;dc<BARN_W&&canPlace;dc++){
                    int r=ty+dr,c=tx+dc;
                    if(r<1||r>=MAP_ROWS-1||c<1||c>=MAP_COLS-1){canPlace=false;break;}
                    TileType tt=G.map[r][c].type;
                    if(tt==TILE_STONE||tt==TILE_WATER_TILE){canPlace=false;break;}
                }
                if (!canPlace){
                    strncpy(G.message,"Vị trí không hợp lệ để đặt chuồng!",sizeof(G.message));
                    G.msgTimer=1.5f; return;
                }
                /* Mark owned */
                for(int dr=0;dr<BARN_H;dr++)
                for(int dc=0;dc<BARN_W;dc++){
                    int r=ty+dr,c=tx+dc;
                    if(r>=0&&r<MAP_ROWS&&c>=0&&c<MAP_COLS)
                        G.map[r][c].owned=true;
                }
                if (!Barn_Build((AnimalType)at,tx,ty)) {
                    strncpy(G.message,"Không thể xây chuồng!",sizeof(G.message));
                    G.msgTimer=1.5f; return;
                }
                barnIdx=G.barnCount-1;
            }
            /* Mua & thêm con vật vào chuồng */
=======
        /* ── Đặt con vật / xây chuồng ── */
        else if (kind>=HBAR_ANIMAL_0&&kind<=HBAR_ANIMAL_LAST) {
            int at=kind-HBAR_ANIMAL_0;
            int barnIdx=FindBarnForAnimal((AnimalType)at);
            if (barnIdx<0) {
                /* Chưa có chuồng phù hợp → xây mới tại vị trí click */
                if (!Barn_Build((AnimalType)at, tx, ty)) return;
                barnIdx = G.barnCount - 1;
            }
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
            Barn_BuyAnimal(barnIdx);
        }
    }

    /* Click phải / ESC → bỏ chọn */
    if (G.hbarPlacing && (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)
                          || IsKeyPressed(KEY_ESCAPE))) {
        G.hbarSel=-1; G.hbarPlacing=false;
    }
}

/* ─────────────────────────────────────────────────────────
   DrawHUD_PlacementBar
───────────────────────────────────────────────────────── */
<<<<<<< HEAD
=======
/* ── End game / win overlay ── */
void DrawHUD_EndGame(void)
{
    if (!G.endGame) return;
    DrawRectangle(0, 0, SCREEN_W, SCREEN_H, (Color){0,0,0,160});

    const char *title = G.endWin ? "CHÚC MỪNG! GAME CLEAR!" : "GAME OVER";
    Color tc = G.endWin ? YELLOW : RED;
    int tw = (int)MeasureTextEx(gameFont, title, 52, 1).x;
    DrawTextEx(gameFont, title,
        (Vector2){(SCREEN_W - tw) * 0.5f, SCREEN_H * 0.35f}, 52, 1, tc);

    const char *sub = G.endWin
        ? "Bạn đã thu thập 3 Ngọc và hạ gục Boss Goblin!"
        : "Bạn đã mất tất cả mạng!";
    int sw = (int)MeasureTextEx(gameFont, sub, 24, 1).x;
    DrawTextEx(gameFont, sub,
        (Vector2){(SCREEN_W - sw) * 0.5f, SCREEN_H * 0.50f}, 24, 1, WHITE);

    /* F5 = Save (giữ nguyên), R = chơi lại */
    DrawTextEx(gameFont, "[R] Chơi lại   |   [F5] Lưu & thoát về menu",
        (Vector2){SCREEN_W * 0.5f - 180, SCREEN_H * 0.62f}, 20, 1, LIGHTGRAY);

    /* Xử lý phím ngay trong hàm draw để gọn */
    if (IsKeyPressed(KEY_R)) {
        /* Reset game mới, giữ nguyên tài khoản */
        G.endGame   = false;
        G.endWin    = false;
        G.day       = 1;
        G.dayTimer  = 0;
        G.gemCount  = 0;
        G.bossAlive = false;
        G.player.hp     = G.player.maxHp;
        G.player.lives  = 3;
        G.player.money  = STARTING_MONEY;
        G.enemyCount    = 0;
        G.goblinCount   = 0;
        G.player.pos    = (Vector2){MAP_PX_W * 0.5f, MAP_PX_H * 0.5f};
        /* Xóa crop, animals, enemies, barns */
        for (int i = 0; i < MAX_CROPS;   i++) G.crops[i].active   = false;
        for (int i = 0; i < MAX_ANIMALS; i++) G.animals[i].active = false;
        for (int i = 0; i < MAX_ENEMIES; i++) G.enemies[i].active = false;
        for (int i = 0; i < MAX_BARNS;   i++) {
            G.barns[i].active = false;
            G.barnHp[i]       = BARN_MAX_HP;
            G.barnDmgTimer[i] = 0.0f;
        }
        G.cropCount = 0; G.animalCount = 0; G.barnCount = 0;
        EntityManager_InitMap();
        GameLogic_Init();
    }
    if (IsKeyPressed(KEY_F5)) {
        /* Lưu rồi về login — gọi Account_Logout để reset toàn bộ
           (xóa form login cũ, reset world, xóa tên/pass) */
        char sp[128];
        snprintf(sp, sizeof(sp), "saves/%s.dat", G.player.username);
        Game_SavePlayer(sp);
        G.endGame = false;
        G.endWin  = false;
        Account_Logout();  /* tự set G.screen = SCR_LOGIN và xóa loginUser/Pass */
    }
}

>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
void DrawHUD_PlacementBar(void)
{
    /* Khong ve hotbar khi mo cac panel UI lon */
    if (G.showInventory||G.showStore||G.showBarnUI||G.showHelp||G.showAchievements) return;
    
    int sz=48, pad=4;  // Giảm size từ 50 xuống 48, tăng padding
    int total=HBAR_SLOT_COUNT*(sz+pad)-pad;
    int startX=SCREEN_W/2-total/2;
    int startY=SCREEN_H-sz-20;

    /* ── Nút Edit Mode (bên trái hotbar) ── */
    int ebx = startX - 130, eby = startY;
    int ebw = 120, ebh = sz;
    
    Color editBg  = G.editMode ? (Color){160,50,20,240} : (Color){18,30,50,215};
    Color editBdr = G.editMode ? (Color){255,100,50,255} : (Color){60,90,130,200};
    
    DrawRectangle(ebx, eby, ebw, ebh, editBg);
    DrawRectangleLines(ebx, eby, ebw, ebh, editBdr);
<<<<<<< HEAD
    
    // Text chính - căn giữa theo chiều dọc
    DrawTextCenteredShort("CHỈNH SỬA", ebx + ebw/2, eby + 8, 11, G.editMode?WHITE:(Color){180,180,180,200});
    DrawTextCenteredShort("NÔNG TRẠI", ebx + ebw/2, eby + 22, 11, G.editMode?WHITE:(Color){180,180,180,200});
    
    /* Sub-mode icons - ĐIỀU CHỈNH LẠI VỊ TRÍ */
    if (G.editMode) {
        Color xoaBg  = (G.editSubMode==0) ? (Color){200,50,50,240} : (Color){80,20,20,200};
        Color moveBg = (G.editSubMode==1) ? (Color){50,120,200,240} : (Color){20,40,80,200};
        
        // Nút XÓA
        DrawRectangle(ebx+10, eby+36, 45, 18, xoaBg);
        DrawRectangleLines(ebx+10, eby+36, 45, 18, (Color){255,100,100,200});
        DrawTextCenteredShort("XÓA", ebx+10+22, eby+40, 10, WHITE);
        
        // Nút MOVE
        DrawRectangle(ebx+65, eby+36, 45, 18, moveBg);
        DrawRectangleLines(ebx+65, eby+36, 45, 18, (Color){100,180,255,200});
        DrawTextCenteredShort("MOVE", ebx+65+22, eby+40, 10, WHITE);
        
        // Xử lý click
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){(float)(ebx+10), (float)(eby+36), 45, 18}))
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) G.editSubMode=0;
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){(float)(ebx+65), (float)(eby+36), 45, 18}))
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) G.editSubMode=1;
    }
    
    /* Click nút chính */
    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){(float)ebx, (float)eby, (float)ebw, (float)ebh})
=======
    DrawTextCenteredShort("CHỈNH SỬA", ebx + ebw/2, eby + 8,  11, G.editMode?WHITE:(Color){180,180,180,200});
    DrawTextCenteredShort("NÔNG TRẠI", ebx + ebw/2, eby + 22, 11, G.editMode?WHITE:(Color){180,180,180,200});

    /* Nút XÓA / MOVE — hiện khi editMode, căn giữa trong ô */
    int btnW = 52, btnH = 20, gap = 6;
    int bx0 = ebx + (ebw - btnW*2 - gap) / 2;
    int by0 = eby + 37;
    bool clickedSubBtn = false;

    if (G.editMode) {
        Color xoaBg  = (G.editSubMode==0)?(Color){200,50,50,240} :(Color){80,20,20,200};
        Color moveBg = (G.editSubMode==1)?(Color){50,120,200,240}:(Color){20,40,80,200};

        /* XÓA */
        Rectangle xoaR = {(float)bx0,(float)by0,(float)btnW,(float)btnH};
        DrawRectangle(bx0, by0, btnW, btnH, xoaBg);
        DrawRectangleLinesEx(xoaR, 1.5f, (Color){255,100,100,220});
        DrawTextCenteredShort("XOA", bx0+btnW/2, by0+4, 12, WHITE);
        if (CheckCollisionPointRec(GetMousePosition(), xoaR)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { G.editSubMode=0; clickedSubBtn=true; }
        }

        /* MOVE */
        int bx1 = bx0 + btnW + gap;
        Rectangle moveR = {(float)bx1,(float)by0,(float)btnW,(float)btnH};
        DrawRectangle(bx1, by0, btnW, btnH, moveBg);
        DrawRectangleLinesEx(moveR, 1.5f, (Color){100,180,255,220});
        DrawTextCenteredShort("MOVE", bx1+btnW/2, by0+4, 12, WHITE);
        if (CheckCollisionPointRec(GetMousePosition(), moveR)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { G.editSubMode=1; clickedSubBtn=true; }
        }
    }

    /* Click nút chính — chỉ toggle nếu KHÔNG click vào nút con */
    if (!clickedSubBtn &&
        CheckCollisionPointRec(GetMousePosition(), (Rectangle){(float)ebx,(float)eby,(float)ebw,(float)ebh})
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
        && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        G.editMode = !G.editMode;
        if (G.editMode) {
            G.hbarSel=-1; G.hbarPlacing=false;
            G.editSubMode=0;
        }
        G.isMoving=false;
    }
    
    /* Label phím tắt - CĂN CHỈNH LẠI */
    DrawTextCenteredShort(G.editMode ? "[ESC]" : "[E]", 
             ebx + ebw/2, eby + ebh + 4, 9, 
             G.editMode ? (Color){255,150,80,200} : (Color){120,120,120,180});

    /* Nền chung hotbar */
    DrawRectangle(startX-8, startY-22, total+16, sz+26, (Color){10,12,22,220});
    DrawRectangleLines(startX-8, startY-22, total+16, sz+26, (Color){55,75,130,200});

    /* Đường phân cách nhóm - ĐIỀU CHỈNH VỊ TRÍ */
    int sep1x = startX + 3*(sz+pad) - pad;
    int sep2x = startX + 14*(sz+pad) - pad;
    DrawRectangle(sep1x, startY-20, 3, sz+22, (Color){80,100,160,180});
    DrawRectangle(sep2x, startY-20, 3, sz+22, (Color){80,100,160,180});

    /* Header nhóm - CĂN GIỮA */
    DrawTextCenteredShort("ĐẤT/NƯỚC/CHUỒNG", startX + (3*(sz+pad))/2, startY-18, 9, (Color){160,200,160,200});
    DrawTextCenteredShort("CÂY TRỒNG", startX + 3*(sz+pad) + (11*(sz+pad))/2, startY-18, 9, (Color){160,200,160,200});
    DrawTextCenteredShort("THÚ NUÔI", startX + 14*(sz+pad) + (3*(sz+pad))/2, startY-18, 9, (Color){200,170,120,200});

    /* Vẽ các slot hotbar */
    for (int i=0; i<HBAR_SLOT_COUNT; i++) {
        int x = startX + i*(sz+pad);
        bool sel = (i==G.hbarSel);
        HotbarItemKind kind = G.hbar[i].kind;

        // Màu nền cho từng loại slot
        Color bg, bdr;
        if (sel) {
            bg  = (Color){220,185,45,245};
            bdr = (Color){255,225,0,255};
        } else if (i<3) {
            bg  = (Color){18,40,22,215};
            bdr = (Color){45,90,55,200};
        } else if (i<14) {
            bg  = (Color){18,35,18,215};
            bdr = (Color){40,75,40,200};
        } else {
            bg  = (Color){35,22,18,215};
            bdr = (Color){85,60,30,200};
        }
        
        DrawRectangle(x, startY, sz, sz, bg);
        DrawRectangleLines(x, startY, sz, sz, bdr);

        // Vẽ icon
        DrawSlotIcon(kind, x, startY, sz);

        // Hiển thị số lượng
        if (kind != HBAR_BARN) {
            int qty = SlotQuantity(kind);
            char qtyStr[8];
            if (qty < 0) {
                snprintf(qtyStr, sizeof(qtyStr), "∞");
            } else {
                snprintf(qtyStr, sizeof(qtyStr), "%d", qty);
            }
            // Đặt số lượng ở góc phải dưới
            int qtyW = MeasureTextShort(qtyStr, 9);
            DrawTextShort(qtyStr, x + sz - qtyW - 4, startY + sz - 14, 9, 
                         (qty > 0 || qty < 0) ? (Color){140,255,140,255} : RED);
        }

        // Tên slot (bên dưới)
        const char *lbl = SlotLabel(kind);
        int lblW = MeasureTextShort(lbl, 8);
        int lblX = x + (sz - lblW) / 2;
        DrawTextShort(lbl, lblX, startY + sz + 2, 8, sel ? GOLD : (Color){150,150,150,200});

        // Xử lý click
        Rectangle sr = {(float)x, (float)startY, (float)sz, (float)sz};
        if (CheckCollisionPointRec(GetMousePosition(), sr) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (G.hbarSel == i) { 
                G.hbarSel = -1; 
                G.hbarPlacing = false; 
            } else { 
                G.hbarSel = i;  
                G.hbarPlacing = true; 
                G.editMode = false; 
            }
        }
    }

    /* Hint cho placement mode - CĂN CHỈNH LẠI */
    if (G.hbarPlacing && G.hbarSel >= 0) {
        HotbarItemKind kind = G.hbar[G.hbarSel].kind;
        const char *hint = "";
        
        if (kind == HBAR_SOIL)  
            hint = "[ĐẤT 5x5] Click vào cỏ xanh | Click phải: Hủy";
        else if (kind == HBAR_WATER) 
            hint = "[TƯỚI] Click đất đã đào (màu nâu) | Click phải: Hủy";
        else if (kind == HBAR_BARN)  
            hint = "[CHUỒNG 5x5] Click vị trí trên map | Click phải: Hủy";
        else if (kind >= HBAR_SEED_0 && kind <= HBAR_SEED_LAST)
            hint = "[TRỒNG] Click đất đã tưới (xanh nhạt) | Click phải: Hủy";
        else if (kind >= HBAR_ANIMAL_0 && kind <= HBAR_ANIMAL_LAST)
            hint = "[THÚ] Click vị trí - tự xây chuồng nếu cần | Click phải: Hủy";

        int hw = MeasureTextShort(hint, 11);
        int hx = SCREEN_W/2 - hw/2 - 8;
        int hy = startY - 36;
        
        DrawRectangle(hx, hy, hw + 16, 22, (Color){0,0,0,200});
        DrawRectangleLines(hx, hy, hw + 16, 22, (Color){255,220,50,200});
        DrawTextCenteredShort(hint, hx + (hw+16)/2, hy + 5, 11, (Color){255,230,80,255});
    }
    
    /* Hint cho edit mode - CĂN CHỈNH LẠI */
    if (G.editMode) {
        const char *hint;
        if (G.editSubMode == 0) {
            hint = G.isMoving ? 
                "ĐANG DI CHUYỂN: Click vị trí mới | Click phải: Hủy" :
                "CHẾ ĐỘ XÓA: Click vào ô đất/chuồng để xóa (hoàn 30-50%) | Click phải: Thoát";
        } else {
            hint = G.isMoving ?
                "ĐANG DI CHUYỂN: Click vị trí mới | Click phải: Hủy" :
                "CHẾ ĐỘ DI CHUYỂN: Click vào ô đất/chuồng muốn di chuyển | Click phải: Thoát";
        }
        
        int hw = MeasureTextShort(hint, 11);
        int hx = SCREEN_W/2 - hw/2 - 8;
        int hy = startY - 36;
        
        DrawRectangle(hx, hy, hw + 16, 22, (Color){0,0,0,200});
        DrawRectangleLines(hx, hy, hw + 16, 22, (Color){255,100,50,200});
        DrawTextCenteredShort(hint, hx + (hw+16)/2, hy + 5, 11, (Color){255,160,80,255});
    }
}

/* ─────────────────────────────────────────────────────────
   DrawHUD_PlacementGhost
───────────────────────────────────────────────────────── */
void DrawHUD_PlacementGhost(void)
{
    /* ── Edit mode ghost: highlight object dưới con trỏ ── */
    if (G.editMode && !G.isMoving) {
        Vector2 mp=GetMousePosition();
        if (mp.y<=SCREEN_H-90) {
            Vector2 mw=ScreenToWorld(mp);
            int tx=WorldToTileX(mw.x), ty=WorldToTileY(mw.y);
            float z=G.camZoom;
            if (tx>=0&&tx<MAP_COLS&&ty>=0&&ty<MAP_ROWS) {
                int bi = G.map[ty][tx].barnIdx;
                bool owned = G.map[ty][tx].owned;
                if (bi >= 0 && bi < G.barnCount && G.barns[bi].active) {
                    /* Highlight chuồng 5x5 */
                    Barn *b=&G.barns[bi];
                    Color col = G.editSubMode==0 ? (Color){255,50,50,90} : (Color){50,150,255,90};
                    Color bdr = G.editSubMode==0 ? (Color){255,80,80,220} : (Color){80,180,255,220};
                    for(int dr=0;dr<BARN_H;dr++) for(int dc=0;dc<BARN_W;dc++) {
                        Vector2 sp=WorldToScreen((Vector2){(float)((b->tileX+dc)*TILE_SIZE),(float)((b->tileY+dr)*TILE_SIZE)});
                        DrawRectangle((int)sp.x,(int)sp.y,(int)(TILE_SIZE*z),(int)(TILE_SIZE*z),col);
                        DrawRectangleLines((int)sp.x,(int)sp.y,(int)(TILE_SIZE*z),(int)(TILE_SIZE*z),bdr);
                    }
                    DrawTextCenteredShort(G.editSubMode==0?"Click: XÓA CHUỒNG (hoàn 50%)":"Click: DI CHUYỂN CHUỒNG",
                             (int)(mp.x+12),(int)(mp.y-20),10,G.editSubMode==0?RED:SKYBLUE);
                } else if (owned) {
<<<<<<< HEAD
                    /* Highlight ô đất — snap 5x5 */
                    int ox=(tx/LAND_PLOT_W)*LAND_PLOT_W, oy=(ty/LAND_PLOT_H)*LAND_PLOT_H;
                    Color col = G.editSubMode==0 ? (Color){255,80,50,80} : (Color){80,200,255,80};
                    Color bdr = G.editSubMode==0 ? (Color){255,100,60,200} : (Color){100,220,255,200};
                    for(int dr=0;dr<LAND_PLOT_H;dr++) for(int dc=0;dc<LAND_PLOT_W;dc++) {
                        int tr=oy+dr, tc=ox+dc;
                        if(tr<0||tr>=MAP_ROWS||tc<0||tc>=MAP_COLS) continue;
                        if(!G.map[tr][tc].owned) continue;
=======
                    /* Highlight ô đất — tìm corner trái-trên của plot chứa tile này */
                    int ox = tx, oy = ty;
                    /* Quét ngược để tìm điểm đầu của vùng owned 5x5 liên tục */
                    while (ox > 0 && G.map[ty][ox-1].owned) ox--;
                    while (oy > 0 && G.map[oy-1][tx].owned) oy--;
                    Color col = G.editSubMode==0 ? (Color){255,80,50,80} : (Color){80,200,255,80};
                    Color bdr = G.editSubMode==0 ? (Color){255,100,60,200} : (Color){100,220,255,200};
                    int gpw=0; while(ox+gpw<MAP_COLS && G.map[oy][ox+gpw].owned && G.map[oy][ox+gpw].barnIdx<0) gpw++;
                    int gph=0; while(oy+gph<MAP_ROWS && G.map[oy+gph][ox].owned && G.map[oy+gph][ox].barnIdx<0) gph++;
                    for(int dr=0;dr<gph;dr++) for(int dc=0;dc<gpw;dc++) {
                        int tr=oy+dr, tc=ox+dc;
                        if(tr<0||tr>=MAP_ROWS||tc<0||tc>=MAP_COLS) continue;
                        if(!G.map[tr][tc].owned || G.map[tr][tc].barnIdx>=0) continue;
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
                        Vector2 sp=WorldToScreen((Vector2){(float)(tc*TILE_SIZE),(float)(tr*TILE_SIZE)});
                        DrawRectangle((int)sp.x,(int)sp.y,(int)(TILE_SIZE*z),(int)(TILE_SIZE*z),col);
                        DrawRectangleLines((int)sp.x,(int)sp.y,(int)(TILE_SIZE*z),(int)(TILE_SIZE*z),bdr);
                    }
<<<<<<< HEAD
                    DrawTextCenteredShort(G.editSubMode==0?"Click: XÓA Ô ĐẤT (hoàn 30%)":"Click: DI CHUYỂN Ô ĐẤT",
=======
                    DrawTextCenteredShort(G.editSubMode==0?"Click: XOA O DAT (hoan 30%)":"Click: DI CHUYEN O DAT",
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
                             (int)(mp.x+12),(int)(mp.y-20),10,G.editSubMode==0?RED:SKYBLUE);
                }
            }
        }
        return;
    }

    /* ── Move ghost: object đang trên tay ── */
    if (G.isMoving) {
        Vector2 mp=GetMousePosition();
        if (mp.y>SCREEN_H-90) return;
        Vector2 mw=ScreenToWorld(mp);
        int tx=WorldToTileX(mw.x), ty=WorldToTileY(mw.y);
        float z=G.camZoom;
<<<<<<< HEAD
        int gW = G.movePlot ? LAND_PLOT_W : BARN_W;
        int gH = G.movePlot ? LAND_PLOT_H : BARN_H;
=======
        /* Dùng kích thước thực của plot/barn đang move */
        int gW = G.movePlot ? (G.movePlotW > 0 ? G.movePlotW : LAND_PLOT_W) : BARN_W;
        int gH = G.movePlot ? (G.movePlotH > 0 ? G.movePlotH : LAND_PLOT_H) : BARN_H;
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
        bool allValid=true;
        for(int dr=0;dr<gH&&allValid;dr++) for(int dc=0;dc<gW&&allValid;dc++) {
            int r=ty+dr,c=tx+dc;
            if(r<1||r>=MAP_ROWS-1||c<2||c>=MAP_COLS-1) { allValid=false; break; }
<<<<<<< HEAD
            if(G.movePlot && (G.map[r][c].type!=TILE_GRASS||G.map[r][c].owned)) allValid=false;
            if(!G.movePlot && (!G.map[r][c].owned||G.map[r][c].barnIdx>=0)) allValid=false;
=======
            if(G.movePlot && G.map[r][c].owned) allValid=false;
            if(!G.movePlot && (G.map[r][c].barnIdx>=0
                               ||G.map[r][c].type==TILE_STONE
                               ||G.map[r][c].type==TILE_WATER_TILE)) allValid=false;
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
        }
        Color col = allValid ? (G.movePlot?(Color){80,200,80,90}:(Color){180,140,60,90}) : (Color){255,50,50,80};
        Color bdr = allValid ? (G.movePlot?(Color){100,240,100,200}:(Color){220,180,80,200}) : (Color){255,80,80,200};
        for(int dr=0;dr<gH;dr++) for(int dc=0;dc<gW;dc++) {
            int r=ty+dr,c=tx+dc;
            if(r<0||r>=MAP_ROWS||c<0||c>=MAP_COLS) continue;
            Vector2 sp=WorldToScreen((Vector2){(float)(c*TILE_SIZE),(float)(r*TILE_SIZE)});
            DrawRectangle((int)sp.x,(int)sp.y,(int)(TILE_SIZE*z),(int)(TILE_SIZE*z),col);
            DrawRectangleLines((int)sp.x,(int)sp.y,(int)(TILE_SIZE*z),(int)(TILE_SIZE*z),bdr);
        }
        DrawTextCenteredShort(allValid?"Click: Đặt xuống đất":"Vị trí không hợp lệ",
                 (int)(mp.x+12),(int)(mp.y-20),10,allValid?LIME:RED);
        return;
    }

    if (!G.hbarPlacing||G.hbarSel<0) return;
    Vector2 mp=GetMousePosition();
    if (mp.y>SCREEN_H-90) return;

    Vector2 mw=ScreenToWorld(mp);
    int tx=WorldToTileX(mw.x), ty=WorldToTileY(mw.y);
    float z=G.camZoom;
    HotbarItemKind kind=G.hbar[G.hbarSel].kind;

<<<<<<< HEAD
    /* Ghost: đất 3x3, chuồng/vật 5x5 */
    bool isBarnKind=(kind==HBAR_BARN||(kind>=HBAR_ANIMAL_0&&kind<=HBAR_ANIMAL_LAST));
    bool is3x3 = (kind==HBAR_SOIL||isBarnKind);
    if (is3x3) {
        bool isBarn = isBarnKind;
        int gW = isBarn ? BARN_W : 3;
        int gH = isBarn ? BARN_H : 3;
=======
    /* Ghost: đất 5x5, chuồng 5x5 */
    bool isBarnKind=(kind==HBAR_BARN||(kind>=HBAR_ANIMAL_0&&kind<=HBAR_ANIMAL_LAST));
    bool isSoilKind=(kind==HBAR_SOIL);
    bool is5x5 = (isSoilKind||isBarnKind);
    if (is5x5) {
        int gW = LAND_PLOT_W;  /* 5 */
        int gH = LAND_PLOT_H;  /* 5 */
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
        for(int dr=0;dr<gH;dr++)
        for(int dc=0;dc<gW;dc++){
            int r=ty+dr,c=tx+dc;
            if(r<0||r>=MAP_ROWS||c<0||c>=MAP_COLS) continue;
            Vector2 sp=WorldToScreen((Vector2){(float)(c*TILE_SIZE),(float)(r*TILE_SIZE)});
<<<<<<< HEAD
            bool valid = (G.map[r][c].type!=TILE_STONE&&G.map[r][c].type!=TILE_WATER_TILE)&&G.map[r][c].owned;
            Color col  = valid?(isBarn?(Color){220,170,60,255}:(Color){160,110,50,200}):(Color){255,50,50,150};
            Color edge = valid?(isBarn?(Color){255,210,80,255}:(Color){220,160,80,255}):(Color){255,80,80,255};
=======

            bool valid;
            bool onHome2 = (c>=29&&c<=33 && r>=9 &&r<=12);
            bool onBldg2 = (c>=17&&c<=45 && r>=14&&r<=17);
            bool inBound = (r>=1 && r<MAP_ROWS-1 && c>=2 && c<MAP_COLS-1);
            if (isSoilKind) {
                /* Đất: tile chưa owned, không stone/water/cây/building */
                valid = inBound
                     && !G.map[r][c].owned
                     && G.map[r][c].type!=TILE_STONE
                     && G.map[r][c].type!=TILE_WATER_TILE
                     && !Tile_IsTree(c,r)
                     && !onHome2 && !onBldg2;
            } else {
                /* Chuồng: không có chuồng khác, không stone/water/building
                   Có thể đặt trên đất chưa owned (tự mua) hoặc đã owned */
                valid = inBound
                     && G.map[r][c].barnIdx < 0
                     && G.map[r][c].type != TILE_STONE
                     && G.map[r][c].type != TILE_WATER_TILE
                     && !onHome2 && !onBldg2;
            }

            Color col  = valid ? (isBarnKind?(Color){220,170,60,200}:(Color){80,200,80,120})
                               : (Color){255,50,50,120};
            Color edge = valid ? (isBarnKind?(Color){255,210,80,255}:(Color){100,240,100,220})
                               : (Color){255,80,80,220};
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
            DrawRectangle((int)sp.x,(int)sp.y,(int)(TILE_SIZE*z),(int)(TILE_SIZE*z),col);
            DrawRectangleLines((int)sp.x,(int)sp.y,(int)(TILE_SIZE*z),(int)(TILE_SIZE*z),edge);
        }
    }
    else if (kind==HBAR_WATER||(kind>=HBAR_SEED_0&&kind<=HBAR_SEED_LAST)) {
        if(tx<0||tx>=MAP_COLS||ty<0||ty>=MAP_ROWS) return;
        Vector2 sp=WorldToScreen((Vector2){(float)(tx*TILE_SIZE),(float)(ty*TILE_SIZE)});
        bool valid=(kind==HBAR_WATER)
            ?(G.map[ty][tx].type==TILE_SOIL_DUG)
            :(G.map[ty][tx].type==TILE_SOIL_WET);
        Color col=valid
            ?(kind==HBAR_WATER?(Color){60,140,255,110}:(Color){80,200,80,110})
            :(Color){255,50,50,80};
        DrawRectangle((int)sp.x,(int)sp.y,(int)(TILE_SIZE*z),(int)(TILE_SIZE*z),col);
        DrawRectangleLinesEx((Rectangle){sp.x,sp.y,(float)(TILE_SIZE*z),(float)(TILE_SIZE*z)},
            2.0f,(Color){255,255,100,200});

        /* Preview cây trồng (frame 1=mầm nhỏ) */
        if (kind>=HBAR_SEED_0&&kind<=HBAR_SEED_LAST && valid) {
            int ct=kind-HBAR_SEED_0;
            float cw=24.0f*z, ch=24.0f*z;
            DrawCropStage(ct,1,(Rectangle){sp.x+TILE_SIZE*z*0.5f-cw*0.5f,
                sp.y+TILE_SIZE*z*0.5f-ch*0.7f,cw,ch});
        }
    }
}

/* ─────────────────────────────────────────────────────────
   HUD cũ
───────────────────────────────────────────────────────── */
void DrawHUD_DayProgress(void)
{
    float t=G.dayTimer/DAY_DURATION;
<<<<<<< HEAD
    int bx=SCREEN_W/2+44,bw=120,by=14,bh=14;
=======
    int bx=SCREEN_W/2+54,bw=150,by=22,bh=14;
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
    DrawRectangle(bx,by,bw,bh,(Color){30,30,50,200});
    Color fill=(t<0.5f)?(Color){255,210,50,255}:(Color){255,100,30,255};
    DrawRectangle(bx,by,(int)(bw*t),bh,fill);
    DrawRectangleLines(bx,by,bw,bh,DARKGRAY);
    DrawCircle(bx+(int)(bw*t),by+bh/2,7,(Color){255,230,80,255});
}

void DrawHUD_WeatherIcon(void)
{
<<<<<<< HEAD
    int wx=SCREEN_W/2+170,wy=6;
=======
    int wx=SCREEN_W/2+215,wy=14;
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
    switch(G.weather.current){
        case WEATHER_SUNNY:
            /* Vẽ mặt trời với tia nắng */
            DrawCircle(wx+12,wy+12,9,(Color){255,220,50,255});
            for(int r=0;r<8;r++){
                float angle=r*45.0f*(3.14159f/180.0f);
                DrawLine(wx+12+(int)(13*cosf(angle)),wy+12+(int)(13*sinf(angle)),
                         wx+12+(int)(17*cosf(angle)),wy+12+(int)(17*sinf(angle)),
                         (Color){255,200,30,200});
            }
<<<<<<< HEAD
            DrawTextCenteredShort("Nang",(int)(wx+46),wy+6,12,YELLOW); break;
        case WEATHER_CLOUDY:
            DrawEllipse(wx+14,wy+11,18,8,(Color){180,180,190,230});
            DrawEllipse(wx+22,wy+8,12,7,(Color){200,200,210,230});
            DrawTextCenteredShort("Day",(int)(wx+46),wy+6,12,LIGHTGRAY); break;
=======
            DrawTextCenteredShort("Nắng",(int)(wx+46),wy+6,12,YELLOW); break;
        case WEATHER_CLOUDY:
            DrawEllipse(wx+14,wy+11,18,8,(Color){180,180,190,230});
            DrawEllipse(wx+22,wy+8,12,7,(Color){200,200,210,230});
            DrawTextCenteredShort("Mây",(int)(wx+46),wy+6,12,LIGHTGRAY); break;
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
        case WEATHER_RAINY:
            DrawEllipse(wx+14,wy+9,18,7,(Color){120,130,160,230});
            DrawEllipse(wx+22,wy+7,12,6,(Color){130,140,170,230});
            for(int i=0;i<5;i++)
                DrawLine(wx+i*6+4,wy+18,wx+i*6+1,wy+28,(Color){100,170,255,220});
<<<<<<< HEAD
            DrawTextCenteredShort("Mua",(int)(wx+46),wy+6,12,SKYBLUE); break;
=======
            DrawTextCenteredShort("Mưa",(int)(wx+46),wy+6,12,SKYBLUE); break;
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
        default: break;
    }
}

void DrawHUD_TopBar(void)
{
<<<<<<< HEAD
    Player *p=&G.player;
    DrawRectangle(0,0,SCREEN_W,52,(Color){12,14,28,215});
    DrawRectangle(0,51,SCREEN_W,2,(Color){60,80,150,255});

    /* Tiền + username - căn trái */
    DrawTextCenteredShort(TextFormat("$%d",p->money), 60, 8, 20, GOLD);
    DrawTextCenteredShort(TextFormat("[%s]",p->username), 60, 32, 11,
             p->role==ROLE_ADMIN?RED:p->role==ROLE_TESTER?ORANGE:LIGHTGRAY);

    /* Ngày - căn giữa */
    DrawTextCenteredShort(TextFormat("Ngày %d",G.day), SCREEN_W/2, 8, 18, WHITE);
    DrawHUD_DayProgress(); DrawHUD_WeatherIcon();

    /* Tool - bên trái giữa */
    DrawTextCenteredShort(toolLabel[p->tool], SCREEN_W/2-220, 16, 14, toolColor[p->tool]);

    /* HP / Level / EXP - căn phải */
    int hbx=SCREEN_W-230, hby=4;
    DrawTextCenteredShort(TextFormat("HP %d/%d",p->hp,p->maxHp), hbx+70, hby, 13, WHITE);
    DrawRectangle(hbx,hby+18,150,10,(Color){40,40,40,210});
    float hr=(float)p->hp/p->maxHp;
    DrawRectangle(hbx,hby+18,(int)(150*hr),10,hr>0.5f?GREEN:hr>0.25f?YELLOW:RED);
    DrawRectangleLines(hbx,hby+18,150,10,DARKGRAY);
    LevelData *lv=&p->lvl;
    DrawTextCenteredShort(TextFormat("Lv.%d",lv->level), hbx+163, hby, 13, GOLD);
    DrawRectangle(hbx,hby+30,150,7,(Color){30,30,30,200});
    float er=(float)lv->exp/lv->expToNext;
    DrawRectangle(hbx,hby+30,(int)(150*er),7,(Color){80,160,255,255});
    DrawRectangleLines(hbx,hby+30,150,7,DARKGRAY);
    DrawTextCenteredShort(TextFormat("%d/%d EXP",lv->exp,lv->expToNext), hbx+180, hby+28, 9, LIGHTGRAY);

    /* Hướng dẫn phím - căn giữa đáy màn hình */
    DrawTextCenteredShort("WASD:Di chuyển | 1-6:Tool | LClick:dùng | I:túi | B:Shop | N:Chuồng | Q:Quest | F5:lưu",
             SCREEN_W/2, SCREEN_H-13, 9, (Color){160,160,160,160});
}

=======
    Player *p = &G.player;

    /* Topbar 64px — 1 dòng chính + 1 dòng phụ */
    DrawRectangle(0, 0, SCREEN_W, 64, (Color){12, 14, 28, 228});
    DrawRectangle(0, 63, SCREEN_W, 2, (Color){60, 80, 150, 255});

    /* ══ ZONE 1: TIỀN (trái, x=14) ══ */
    DrawTextShort(TextFormat("$%d", p->money), 14, 12, 30, GOLD);

    /* ══ ZONE 2: NGÀY + PROGRESS (giữa-trái) ══ */
    /* "Ngay X" căn giữa vùng 300..550 */
    int midX = SCREEN_W / 2 - 80;
    const char *dayLabel = G.isNight ? TextFormat("Dêm %d", G.day)
                                     : TextFormat("Ngày %d", G.day);
    Color dayColor = G.isNight ? (Color){180,200,255,255} : WHITE;
    DrawTextCenteredShort(dayLabel, midX, 12, 28, dayColor);

    /* Progress bar ngày — bên phải chữ ngày */
    float t = G.dayTimer / DAY_DURATION;
    int bx = midX + 64, bw = 130, by2 = 20, bh2 = 14;
    DrawRectangle(bx, by2, bw, bh2, (Color){30,30,50,200});
    Color barFill = (t < 0.5f) ? (Color){255,210,50,255} : (Color){255,100,30,255};
    DrawRectangle(bx, by2, (int)(bw*t), bh2, barFill);
    DrawRectangleLines(bx, by2, bw, bh2, DARKGRAY);
    DrawCircle(bx+(int)(bw*t), by2+bh2/2, 6, (Color){255,230,80,255});

    /* ══ ZONE 3: THỜI TIẾT + TOOL (giữa-phải) ══
       Cạnh nhau, đủ chỗ giữa ZONE 2 và ZONE 4 */
    int wx = bx - 250;  
    /* Icon thời tiết nhỏ gọn */
    switch (G.weather.current) {
        case WEATHER_SUNNY:
            DrawCircle(wx+10, 22, 9, (Color){255,220,50,255});
            for (int r=0;r<6;r++) {
                float ang = r*60.0f*(3.14159f/180.0f);
                DrawLine(wx+10+(int)(12*cosf(ang)), 22+(int)(12*sinf(ang)),
                         wx+10+(int)(16*cosf(ang)), 22+(int)(16*sinf(ang)),
                         (Color){255,200,30,200});
            }
            DrawTextShort("NẮNG", wx+26, 10, 20, YELLOW);
            break;
        case WEATHER_CLOUDY:
            DrawEllipse(wx+12, 20, 14, 7, (Color){180,180,190,230});
            DrawEllipse(wx+20, 17, 10, 6, (Color){200,200,210,230});
            DrawTextShort("MÂY", wx+26, 10, 20, LIGHTGRAY);
            break;
        case WEATHER_RAINY:
            DrawEllipse(wx+12, 18, 14, 6, (Color){120,130,160,230});
            for (int i=0;i<4;i++)
                DrawLine(wx+i*7+4, 30, wx+i*7+1, 40, (Color){100,170,255,220});
            DrawTextShort("MƯA", wx+26, 10, 20, SKYBLUE);
            break;
        default: break;
    }

    /* Tool — sau thời tiết */
    int toolX = wx - 200;  /* dịch trái thêm 100px (tổng -250) */
    DrawTextShort(toolLabel[p->tool], toolX, 10, 24, toolColor[p->tool]);

    /* ══ ZONE 4: TIM + HP + NGỌC + LEVEL + EXP (phải) ══
       Dòng 1: ♥♥♥  [HP]  Ngoc:X/3 ●●●
       Dòng 2: Lv.X  [EXP bar]                          */
    int rx = SCREEN_W - 440;

    /* Dòng 1 — y=4 */
    /* Tim */
    for (int hi = 0; hi < 3; hi++) {
        int hx = rx + hi*34, hy = 4;
        bool alive = (hi < p->lives);
        Color fill = alive ? (Color){220,30,30,255} : (Color){45,45,45,255};
        DrawCircle(hx+6,  hy+7, 8, WHITE);
        DrawCircle(hx+18, hy+7, 8, WHITE);
        DrawTriangle((Vector2){hx-1,hy+11},(Vector2){hx+25,hy+11},(Vector2){hx+12,hy+26},WHITE);
        DrawCircle(hx+6,  hy+7, 7, fill);
        DrawCircle(hx+18, hy+7, 7, fill);
        DrawTriangle((Vector2){hx,hy+11},(Vector2){hx+24,hy+11},(Vector2){hx+12,hy+25},fill);
    }

    /* HP bar */
    int hpX = rx + 106, hpW = 100;
    float hr = (float)p->hp / p->maxHp;
    DrawRectangle(hpX, 6, hpW, 18, (Color){40,40,40,200});
    DrawRectangle(hpX, 6, (int)(hpW*hr), 18,
                  hr>0.5f?GREEN : hr>0.25f?YELLOW : RED);
    DrawRectangleLines(hpX, 6, hpW, 18, DARKGRAY);
    DrawTextCenteredShort(TextFormat("%d/%d", p->hp, p->maxHp),
                          hpX+hpW/2, 7, 12, WHITE);

    /* Ngọc */
    int gemX = hpX + hpW + 20;
    Color gemCol = G.gemCount>=3 ? (Color){100,230,255,255} : (Color){220,200,80,255};
    DrawTextShort(TextFormat("Ngọc: %d/3", G.gemCount), gemX, 4, 18, gemCol);
    for (int g=0;g<3;g++) {
        int _gx = gemX+84+g*16, _gy = 14;
        if (g < G.gemCount) {
            /* Ngọc đã có: cục tròn đỏ */
            DrawCircle(_gx, _gy, 6, (Color){200,30,30,255});
            DrawCircleLines(_gx, _gy, 6, (Color){255,120,120,255});
            DrawCircle(_gx-2, _gy-2, 2, (Color){255,180,180,200});
        } else {
            /* Chưa có: vòng tròn xám */
            DrawCircle(_gx, _gy, 6, (Color){55,55,65,220});
            DrawCircleLines(_gx, _gy, 6, DARKGRAY);
        }
    }

    /* Dòng 2 — y=36 */
    LevelData *lv = &p->lvl;
    DrawTextShort(TextFormat("Lv.%d", lv->level), rx, 38, 22, GOLD);
    int expX = rx+50, expW = SCREEN_W - rx - 50 - 8;
    float er = (float)lv->exp / lv->expToNext;
    DrawRectangle(expX, 40, expW, 14, (Color){30,30,30,200});
    DrawRectangle(expX, 40, (int)(expW*er), 14, (Color){80,160,255,255});
    DrawRectangleLines(expX, 40, expW, 14, DARKGRAY);
    DrawTextCenteredShort(TextFormat("%d/%d EXP", lv->exp, lv->expToNext),
                          expX+expW/2, 41, 12, (Color){200,200,200,255});

    
}
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
void DrawHUD_LevelUp(void)
{
    if(!G.levelUpAnim) return;
    float a=G.levelUpTimer>1.0f?1.0f:G.levelUpTimer;
    unsigned char alpha=(unsigned char)(a*255);
    float y=SCREEN_H*0.35f-sinf(G.levelUpTimer*2.0f)*30.0f;
<<<<<<< HEAD
    DrawTextCenteredShort(TextFormat("LEVEL UP!  Cap %d",G.player.lvl.level),
=======
    DrawTextCenteredShort(TextFormat("LEVEL UP!  Cấp %d",G.player.lvl.level),
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
                     SCREEN_W/2,(int)y,40,(Color){255,220,0,alpha});
    DrawTextCenteredShort(TextFormat("+ $%d  + HP Max",G.player.lvl.level*50),
                     SCREEN_W/2,(int)(y+46),20,(Color){255,255,200,alpha});
}

void DrawHUD_Message(void)
{
    if(G.msgTimer<=0) return;
    float a=G.msgTimer>1.0f?1.0f:G.msgTimer;
    unsigned char al=(unsigned char)(a*230);
    int tw=MeasureText(G.message,17);
    int bx=SCREEN_W/2-tw/2-14,by=SCREEN_H/2-70;
    DrawRectangle(bx,by,tw+28,32,(Color){0,0,0,(unsigned char)(a*145)});
    DrawRectangleLines(bx,by,tw+28,32,(Color){255,210,50,al});
    DrawTextCenteredShort(G.message,bx+(tw + 28)/2,by+8,17,(Color){255,255,255,al});
}

void DrawHUD_Minimap(void)
{
<<<<<<< HEAD
    int mmX=SCREEN_W-152,mmY=SCREEN_H-170;
    int mmW=144,mmH=98;
    DrawRectangle(mmX,mmY,mmW,mmH,(Color){8,18,8,210});
    DrawRectangleLines(mmX,mmY,mmW,mmH,(Color){70,90,70,255});
    float sx=(float)mmW/MAP_COLS,sy=(float)mmH/MAP_ROWS;
    for(int r=0;r<MAP_ROWS;r++) for(int c=0;c<MAP_COLS;c++)
        if(G.map[r][c].owned)
            DrawRectangle(mmX+(int)(c*sx),mmY+(int)(r*sy),(int)sx+1,(int)sy+1,(Color){140,100,40,160});
    DrawRectangle(mmX,mmY,(int)(2*sx),mmH,(Color){40,80,200,120});
    for(int i=0;i<MAX_ENEMIES;i++){
        if(!G.enemies[i].active) continue;
        DrawRectangle(mmX+(int)(G.enemies[i].pos.x/TILE_SIZE*sx)-2,
                      mmY+(int)(G.enemies[i].pos.y/TILE_SIZE*sy)-2,5,5,RED);
    }
    for(int i=0;i<MAX_ANIMALS;i++){
        if(!G.animals[i].active) continue;
        DrawRectangle(mmX+(int)(G.animals[i].pos.x/TILE_SIZE*sx)-1,
                      mmY+(int)(G.animals[i].pos.y/TILE_SIZE*sy)-1,4,4,YELLOW);
    }
    DrawCircle(mmX+(int)(G.player.pos.x/TILE_SIZE*sx),
               mmY+(int)(G.player.pos.y/TILE_SIZE*sy),4,BLUE);
=======
    int mmX=4,mmY=66;
    int mmW=144,mmH=98;
    DrawRectangle(mmX,mmY,mmW,mmH,(Color){8,18,8,210});
    DrawRectangleLines(mmX,mmY,mmW,mmH,(Color){70,90,70,255});
    float sx=(float)mmW/MAP_COLS, sy=(float)mmH/MAP_ROWS;

    /* Vùng rừng goblin — xanh lam mờ */
    DrawRectangle(mmX, mmY,
                  (int)(18*sx), (int)(18*sy),
                  (Color){30,60,120,80});

    /* Buildings — nâu vàng */
    /* HOME (30,10,3x2) */
    DrawRectangle(mmX+(int)(30*sx), mmY+(int)(10*sy),
                  (int)(3*sx)+1, (int)(2*sy)+1, (Color){180,140,60,200});
    /* Row buildings (18..44, 15, 3x2 each) */
    for (int bx=18; bx<=42; bx+=6)
        DrawRectangle(mmX+(int)(bx*sx), mmY+(int)(15*sy),
                      (int)(3*sx)+1, (int)(2*sy)+1, (Color){160,120,50,200});

    /* Đất đã mua — nâu sáng */
    for(int r=0;r<MAP_ROWS;r++) for(int c=0;c<MAP_COLS;c++)
        if(G.map[r][c].owned)
            DrawRectangle(mmX+(int)(c*sx),mmY+(int)(r*sy),
                          (int)sx+1,(int)sy+1,(Color){140,100,40,200});

    /* Enemies — đỏ */
    for(int i=0;i<MAX_ENEMIES;i++){
        if(!G.enemies[i].active) continue;
        DrawRectangle(mmX+(int)(G.enemies[i].pos.x/TILE_SIZE*sx)-1,
                      mmY+(int)(G.enemies[i].pos.y/TILE_SIZE*sy)-1,3,3,RED);
    }

    /* Animals — vàng */
    for(int i=0;i<MAX_ANIMALS;i++){
        if(!G.animals[i].active) continue;
        DrawRectangle(mmX+(int)(G.animals[i].pos.x/TILE_SIZE*sx)-1,
                      mmY+(int)(G.animals[i].pos.y/TILE_SIZE*sy)-1,3,3,YELLOW);
    }

    /* Player — xanh lam */
    DrawCircle(mmX+(int)(G.player.pos.x/TILE_SIZE*sx),
               mmY+(int)(G.player.pos.y/TILE_SIZE*sy),3,BLUE);
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
    DrawTextCenteredShort("MAP",mmX+4,mmY+2,9,(Color){150,150,150,180});
}

void DrawHUD_Weather(void)
{
<<<<<<< HEAD
    Weather *w=&G.weather;
    /* Mây: hiện thị mọi thời tiết */
    for(int i=0;i<8;i++){
        float a=(w->current==WEATHER_SUNNY)?60:
                (w->current==WEATHER_CLOUDY)?160:120;
        /* Đám mây có bóng */
        DrawEllipse((int)w->cloudX[i]+2,(int)w->cloudY[i]+2,72,24,(Color){0,0,0,(unsigned char)(a*0.3f)});
        DrawEllipse((int)w->cloudX[i],(int)w->cloudY[i],70,22,(Color){255,255,255,(unsigned char)a});
        /* Đám mây thứ 2 nhỏ hơn */
        DrawEllipse((int)w->cloudX[i]+24,(int)w->cloudY[i]-10,42,18,(Color){245,245,255,(unsigned char)(a*0.8f)});
    }

    if(w->current==WEATHER_CLOUDY){
        /* Phủ màn mờ nhạt */
        DrawRectangle(0,0,SCREEN_W,SCREEN_H,(Color){200,210,220,18});
    }

    if(w->current==WEATHER_RAINY){
        /* Phủ màn xanh mưa */
        DrawRectangle(0,0,SCREEN_W,SCREEN_H,(Color){40,60,120,35});
        /* Vẽ hạt mưa lớn hơn, rõ hơn */
        for(int i=0;i<40;i++){
            int rx=(int)w->rainDropX[i];
            int ry=(int)w->rainDropY[i];
            /* Đuôi mưa dài */
            DrawLine(rx,ry, rx-3,ry+18,(Color){160,200,255,200});
            DrawLine(rx,ry, rx-2,ry+12,(Color){200,230,255,140});
        }
        /* Bụi mưa ở mặt đất */
        for(int i=0;i<20;i++){
            int sx=((int)w->rainDropX[i*2%40])%SCREEN_W;
            DrawEllipse(sx,SCREEN_H-2,GetRandomValue(1,4),1,(Color){180,220,255,80});
        }
        /* Hiệu ứng sấm chớp ngẫu nhiên */
        if(GetRandomValue(0,600)==0){
            DrawRectangle(0,0,SCREEN_W,SCREEN_H,(Color){255,255,255,60});
        }
=======
    Weather *w = &G.weather;

    /* ══════════════════════════════════════════════════
       HIỆU ỨNG NẮNG (WEATHER_SUNNY)
       ══════════════════════════════════════════════════ */
    if (w->current == WEATHER_SUNNY) {
        /* Vignette vàng ấm góc trên - ánh sáng mặt trời */
        DrawRectangleGradientV(0, 0, SCREEN_W, 100,
            (Color){255, 220, 80, 22}, (Color){0, 0, 0, 0});
        DrawRectangleGradientH(SCREEN_W-150, 0, 150, SCREEN_H,
            (Color){0, 0, 0, 0}, (Color){255, 200, 50, 10});


        /* Mặt trời nhỏ góc trên phải (hiệu ứng glow) */
        DrawCircleGradient(SCREEN_W - 70, 80, 55,
            (Color){255, 240, 150, 0}, (Color){255, 220, 60, 0});
        DrawCircle(SCREEN_W - 70, 80, 28, (Color){255, 230, 80, 30});
        DrawCircle(SCREEN_W - 70, 80, 18, (Color){255, 240, 120, 55});
        DrawCircle(SCREEN_W - 70, 80, 10, (Color){255, 250, 180, 90});
    }

    /* ══════════════════════════════════════════════════
       MÂY (tất cả thời tiết, mật độ khác nhau)
       ══════════════════════════════════════════════════ */
    for (int i = 0; i < 8; i++) {
        float a = (w->current == WEATHER_SUNNY)  ? 55.0f :
                  (w->current == WEATHER_CLOUDY) ? 170.0f : 130.0f;
        int cx = (int)w->cloudX[i];
        int cy = (int)w->cloudY[i];

        /* Bóng mây */
        DrawEllipse(cx + 3, cy + 4, 72, 22, (Color){0, 0, 0, (unsigned char)(a * 0.28f)});
        /* Thân mây chính */
        DrawEllipse(cx,      cy,     70, 22, (Color){255, 255, 255, (unsigned char)a});
        /* Phần mây nổi trên */
        DrawEllipse(cx + 24, cy - 12, 44, 20, (Color){240, 245, 255, (unsigned char)(a * 0.82f)});
        DrawEllipse(cx - 16, cy - 6,  32, 16, (Color){250, 250, 255, (unsigned char)(a * 0.68f)});
        /* Mây trời nhiều mây: thêm khối phụ */
        if (w->current == WEATHER_CLOUDY || w->current == WEATHER_RAINY) {
            DrawEllipse(cx + 50, cy + 4, 28, 14, (Color){200, 205, 215, (unsigned char)(a * 0.6f)});
        }
    }

    /* ══════════════════════════════════════════════════
       NHIỀU MÂY (WEATHER_CLOUDY)
       ══════════════════════════════════════════════════ */
    if (w->current == WEATHER_CLOUDY) {
        /* Màn mờ xám nhẹ phủ toàn màn hình */
        DrawRectangle(0, 0, SCREEN_W, SCREEN_H, (Color){180, 190, 210, 20});
        /* Gradient tối nhẹ trên xuống */
        DrawRectangleGradientV(0, 0, SCREEN_W, SCREEN_H / 3,
            (Color){100, 110, 140, 28}, (Color){0, 0, 0, 0});
    }

    /* ══════════════════════════════════════════════════
       MƯA (WEATHER_RAINY)
       ══════════════════════════════════════════════════ */
    if (w->current == WEATHER_RAINY) {
        /* Màn xanh lam tối phủ map */
        DrawRectangle(0, 0, SCREEN_W, SCREEN_H, (Color){20, 45, 100, 38});
        DrawRectangleGradientV(0, 0, SCREEN_W, SCREEN_H,
            (Color){10, 30, 80, 28}, (Color){0, 0, 0, 0});

        /* Hạt mưa lớp xa (mờ, ngắn) */
        for (int i = 0; i < 40; i++) {
            int rx = (int)w->rainDropX[i];
            int ry = (int)w->rainDropY[i];
            DrawLine(rx + 4, ry,     rx + 2, ry + 10, (Color){140, 180, 255, 80});
        }
        /* Hạt mưa lớp gần (rõ, dài) */
        for (int i = 0; i < 40; i++) {
            int rx = (int)w->rainDropX[i];
            int ry = (int)w->rainDropY[i];
            DrawLine(rx,     ry,     rx - 3, ry + 22, (Color){170, 210, 255, 200});
            DrawLine(rx,     ry + 4, rx - 2, ry + 15, (Color){210, 235, 255, 120});
        }

        /* Splash mưa chạm đất */
        for (int i = 0; i < 20; i++) {
            int sx = ((int)w->rainDropX[i * 2 % 40]) % SCREEN_W;
            int splashR = GetRandomValue(1, 5);
            DrawEllipse(sx, SCREEN_H - 2, splashR, 1, (Color){180, 220, 255, 75});
        }

        /* Vũng nước lấp lánh ở cuối màn hình */
        DrawRectangleGradientV(0, SCREEN_H - 18, SCREEN_W, 18,
            (Color){0, 0, 0, 0}, (Color){80, 130, 200, 40});

        /* Sấm chớp ngẫu nhiên - flash toàn màn */
        static float lightningTimer = 0.0f;
        float dt = GetFrameTime();
        lightningTimer -= dt;
        if (lightningTimer <= 0.0f) {
            /* Flash sáng trắng */
            DrawRectangle(0, 0, SCREEN_W, SCREEN_H, (Color){240, 245, 255, 55});
            lightningTimer = 4.0f + (float)GetRandomValue(0, 60) * 0.1f;
        } else if (lightningTimer < 0.08f) {
            /* Giữ flash trong 80ms */
            DrawRectangle(0, 0, SCREEN_W, SCREEN_H, (Color){255, 255, 255, 45});
        }

        /* Tia sét thẳng đứng ngẫu nhiên */
        static int lightningX = -1;
        static float boltTimer = 0.0f;
        boltTimer -= dt;
        if (boltTimer <= 0.0f) {
            lightningX = GetRandomValue(80, SCREEN_W - 80);
            boltTimer  = 6.0f + (float)GetRandomValue(0, 80) * 0.1f;
        }
        if (boltTimer > boltTimer - 0.12f && lightningX > 0) {
            int lx = lightningX;
            /* Tia sét zigzag 3 đoạn */
            int y0=0, y1=SCREEN_H/3, y2=SCREEN_H*2/3, y3=(int)(SCREEN_H*0.75f);
            int ox1 = GetRandomValue(-20,20), ox2 = GetRandomValue(-20,20);
            DrawLineEx((Vector2){(float)lx,       (float)y0},
                       (Vector2){(float)(lx+ox1), (float)y1}, 2.5f,
                       (Color){255, 255, 180, 200});
            DrawLineEx((Vector2){(float)(lx+ox1), (float)y1},
                       (Vector2){(float)(lx+ox2), (float)y2}, 2.0f,
                       (Color){255, 255, 200, 170});
            DrawLineEx((Vector2){(float)(lx+ox2), (float)y2},
                       (Vector2){(float)(lx+ox2+GetRandomValue(-15,15)), (float)y3}, 1.5f,
                       (Color){200, 220, 255, 130});
            /* Glow xung quanh tia sét */
            DrawLineEx((Vector2){(float)lx,       (float)y0},
                       (Vector2){(float)(lx+ox1), (float)y1}, 8.0f,
                       (Color){180, 200, 255, 30});
        }

        /* Chữ "MƯA" mờ góc dưới */
        DrawTextEx(gameFont, "MƯA",
            (Vector2){(float)(SCREEN_W/2 - 24), (float)(SCREEN_H - 30)},
            16, 1, (Color){140, 190, 255, 90});
    }
}

/* ══════════════════════════════════════════════════════════════════
   DrawHUD_NightOverlay — màn đêm + sao + trăng
   Gọi SAU DrawHUD_Weather, TRƯỚC DrawTile_All để overlay phủ cả map
   ══════════════════════════════════════════════════════════════════ */
void DrawHUD_NightOverlay(void)
{
    float alpha = G.nightOverlay;
    if (alpha <= 0.01f) return;

    /* ── Màn đêm gradient ── */
    /* Lớp base: xanh tím tối */
    DrawRectangle(0, 0, SCREEN_W, SCREEN_H,
        (Color){8, 10, 35, (unsigned char)(alpha * 170)});
    /* Gradient nhẹ: tối hơn ở viền */
    DrawRectangleGradientV(0, 0, SCREEN_W, SCREEN_H,
        (Color){0, 0, 20, (unsigned char)(alpha * 40)},
        (Color){5, 8, 30, (unsigned char)(alpha * 80)});

    /* ── Sao: vẽ dựa trên seed cố định + alpha ── */
    if (alpha > 0.3f) {
        float starAlpha = (alpha - 0.3f) / 0.7f;  /* fade in từ 30% */
        /* 80 ngôi sao phân bố ngẫu nhiên cố định */
        static const int STAR_COUNT = 80;
        for (int i = 0; i < STAR_COUNT; i++) {
            /* Dùng hash cố định để vị trí sao không thay đổi mỗi frame */
            unsigned int hx = (unsigned int)(i * 2654435761u);
            unsigned int hy = (unsigned int)(i * 2246822519u);
            int sx = (int)(hx % (unsigned int)SCREEN_W);
            int sy = (int)(hy % (unsigned int)(SCREEN_H / 2));  /* chỉ nửa trên */
            /* Size sao: 1-3px tùy index */
            int ssize = 1 + (int)((i * 374761393u) % 3);
            /* Nhấp nháy nhẹ */
            float twinkle = 0.6f + 0.4f * sinf(G.gameTime * (1.0f + (i % 7) * 0.3f) + i);
            unsigned char sa = (unsigned char)(starAlpha * twinkle * 220);
            Color starCol = (i % 5 == 0) ? (Color){255, 220, 180, sa} :
                            (i % 3 == 0) ? (Color){200, 215, 255, sa} :
                                           (Color){255, 255, 255, sa};
            if (ssize == 1) DrawPixel(sx, sy, starCol);
            else            DrawCircle(sx, sy, (float)ssize * 0.5f, starCol);
            /* Ánh sáng glow cho sao sáng nhất */
            if (i % 15 == 0 && ssize >= 2) {
                DrawCircle(sx, sy, (float)ssize * 1.8f,
                    (Color){starCol.r, starCol.g, starCol.b, (unsigned char)(sa / 5)});
            }
        }
    }

    /* ── Mặt trăng ── */
    if (alpha > 0.5f) {
        float moonAlpha = (alpha - 0.5f) / 0.5f;
        /* Vị trí trăng: góc trên phải, đối xứng với mặt trời ban ngày */
        int mx = SCREEN_W - 110;
        int my = 90;
        float ma = moonAlpha;

        /* Glow ngoài cùng */
        DrawCircle(mx, my, 48, (Color){180, 200, 230, (unsigned char)(ma * 18)});
        DrawCircle(mx, my, 36, (Color){200, 215, 240, (unsigned char)(ma * 30)});
        /* Thân trăng */
        DrawCircle(mx, my, 24, (Color){230, 235, 255, (unsigned char)(ma * 220)});
        DrawCircle(mx, my, 22, (Color){210, 220, 245, (unsigned char)(ma * 200)});
        /* Hiệu ứng lưỡi liềm: che 1 phần bằng vòng tròn tối */
        DrawCircle(mx + 10, my - 4, 18, (Color){8, 10, 35, (unsigned char)(ma * 210)});
        /* Vết lõm trên bề mặt trăng */
        DrawCircle(mx - 6, my + 4,  4, (Color){180, 185, 210, (unsigned char)(ma * 90)});
        DrawCircle(mx - 10, my - 5, 3, (Color){190, 195, 220, (unsigned char)(ma * 70)});
        DrawCircle(mx + 2,  my + 9, 2, (Color){170, 180, 200, (unsigned char)(ma * 80)});
        /* Text "ĐÊM" nhỏ */
        DrawTextEx(gameFont, TextFormat("Đêm %d", G.day),
            (Vector2){(float)(mx - 20), (float)(my + 32)},
            12, 1, (Color){180, 200, 230, (unsigned char)(ma * 160)});
    }

    /* ── Vignette tối viền màn hình ban đêm ── */
    if (alpha > 0.4f) {
        float va = (alpha - 0.4f) / 0.6f;
        DrawRectangleGradientH(0, 0, 200, SCREEN_H,
            (Color){0, 0, 15, (unsigned char)(va * 80)}, (Color){0,0,0,0});
        DrawRectangleGradientH(SCREEN_W-200, 0, 200, SCREEN_H,
            (Color){0,0,0,0}, (Color){0, 0, 15, (unsigned char)(va * 80)});
        DrawRectangleGradientV(0, 0, SCREEN_W, 120,
            (Color){0, 0, 20, (unsigned char)(va * 60)}, (Color){0,0,0,0});
        DrawRectangleGradientV(0, SCREEN_H-120, SCREEN_W, 120,
            (Color){0,0,0,0}, (Color){0, 0, 20, (unsigned char)(va * 60)});
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
    }
}