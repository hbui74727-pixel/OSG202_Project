#ifndef DRAW_LOGIN_H
#define DRAW_LOGIN_H

#include "raylib.h"
#include <stdbool.h>

void DrawLogin_Init();
void DrawLogin_Update();
void DrawLogin_Render();
void DrawLogin_Unload();

bool Login_IsDone();
const char* Login_GetUsername();

#endif