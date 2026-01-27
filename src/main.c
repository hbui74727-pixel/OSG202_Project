#include<stdio.h>
#include<unistd.h>
#include<time.h>

#include "crop.h"
#include "growth.h"
#include "water.h"

int main(){
    Crop crop;
    init_crop(&crop,1);
    plant(&crop);

    int i;
    for(i=0; i<15; i++){
       sleep(5);
       water(&crop,10);
       update_growth(&crop,time(NULL));
       
       printf("Stage= %d\nHealth= %d\nWater= %d\n",crop.stage,crop.health,crop.water_level);
    }

    if(harvest(&crop) > 0)
        printf("Harvest success!\n");

    return 0;
}