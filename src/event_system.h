#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include "types.h"

typedef enum {
    EVT_CROP_PLANTED = 0,
    EVT_CROP_HARVESTED,
    EVT_ENEMY_KILLED,
    EVT_ITEM_SOLD,
    EVT_ITEM_BOUGHT,
    EVT_ANIMAL_COLLECTED,
    EVT_NEW_DAY,
    EVT_PLAYER_HURT,
    EVT_COUNT
} EventType;

typedef struct {
    EventType type;
    int       value;   // e.g. số tiền kiếm được, số lượng, ...
} GameEvent;

void Event_Push(EventType type, int value);
void Event_FlushAll(void);   // gọi mỗi frame, xử lý queue

#endif
