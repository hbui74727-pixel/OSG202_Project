#include "growth.h"
#include "water.h"

void update_growth(Crop *crop, time_t current_time){
    if(crop->stage == DEAD)
    return;
 int elapsed = (int)difftime(current_time, crop->planted_at);

 if(elapsed >= crop->grow_time){
    crop->stage = MATURE;
    crop->is_harvestable = true;
 }
 else if (elapsed >= crop->grow_time * 0.6){
    crop->stage = YOUNG;
 }
 else if (elapsed >= crop->grow_time * 0.3){
    crop->stage = SPROUT;
 }
}