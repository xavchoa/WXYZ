//---------------------------------------------------------
// file:	level.c
// author:	[Liu Wan Ting]
// email:	[wanting.liu@digipen.edu]
//
// brief:	Contains code which displays the instructions
// on how to play the game as well as game warnings to players
// This instructions will appear subsequently when players
// are at specified spots/ situations during gameplay 
// 
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
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

int windowWidth, windowHeight;
float const gravity = 980.f;
CP_BOOL isGrounded = FALSE;
CP_BOOL rightPressed = FALSE;
CP_BOOL leftPressed = FALSE;
CP_BOOL shootPressed = FALSE;
CP_BOOL isPlatformCollided = FALSE;
CP_BOOL isGameOver = FALSE;


void LevelInit() {
	currentLevel = Level0;
	nextLevel = Level1;
	goPtr = (GameObject*)malloc(GOARRAY_SIZE * sizeof(GameObject));
	if (goPtr) {
		for (int i = 0; i < GOARRAY_SIZE; ++i)
			(goPtr + i)->isActive = FALSE;
	}
	

	InitPlayerProjectile();
	InitEndPoint(1800, 530);
	InitPlayer(0, 100);

	CreateDummy(1500.f, 580);

	CreateLaser(1400, 0, 10, (float)windowHeight, 0, 0, 0);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0, (float)windowHeight * 0.6f), CP_Vector_Set(400, 540), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(550, (float)windowHeight * 0.7f), CP_Vector_Set(200, 600), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(900, (float)windowHeight * 0.7f), CP_Vector_Set(1080, 540), PLATFORM_COLOR);

	CP_System_SetWindowSize(windowWidth, windowHeight);
}
void LevelUpdate() {
	CP_System_SetFrameRate(60);
	float textSize = 50.0f;
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(textSize);
	
	
	CP_Font_DrawTextBox("Arrow keys to move", 20, 122, 300);
	CP_Settings_TextSize(30);
	CP_Font_DrawTextBox("Dummy", 1470, 550, 100);
	CP_Settings_TextSize(textSize);

	if(player->goPlayer->pos.x > 300)
		CP_Font_DrawTextBox("Space bar to jump", 500, 125, 300);
	if (player->goPlayer->pos.x > 800) {
		CP_Font_DrawTextBox("\"X\"  to mark target, press again to switch", 900, 125, 400);
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Settings_TextSize(30);
		CP_Font_DrawTextBox("NOTE: Target must be fully visible on your screen to switch", 900, 230, 400);
	}
	if (player->goPlayer->pos.x > 1400) {
		CP_Settings_TextSize(50);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawTextBox("Assassinate all targets Reach the endpoint", 1450, 125, 450);
	}
	if (player->goPlayer->pos.x > 1600) {
		CP_Font_DrawTextBox("Good luck,", 1450, 300, 450);
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawTextBox("Marksman", 1450, 350, 450);
	}
	
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	if (isGameOver == FALSE) {
		CP_Graphics_ClearBackground(CP_Color_Create(240, 200, 200, 255));

		ManageCollision();

		for (int i = 0; i < GOARRAY_SIZE; ++i) {
			if ((goPtr + i)->isActive) {
				if ((goPtr + i)->type == Type_Platform) {
				} else if ((goPtr + i)->type == Type_Enemy) {
					UpdateEnemy(goPtr + i);
					if ((goPtr + i)->pos.y > windowHeight) {
						DespawnGameObject(goPtr + i);
						endPoint->enemyCount--;
					}
				} else if ((goPtr + i)->type == Type_EndPoint){
					UpdateEndPoint(goPtr + i);
				} else if ((goPtr + i)->type == Type_Obstacle) {
				} else if ((goPtr + i)->type == Type_Proj && projectile->projAlive) {
					UpdateProjectile(goPtr + i);
				} else if ((goPtr + i)->type == Type_EnemyProj) {
					UpdateEnemyProj(goPtr + i);
				} else if ((goPtr + i)->type == Type_Door) {
					UpdateDoor(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_Button) {
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
		CP_Settings_TextSize(50);
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		if (player->goPlayer->pos.x > 800) 
			CP_Font_DrawTextBox("Becareful! Lasers only kill you. Enemies are immune.", 1000, 700, 600);
		//simulate gravity
		player->goPlayer->pos.y += player->vel.y * CP_System_GetDt();
		player->goPlayer->pos.x += player->vel.x * CP_System_GetDt();

		if (player->goPlayer->pos.y < windowHeight + 2 * player->goPlayer->size.y) {
			player->vel.y += gravity * CP_System_GetDt();
		} else {
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

	
	} else {
		//gameover screen
		DisplayGameOver();
	}

	RestartPressed();
	QuitPressed();

}
void LevelExit() {
	free(goPtr);
	free(player);
	free(projectile);
}