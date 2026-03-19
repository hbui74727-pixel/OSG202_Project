#include "tree_system.h"
#include "types.h"
#include "raylib.h"
#include "game_logic.h"
Tree trees[MAX_TREES];
int treeCount = 0;

void Tree_Init()
{
    treeCount = 0;
}

void Tree_Generate()
{
    for(int r=2;r<MAP_ROWS-2;r++)
    for(int c=2;c<MAP_COLS-2;c++)
    {
        if(G.map[r][c].type != TILE_GRASS) continue;

        // if(TileRand(c,r,99,100) < 6)
        // {
        //     Tree *t = &trees[treeCount++];
        //     t->tileX = c;
        //     t->tileY = r;
        //     t->hp = 3;
        //     t->alive = true;
        // }
    }
}

void Tree_Hit(int tx,int ty)
{
    for(int i=0;i<treeCount;i++)
    {
        Tree *t=&trees[i];
        if(!t->alive) continue;

        if(t->tileX==tx && t->tileY==ty)
        {
            t->hp--;

            if(t->hp<=0)
            {
                t->alive=false;
               // AddItem(ITEM_WOOD,3);
            }
        }
    }
}
//player_action
void Player_UseTool(Vector2 worldPos)
{
    int tx = WorldToTileX(worldPos.x);
    int ty = WorldToTileY(worldPos.y);

    if(G.player.tool == TOOL_AXE)
    {
        Tree_Hit(tx,ty);
    }
}
