#include "water.h"

#define MAX_WATER 100
#define MIN_WATER 0

void water( Crop *crop, int amount){
    crop->water_level += amount;

    if(crop->water_level > MAX_WATER)
    crop->water_level = MAX_WATER;
    if(crop->water_level < MIN_WATER)
    crop->water_level = MIN_WATER;
}

void wither(Crop *crop){
    crop->health -= 20;

    if (crop->health <= 0){
        crop->health = 0;
        crop->stage = DEAD;
    }
}
