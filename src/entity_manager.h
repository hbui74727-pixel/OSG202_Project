#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "types.h"
#include "renderer.h"

void EntityManager_InitMap(void);
void EntityManager_InitAnimals(void);
void EntityManager_SpawnEnemy(void);

void EntityManager_UpdateCrops(float dt);
void EntityManager_UpdateAnimals(float dt);
void EntityManager_UpdateEnemies(float dt);
void EntityManager_UpdateWeather(float dt);

void EntityManager_DrawEnemies(void);

/* Land / Barn management */
bool Land_BuyPlot(int tileX, int tileY);
bool Barn_Build(AnimalType type, int tileX, int tileY);
bool Barn_BuyAnimal(int barnIdx);

/* Delete / Move */
bool Barn_Delete(int tileX, int tileY);
bool Plot_Delete(int tileX, int tileY);
bool Barn_StartMove(int tileX, int tileY);
bool Plot_StartMove(int tileX, int tileY);
bool Object_PlaceAtTile(int tileX, int tileY);
void Object_CancelMove(void);

/* Cây: nhận diện + chặt */
bool Tile_IsTree(int tileX, int tileY);
bool Tree_Click(int tileX, int tileY);
void Tree_UpdateTimers(float dt);

<<<<<<< HEAD
<<<<<<< HEAD
#endif
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
/* Boss */
void SpawnBoss(void);
void SpawnSkeleton_Pub(void);

bool Entity_ResetFirstSpawn(void); /* BUG FIX #5 */
void UpdateBarnDmgTimers(float dt);
#endif
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
