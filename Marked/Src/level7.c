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

void Level7_Init() {
	CP_System_SetFrameRate(60);
	currentLevel = Level7;
	nextLevel = Cutscene8;
	goPtr = (GameObject*)malloc(GOARRAY_SIZE * sizeof(GameObject));
	for (int i = 0; i < GOARRAY_SIZE; ++i) {
		(goPtr + i)->isActive = FALSE;
	}

	InitEndPoint(2720.f, (float)windowHeight*0.7f- 10.f);
	InitPlayer(0.f, 500.f);
	InitPlayerProjectile();



	CreateEnemy(2300.f, (float)windowHeight * 0.29f);
	CreateEnemy(2350.f, (float)windowHeight * 0.7f);

	CreateDummy(860.f, (float)windowHeight * 0.7f);
	CreateDummy(1800.f, (float)windowHeight * 0.29f);


	//              pos         size            vel  timing for rebound
	CreateLaser(1700.f, 0.f, 10, (float)windowHeight, 0, 0, 0);



	// Platforms
	//BEHIND START 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(-1000.f, 0.f), CP_Vector_Set(1000, (float)windowHeight), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, (float)windowHeight * 0.8f), CP_Vector_Set(2000, (float)windowHeight * 0.7f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2000.f, (float)windowHeight * 0.9f), CP_Vector_Set(800, 100), PLATFORM_COLOR);

	// steps to go to door 2
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(100.f, (float)windowHeight * 0.68f), CP_Vector_Set(100, 50), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(300.f, (float)windowHeight * 0.58f), CP_Vector_Set(100, 50), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(500.f, (float)windowHeight * 0.48f), CP_Vector_Set(100, 50), PLATFORM_COLOR);


	// door 1 button 1
	CreateButtonDoorLink(CP_Vector_Set(550.f, (float)windowHeight * 0.79f), CP_Vector_Set(700, (float)windowHeight * 0.69f), 1);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(698.f, (float)windowHeight * 0.5f), CP_Vector_Set(54, (float)windowHeight * 0.19f), PLATFORM_COLOR);


	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(698.f, (float)windowHeight * 0.4f), CP_Vector_Set(682, 100), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1300.f, (float)windowHeight * 0.5f), CP_Vector_Set(80, (float)windowHeight * 0.5f), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(698.f, 0), CP_Vector_Set(682, 100), PLATFORM_COLOR);

	// door 2 button 2
	CreateButtonDoorLink(CP_Vector_Set(1100.f, (float)windowHeight * 0.79f), CP_Vector_Set(700, (float)windowHeight * 0.29f), 1);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(698.f, (float)windowHeight * 0.1f), CP_Vector_Set(54, (float)windowHeight * 0.19f), PLATFORM_COLOR);


	//throw enemy off the laser
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2460.f, 0), CP_Vector_Set(50, (float)windowHeight * 0.4f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1810.f, (float)windowHeight * 0.17f), CP_Vector_Set(150, 50), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1710.f, (float)windowHeight * 0.4f), CP_Vector_Set(800, 100), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2060.f, (float)windowHeight * 0.27f), CP_Vector_Set(100, 50), PLATFORM_COLOR);



	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2200.f, (float)windowHeight * 0.79f), CP_Vector_Set(310, 30), PLATFORM_COLOR);

	// door 3 button 3
	CreateButtonDoorLink(CP_Vector_Set(2310.f, (float)windowHeight * 0.89f), CP_Vector_Set(2200.f, (float)windowHeight * 0.68f), 1);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2198.f, (float)windowHeight * 0.5f), CP_Vector_Set(54, (float)windowHeight * 0.18f), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2460.f, (float)windowHeight * 0.5f), CP_Vector_Set(50, (float)windowHeight * 0.29f), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2650.f, (float)windowHeight * 0.8f), CP_Vector_Set(150, 87), PLATFORM_COLOR);

	// AFTER END 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2801.f, 0.f), CP_Vector_Set(1100, (float)windowHeight), PLATFORM_COLOR);


	CP_System_SetWindowSize(windowWidth, windowHeight);
}


void Level7_Update() {
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


void Level7_Exit() {
	free(goPtr);
	free(player);
	free(projectile);
}