#include <cprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "mainmenu.h"
#include "level.h"
#include "game.h"
#include "scenes.h"


void Level8_Init() {
	CP_System_SetFrameRate(60);
	currentLevel = Level8;
	nextLevel = Cutscene9;
	goPtr = (GameObject*)malloc(GOARRAY_SIZE * sizeof(GameObject));
	for (int i = 0; i < GOARRAY_SIZE; ++i) {
		(goPtr + i)->isActive = FALSE;
	}

	
	InitEndPoint(1840.f, windowHeight*0.25 - 20);
	InitPlayer(200,600);
	InitPlayerProjectile();

	CreateDummy(301.f, windowHeight * 0.1);
	CreateDummy(678.f, windowHeight * 0.1);
	CreateDummy(1045, windowHeight * 0.1);

	// Platforms
	//BEHIND START 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(-1000.f, 0.f), CP_Vector_Set(1000, windowHeight), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, windowHeight * 0.92), CP_Vector_Set(950, 100), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, windowHeight * 0.85), CP_Vector_Set(200, 62), PLATFORM_COLOR);
	// step to go up 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, windowHeight * 0.8), CP_Vector_Set(100, 50), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(350.f, windowHeight * 0.85), CP_Vector_Set(100, 62), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(600.f, windowHeight * 0.85), CP_Vector_Set(100, 62), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(630.f, windowHeight * 0.82), CP_Vector_Set(40, 30), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(850.f, windowHeight * 0.7), CP_Vector_Set(100, 200), PLATFORM_COLOR);

	// top pillar
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, 0.f), CP_Vector_Set(200, windowHeight * 0.57), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(475.f, 0.f), CP_Vector_Set(100, windowHeight * 0.57), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(850.f, 0.f), CP_Vector_Set(100, windowHeight * 0.57), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1210.f, 0.f), CP_Vector_Set(100, windowHeight * 0.57), PLATFORM_COLOR);


	// platform along with door 1
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(200.f, windowHeight * 0.685), CP_Vector_Set(400, 50), PLATFORM_COLOR);
	//door 1 button 1
	CreateButtonDoorLink(CP_Vector_Set(240.f, windowHeight * 0.91), CP_Vector_Set(600, windowHeight * 0.685), 2);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(700.f, windowHeight * 0.685), CP_Vector_Set(250, 50), PLATFORM_COLOR);

	//platform with top door 1
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(950.f, windowHeight * 0.2), CP_Vector_Set(80, 50), PLATFORM_COLOR);
	// top door 1
	CreateButtonDoorLink(CP_Vector_Set(240.f, windowHeight * 0.91), CP_Vector_Set(1030, windowHeight * 0.2), 2);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1130.f, windowHeight * 0.2), CP_Vector_Set(80, 50), PLATFORM_COLOR);


	//button 2 door 2
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(575.f, windowHeight * 0.2), CP_Vector_Set(84, 50), PLATFORM_COLOR);
	CreateButtonDoorLink(CP_Vector_Set(490.f, windowHeight * 0.91), CP_Vector_Set(660, windowHeight * 0.2), 2);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(760.f, windowHeight * 0.2), CP_Vector_Set(87, 50), PLATFORM_COLOR);

	//button 3 door 3
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(200.f, windowHeight * 0.2), CP_Vector_Set(84, 50), PLATFORM_COLOR);
	CreateButtonDoorLink(CP_Vector_Set(740.f, windowHeight * 0.91), CP_Vector_Set(285, windowHeight * 0.2), 2);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(385.f, windowHeight * 0.2), CP_Vector_Set(87, 50), PLATFORM_COLOR);

	//button 4 door 4
	CreateButtonDoorLink(CP_Vector_Set(678.f, windowHeight * 0.19), CP_Vector_Set(370, windowHeight * 0.74), 1);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(950.f, windowHeight * 0.3), CP_Vector_Set(80, 50), PLATFORM_COLOR);
	CreateButtonDoorLink(CP_Vector_Set(676.f, windowHeight * 0.19), CP_Vector_Set(1030, windowHeight * 0.3), 2);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1130.f, windowHeight * 0.3), CP_Vector_Set(80, 50), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(950.f, windowHeight * 0.685), CP_Vector_Set(80, 50), PLATFORM_COLOR);
	CreateButtonDoorLink(CP_Vector_Set(676.f, windowHeight * 0.19), CP_Vector_Set(1030, windowHeight * 0.685), 2);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1130.f, windowHeight * 0.685), CP_Vector_Set(80, 50), PLATFORM_COLOR);


	//button 5 door 5
	CreateButtonDoorLink(CP_Vector_Set(676.f, windowHeight * 0.5), CP_Vector_Set(875, windowHeight * 0.57), 1);
	//platform for button 5
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(575.f, windowHeight * 0.515), CP_Vector_Set(275, 50), PLATFORM_COLOR);


	//button 6 door 6
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(950.f, windowHeight * 0.885), CP_Vector_Set(80, 50), PLATFORM_COLOR);
	CreateButtonDoorLink(CP_Vector_Set(301.f, windowHeight * 0.19), CP_Vector_Set(1030, windowHeight * 0.885), 2);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1130.f, windowHeight * 0.885), CP_Vector_Set(80, 50), PLATFORM_COLOR);


	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1210.f, windowHeight * 0.685), CP_Vector_Set(200.f, 50.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1210.f, windowHeight * 0.885), CP_Vector_Set(710.f, windowHeight * 0.57), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1425.f, windowHeight * 0.83), CP_Vector_Set(50.f, 50.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1475.f, windowHeight * 0.78), CP_Vector_Set(50.f, 95.f), PLATFORM_COLOR);

	// steps to end point
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1525.f, windowHeight * 0.685), CP_Vector_Set(150.f, windowHeight * 0.57), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1720.f, windowHeight * 0.34), CP_Vector_Set(200, windowHeight * 0.57), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1660.f, windowHeight * 0.53), CP_Vector_Set(60.f, windowHeight * 0.63), PLATFORM_COLOR);
	







	// AFTER END 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2801.f, 0.f), CP_Vector_Set(1100, windowHeight), PLATFORM_COLOR);


	CP_System_SetWindowSize(windowWidth, windowHeight);
}


void Level8_Update() {
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


void Level8_Exit() {
	free(goPtr);
	free(player);
	free(projectile);
}