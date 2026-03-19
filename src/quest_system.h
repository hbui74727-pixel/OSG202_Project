#ifndef QUEST_SYSTEM_H
#define QUEST_SYSTEM_H

#include "types.h"

void Quest_Init(void);
// type: 0=harvest 1=plant 2=earn 3=kill 4=collect
void Quest_Progress(int type, int amount);

#endif
