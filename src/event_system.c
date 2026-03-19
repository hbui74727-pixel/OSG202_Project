#include "event_system.h"
#include "quest_system.h"

#define EVT_QUEUE_SIZE 64

static GameEvent queue[EVT_QUEUE_SIZE];
static int       qHead = 0, qTail = 0;

void Event_Push(EventType type, int value)
{
    int next = (qTail + 1) % EVT_QUEUE_SIZE;
    if (next == qHead) return;  // queue đầy, bỏ qua
    queue[qTail] = (GameEvent){ type, value };
    qTail = next;
}

void Event_FlushAll(void)
{
    while (qHead != qTail) {
        GameEvent e = queue[qHead];
        qHead = (qHead + 1) % EVT_QUEUE_SIZE;

        switch (e.type) {
            case EVT_CROP_PLANTED:    Quest_Progress(1, e.value); break;
            case EVT_CROP_HARVESTED:  Quest_Progress(0, e.value); break;
            case EVT_ENEMY_KILLED:    Quest_Progress(3, e.value); break;
            case EVT_ITEM_SOLD:       Quest_Progress(2, e.value); break;
            case EVT_ANIMAL_COLLECTED:Quest_Progress(4, e.value); break;
            default: break;
        }
    }
}
