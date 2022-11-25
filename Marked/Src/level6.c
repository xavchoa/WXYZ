//---------------------------------------------------------
// file:	level6.c
// author:	[CHEONG YU QING]
// email:	[c.yuqing@digipen.edu]
//
// brief:	LEVEL 6 requires the player to time well to make
//  enermies kill each other inorder to pass the level.
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

void Level6Init() {
	CP_System_SetFrameRate(60);
	currentLevel = Level6;
	nextLevel = Cutscene7;
	goPtr = (GameObject*)malloc(GOARRAY_SIZE * sizeof(GameObject));
	if (goPtr) {
		for (int i = 0; i < GOARRAY_SIZE; ++i)
			(goPtr + i)->isActive = FALSE;
	}

	InitEndPoint(1420.f, (float)windowHeight *0.7f -20.f);
	InitPlayer(0, 500.f);
	InitPlayerProjectile();



	CreateEnemy(1110.f, (float)windowHeight * 0.8f);
	CreateEnemy(400.f, (float)windowHeight * 0.5f);
	CreateEnemy(400.f, (float)windowHeight * 0.8f);
	

	// Platforms
	//BEHIND START 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(-1000.f, 0.f), CP_Vector_Set(1000, (float)windowHeight), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, (float)windowHeight * 0.8f), CP_Vector_Set(400, (float)windowHeight * 0.7f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, (float)windowHeight * 0.72f), CP_Vector_Set(100, 80), PLATFORM_COLOR);


	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(400.f, (float)windowHeight * 0.9f), CP_Vector_Set(1100, 100), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(350.f, (float)windowHeight * 0.6f), CP_Vector_Set(600, 70), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(870.f, (float)windowHeight * 0.68f), CP_Vector_Set(80, (float)windowHeight * 0.22f), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1400.f, (float)windowHeight * 0.79f), CP_Vector_Set(100, 100), PLATFORM_COLOR);


	// AFTER END 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1501.f, 0.f), CP_Vector_Set(1100, (float)windowHeight), PLATFORM_COLOR);


	CP_System_SetWindowSize(windowWidth, windowHeight);
}



void Level6Update() {
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
				else if ((goPtr + i)->type == Type_Proj && projectile->projAlive) {
					UpdateProjectile(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_EnemyProj) {
					UpdateEnemyProj(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Door) {
					UpdateDoor(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Button) {
					SideScrolling(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Dummy) {
					UpdateDummy(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Laser){
					UpdateLaser(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_EndPoint) {
					UpdateEndPoint(goPtr + i);
				}
			}
		}

		CP_Settings_TextSize(50);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawTextBox("Enemy projectiles are deadly. No one can survive them.", 350, 300, 600);
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawTextBox("NO ONE.", 1100, 500, 200);
		RenderScene();

		//simulate gravity
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
		//gameover screen
		DisplayGameOver();
	}

	QuitPressed();
	RestartPressed();
}


void Level6Exit() {
	free(goPtr);
	free(player);
	free(projectile);
}