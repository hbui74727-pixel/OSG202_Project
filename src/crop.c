#include "crop.h"
#include <time.h>

void init_crop(Crop *crop, int id){
    crop->id = id;
    crop->stage = SEED;
    crop->health = 100;
    crop->water_level = 50;
    crop->planted_at = time(NULL);
    crop->grow_time = 30;
    crop->is_harvestable = false;
}

int plant(Crop *crop){
    if(crop->stage != SEED)
    return -1;

    crop->planted_at = time(NULL);
    crop->health = 100;
    crop->water_level = 50;
    crop->stage = SPROUT;
    crop->is_harvestable = false;
    return 0;
}

int harvest(Crop *crop){
    if(!crop->is_harvestable || crop->stage != MATURE)
    return -1;

    crop->stage = SEED;
    crop->health = 100;
    crop->water_level = 50;
    crop->is_harvestable = false;
    crop->planted_at = time(NULL);

    return 1;
}
