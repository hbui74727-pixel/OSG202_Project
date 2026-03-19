#include "draw_animal.h"
#include "../font_manager.h"

static const char *animalName[]={"Gà","Lợn","Cừu"};

/* ─────────────────────────────────────────────────────────
   FENCE (CHUỒNG) từ animal.png — 160x160px
   Chuồng 5x5 tiles trong world

   Fence pieces (16x16 mỗi cái):
     Corners : TL=(32,16)  TR=(112,16)  BL=(32,80)  BR=(112,80)
     Top rail: TM=(48..96,16) — 4 mid pieces
     Bot rail: BM=(48..96,80) — 4 mid pieces
     Left rail: LT=(32,32) LM=(32,48) LB=(32,64)
     Right rail: RT=(112,32) RM=(112,48) RB=(112,64)
───────────────────────────────────────────────────────── */
static void DrawFencePiece(int sx, int sy, float dx, float dy, float dw, float dh, Color tint)
{
    if (T.animal_fence.width < 16) return;
    Rectangle src = {(float)sx, (float)sy, 16, 16};
    Rectangle dst = {dx, dy, dw, dh};
    DrawTexturePro(T.animal_fence, src, dst, (Vector2){0,0}, 0, tint);
}

/* Vẽ chuồng 5x5 tiles tại screen pos (sx,sy), kích thước (bw x bh) */
static void DrawBarnFence(float sx, float sy, float bw, float bh, Color tint)
{
    /* Mỗi tile fence = 1/5 chiều rộng/cao của chuồng */
    float tw = bw / 5.0f;  /* tile width trên màn hình */
    float th = bh / 5.0f;  /* tile height trên màn hình */

    /* Cặp mid pieces top rail (4 biến thể) */
    static const int topMidX[4] = {48, 64, 80, 96};
    static const int botMidX[4] = {48, 64, 80, 96};

    /* ── Hàng TOP (y=sy) ── */
    /* Corner trái */
    DrawFencePiece(32, 16, sx,             sy,      tw, th, tint);
    /* Mid pieces (3 tiles) */
    for (int i = 0; i < 3; i++)
        DrawFencePiece(topMidX[i], 16, sx+tw*(i+1), sy, tw, th, tint);
    /* Corner phải */
    DrawFencePiece(112, 16, sx+tw*4,       sy,      tw, th, tint);

    /* ── Hàng BOTTOM (y=sy+bh-th) ── */
    DrawFencePiece(32,  80, sx,            sy+th*4, tw, th, tint);
    for (int i = 0; i < 3; i++)
        DrawFencePiece(botMidX[i], 80, sx+tw*(i+1), sy+th*4, tw, th, tint);
    DrawFencePiece(112, 80, sx+tw*4,       sy+th*4, tw, th, tint);

    /* ── Cột LEFT (3 tiles dọc) ── */
    DrawFencePiece(32, 32, sx, sy+th,   tw, th, tint);
    DrawFencePiece(32, 48, sx, sy+th*2, tw, th, tint);
    DrawFencePiece(32, 64, sx, sy+th*3, tw, th, tint);

    /* ── Cột RIGHT (3 tiles dọc) ── */
    DrawFencePiece(112, 32, sx+tw*4, sy+th,   tw, th, tint);
    DrawFencePiece(112, 48, sx+tw*4, sy+th*2, tw, th, tint);
    DrawFencePiece(112, 64, sx+tw*4, sy+th*3, tw, th, tint);
}

/* ─────────────────────────────────────────────────────────
   DRAW BARNS
───────────────────────────────────────────────────────── */
void DrawAnimal_Barns(void)
{
    float z = G.camZoom;
    static const Color barnFloor[3] = {
        {220,195,150,255},   /* Gà  - đất vàng ấm */
        {205,175,130,255},   /* Lợn - đất nâu cam */
        {195,190,180,255}    /* Cừu - đất xám nhạt */
    };
    static const Color fenceTint[3] = {
        {255, 220, 160, 255},   /* Gà  - vàng ấm */
        {255, 200, 150, 255},   /* Lợn - cam */
        {225, 240, 220, 255}    /* Cừu - xanh lá nhạt */
    };
    static const char *animalIcon[3] = {"[Gà]", "[Lợn]", "[Cừu]"};

    for (int i = 0; i < G.barnCount; i++) {
        Barn *b = &G.barns[i];
        if (!b->active) continue;

        /* Tọa độ screen của góc trái-trên chuồng */
        Vector2 sp = WorldToScreen((Vector2){
            (float)(b->tileX * TILE_SIZE),
            (float)(b->tileY * TILE_SIZE)
        });
        float bw = 5.0f * TILE_SIZE * z;
        float bh = 5.0f * TILE_SIZE * z;

        /* 1. Nền sàn chuồng (bên trong fence) */
        /* nền chuồng dạng caro giống map */
int tiles = 4;

for (int ty = 0; ty < tiles; ty++)
for (int tx = 0; tx < tiles; tx++)
{
    float fx = sp.x + (tx + 0.5f) * TILE_SIZE * z;
float fy = sp.y + (ty + 0.5f) * TILE_SIZE * z;

    Color c = ((tx + ty) % 2 == 0) ?
        (Color){205,185,140,255} :
        (Color){220,200,155,255};

    DrawRectangle(
        (int)fx,
        (int)fy,
        (int)(TILE_SIZE*z +1),
        (int)(TILE_SIZE*z+1),
        c
    );
}

        /* 2. Hàng rào */
        if (T.animal_fence.width >= 16) {
            DrawBarnFence(sp.x, sp.y, bw, bh, fenceTint[b->type]);
        } else {
            /* Fallback */
            DrawRectangleLinesEx((Rectangle){sp.x,sp.y,bw,bh}, 3.0f*z, fenceTint[b->type]);
        }

        /* 3. Nhãn tên + số con */
        int hungryCount = 0, totalCount = 0;
        for (int j = 0; j < MAX_ANIMALS; j++) {
            if (G.animals[j].active && G.animals[j].barnIdx == i) {
                totalCount++;
                if (G.animals[j].hungry) hungryCount++;
            }
        }
        const char *lbl = TextFormat("%s %d/5", animalIcon[b->type], b->animalCount);
        int lw = MeasureText(lbl, (int)(9*z));
        DrawRectangle((int)(sp.x+bw/2-lw/2-4), (int)(sp.y+4),
                      lw+8, (int)(13*z), (Color){0,0,0,180});
        DrawTextCentered(lbl, (int)(sp.x+bw/2), (int)(sp.y+6), (int)(9*z), YELLOW);

        /* 4. Trạng thái đói / sản phẩm */
        if (totalCount > 0) {
            if (hungryCount > 0) {
                const char *fl = TextFormat("[6]Cho ăn: %d đói", hungryCount);
                float ty2 = sp.y + bh - 14*z;
                DrawRectangle((int)(sp.x+2),(int)ty2,(int)(bw-4),(int)(12*z),(Color){0,0,0,160});
                DrawTextCenteredShort(fl, (int)(sp.x+40), (int)(ty2+1), (int)(8*z), RED);
            } else {
                DrawTextCenteredShort("[RClick]Thu sản phẩm",(int)(sp.x+40),(int)(sp.y+bh-12*z),(int)(8*z),LIME);
            }
        }
    }
}

/* ─────────────────────────────────────────────────────────
   DRAW ANIMALS
───────────────────────────────────────────────────────── */
static void DrawProductBubble(Vector2 sp, float z)
{
    float bounce = sinf(G.gameTime * 5.0f) * 3.0f;
    float bx = sp.x + 18*z, by = sp.y - 30*z + bounce;
    DrawCircle((int)bx,(int)by,(int)(8*z),(Color){255,220,40,230});
    DrawTextCenteredShort("!", (int)(bx-3*z), (int)(by-6*z), (int)(12*z), DARKBROWN);
}

void DrawAnimal_All(void)
{
    float z = G.camZoom;
    for (int i = 0; i < MAX_ANIMALS; i++) {
        Animal *a = &G.animals[i];
        if (!a->active) continue;

        Texture2D tex = T.animal[a->type];
        if (tex.width == 0) {
            /* Fallback: hình tròn màu */
            static const Color fb[3]={{255,240,180,220},{255,200,160,220},{230,230,210,220}};
            Vector2 sp2 = WorldToScreen(a->pos);
            DrawCircle((int)sp2.x,(int)sp2.y,(int)(12*z), fb[a->type]);
            if (a->hungry) DrawTextCenteredShort("ĐÓI",(int)(sp2.x-10),(int)(sp2.y-16),(int)(8*z),RED);
            continue;
        }
        int frameW = tex.width;
        int frameH = tex.height;

        /* Tint: đói → đỏ nhạt, có sản phẩm → vàng nhạt, bình thường → trắng */
        Color tint = WHITE;
        if      (a->hungry)     tint = (Color){255,170,170,255};
        else if (a->hasProduct) tint = (Color){255,245,180,255};

        /* Scale nhỏ gọn */
        float scl = (a->type == ANIMAL_CHICKEN) ? 1.0f : 1.4f;
        float dw = (float)frameW * z * scl;
        float dh = (float)frameH * z * scl;

        /* Flip ngang nếu di chuyển sang trái */
        /* flip nếu đi sang trái */
        bool flipX = (a->moveVel.x < -1.0f);

        Rectangle src = {
            flipX ? (float)frameW : 0,
            0,
            flipX ? -(float)frameW : (float)frameW,
            (float)frameH
        };

        Vector2 sp = WorldToScreen(a->pos);

        Rectangle dst = {
            sp.x - dw * 0.5f,
            sp.y - dh * 0.9f,
            dw,
            dh
       // 
       
        };
        DrawTexturePro(tex, src, dst, (Vector2){0,0}, 0, tint);
        /* Bong bóng "ĐÓI" */
        if (a->hungry) {
            float bounce = sinf(G.gameTime*6.0f+i)*2.0f;
            DrawTextCenteredShort("ĐÓI!",(int)(sp.x-12*z),(int)(sp.y-dh-8+bounce),(int)(9*z),RED);
        }

        /* Bong bóng sản phẩm */
        if (a->hasProduct)
            DrawProductBubble(sp, z);
    }
}
