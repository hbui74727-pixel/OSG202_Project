#include "achievement_system.h"

Achievement achievements[MAX_ACHIEVEMENTS];
int achTotalHarvested = 0;
int achTotalKills     = 0;
int achTotalPlanted   = 0;
int achTotalCollected = 0;
<<<<<<< HEAD
<<<<<<< HEAD
=======
int achTotalEarned    = 0;  /* BUG FIX #8: Tong tien da kiem (khong giam khi tieu) */
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
int achTotalEarned    = 0;  /* BUG FIX #8: Tong tien da kiem (khong giam khi tieu) */
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23

void Achievement_Init(void)
{
    /* checkType: 0=harvest 1=money 2=day 3=kill 4=plant 5=level 6=barn 7=collect */
<<<<<<< HEAD
<<<<<<< HEAD
    achievements[ 0]=(Achievement){"Nong Dan Moi",    "Thu hoach cay dau tien",        "*",  false,0,1,  0};
    achievements[ 1]=(Achievement){"Nha Nong Gioi",   "Thu hoach 20 cay",              "**", false,0,20, 0};
    achievements[ 2]=(Achievement){"Trang Trai Lon",  "Thu hoach 100 cay",             "***",false,0,100,0};
    achievements[ 3]=(Achievement){"Trong Cay Dau",   "Trong cay dau tien",            "~",  false,4,1,  0};
    achievements[ 4]=(Achievement){"Nguoi Lam Vuon",  "Trong 50 cay",                  "~~", false,4,50, 0};
    achievements[ 5]=(Achievement){"Ty Phu Moi",      "Tich luy 1000 dong",            "$",  false,1,1000,0};
    achievements[ 6]=(Achievement){"Dai Gia",         "Tich luy 5000 dong",            "$$", false,1,5000,0};
    achievements[ 7]=(Achievement){"Chien Binh",      "Danh bai 5 quai vat",           "!",  false,3,5,  0};
    achievements[ 8]=(Achievement){"Anh Hung",        "Danh bai 30 quai vat",          "!!", false,3,30, 0};
    achievements[ 9]=(Achievement){"Song Sot Ngay 5", "Qua duoc ngay thu 5",           "D5", false,2,5,  0};
    achievements[10]=(Achievement){"Vet Chien",       "Qua duoc ngay thu 15",          "D15",false,2,15, 0};
    achievements[11]=(Achievement){"Cap 5",           "Dat cap do 5",                  "L5", false,5,5,  0};
    achievements[12]=(Achievement){"Cap 10",          "Dat cap do 10",                 "L10",false,5,10, 0};
    achievements[13]=(Achievement){"Chu Chuong",      "Xay duoc chuong dau tien",      "[_]",false,6,1,  0};
    achievements[14]=(Achievement){"Thu Hoach Vien",  "Thu san pham dong vat 10 lan",  "o",  false,7,10, 0};
    achievements[15]=(Achievement){"Huyen Thoai",     "Dat cap 20 va giet 50 quai",    "MAX",false,5,20, 0};
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    achievements[ 0]=(Achievement){"Nông Dân Mới",    "Thu hoạch cây đầu tiên",        "*",  false,0,1,  0};
    achievements[ 1]=(Achievement){"Nhà Nông Giỏi",   "Thu hoạch 20 cây",              "**", false,0,20, 0};
    achievements[ 2]=(Achievement){"Trang Trại Lớn",  "Thu hoạch 100 cây",             "***",false,0,100,0};
    achievements[ 3]=(Achievement){"Trồng Cây Đầu",   "Trồng cây đầu tiên",            "~",  false,4,1,  0};
    achievements[ 4]=(Achievement){"Người Làm Vườn",  "Trồng 50 cây",                  "~~", false,4,50, 0};
    achievements[ 5]=(Achievement){"Tỷ Phú Mới",      "Kiếm 1000 đồng",            "$",  false,1,1000,0};
    achievements[ 6]=(Achievement){"Đại Gia",         "Kiếm 5000 đồng",            "$$", false,1,5000,0};
    achievements[ 7]=(Achievement){"Chiến Binh",      "Đánh bại 5 quái vật",           "!",  false,3,5,  0};
    achievements[ 8]=(Achievement){"Anh Hùng",        "Đánh bại 30 quái vật",          "!!", false,3,30, 0};
    achievements[ 9]=(Achievement){"Sống Sót Ngày 5", "Qua dược ngày thứ 5",           "D5", false,2,5,  0};
    achievements[10]=(Achievement){"Chiến Binh",       "Qua dược ngày thứ 15",          "D15",false,2,15, 0};
    achievements[11]=(Achievement){"Cấp 5",           "Đạt cấp độ 5",                  "L5", false,5,5,  0};
    achievements[12]=(Achievement){"Cấp 10",          "Đạt cấp độ 10",                 "L10",false,5,10, 0};
    achievements[13]=(Achievement){"Chủ chuồng",      "Xây được chuồng đầu tiên",      "[_]",false,6,1,  0};
    achievements[14]=(Achievement){"Thu Hoạch Viên",  "Thu sản phẩm động vật 10 lần",  "o",  false,7,10, 0};
    achievements[15]=(Achievement){"Huyền Thoại",     "Đạt cấp độ 20 và giết 50 quái vật",    "MAX",false,5,20, 0};
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
}

static void TryUnlock(int i)
{
    Achievement *a = &achievements[i];
    if (a->unlocked) return;
    bool ok = false;
    switch (a->checkType) {
        case 0: a->progress=achTotalHarvested; ok=(achTotalHarvested>=a->threshold); break;
<<<<<<< HEAD
<<<<<<< HEAD
        case 1: a->progress=G.player.money;    ok=(G.player.money>=a->threshold);    break;
=======
        case 1: a->progress=achTotalEarned; ok=(achTotalEarned>=a->threshold); break; /* BUG FIX #8 */
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
        case 1: a->progress=achTotalEarned; ok=(achTotalEarned>=a->threshold); break; /* BUG FIX #8 */
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        case 2: a->progress=G.day;             ok=(G.day>=a->threshold);             break;
        case 3: a->progress=achTotalKills;     ok=(achTotalKills>=a->threshold);     break;
        case 4: a->progress=achTotalPlanted;   ok=(achTotalPlanted>=a->threshold);   break;
        case 5: a->progress=G.player.lvl.level;ok=(G.player.lvl.level>=a->threshold);break;
        case 6: a->progress=G.barnCount;       ok=(G.barnCount>=a->threshold);       break;
        case 7: a->progress=achTotalCollected; ok=(achTotalCollected>=a->threshold); break;
    }
    if (ok) {
        a->unlocked = true;
<<<<<<< HEAD
<<<<<<< HEAD
        snprintf(G.message,sizeof(G.message),"[Thanh Tuu] %s!",a->name);
=======
        snprintf(G.message,sizeof(G.message),"[Thành Tựu] %s!",a->name);
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
        snprintf(G.message,sizeof(G.message),"[Thành Tựu] %s!",a->name);
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        G.msgTimer = 4.0f;
    }
}

void Achievement_Check(void)
{
    for (int i=0;i<MAX_ACHIEVEMENTS;i++) TryUnlock(i);
}

void Achievement_AddHarvest(int n)  { achTotalHarvested+=n; Achievement_Check(); }
void Achievement_AddKill(int n)     { achTotalKills+=n;     Achievement_Check(); }
void Achievement_AddPlant(int n)    { achTotalPlanted+=n;   Achievement_Check(); }
void Achievement_AddCollect(int n)  { achTotalCollected+=n; Achievement_Check(); }
