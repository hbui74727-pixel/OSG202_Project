#include "draw_player.h"
#include "../textures.h"
#include "../data_manager.h"
<<<<<<< HEAD
<<<<<<< HEAD

=======
#include "font_manager.h" 
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
#include "font_manager.h" 
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
// Tên tool ngắn để hiện trên đầu player
static const char *TOOL_LABEL[TOOL_COUNT] = {
    "[Đào]", "[Tưới]", "[Liềm]", "[Kiếm]"
};
static const Color TOOL_COLOR[TOOL_COUNT] = {
    {180,120,60,255}, {80,180,255,255}, {200,200,60,255}, {220,60,60,255}
};

void DrawPlayer_Character(void)
{
    Player *p = &G.player;
    Color tint = (p->hurtTimer > 0.0f) ? (Color){255,80,80,255} : WHITE;
    bool flipX = false;

    Texture2D tex = T.pIdle;

    if (p->isActing) {
        tex = (p->animState == ANIM_DIG) ? T.pDig : T.pWater;
    } else {
        switch (p->animState) {
            case ANIM_WALK:
                tex    = T.pWalk[p->dir];
                flipX  = (p->dir == DIR_LEFT);
                break;
            case ANIM_RUN:
                tex   = T.pRun[p->dir];
                flipX = (p->dir == DIR_LEFT);
                break;
            case ANIM_HURT:
                tex = T.pHurt;
                break;
            default:
                tex = T.pIdle;
                break;
        }
    }

    DrawSprite(tex, p->animFrame, PLAYER_FRAME_W, PLAYER_FRAME_H,
               p->pos.x, p->pos.y, 1.4f, tint, flipX);

    // ── HP bar ────────────────────────────────────────────
    Vector2 sp  = WorldToScreen(p->pos);
    float   z   = G.camZoom;
    float   barW = 44.0f * z, barH = 5.0f * z;
    float   bx  = sp.x - barW * 0.5f;
    float   by  = sp.y - 44.0f * z;

    DrawRectangle((int)bx, (int)by, (int)barW, (int)barH, DARKGRAY);
    float ratio = (float)p->hp / (float)p->maxHp;
    Color hcol  = ratio > 0.5f ? GREEN : (ratio > 0.25f ? YELLOW : RED);
    DrawRectangle((int)bx, (int)by, (int)(barW * ratio), (int)barH, hcol);

    // ── Tool label ───────────────────────────────────────
<<<<<<< HEAD
<<<<<<< HEAD
    DrawText(TOOL_LABEL[p->tool],
=======
    DrawTextShort(TOOL_LABEL[p->tool],
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
    DrawTextShort(TOOL_LABEL[p->tool],
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
             (int)(sp.x - 20), (int)(by - 14.0f * z),
             (int)(10.0f * z), TOOL_COLOR[p->tool]);

    // ── ADMIN badge ──────────────────────────────────────
    if (p->role == ROLE_ADMIN) {
<<<<<<< HEAD
<<<<<<< HEAD
        DrawText("ADMIN", (int)(sp.x - 18), (int)(by - 26.0f * z),
                 (int)(9.0f * z), (Color){255,80,80,255});
    } else if (p->role == ROLE_TESTER) {
        DrawText("TESTER", (int)(sp.x - 20), (int)(by - 26.0f * z),
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        DrawTextShort("ADMIN", (int)(sp.x - 18), (int)(by - 26.0f * z),
                 (int)(9.0f * z), (Color){255,80,80,255});
    } else if (p->role == ROLE_TESTER) {
        DrawTextShort("TESTER", (int)(sp.x - 20), (int)(by - 26.0f * z),
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
                 (int)(9.0f * z), ORANGE);
    }

    // ── Click target marker ──────────────────────────
    if (p->hasClickTarget) {
        Vector2 tsp = WorldToScreen(p->clickTarget);
        float r2 = 10.0f * G.camZoom;
        float pulse = 0.5f + sinf(G.gameTime * 8.0f) * 0.5f;
        DrawCircle((int)tsp.x,(int)tsp.y,(int)(r2*pulse),
                   (Color){255,220,50,(unsigned char)(180*pulse)});
        DrawCircle((int)tsp.x,(int)tsp.y,(int)(3*G.camZoom),(Color){255,255,100,220});
    }
}

void DrawPlayer_Hotbar(void)
{
    Player *p = &G.player;
    int slotSize = 44;
    int padding  = 4;
    int totalW   = HOTBAR_SIZE * (slotSize + padding) - padding;
    int startX   = SCREEN_W / 2 - totalW / 2;
    int startY   = SCREEN_H - slotSize - 10;

    for (int i = 0; i < HOTBAR_SIZE; i++) {
        int sx = startX + i * (slotSize + padding);
        int sy = startY;

        bool selected = (i == p->hotbarIdx);
        Color bg  = selected ? (Color){200,170,60,220} : (Color){30,30,30,190};
        Color bdr = selected ? GOLD : (Color){80,80,80,200};

        DrawRectangle(sx, sy, slotSize, slotSize, bg);
        DrawRectangleLines(sx, sy, slotSize, slotSize, bdr);

        InvSlot *slot = &p->inv[i];
        if (slot->type == ITEM_NONE || slot->quantity == 0) continue;

        // Nếu là seed → vẽ crop stage 0
        if (slot->type >= ITEM_SEED_CARROT && slot->type <= ITEM_SEED_WHEAT) {
            int ct = slot->type - ITEM_SEED_CARROT;
            Texture2D ct2 = T.crop[ct];
            if (ct2.width > 0) {
                Rectangle src = {0, 0, 32, 32};
                DrawTexturePro(ct2, src,
                    (Rectangle){(float)(sx+4), (float)(sy+4), (float)(slotSize-8), (float)(slotSize-8)},
                    (Vector2){0,0}, 0, WHITE);
            }
        }
        // Nếu là harvest → vẽ crop stage cuối
        else if (slot->type >= ITEM_CARROT && slot->type <= ITEM_WHEAT) {
            int ct = slot->type - ITEM_CARROT;
            Texture2D ct2 = T.crop[ct];
            if (ct2.width > 0) {
                int lastStage = 5;
                Rectangle src = {(float)(lastStage * 32), 0, 32, 32};
                DrawTexturePro(ct2, src,
                    (Rectangle){(float)(sx+4), (float)(sy+4), (float)(slotSize-8), (float)(slotSize-8)},
                    (Vector2){0,0}, 0, WHITE);
            }
        }
        // Item đặc biệt: vẽ icon nhỏ
        else {
            Texture2D icon = {0};
            switch (slot->type) {
                case ITEM_EGG:  icon = T.iEgg;  break;
                case ITEM_MILK: icon = T.iMilk; break;
                case ITEM_WOOD: icon = T.iWood; break;
                case ITEM_ROCK: icon = T.iRock; break;
<<<<<<< HEAD
<<<<<<< HEAD
=======
                case ITEM_FEED: icon = T.iFeed; break;
                case ITEM_FISH: icon = T.iFeed; break;
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
                case ITEM_FEED: icon = T.iFeed; break;
                case ITEM_FISH: icon = T.iFeed; break;
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
                default: break;
            }
            if (icon.width > 0) {
                Rectangle src = {0,0,(float)icon.width,(float)icon.height};
                DrawTexturePro(icon, src,
                    (Rectangle){(float)(sx+4),(float)(sy+4),(float)(slotSize-8),(float)(slotSize-8)},
                    (Vector2){0,0}, 0, WHITE);
<<<<<<< HEAD
<<<<<<< HEAD
            } else {
                // Fallback: chữ cái đầu
                const char *nm = GetItemName(slot->type);
                DrawText(TextFormat("%c", nm[0]),
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
            } else if (slot->type == ITEM_WOOL) {
                int _cx = sx+slotSize/2, _cy = sy+slotSize/2, _r = slotSize/8;
                DrawCircle(_cx-_r, _cy,   _r+1, (Color){240,240,255,255});
                DrawCircle(_cx+_r, _cy,   _r+1, (Color){240,240,255,255});
                DrawCircle(_cx,    _cy-_r,_r+1, (Color){255,255,255,255});
                DrawCircle(_cx,    _cy+_r,_r,   (Color){240,240,255,255});
            } else if (slot->type == ITEM_GEM) {
                int _cx = sx+slotSize/2, _cy = sy+slotSize/2, _r = slotSize/4;
                DrawCircle(_cx, _cy, (float)_r,      (Color){200,30,30,255});
                DrawCircleLines(_cx, _cy, (float)_r, (Color){255,120,120,255});
                DrawCircle(_cx-_r/3, _cy-_r/3, _r/4,(Color){255,180,180,200});
            } else {
                // Fallback: chữ cái đầu
                const char *nm = GetItemName(slot->type);
                DrawTextShort(TextFormat("%c", nm[0]),
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
                         sx + slotSize/2 - 6, sy + slotSize/2 - 8, 18, WHITE);
            }
        }

        // Số lượng
        if (slot->quantity > 1)
<<<<<<< HEAD
<<<<<<< HEAD
            DrawText(TextFormat("%d", slot->quantity),
=======
            DrawTextShort(TextFormat("%d", slot->quantity),
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
            DrawTextShort(TextFormat("%d", slot->quantity),
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
                     sx + slotSize - 16, sy + slotSize - 14, 12, WHITE);
    }

    // Hint phím 1-8
    for (int i = 0; i < HOTBAR_SIZE; i++) {
        int sx = startX + i * (slotSize + padding);
<<<<<<< HEAD
<<<<<<< HEAD
        DrawText(TextFormat("%d", i + 1), sx + 3, startY + 3, 9, (Color){200,200,200,160});
=======
        DrawTextShort(TextFormat("%d", i + 1), sx + 3, startY + 3, 9, (Color){200,200,200,160});
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
        DrawTextShort(TextFormat("%d", i + 1), sx + 3, startY + 3, 9, (Color){200,200,200,160});
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    }
}
