#ifndef TREE_SYSTEM_H
#define TREE_SYSTEM_H
<<<<<<< HEAD
<<<<<<< HEAD
=======
#include <stdbool.h>
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
#include <stdbool.h>
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23

#define MAX_TREES 1024

typedef struct
{
    int tileX;
    int tileY;
    int hp;
    bool alive;
} Tree;

extern Tree trees[MAX_TREES];
extern int treeCount;

void Tree_Init();
void Tree_Generate();
void Tree_Draw();
void Tree_Hit(int tx,int ty);

#endif