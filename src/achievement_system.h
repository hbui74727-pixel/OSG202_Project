#ifndef ACHIEVEMENT_SYSTEM_H
#define ACHIEVEMENT_SYSTEM_H
#include "types.h"

#define MAX_ACHIEVEMENTS 16

typedef struct {
    char  name[48];
    char  desc[80];
    char  icon[4];     /* emoji-like text icon */
    bool  unlocked;
    int   checkType;   /* 0=harvest 1=money 2=day 3=kill 4=plant 5=level 6=barn 7=collect */
    int   threshold;
    int   progress;    /* tiến độ hiện tại để hiện trong UI */
} Achievement;

extern Achievement achievements[MAX_ACHIEVEMENTS];
extern int achTotalHarvested;
extern int achTotalKills;
extern int achTotalPlanted;
extern int achTotalCollected;
<<<<<<< HEAD
<<<<<<< HEAD
=======
extern int achTotalEarned; /* BUG FIX #8 */
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
extern int achTotalEarned; /* BUG FIX #8 */
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23

void Achievement_Init(void);
void Achievement_Check(void);
void Achievement_AddHarvest(int n);
void Achievement_AddKill(int n);
void Achievement_AddPlant(int n);
void Achievement_AddCollect(int n);
#endif
