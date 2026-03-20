#include "quest_system.h"

void Quest_Init(void)
{
    G.quests[0] = (Quest){"Thu hoạch 5 cây",    5,  0, 50,  false, 0};
    G.quests[1] = (Quest){"Trồng 10 hạt giống", 10, 0, 40,  false, 1};
    G.quests[2] = (Quest){"Kiếm 200 đồng",      200,0, 100, false, 2};
    G.quests[3] = (Quest){"Đánh bại 3 quái",    3,  0, 80,  false, 3};
    G.quests[4] = (Quest){"Thu thập 5 sản phẩm",     5,  0, 60,  false, 4};
}

void Quest_Progress(int type, int amount)
{
    for (int i = 0; i < MAX_QUESTS; i++) {
        Quest *q = &G.quests[i];
        if (q->done || q->qtype != type) continue;

        q->progress += amount;
        if (q->progress >= q->target) {
            q->progress = q->target;
            q->done     = true;
            G.player.money += q->reward;
            snprintf(G.message, sizeof(G.message),
                     "Hoàn thành: %s! +$%d", q->desc, q->reward);
            G.msgTimer = 4.0f;
        }
    }
}
