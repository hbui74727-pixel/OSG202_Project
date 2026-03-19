#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include "types.h"
#include "renderer.h"
#include "data_manager.h"

void GameLogic_Init(void);
void GameLogic_Update(float dt);
void GameLogic_UpdatePlayer(float dt);
void GameLogic_HandleInput(void);
void GameLogic_HandleTileClick(Vector2 worldPos);
void GameLogic_UpdateCamera(void);
void Player_UseTool(Vector2 worldPos);
#endif
