#include "access_control.h"

bool Access_CanEditMap(void)    { return G.player.role >= ROLE_TESTER; }
bool Access_CanSpawnItem(void)  { return G.player.role == ROLE_ADMIN; }
bool Access_CanFastForward(void){ return G.player.role >= ROLE_TESTER; }
