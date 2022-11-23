#include <cprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "mainmenu.h"
#include "level.h"
#include "game.h"
#include "scenes.h"


void Level9_Init() {
	CP_System_SetFrameRate(60);
	currentLevel = Level9;
	nextLevel = Cutscene10;
	goPtr = (GameObject*)malloc(GOARRAY_SIZE * sizeof(GameObject));
	for (int i = 0; i < GOARRAY_SIZE; ++i) {
		(goPtr + i)->isActive = FALSE;
	}

	InitEndPoint(1100, windowHeight * 0.21);
	InitPlayer(800.f, 700.f);
	InitPlayerProjectile();

	// enemies
	
	CreateEnemy(400.f, windowHeight * 0.7f);
	CreateEnemy(1550.f, windowHeight * 0.7f);
	CreateEnemy(1750.f, windowHeight * 0.7f);
	
	// 4 dummies (1st half)
	CreateDummy(1.f, windowHeight * 0.7f);
	CreateDummy(549.f, windowHeight * 0.62f);
	CreateDummy(1.f, windowHeight * 0.47f);
	CreateDummy(800.f, windowHeight * 0.42f);
	// 1 dummy (2nd half)
	CreateDummy(1230.f, windowHeight * 0.8f);
	CreateDummy(1680.f, windowHeight * 0.6f);

	//          pos(x,y)     size(w,h)	       vel(x,y)  timing for rebound
	CreateLaser(1375.f, windowHeight * 0.33, 10, windowHeight * 0.8, 0, 0, 0);

	// Platforms
	//BEHIND START 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(-1000.f, 0.f), CP_Vector_Set(1000, windowHeight), PLATFORM_COLOR);

	// BTM PLATFORM FIRST SEPARATION
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, windowHeight * 0.8), CP_Vector_Set(220, windowHeight * 0.7), PLATFORM_COLOR);
	// SECOND EXTENDER AND SO ON
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(415.f, windowHeight * 0.8), CP_Vector_Set(585, windowHeight * 0.7), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1080.f, windowHeight * 0.8), CP_Vector_Set(200, windowHeight * 0.7), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1280.f, windowHeight * 0.9), CP_Vector_Set(200, windowHeight * 0.7), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1480.f, windowHeight * 0.8), CP_Vector_Set(1200, windowHeight * 0.7), PLATFORM_COLOR);


	//map length
	//CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1800.f, windowHeight * 0.9), CP_Vector_Set(200, 100), PLATFORM_COLOR);

	// platforms from lowest to highest
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(400.f, windowHeight * 0.62), CP_Vector_Set(200, 25), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, windowHeight * 0.47), CP_Vector_Set(200, 25), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(400.f, windowHeight * 0.32), CP_Vector_Set(530, 25), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(700.f, windowHeight * 0.42), CP_Vector_Set(200, 25), PLATFORM_COLOR);

	// first half button and door
	CreateButtonDoorLink(CP_Vector_Set(500.f, windowHeight * 0.31), CP_Vector_Set(600, windowHeight * 0.21), 1);
	// wall on top of door
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(598.f, 0), CP_Vector_Set(54, windowHeight * 0.21), PLATFORM_COLOR);

	// wall separator
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1000.f, 0), CP_Vector_Set(80, windowHeight * 0.66), PLATFORM_COLOR);
	// connecting platform with finish
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1000.f, windowHeight * 0.32), CP_Vector_Set(530, 25), PLATFORM_COLOR); //finish platform
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1000.f, windowHeight * 0.66), CP_Vector_Set(150, 25), PLATFORM_COLOR); // below finish platform
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1260.f, windowHeight * 0.53), CP_Vector_Set(100, 25), PLATFORM_COLOR); //beside laser left

	// pillar player starts beside
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(850.f, windowHeight * 0.325), CP_Vector_Set(80, windowHeight * 0.6), PLATFORM_COLOR);

	// 2nd half button and door
	CreateButtonDoorLink(CP_Vector_Set(1345.f, windowHeight * 0.89), CP_Vector_Set(1680, windowHeight * 0.69), 1);
	// wall on top of door
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1390.f, windowHeight * 0.66), CP_Vector_Set(800, 25), PLATFORM_COLOR);
	// vertical end of wall on top door
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2190.f, windowHeight * 0.66), CP_Vector_Set(80, windowHeight * 0.74), PLATFORM_COLOR);

	// last set of platform steps towards the end
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2172.f, windowHeight * 0.53), CP_Vector_Set(100, 25), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1902.f, windowHeight * 0.43), CP_Vector_Set(100, 25), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1612.f, windowHeight * 0.32), CP_Vector_Set(100, 25), PLATFORM_COLOR);


	// AFTER END 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2272.f, 0.f), CP_Vector_Set(1100, windowHeight), PLATFORM_COLOR);

	CP_System_SetWindowSize(windowWidth, windowHeight);
}


void Level9_Update() {
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


void Level9_Exit() {
	free(goPtr);
	free(player);
	free(projectile);
}