//---------------------------------------------------------
// file:	level1.c
// author:	[CHEONG YU QING]
// email:	[c.yuqing@digipen.edu]
//
// brief:	LEVEL 1
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <cprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "mainmenu.h"
#include "level.h"
#include "game.h"
#include "scenes.h"
#include "player.h"
#include "enemy.h"
#include "render.h"
#include "gameelements.h"


void Level1Init() {
	currentLevel = Level1;
	nextLevel = Level2;
	goPtr = (GameObject*)malloc(GOARRAY_SIZE * sizeof(GameObject));
	if (goPtr) {
		for (int i = 0; i < GOARRAY_SIZE; ++i)
			(goPtr + i)->isActive = FALSE;
	}
	
	CreateGameElement(TRUE, Type_Info, CP_Vector_Set(1000, (float)windowHeight - 100), CP_Vector_Set(1200, 0), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Info2, CP_Vector_Set(1000, 200), CP_Vector_Set(800, 0), PLATFORM_COLOR);



	InitPlayerProjectile();
	InitEndPoint(2150.f, (float)windowHeight * 0.55f);
	InitPlayer(0.f, 700.f);

	CreateEnemy(1950.f, (float)windowHeight * 0.6f);

	CreateButtonDoorLink(CP_Vector_Set(1440.f, (float)windowHeight * 0.64f), CP_Vector_Set(1900, (float)windowHeight * 0.54f), 1);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1898.f, 0.f), CP_Vector_Set(54.f, (float)windowHeight * 0.54f), PLATFORM_COLOR);

	// Platforms

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(-1000.f, 0.f), CP_Vector_Set(1000.f, (float)windowHeight), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, (float)windowHeight * 0.9f), CP_Vector_Set(210, 100.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(400.f, (float)windowHeight * 0.9f), CP_Vector_Set(300.f, 200.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(700.f, (float)windowHeight * 0.8f), CP_Vector_Set(100.f, 250.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(800.f, (float)windowHeight * 0.7f), CP_Vector_Set(100.f, 350.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(900.f, (float)windowHeight * 0.6f), CP_Vector_Set(100.f, 450.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1100.f, (float)windowHeight * 0.5f), CP_Vector_Set(100.f, 90.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1300.f, (float)windowHeight * 0.4f), CP_Vector_Set(100.f, 90.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1410.f, (float)windowHeight * 0.65f), CP_Vector_Set(200.f, 90.f), PLATFORM_COLOR);


	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1850.f, (float)windowHeight * 0.65f), CP_Vector_Set(400.f, 90.f), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2251.f, 0.f), CP_Vector_Set(1000.f, (float)windowHeight), PLATFORM_COLOR);



	CP_System_SetWindowSize(windowWidth, windowHeight);
}

void Level1Update() {
	CP_System_SetFrameRate(60);
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
					UpdateEndPoint(goPtr +i);
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
				else if ((goPtr + i)->type == Type_Info) {
					SideScrolling(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Info2) {
					SideScrolling(goPtr + i);
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
	else{
		DisplayGameOver();
	}

	QuitPressed();
	RestartPressed();
}


void Level1Exit() {
	free(goPtr);
	free(player);
	free(projectile);
}