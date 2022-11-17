//#include "game.h"
//#include "scenes.h"
//#include <cprocessing.h>
//#include <stdio.h>
#include <cprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "mainmenu.h"
#include "level.h"
#include "game.h"
#include "scenes.h"

void Level10_Init() {
	CP_System_SetFrameRate(60);
	nextLevel = Level1;
	goPtr = (GameObject*)malloc(GOARRAY_SIZE * sizeof(GameObject));
	for (int i = 0; i < GOARRAY_SIZE; ++i) {
		(goPtr + i)->isActive = FALSE;
	}

	
	InitEndPoint(3400.f, 100.f);
	InitPlayer(100.f, 799.f);
	InitPlayerProjectile();

	CreateEnemy(1900.f, 224.f);
	CreateEnemy(800.f, 799.f);
	
	CreateDummy(1500.f, 224.f);
	CreateDummy(2250.f, 559.f);
	CreateDummy(2841.f, 785.f);
	CreateDummy(3000.f, 155.f);

	CreateButtonDoorLink(CP_Vector_Set(950.f, 790.f), CP_Vector_Set(450.f, 700.f), 1);
	
	//CreateLaser(-850, 0, 10, windowHeight, 60, 0, 100);
	CreateLaser(-600, 0, 10, windowHeight, 60, 0, 100);
	CreateLaser(-200, 0, 10, windowHeight, 60, 0, 100);
	CreateLaser(-400, 0, 10, windowHeight, 60, 0, 40);
	CreateLaser(0, 0, 10, windowHeight, 60, 0, 40);
	CreateLaser(450, 0, 10, windowHeight - 200, 0, 0, 0);
	CreateLaser(1350, 0, 10, windowHeight, 80, 0, 4);
	CreateLaser(2000, 228, 250, 10, 0, 200, 3);
	CreateLaser(2600, 800, 1200, 10, 0, -100, 8);
	CreateLaser(2700, 0, 10, windowHeight, 0, 0, 0);
	CreateLaser(2893, 0, 10, windowHeight, 0, 0, 0);


	//CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1898.f, 0.f), CP_Vector_Set(54, windowHeight * 0.54), PLATFORM_COLOR);

	// Platforms

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(-1000.f, 0.f), CP_Vector_Set(1000, windowHeight), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, 800.f), CP_Vector_Set(500, 100.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(800.f, 800.f), CP_Vector_Set(250.f, 200.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1240.f, 750.f), CP_Vector_Set(200.f, 25.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1500.f, 650.f), CP_Vector_Set(200.f, 25.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1240.f, 550.f), CP_Vector_Set(200.f, 25.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1000.f, 450.f), CP_Vector_Set(200.f, 25.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(750.f, 350.f), CP_Vector_Set(200.f, 25.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1000.f, 228.f), CP_Vector_Set(200.f, 25.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1450.f, 228.f), CP_Vector_Set(200.f, 25.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1900.f, 228.f), CP_Vector_Set(100.f, 1000.f), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2250.f, 0.f), CP_Vector_Set(350.f, 500.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2330.f, 228.f), CP_Vector_Set(270.f, 400.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2250.f, 560.f), CP_Vector_Set(350.f, 100.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2250.f, 800.f), CP_Vector_Set(350.f, 500.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2700.f, 870.f), CP_Vector_Set(200.f, 500.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(3000.f, 200.f), CP_Vector_Set(500.f, 800.f), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2875.f, 800.f), CP_Vector_Set(15.f, 15.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2715.f, 700.f), CP_Vector_Set(15.f, 15.f), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2875.f, 600.f), CP_Vector_Set(15.f, 15.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2715.f, 500.f), CP_Vector_Set(15.f, 15.f), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2875.f, 400.f), CP_Vector_Set(15.f, 15.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2715.f, 300.f), CP_Vector_Set(15.f, 15.f), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(3500.f, 0.f), CP_Vector_Set(1000, windowHeight), PLATFORM_COLOR);
	
	
	


	//CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1850.f, windowHeight * 0.65), CP_Vector_Set(400.f, 90.f), PLATFORM_COLOR);

	//CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2251.f, 0.f), CP_Vector_Set(1000, windowHeight), PLATFORM_COLOR);



	CP_System_SetWindowSize(windowWidth, windowHeight);
}

void Level10_Update() {
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

	if (CP_Input_KeyDown(KEY_Q)) {
		shootPressed = FALSE;
		rightPressed = FALSE;
		leftPressed = FALSE;
		isGameOver = FALSE;
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}

	if (CP_Input_KeyTriggered(KEY_R)) {
		shootPressed = FALSE;
		rightPressed = FALSE;
		leftPressed = FALSE;
		isGameOver = FALSE;
		CP_Engine_SetNextGameStateForced(Level10_Init, Level10_Update, Level10_Exit);
	}
}


void Level10_Exit() {
	free(goPtr);
	free(player);
	free(projectile);
}