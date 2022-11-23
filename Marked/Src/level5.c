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

void Level5_Init() {
	CP_System_SetFrameRate(60);
	currentLevel = Level5;
	nextLevel = Level6;
	goPtr = (GameObject*)malloc(GOARRAY_SIZE * sizeof(GameObject));
	if (goPtr) {
		for (int i = 0; i < GOARRAY_SIZE; ++i)
			(goPtr + i)->isActive = FALSE;
	}

	InitEndPoint(20.f, (float)windowHeight * 0.8f- 10.f);
	InitPlayer(700,800);
	InitPlayerProjectile();
	


	CreateEnemy(300.f, (float)windowHeight * 0.3f);


	//              pos         size            vel
	CreateLaser(1540.f, 0.f, 10, (float)windowHeight * 0.9f, 0, 0, 0);

	// horizontal door 1 button 1 
	CreateButtonDoorLink(CP_Vector_Set(200.f, (float)windowHeight * 0.89f), CP_Vector_Set(1550, (float)windowHeight * 0.9f), 2);


	// door 2 button 2
	CreateButtonDoorLink(CP_Vector_Set(1568.f, (float)windowHeight * 0.89f), CP_Vector_Set(568, (float)windowHeight * 0.8f), 1);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(566.f, (float)windowHeight * 0.57f), CP_Vector_Set(54, (float)windowHeight * 0.23f), PLATFORM_COLOR);


	// Platforms
	//BEHIND START 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(-1001.f, 0.f), CP_Vector_Set(1000.f, (float)windowHeight), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, (float)windowHeight * 0.9f), CP_Vector_Set(1550, 100), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, 0.f), CP_Vector_Set(620, 100), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, (float)windowHeight * 0.47f), CP_Vector_Set(620, 90), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(900.f, (float)windowHeight * 0.77f), CP_Vector_Set(100.f, (float)windowHeight * 0.13f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1000.f, (float)windowHeight * 0.67f), CP_Vector_Set(100.f, (float)windowHeight * 0.23f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1100.f, (float)windowHeight * 0.57f), CP_Vector_Set(100.f, (float)windowHeight * 0.33f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1200.f, (float)windowHeight * 0.47f), CP_Vector_Set(100.f, (float)windowHeight * 0.43f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1300.f, (float)windowHeight * 0.37f), CP_Vector_Set(175.f, (float)windowHeight * 0.53f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1375.f, (float)windowHeight * 0.315f), CP_Vector_Set(100.f, 50.f), PLATFORM_COLOR);
	CreateLaser(1476.f, (float)windowHeight * 0.315f, 174, 10, 0, 0, 0);


	// AFTER END 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1651.f, 0.f), CP_Vector_Set(1100, (float)windowHeight), PLATFORM_COLOR);


	CP_System_SetWindowSize(windowWidth, windowHeight);
}

void Level5_Update() {
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
					//SideScrolling(goPtr + i);
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

		//simulate gravity
		player->goPlayer->pos.y += player->vel.y * CP_System_GetDt();
		player->goPlayer->pos.x += player->vel.x * CP_System_GetDt();

		if (player->goPlayer->pos.y < windowHeight + 2 * player->goPlayer->size.y) {
			player->vel.y += gravity * CP_System_GetDt();
		}
		else {
			isGameOver = TRUE;
			//player->goPlayer->pos.y -= player->goPlayer->pos.y + player->goPlayer->size.y - windowHeight;
			/*player->vel.y = 0.f;
			isGrounded = TRUE;*/
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


void Level5_Exit() {
	free(goPtr);
	free(player);
	free(projectile);
}