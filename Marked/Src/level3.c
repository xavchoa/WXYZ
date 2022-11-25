//---------------------------------------------------------
// file:	level3.c
// author:	[CHEONG YU QING]
// email:	[c.yuqing@digipen.edu]
//
// brief:	LEVEL 3 has lasers which adds another lose 
// condition to the players and it increases the difficulty 
// to players as their range of movement is restricted.
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

void Level3Init() {
	CP_System_SetFrameRate(60);
	currentLevel = Level3;
	nextLevel = Cutscene1;
	goPtr = (GameObject*)malloc(GOARRAY_SIZE * sizeof(GameObject));
	if (goPtr) {
		for (int i = 0; i < GOARRAY_SIZE; ++i)
			(goPtr + i)->isActive = FALSE;
	}

	InitEndPoint(1720.f, (float)windowHeight * 0.47f);
	InitPlayer(200.f, 500.f);
	InitPlayerProjectile();


	CreateEnemy(300.f, (float)windowHeight * 0.7f);

	//              pos         size            vel  timing for rebound
	CreateLaser(700.f, 0.f, 10, (float)windowHeight, 100, 0, 8.9f);
	//CreateLaser(1590.f, 0.f, 10, windowHeight, -50, 0, 10);

	// Platforms
	//BEHIND START 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(-1000.f, 0.f), CP_Vector_Set(1000.f, (float)windowHeight), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(100.f, (float)windowHeight * 0.7f), CP_Vector_Set(150.f, 100.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(100.f, (float)windowHeight * 0.8f), CP_Vector_Set(600.f, (float)windowHeight * 0.8f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(700.f, (float)windowHeight * 0.7f), CP_Vector_Set(1100.f, (float)windowHeight * 0.7f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1600.f, (float)windowHeight * 0.58f), CP_Vector_Set(200.f, 300.f), PLATFORM_COLOR);


	// door 1 button 1
	CreateButtonDoorLink(CP_Vector_Set(1130.f, (float)windowHeight * 0.69f), CP_Vector_Set(0.f, (float)windowHeight * 0.8f), 2);


	// AFTER END 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1801.f, 0.f), CP_Vector_Set(1100.f, (float)windowHeight), PLATFORM_COLOR);


	CP_System_SetWindowSize(windowWidth, windowHeight);
}


void Level3Update() {
	if (isGameOver == FALSE) {
		CP_Graphics_ClearBackground(CP_Color_Create(240, 200, 200, 255));
		ManageCollision();

		for (int i = 0; i < GOARRAY_SIZE; ++i) {
			if ((goPtr + i)->isActive) {
				if ((goPtr + i)->type == Type_Platform) {
					//SideScrolling(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Enemy) {
					//SideScrolling(goPtr + i);
					UpdateEnemy(goPtr + i);
					if ((goPtr + i)->pos.y > windowHeight) {
						DespawnGameObject(goPtr + i);
						endPoint->enemyCount--;
					}
				}
				else if ((goPtr + i)->type == Type_EndPoint) {
					UpdateEndPoint(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Obstacle) {
					//SideScrolling(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Proj && projectile->projAlive) {
					UpdateProjectile(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_EnemyProj) {
					UpdateEnemyProj(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Door) {
					UpdateDoor(goPtr + i);
					//SideScrolling(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Button) {
					//SideScrolling(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Dummy) {
					//SideScrolling(goPtr + i);
					UpdateDummy(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Laser) {
					//SideScrolling(goPtr + i);
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


void Level3Exit() {
	free(goPtr);
	free(player);
	free(projectile);
}