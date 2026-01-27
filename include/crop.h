#ifndef CROP_H
#define CROP_H

#include <stdbool.h>
#include <time.h>

typedef enum{
    SEED = 0,
    SPROUT,
    YOUNG,
    MATURE,
    DEAD
} CropStage;

typedef struct{
    int id;
    CropStage stage;
    int health;
    int water_level;
    time_t planted_at;
    int grow_time;
    bool is_harvestable;
} Crop;

void init_crop(Crop *crop, int id);
int plant(Crop *crop);
int harvest(Crop *crop);

#endif