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

void Level10Init() {
	CP_System_SetFrameRate(60);
	currentLevel = Level10;
	nextLevel = Winscene;
	goPtr = (GameObject*)malloc(GOARRAY_SIZE * sizeof(GameObject));
	if (goPtr) {
		for (int i = 0; i < GOARRAY_SIZE; ++i)
			(goPtr + i)->isActive = FALSE;
	}

	CP_System_SetWindowSize(windowWidth, windowHeight);
	
	InitEndPoint(3400.f, 100.f);
	InitPlayer(100.f, 799.f);
	InitPlayerProjectile();

	//Enemies
	CreateEnemy(1900.f, 224.f);
	CreateEnemy(800.f, 799.f);
	
	//Dummies
	CreateDummy(1500.f, 224.f);
	CreateDummy(2250.f, 559.f);
	CreateDummy(2841.f, 785.f);
	CreateDummy(3000.f, 155.f);

	//Doors
	CreateButtonDoorLink(CP_Vector_Set(950.f, 790.f), CP_Vector_Set(450.f, 700.f), 1);
	
	// Lasers
	CreateLaser(-600.f, 0.f, 10.f, (float)windowHeight, 60.f, 0.f, 100.f);
	CreateLaser(-200.f, 0.f, 10.f, (float)windowHeight, 60.f, 0.f, 100.f);
	CreateLaser(-400.f, 0.f, 10.f, (float)windowHeight, 60.f, 0.f, 40.f);
	CreateLaser(0.f, 0.f, 10.f, (float)windowHeight, 60.f, 0.f, 40.f);
	CreateLaser(450.f, 0.f, 10.f, (float)windowHeight - 200.f, 0.f, 0.f, 0.f);
	CreateLaser(1350.f, 0.f, 10.f, (float)windowHeight, 80.f, 0.f, 4.f);
	CreateLaser(2000.f, 228.f, 250.f, 10.f, 0.f, 200.f, 3.f);
	CreateLaser(2600.f, 800.f, 1200.f, 10.f, 0.f, -100.f, 8.f);
	CreateLaser(2700.f, 0.f, 10.f, (float)windowHeight, 0.f, 0.f, 0.f);
	CreateLaser(2893.f, 0.f, 10.f, (float)windowHeight, 0.f, 0.f, 0.f);

	// Platforms
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(-1000.f, 0.f), CP_Vector_Set(1000.f , (float)windowHeight), PLATFORM_COLOR);

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

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(3500.f, 0.f), CP_Vector_Set(1000.f, (float)windowHeight), PLATFORM_COLOR);
}

void Level10Update() {
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
					SideScrolling(goPtr + i);
					UpdateDoor(goPtr + i);
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


void Level10Exit() {
	free(goPtr);
	free(player);
	free(projectile);
}