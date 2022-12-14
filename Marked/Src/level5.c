//---------------------------------------------------------
// file:	level5.c
// author:	[CHEONG YU QING]
// email:	[c.yuqing@digipen.edu]
//
// brief:	LEVEL 5 introduces player to the mechanic that
// enemies can be "thrown" over platforms due to their velocity
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright ? 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "cprocessing.h"
#include "game.h"
#include "scenes.h"
#include "player.h"
#include "enemy.h"
#include "render.h"
#include "gameelements.h"

void Level5Init() {
	CP_System_SetFrameRate(60);
	currentLevel = Level5;
	nextLevel = Level6;
	goPtr = InitGoPtr();

	InitEndPoint(20.f, (float)windowHeight * 0.8f- 10.f);
	InitPlayer(700,800);
	InitPlayerProjectile();
	
	CreateEnemy(300.f, (float)windowHeight * 0.3f);

	//              pos         size            vel
	CreateLaser(1540.f, 0.f, 10, (float)windowHeight * 0.9f, 0, 0, 0);

	// horizontal door 1 button 1 
	CreateButtonDoorLink(CP_Vector_Set(200.f, (float)windowHeight * 0.89f), CP_Vector_Set(1550, (float)windowHeight * 0.9f), 2);

	// door 2 button 2
	CreateButtonDoorLink(CP_Vector_Set(1568.f, (float)windowHeight * 0.89f), CP_Vector_Set(568, (float)windowHeight * 0.8f), 1);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(566.f, (float)windowHeight * 0.57f), CP_Vector_Set(54, (float)windowHeight * 0.23f), PLATFORM_COLOR);

	// Platforms
	//BEHIND START 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(-1001.f, 0.f), CP_Vector_Set(1000.f, (float)windowHeight), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, (float)windowHeight * 0.9f), CP_Vector_Set(1550, 100), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, 0.f), CP_Vector_Set(620, 100), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, (float)windowHeight * 0.47f), CP_Vector_Set(620, 90), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(900.f, (float)windowHeight * 0.77f), CP_Vector_Set(100.f, (float)windowHeight * 0.13f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1000.f, (float)windowHeight * 0.67f), CP_Vector_Set(100.f, (float)windowHeight * 0.23f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1100.f, (float)windowHeight * 0.57f), CP_Vector_Set(100.f, (float)windowHeight * 0.33f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1200.f, (float)windowHeight * 0.47f), CP_Vector_Set(100.f, (float)windowHeight * 0.43f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1300.f, (float)windowHeight * 0.37f), CP_Vector_Set(175.f, (float)windowHeight * 0.53f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1375.f, (float)windowHeight * 0.315f), CP_Vector_Set(100.f, 50.f), PLATFORM_COLOR);
	CreateLaser(1476.f, (float)windowHeight * 0.315f, 174, 10, 0, 0, 0);

	// AFTER END 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1651.f, 0.f), CP_Vector_Set(1100, (float)windowHeight), PLATFORM_COLOR);

	CP_System_SetWindowSize(windowWidth, windowHeight);
}

void Level5Update() {
	if (isGameOver == FALSE) {
		CP_Graphics_ClearBackground(CP_Color_Create(240, 200, 200, 255));
		ManageCollision();

		for (int i = 0; i < GOARRAY_SIZE; ++i) {
			if ((goPtr + i)->isActive) {
				if ((goPtr + i)->type == Type_Enemy) {
					UpdateEnemy(goPtr + i);
					if ((goPtr + i)->pos.y > windowHeight) {
						DespawnGameObject(goPtr + i);
						endPoint->enemyCount--;
					}
				}
				else if ((goPtr + i)->type == Type_EndPoint) {
					UpdateEndPoint(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Proj && projectile->projAlive) {
					UpdateProjectile(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_EnemyProj) {
					UpdateEnemyProj(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Door) {
					UpdateDoor(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Dummy) {
					UpdateDummy(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Laser) {
					UpdateLaser(goPtr + i);
				}
			}
		}

		RenderScene();

		player->goPlayer->pos.y += player->vel.y * CP_System_GetDt();
		player->goPlayer->pos.x += player->vel.x * CP_System_GetDt();

		if (player->goPlayer->pos.y < windowHeight + 2 * player->goPlayer->size.y) {
			player->vel.y += gravity * CP_System_GetDt();
		}
		else {
			isGameOver = TRUE;
		}

		PlayerMovement();
		KeysPressed();

		if (CP_Input_KeyTriggered(KEY_X)) {
			if (player->markedObject != NULL && player->markedObject->pos.x > 0 && player->markedObject->pos.x < windowWidth) {
				SwapPositions();

				player->markedObject = NULL;
			}
			else
				shootPressed = TRUE;
		}
		if (CP_Input_KeyReleased(KEY_X)) {
			shootPressed = FALSE;
		}

	}
	else {
		DisplayGameOver();
	}

	QuitPressed();
	RestartPressed();
}

void Level5Exit() {
	FreeGoPtr(goPtr);
	free(goPtr);
}