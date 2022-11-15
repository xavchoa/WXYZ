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

	GameObject* goPlayer = GetGameObject();
	goPlayer->isActive = TRUE;
	goPlayer->hasCollider = TRUE;
	goPlayer->type = Type_Player;
	goPlayer->pos = CP_Vector_Set(300.f, 100.f);
	goPlayer->size = CP_Vector_Set(50.f, 50.f);
	goPlayer->color = CP_Color_Create(255, 255, 255, 0);
	player = (Player*)malloc(sizeof(Player));
	player->speed = 10000.f;
	player->vel.x = 0.f;
	player->vel.y = 500.f;
	player->dir.x = 1.f;
	player->dir.y = 0.f;
	player->goPlayer = goPlayer;
	player->markedObject = NULL;
	goPlayer->childData = player;

	InitPlayerProjectile();

	GameObject* goEndPoint = GetGameObject();
	goEndPoint->isActive = TRUE;
	goEndPoint->hasCollider = TRUE;
	goEndPoint->type = Type_EndPoint;
	goEndPoint->pos = CP_Vector_Set(1800.f, 530.f);
	goEndPoint->size = CP_Vector_Set(60.f, 100.f);
	goEndPoint->color = CP_Color_Create(75, 0, 130, 255);
	endPoint = (EndPoint*)malloc(sizeof(EndPoint));
	goEndPoint->childData = endPoint;
	endPoint->enemyCount = 0;


	CreateDummy(1500.f, 580);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, windowHeight * 0.6), CP_Vector_Set(400.f, 540.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(550.f, windowHeight * 0.7), CP_Vector_Set(200.f, 600.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(900.f, windowHeight * 0.7), CP_Vector_Set(1080.f, 540.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1450.f, 0), CP_Vector_Set(100.f, 550.f), PLATFORM_COLOR);
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

	

	//CreateButtonDoorLink(CP_Vector_Set(500, 800), CP_Vector_Set(700, 710),1);
	//CreateButtonDoorLink(CP_Vector_Set(500, 800), CP_Vector_Set(1500, 710),1);


	// Enemies
	//CreateGameElement(TRUE, Type_Enemy, CP_Vector_Set(1000.f, 300.f), CP_Vector_Set(50.f, 50.f), ENEMY_COLOR);
	//CreateGameElement(TRUE, Type_Enemy, CP_Vector_Set(700.f, 300.f), CP_Vector_Set(50.f, 50.f), ENEMY_COLOR);

	CP_System_SetWindowSize(windowWidth, windowHeight);
}


void Level_Update() {
	CP_System_SetFrameRate(60);
	float textSize = 30.0f;
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect(20, 80, 300, 100);
	CP_Graphics_DrawRect(515, 80, 300, 100);
	CP_Graphics_DrawRect(1000, 60, 350, 200);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(textSize);
	CP_Font_DrawTextBox("Press arrow keys to move forward and backward", 20, 120, 300);
	CP_Font_DrawTextBox("Press space bar to jump", 515, 125, 300);
	CP_Font_DrawTextBox("Press X to mark target, press again to swap positions", 1000, 105, 350);
	textSize = 20.0f;
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Settings_TextSize(textSize);
	CP_Font_DrawTextBox("NOTE: Once target is marked, target must be within vision (fully visible on your screen) in order to swap", 1000, 180, 350);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	//printf("%f\n", CP_System_GetDt());
	//printf("%f\n", CP_System_GetFrameRate());
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
					//SideScrolling(goPtr + i);
				} else if ((goPtr + i)->type == Type_Obstacle) {
					//SideScrolling(goPtr + i);
				} else if ((goPtr + i)->type == Type_Proj && projectile->projAlive) {
					UpdateProjectile(goPtr + i);
				} else if ((goPtr + i)->type == Type_EnemyProj) {
					UpdateEnemyProj(goPtr + i);
				} else if ((goPtr + i)->type == Type_Door) {
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
				//Enemy* e = (Enemy*)player->markedObject->childData;
				//GameObject* target = (GameObject*)player->markedObject->childData;
				//e->collidedWithPlatform = FALSE;
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






