#include "draw_crop.h"

void DrawCrop_ReadyBadge(float sx, float sy, float z)
{
    float a=0.65f+sinf(G.gameTime*4.0f)*0.35f;
    float bounce=sinf(G.gameTime*3.0f)*4.0f;
    Color c={(unsigned char)255,(unsigned char)220,(unsigned char)0,(unsigned char)(a*255)};
    DrawTextCentered("CHÍN",(int)sx,(int)(sy+bounce),(int)(9.0f*z),c);
}

void DrawCrop_WateredDot(float sx, float sy, float z)
{
    DrawCircle((int)(sx+14*z),(int)(sy-12*z),(int)(3.5f*z),(Color){80,180,255,210});
}

void DrawCrop_All(void)
{
    float z=G.camZoom;
    for (int i=0;i<MAX_CROPS;i++) {
        Crop *c2=&G.crops[i];
        if (!c2->active) continue;

        float wx=(c2->tileX+0.5f)*(float)TILE_SIZE;
        float wy=(c2->tileY+0.5f)*(float)TILE_SIZE;
        Vector2 sp=WorldToScreen((Vector2){wx,wy});

        Texture2D tex=T.crop[c2->type];
        if (tex.width==0) continue;

        /* Strip 6 frames: 0=hat/mam, 1=mam nho, 2=nho, 3=vua, 4=lon, 5=chin */
        int fw=tex.width/6;
        if(fw<=0) fw=tex.width;

        int frame=0;
        switch(c2->stage){
            case CSTAGE_DUG:
                frame=0;
                break;
            case CSTAGE_WATERED:
                frame=1;  /* mam nho moi tuoi */
                break;
            case CSTAGE_GROWING: {
                /* 3 sub-stage dua vao growTimer:
                   0-33% -> frame 2 (nho)
                   33-66% -> frame 3 (vua)
                   66-100% -> frame 4 (lon, sap chin) */
                float ratio=c2->growTimer/GROW_SECS_STAGE;
                if(ratio<0.0f) ratio=0.0f;
                if(ratio>1.0f) ratio=1.0f;
                if      (ratio<0.33f) frame=2;
                else if (ratio<0.66f) frame=3;
                else                  frame=4;
                break;
            }
            case CSTAGE_READY:
                frame=5;  /* chin hoan toan */
                break;
        }

        /* Kich thuoc tang dan theo frame (cay lon dan nhin thay ro hon) */
        float sizeScale=1.0f + (float)frame*0.08f;
        float dw=(float)fw*sizeScale*z;
        float dh=(float)tex.height*sizeScale*z;

        Rectangle src={(float)(frame*fw),0,(float)fw,(float)tex.height};
        Rectangle dst={sp.x-dw*0.5f, sp.y-dh*0.88f, dw, dh};
        DrawTexturePro(tex,src,dst,(Vector2){0,0},0,WHITE);

        /* Cham xanh "da tuoi" */
        if (c2->stage==CSTAGE_WATERED||c2->stage==CSTAGE_GROWING)
            DrawCrop_WateredDot(sp.x,sp.y,z);

        /* READY badge */
        if (c2->stage==CSTAGE_READY)
            DrawCrop_ReadyBadge(sp.x,sp.y-dh,z);

        /* Thanh tien trinh khi dang lon */
        if (c2->stage==CSTAGE_GROWING) {
            float ratio=c2->growTimer/GROW_SECS_STAGE;
            float bw=30.0f*z, bx2=sp.x-bw*0.5f, by2=sp.y+4.0f*z;
            DrawRectangle((int)bx2,(int)by2,(int)bw,(int)(4.0f*z),DARKGRAY);
            /* Mau thanh thay doi theo sub-stage */
            Color progColor=(ratio<0.33f)?(Color){100,200,100,255}
                           :(ratio<0.66f)?(Color){200,200,50,255}
                                         :(Color){255,150,50,255};
            DrawRectangle((int)bx2,(int)by2,(int)(bw*ratio),(int)(4.0f*z),progColor);
            DrawRectangleLines((int)bx2,(int)by2,(int)bw,(int)(4.0f*z),(Color){60,60,60,200});
        }
    }
}
