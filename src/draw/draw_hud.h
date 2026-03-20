#ifndef DRAW_HUD_H
#define DRAW_HUD_H
#include "../types.h"
#include "../renderer.h"

void DrawHUD_TopBar(void);
void DrawHUD_DayProgress(void);
void DrawHUD_WeatherIcon(void);
void DrawHUD_Weather(void);
void DrawHUD_Message(void);
void DrawHUD_Minimap(void);
void DrawHUD_LevelUp(void);

/* Hotbar placement system */
void HotbarPlacement_Init(void);
void HotbarPlacement_HandleInput(void);
void DrawHUD_PlacementBar(void);
void DrawHUD_PlacementGhost(void);

void DrawHUD_EndGame(void);
void DrawHUD_NightOverlay(void);
#endif
