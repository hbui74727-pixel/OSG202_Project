#include "quest_system.h"

void Quest_Init(void)
{
<<<<<<< HEAD
    G.quests[0] = (Quest){"Thu hoach 5 cay",    5,  0, 50,  false, 0};
    G.quests[1] = (Quest){"Trong 10 hat giong", 10, 0, 40,  false, 1};
    G.quests[2] = (Quest){"Kiem 200 dong",      200,0, 100, false, 2};
    G.quests[3] = (Quest){"Danh bai 3 quai",    3,  0, 80,  false, 3};
    G.quests[4] = (Quest){"Thu 5 san pham",     5,  0, 60,  false, 4};
=======
    G.quests[0] = (Quest){"Thu hoạch 5 cây",    5,  0, 50,  false, 0};
    G.quests[1] = (Quest){"Trồng 10 hạt giống", 10, 0, 40,  false, 1};
    G.quests[2] = (Quest){"Kiếm 200 đồng",      200,0, 100, false, 2};
    G.quests[3] = (Quest){"Đánh bại 3 quái",    3,  0, 80,  false, 3};
    G.quests[4] = (Quest){"Thu thập 5 sản phẩm",     5,  0, 60,  false, 4};
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
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
<<<<<<< HEAD
                     "Hoan thanh: %s! +$%d", q->desc, q->reward);
=======
                     "Hoàn thành: %s! +$%d", q->desc, q->reward);
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
            G.msgTimer = 4.0f;
        }
    }
}
