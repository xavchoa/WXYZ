//---------------------------------------------------------
// file:	level9.c
// author:	[TAN ZHI XIN, DARIEN]
// email:	[t.zhixindarien@digipen.edu]
//
// brief:	LEVEL 9 challenges the player's reaction time,
// and problem solving skills, stacking of dummies are required
// and certain techniques from previous levels.
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <stdlib.h>
#include "cprocessing.h"
#include "game.h"
#include "scenes.h"
#include "player.h"
#include "enemy.h"
#include "render.h"
#include "gameelements.h"

void Level9Init() {
	CP_System_SetFrameRate(60);
	currentLevel = Level9;
	nextLevel = Cutscene10;
	goPtr = InitGoPtr();

	InitEndPoint(1100, (float)windowHeight * 0.21f);
	InitPlayer(800.f, 700.f);
	InitPlayerProjectile();
	// enemies
	CreateEnemy(400.f, (float)windowHeight * 0.7f);
	CreateEnemy(1550.f, (float)windowHeight * 0.7f);
	CreateEnemy(1750.f, (float)windowHeight * 0.7f);
	// 4 dummies (1st half)
	CreateDummy(1.f, (float)windowHeight * 0.7f);
	CreateDummy(549.f, (float)windowHeight * 0.62f);
	CreateDummy(1.f, (float)windowHeight * 0.47f);
	CreateDummy(800.f, (float)windowHeight * 0.42f);
	// 1 dummy (2nd half)
	CreateDummy(1230.f, (float)windowHeight * 0.8f);
	CreateDummy(1680.f, (float)windowHeight * 0.6f);

	//          pos(x,y)     size(w,h)	       vel(x,y)  timing for rebound
	CreateLaser(1375.f, (float)windowHeight * 0.33f, 10, (float)windowHeight * 0.8f, 0, 0, 0);

	// Platforms
	//BEHIND START 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(-1000.f, 0.f), CP_Vector_Set(1000, (float)windowHeight), PLATFORM_COLOR);

	// BTM PLATFORM FIRST SEPARATION
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, (float)windowHeight * 0.8f), CP_Vector_Set(220, (float)windowHeight * 0.7f), PLATFORM_COLOR);
	// SECOND EXTENDER AND SO ON
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(415.f, (float)windowHeight * 0.8f), CP_Vector_Set(585, (float)windowHeight * 0.7f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1080.f, (float)windowHeight * 0.8f), CP_Vector_Set(200, (float)windowHeight * 0.7f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1280.f, (float)windowHeight * 0.9f), CP_Vector_Set(200, (float)windowHeight * 0.7f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1480.f, (float)windowHeight * 0.8f), CP_Vector_Set(1200, (float)windowHeight * 0.7f), PLATFORM_COLOR);

	// platforms from lowest to highest
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(400.f, (float)windowHeight * 0.62f), CP_Vector_Set(200, 25), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, (float)windowHeight * 0.47f), CP_Vector_Set(200, 25), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(400.f, (float)windowHeight * 0.32f), CP_Vector_Set(530, 25), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(700.f, (float)windowHeight * 0.42f), CP_Vector_Set(200, 25), PLATFORM_COLOR);

	// first half button and door
	CreateButtonDoorLink(CP_Vector_Set(500.f, (float)windowHeight * 0.31f), CP_Vector_Set(600.f, (float)windowHeight * 0.21f), 1);
	// wall on top of door
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(598.f, 0), CP_Vector_Set(54.f, (float)windowHeight * 0.21f), PLATFORM_COLOR);

	// wall separator
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1000.f, 0), CP_Vector_Set(80, (float)windowHeight * 0.66f), PLATFORM_COLOR);
	// connecting platform with finish
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1000.f, (float)windowHeight * 0.32f), CP_Vector_Set(530.f, 25.f), PLATFORM_COLOR); //finish platform
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1000.f, (float)windowHeight * 0.66f), CP_Vector_Set(150.f, 25.f), PLATFORM_COLOR); // below finish platform
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1260.f, (float)windowHeight * 0.53f), CP_Vector_Set(100.f, 25.f), PLATFORM_COLOR); //beside laser left

	// pillar player starts beside
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(850.f,(float)windowHeight * 0.325f), CP_Vector_Set(80, (float)windowHeight * 0.6f), PLATFORM_COLOR);

	// 2nd half button and door
	CreateButtonDoorLink(CP_Vector_Set(1345.f, (float)windowHeight * 0.89f), CP_Vector_Set(1680, (float)windowHeight * 0.69f), 1);
	// wall on top of door
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1390.f, (float)windowHeight * 0.66f), CP_Vector_Set(800, 25), PLATFORM_COLOR);
	// vertical end of wall on top door
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2190.f, (float)windowHeight * 0.66f), CP_Vector_Set(80, (float)windowHeight * 0.74f), PLATFORM_COLOR);

	// last set of platform steps towards the end
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2172.f, (float)windowHeight * 0.53f), CP_Vector_Set(100, 25), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1902.f, (float)windowHeight * 0.43f), CP_Vector_Set(100, 25), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1612.f, (float)windowHeight * 0.32f), CP_Vector_Set(100, 25), PLATFORM_COLOR);

	// AFTER END 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2272.f, 0.f), CP_Vector_Set(1100.f, (float)windowHeight), PLATFORM_COLOR);

	CP_System_SetWindowSize(windowWidth, windowHeight);
}

void Level9Update() {
	if (isGameOver == FALSE) {
		CP_Graphics_ClearBackground(CP_Color_Create(240, 200, 200, 255));
		ManageCollision();

		for (int i = 0; i < GOARRAY_SIZE; ++i) {
			if ((goPtr + i)->isActive) {
				if ((goPtr + i)->type == Type_Platform) {
					SideScrolling(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Enemy) {
					SideScrolling(goPtr + i);
					UpdateEnemy(goPtr + i);
					if ((goPtr + i)->pos.y > windowHeight) {
						DespawnGameObject(goPtr + i);
						endPoint->enemyCount--;
					}
				}
				else if ((goPtr + i)->type == Type_EndPoint) {
					SideScrolling(goPtr + i);
					UpdateEndPoint(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Obstacle) {
					SideScrolling(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Proj && projectile->projAlive) {
					UpdateProjectile(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_EnemyProj) {
					UpdateEnemyProj(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Door) {
					UpdateDoor(goPtr + i);
					SideScrolling(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Button) {
					SideScrolling(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Dummy) {
					SideScrolling(goPtr + i);
					UpdateDummy(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Laser) {
					SideScrolling(goPtr + i);
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

void Level9Exit() {
	FreeGoPtr(goPtr);
	free(goPtr);
}