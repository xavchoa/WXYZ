#include <cprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "mainmenu.h"
#include "level.h"
#include "game.h"
#include "scenes.h"

int windowWidth, windowHeight;
float const gravity = 980.f;
CP_BOOL isGrounded = FALSE;
CP_BOOL rightPressed = FALSE;
CP_BOOL leftPressed = FALSE;
CP_BOOL shootPressed = FALSE;
CP_BOOL isPlatformCollided = FALSE;
CP_BOOL isGameOver = FALSE;


void Level_Init() {

	nextLevel = Level1;
	goPtr = (GameObject*)malloc(GOARRAY_SIZE * sizeof(GameObject));
	for (int i = 0; i < GOARRAY_SIZE; ++i) {
		(goPtr + i)->isActive = FALSE;
	}

	InitPlayerProjectile();

	InitEndPoint(1800.f, 530.f);

	InitPlayer(0, 100);

	CreateDummy(1500.f, 580);

	CreateLaser(1400, 0, 10, windowHeight, 0, 0, 0);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, windowHeight * 0.6), CP_Vector_Set(400.f, 540.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(550.f, windowHeight * 0.7), CP_Vector_Set(200.f, 600.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(900.f, windowHeight * 0.7), CP_Vector_Set(1080.f, 540.f), PLATFORM_COLOR);
	//CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1450.f, 0), CP_Vector_Set(100.f, 550.f), PLATFORM_COLOR);
	//CreateEnemy(1000.f, 300.f);
	

	//CreateGameElement(TRUE, Type_Laser, CP_Vector_Set(900.f, 0.f), CP_Vector_Set(10.f, windowHeight), OBSTACLE_COLOR);



	//CreateEnemy(700.f, 300.f);
	
	//CreateLaser(1000,0, 10, windowHeight,-60,0,0);


	//Platforms
	//CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(100.f, 600), CP_Vector_Set(100.f, 200.f), PLATFORM_COLOR);
	//CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(500.f, windowHeight * 0.9), CP_Vector_Set(2000.f, 100.f), PLATFORM_COLOR);
	//CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(480.f, windowHeight * 0.8 + 10), CP_Vector_Set(20.f, 100.f), OBSTACLE_COLOR);
	//CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1000.f, windowHeight * 0.8), CP_Vector_Set(200.f, 100.f), PLATFORM_COLOR);
	//CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(1000.f, windowHeight * 0.8 + 10), CP_Vector_Set(100.f, 100.f), OBSTACLE_COLOR);
	//CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(200.f, windowHeight * 0.8), CP_Vector_Set(200.f, 100.f), PLATFORM_COLOR);

	

	//CreateButtonDoorLink(CP_Vector_Set(500, windowHeight * 0.7 - 50), CP_Vector_Set(700, windowHeight * 0.7 - 100),1);
	//CreateButtonDoorLink(CP_Vector_Set(500, windowHeight * 0.7 - 50), CP_Vector_Set(1000, windowHeight * 0.7 - 100),2);
	//CreateButtonDoorLink(CP_Vector_Set(500, 800), CP_Vector_Set(1500, 710),1);


	// Enemies
	//CreateGameElement(TRUE, Type_Enemy, CP_Vector_Set(1000.f, 300.f), CP_Vector_Set(50.f, 50.f), ENEMY_COLOR);
	//CreateGameElement(TRUE, Type_Enemy, CP_Vector_Set(700.f, 300.f), CP_Vector_Set(50.f, 50.f), ENEMY_COLOR);

	CP_System_SetWindowSize(windowWidth, windowHeight);
}
void Level_Update() {
	CP_System_SetFrameRate(60);
	float textSize = 50.0f;
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	//CP_Graphics_DrawRect(20, 80, 300, 100);
	//CP_Graphics_DrawRect(515, 80, 300, 100);
	//CP_Graphics_DrawRect(1000, 60, 350, 200);
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
		for (int x = 0; x < GOARRAY_SIZE; ++x) {
			if ((goPtr + x)->isActive && (goPtr + x)->hasCollider) {
				for (int y = x + 1; y < GOARRAY_SIZE; ++y) {
					if ((goPtr + y)->isActive && (goPtr + y)->hasCollider) {
						if (CheckCollision((goPtr + x), (goPtr + y))) {
							CollisionResponse((goPtr + x), (goPtr + y));
						}
					}
				}
			}
		}

		for (int i = 0; i < GOARRAY_SIZE; ++i) {
			if ((goPtr + i)->isActive) {
				if ((goPtr + i)->type == Type_Platform) {
					//SideScrolling(goPtr + i);
				} else if ((goPtr + i)->type == Type_Enemy) {
					//SideScrolling(goPtr + i);
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

	if (CP_Input_KeyDown(KEY_Q)) {
		shootPressed = FALSE;
		rightPressed = FALSE;
		leftPressed = FALSE;
		isGameOver = FALSE;
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}

	if (CP_Input_KeyTriggered(KEY_R)) {
		projectile->projAlive = FALSE;
		shootPressed = FALSE;
		rightPressed = FALSE;
		leftPressed = FALSE;
		isGameOver = FALSE;
		CP_Engine_SetNextGameStateForced(Level_Init, Level_Update, Level_Exit);
	}
}
void Level_Exit() {
	free(goPtr);
	free(player);
	free(projectile);
}






