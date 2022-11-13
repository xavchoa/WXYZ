#include <cprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "mainmenu.h"
#include "level.h"
#include "game.h"
#include "scenes.h"

void Level3_Init() {
	level = Level4;
	goPtr = (GameObject*)malloc(GOARRAY_SIZE * sizeof(GameObject));
	for (int i = 0; i < GOARRAY_SIZE; ++i) {
		(goPtr + i)->isActive = FALSE;
	}

	GameObject* goPlayer = GetGameObject();
	goPlayer->isActive = TRUE;
	goPlayer->hasCollider = TRUE;
	goPlayer->type = Type_Player;
	goPlayer->pos = CP_Vector_Set(0.f, 100.f);
	goPlayer->size = CP_Vector_Set(50.f, 50.f);
	goPlayer->color = CP_Color_Create(255, 255, 255, 255);
	player = (Player*)malloc(sizeof(Player));
	player->speed = 10000.f;
	player->vel.x = 0.f;
	player->vel.y = 500.f;
	player->dir.x = 1.f;
	player->dir.y = 0.f;
	player->goPlayer = goPlayer;
	player->markedObject = NULL;
	goPlayer->childData = player;

	GameObject* goProj = GetGameObject();
	goProj->isActive = TRUE;
	goProj->hasCollider = TRUE;
	goProj->type = Type_Proj;
	goProj->size = CP_Vector_Set(20.f, 20.f);
	goProj->color = CP_Color_Create(128, 0, 0, 255);
	projectile = (Projectile*)malloc(sizeof(Projectile));
	projectile->maxRange = 1000.f;
	projectile->range = 0.f;
	projectile->speed = 1000.f;
	projectile->goProj = goProj;
	goProj->childData = projectile;

	GameObject* goEndPoint = GetGameObject();
	goEndPoint->isActive = TRUE;
	goEndPoint->hasCollider = TRUE;
	goEndPoint->type = Type_EndPoint;
	goEndPoint->pos = CP_Vector_Set(2300.f, windowHeight * 0.58);
	goEndPoint->size = CP_Vector_Set(50.f, 100.f);
	goEndPoint->color = CP_Color_Create(75, 0, 130, 255);
	endPoint = (EndPoint*)malloc(sizeof(EndPoint));
	goEndPoint->childData = endPoint;
	endPoint->enemyCount = 0;



	CreateEnemy(750.f, windowHeight * 0.1f);
	CreateEnemy(1800.f, windowHeight * 0.1f);
	CreateEnemy(2550.f, windowHeight * 0.6f);

	CreateDummy(860.f, windowHeight * 0.7f);
	CreateDummy(2750.f, windowHeight * 0.19f);
	//                           button                      door

	CreateButtonDoorLink(CP_Vector_Set(1055.f, windowHeight * 0.875), CP_Vector_Set(1050, windowHeight * 0.09));

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1048.f, 0.f), CP_Vector_Set(54, 95), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(1100.f, windowHeight * 0.09), CP_Vector_Set(10.f, 100.f), OBSTACLE_COLOR);
	CreateButtonDoorLink(CP_Vector_Set(2054.f, windowHeight * 0.28), CP_Vector_Set(3050, windowHeight * 0.12));
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(3048.f, 0.f), CP_Vector_Set(54, 110), PLATFORM_COLOR);

	//                                                pos                         size
	//CreateGameElement(TRUE, Type_Laser, CP_Vector_Set(900.f, 0.f), CP_Vector_Set(10.f, windowHeight), OBSTACLE_COLOR);



	// Platforms
	//BEHIND START 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(-1000.f, 0.f), CP_Vector_Set(1000, windowHeight), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, windowHeight * 0.7), CP_Vector_Set(400, windowHeight * 0.7), PLATFORM_COLOR);


	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(450.f, windowHeight * 0.58), CP_Vector_Set(200, 100), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(750.f, windowHeight * 0.7), CP_Vector_Set(200, windowHeight * 0.7), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(950.f, windowHeight * 0.9), CP_Vector_Set(300, windowHeight * 0.9), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1250.f, windowHeight * 0.7), CP_Vector_Set(200, windowHeight * 0.7), PLATFORM_COLOR);


	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(150.f, windowHeight * 0.45), CP_Vector_Set(200, 80), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(100.f, windowHeight * 0.32), CP_Vector_Set(100, 80), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(320.f, windowHeight * 0.25), CP_Vector_Set(200, 100), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(750.f, windowHeight * 0.2), CP_Vector_Set(450, 100), PLATFORM_COLOR);


	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1750.f, windowHeight * 0.2), CP_Vector_Set(200, 100), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1950.f, windowHeight * 0.3), CP_Vector_Set(300, 100), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2250.f, windowHeight * 0.2), CP_Vector_Set(200, 100), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2250.f, windowHeight * 0.5), CP_Vector_Set(50, windowHeight * 0.9), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2750.f, windowHeight * 0.2), CP_Vector_Set(300, 100), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(3000.f, windowHeight * 0.5), CP_Vector_Set(100, 100), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2850.f, windowHeight * 0.7), CP_Vector_Set(100, 100), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(2400.f, windowHeight * 0.7), CP_Vector_Set(300, 100), PLATFORM_COLOR);


	// AFTER END 
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(3150.f, 0.f), CP_Vector_Set(1000, windowHeight), PLATFORM_COLOR);




	CP_System_SetWindowSize(windowWidth, windowHeight);
}



void Level3_Update() {
	CP_System_SetFrameRate(60);
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

		if (CP_Input_KeyTriggered(KEY_X)) {
			shootPressed = TRUE;

		}
		if (CP_Input_KeyReleased(KEY_X)) {
			shootPressed = FALSE;
		}
		if (CP_Input_KeyTriggered(KEY_Z) && player->markedObject != NULL && player->markedObject->pos.x > 0 && player->markedObject->pos.x < windowWidth) {
			SwapPositions();
			Enemy* e = (Enemy*)player->markedObject->childData;
			e->collidedWithPlatform = FALSE;
			player->markedObject = NULL;
		}

		if (rightPressed) {
			player->dir.x = 1.f;
			player->vel.x = player->speed * CP_System_GetDt();
		}
		else if (leftPressed) {
			player->dir.x = -1.f;
			player->vel.x = -player->speed * CP_System_GetDt();
		}
		else {
			player->vel.x = 0.f;
		}

		if (shootPressed && !projectile->projAlive) {
			projectile->vel.x = player->dir.x * projectile->speed;
			SetProjSpawn(player->goPlayer->pos.x + player->goPlayer->size.x, player->goPlayer->pos.y + player->goPlayer->size.y / 2);
		}



	}
	else {
		//gameover screen
		CP_Graphics_ClearBackground(CP_Color_Create(128, 0, 0, 120));
		RenderScene();
	}

	if (CP_Input_KeyDown(KEY_Q)) {
		rightPressed = FALSE;
		leftPressed = FALSE;
		isGameOver = FALSE;
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
	if (CP_Input_KeyDown(KEY_R)) {
		shootPressed = FALSE;
		rightPressed = FALSE;
		leftPressed = FALSE;
		isGameOver = FALSE;
		CP_Engine_SetNextGameStateForced(Level3_Init, Level3_Update, Level3_Exit);
	}

}


void Level3_Exit() {
	free(goPtr);
	free(player);
	free(projectile);
}