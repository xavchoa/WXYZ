#include <cprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "mainmenu.h"
#include "level.h"
#include "game.h"
#include "scenes.h"


void Level2_Init() {
	currentLevel = Level2;
	nextLevel = Level3;
	goPtr = (GameObject*)malloc(GOARRAY_SIZE * sizeof(GameObject));
	for (int i = 0; i < GOARRAY_SIZE; ++i) {
		(goPtr + i)->isActive = FALSE;
	}

	InitEndPoint(2420, windowHeight * 0.59f);
	InitPlayerProjectile();
	InitPlayer(0, 500);


	CreateEnemy(1950.f, windowHeight * 0.4f);
	CreateDummy(750.f, windowHeight * 0.7f);
	//                           button                      door
	CreateButtonDoorLink(CP_Vector_Set(425.f, windowHeight * 0.89), CP_Vector_Set(950, windowHeight * 0.59), 1);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(948.f, 0.f), CP_Vector_Set(54, windowHeight * 0.59), PLATFORM_COLOR);


	// Platforms

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(-1000.f, 0.f), CP_Vector_Set(1000, windowHeight), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, windowHeight * 0.7), CP_Vector_Set(300, windowHeight * 0.7), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(300.f, windowHeight * 0.9), CP_Vector_Set(300, windowHeight * 0.9), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(600.f, windowHeight * 0.7), CP_Vector_Set(400, windowHeight * 0.7), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1130.f, windowHeight * 0.6), CP_Vector_Set(300, windowHeight * 0.6), PLATFORM_COLOR);


	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1800.f, windowHeight * 0.5), CP_Vector_Set(300.f, 100.f), PLATFORM_COLOR);


	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2200.f, windowHeight * 0.7), CP_Vector_Set(300.f, windowHeight * 0.7), PLATFORM_COLOR);

	// BEHIND THE END 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2501.f, 0.f), CP_Vector_Set(1000, windowHeight), PLATFORM_COLOR);



	CP_System_SetWindowSize(windowWidth, windowHeight);
}

void Level2_Update() {
	CP_System_SetFrameRate(60);
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


void Level2_Exit() {
	free(goPtr);
	free(player);
	free(projectile);
}

		




