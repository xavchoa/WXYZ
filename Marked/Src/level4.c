#include <cprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "mainmenu.h"
#include "level.h"
#include "game.h"
#include "scenes.h"

void Level4_Init() {
	CP_System_SetFrameRate(60);
	currentLevel = Level4;
	nextLevel = Level5;
	goPtr = (GameObject*)malloc(GOARRAY_SIZE * sizeof(GameObject));
	for (int i = 0; i < GOARRAY_SIZE; ++i) {
		(goPtr + i)->isActive = FALSE;
	}

	

	InitEndPoint(1822.f, windowHeight* 0.59);
	InitPlayer(0, 500.f);
	InitPlayerProjectile();



	CreateEnemy(750.f, windowHeight * 0.1f);
	CreateEnemy(1800.f, windowHeight * 0.1f);
	CreateEnemy(2200.f, windowHeight * 0.6f);
	CreateEnemy(2550.f, windowHeight * 0.6f);

	CreateDummy(860.f, windowHeight * 0.7f);
	CreateDummy(2750.f, windowHeight * 0.19f);
	//                           button                      door

	CreateButtonDoorLink(CP_Vector_Set(1055.f, windowHeight * 0.89), CP_Vector_Set(1050, windowHeight * 0.09), 1);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1048.f, 0.f), CP_Vector_Set(54, 78), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(1090.f, windowHeight * 0.1), CP_Vector_Set(10.f, 100.f), OBSTACLE_COLOR);

	CreateButtonDoorLink(CP_Vector_Set(2055.f, windowHeight * 0.3), CP_Vector_Set(3050, windowHeight * 0.2), 2);
	//CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(3048.f, 0.f), CP_Vector_Set(54, 110), PLATFORM_COLOR);

	//              pos         size            vel
	CreateLaser(2450.f, windowHeight * 0.3, 300, 10, 0, 0, 0);
	CreateLaser(950.f, windowHeight * 0.72, 300, 10, 0, 0, 0);
	CreateLaser(2440.f, windowHeight * 0.42, 10, windowHeight * 0.6, -60, 0, 8);



	// Platforms
	//BEHIND START 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(-1000.f, 0.f), CP_Vector_Set(1000, windowHeight), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, windowHeight * 0.7), CP_Vector_Set(400, windowHeight * 0.7), PLATFORM_COLOR);

	//STEPS TO GO UP
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(450.f, windowHeight * 0.58), CP_Vector_Set(200, 50), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(250.f, windowHeight * 0.45), CP_Vector_Set(100, 50), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(100.f, windowHeight * 0.32), CP_Vector_Set(100, 50), PLATFORM_COLOR);
	//CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(320.f, windowHeight * 0.25), CP_Vector_Set(100, 50), PLATFORM_COLOR);


	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(750.f, windowHeight * 0.7), CP_Vector_Set(200, windowHeight * 0.7), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(950.f, windowHeight * 0.9), CP_Vector_Set(300, windowHeight * 0.9), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1250.f, windowHeight * 0.7), CP_Vector_Set(200, windowHeight * 0.7), PLATFORM_COLOR);


	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(750.f, windowHeight * 0.2), CP_Vector_Set(450, 100), PLATFORM_COLOR);


	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1750.f, windowHeight * 0.2), CP_Vector_Set(200, 100), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1750.f, windowHeight * 0.31), CP_Vector_Set(700, 100), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2250.f, windowHeight * 0.2), CP_Vector_Set(200, 100), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1750.f, windowHeight * 0.42), CP_Vector_Set(50, windowHeight * 0.9), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2750.f, windowHeight * 0.2), CP_Vector_Set(300, 100), PLATFORM_COLOR);

	
	//after the door

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1800.f, windowHeight * 0.7), CP_Vector_Set(150, 100), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2050.f, windowHeight * 0.75), CP_Vector_Set(300, 100), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2450.f, windowHeight * 0.7), CP_Vector_Set(300, 100), PLATFORM_COLOR);



	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2900.f, windowHeight * 0.7), CP_Vector_Set(100, 100), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(3020.f, windowHeight * 0.5), CP_Vector_Set(100, 100), PLATFORM_COLOR);



	// AFTER END 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(3150.f, 0.f), CP_Vector_Set(1000, windowHeight), PLATFORM_COLOR);




	CP_System_SetWindowSize(windowWidth, windowHeight);
}


void Level4_Update() {
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

		//simulate gravity
		player->goPlayer->pos.y += player->vel.y * CP_System_GetDt();
		player->goPlayer->pos.x += player->vel.x * CP_System_GetDt();

		if (player->goPlayer->pos.y < windowHeight + 2 * player->goPlayer->size.y) {
			player->vel.y += gravity * CP_System_GetDt();
		}
		else {
			isGameOver = TRUE;
			DisplayGameOver();
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


void Level4_Exit() {
	free(goPtr);
	free(player);
	free(projectile);
}