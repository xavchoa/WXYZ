#include <cprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "mainmenu.h"
#include "level.h"

#define FALSE 0
#define TRUE 1
#define GOARRAY_SIZE 20
#define PLATFORM_COLOR CP_Color_Create(0, 0, 0, 50)
#define ENEMY_COLOR CP_Color_Create(100, 100, 100, 255)

int windowWidth, windowHeight;
float const gravity = 1000.f;
CP_BOOL isGrounded = FALSE;
CP_BOOL rightPressed = FALSE;
CP_BOOL leftPressed = FALSE;
CP_BOOL shootPressed = FALSE;
CP_BOOL projAlive = FALSE;
CP_BOOL isPlatformCollided = FALSE;

enum GAMEOBJECT_TYPE {
	Type_Player,
	Type_Proj,
	Type_Enemy,
	Type_EnemyProj,
	Type_Dummy,
	Type_Barrel,
	Type_Button,
	Type_Door,
	Type_Platform,
	Type_EndPoint,
	Type_None
};

typedef struct GameObject {

	CP_BOOL isActive;

	CP_Vector pos;
	CP_Vector size;
	CP_Color color;

	void* childData;

	CP_BOOL hasCollider;

	enum GAMEOBJECT_TYPE type;

} GameObject;


typedef struct Player {
	CP_Vector vel;
	CP_Vector dir;
	float speed;
	GameObject* goPlayer;
	GameObject* markedObject;

} Player;

typedef struct Enemy {
	CP_Vector vel;
	CP_Vector dir;
	float speed;
	CP_BOOL collidedWithPlatform;
	GameObject* goEnemy;
} Enemy;

typedef struct Projectile {
	CP_Vector vel;
	float maxRange;
	float range;
	float speed;
	GameObject* goProj;

} Projectile;

typedef struct EnemyProjectile {
	CP_Vector vel;
	float range;
	float speed;

} EnemyProjectile;

typedef struct EndPoint {
	CP_BOOL winCondition;

} EndPoint;

typedef struct Platform {
	CP_BOOL isMovable;
	CP_Vector vel;
	float speed;
} Platform;

typedef struct Button {
	CP_BOOL isPushed;

} Button;

GameObject* goPtr;

Player* player;
Projectile* projectile;
EndPoint* endPoint;

GameObject* GetGameObject() {
	for (int i = 0; i < GOARRAY_SIZE; ++i) {
		if (!(goPtr + i)->isActive) {
			return (goPtr + i);
		}
	}
	return;
}

void PlayerMovement() {
	//player movement
	if (CP_Input_KeyDown(KEY_SPACE) && isGrounded) {
		player->vel.y -= 13000.f * CP_System_GetDt();
		isGrounded = FALSE;
	}
	if (CP_Input_KeyDown(KEY_LEFT)) {
		leftPressed = TRUE;
	}
	if (CP_Input_KeyReleased(KEY_LEFT)) {
		leftPressed = FALSE;
	}

	if (CP_Input_KeyDown(KEY_RIGHT)) {
		rightPressed = TRUE;
	}
	if (CP_Input_KeyReleased(KEY_RIGHT)) {
		rightPressed = FALSE;
	}
}
void DespawnGameObject(GameObject* go) {
	go->isActive = FALSE;
	go->hasCollider = FALSE;
	go->type = Type_None;
	go->pos = CP_Vector_Set(0, 0);
	go->size = CP_Vector_Set(0, 0);
	go->childData = NULL;
}

void CollisionResponse(GameObject* go, GameObject* go2) {
	switch (go->type) {
	case Type_Player:
		switch (go2->type) {
		case Type_Platform:
			//isPlatformCollided = TRUE;
			if (go->pos.x + go->size.x <= go2->pos.x + go2->size.x) {
				float intwidth = go->pos.x + go->size.x - go2->pos.x;

				if (go->pos.y > go2->pos.y) {
					float intheight = go2->pos.y + go2->size.y - go->pos.y;

					if (intwidth < intheight) {
						go->pos.x -= intwidth;
					}
					else {
						player->vel.y = 0.f;
						go->pos.y += intheight + 1;
						//go->hasGravity = FALSE;
						//go->hasCollider = FALSE;
						//isGrounded = TRUE;
					}
				}
				else {
					float intheight = go->pos.y + go->size.y - go2->pos.y;

					if (intwidth < intheight) {
						go->pos.x -= intwidth;
					}
					else {
						player->vel.y = 0.f;
						go->pos.y -= intheight + 1;
						//go->hasGravity = FALSE;
						//go->hasCollider = FALSE;
						isGrounded = TRUE;
					}
				}
			}
			else {
				float intwidth = go2->pos.x + go2->size.x - go->pos.x;

				if (go->pos.y > go2->pos.y) {
					float intheight = go2->pos.y + go2->size.y - go->pos.y;

					if (intwidth < intheight) {
						go->pos.x += intwidth;
					}
					else {
						player->vel.y = 0.f;
						go->pos.y += intheight + 1;
						//go->hasGravity = FALSE;
						//go->hasCollider = FALSE;
						//isGrounded = TRUE;
					}
				}
				else {
					float intheight = go->pos.y + go->size.y - go2->pos.y;

					if (intwidth < intheight) {
						go->pos.x += intwidth;
					}
					else {
						player->vel.y = 0.f;
						go->pos.y -= intheight + 1;
						//go->hasGravity = FALSE;
						//go->hasCollider = FALSE;
						isGrounded = TRUE;
					}
				}
			}
			break;
		case Type_EndPoint:
			endPoint = (EndPoint*)go2->childData;
			if (endPoint->winCondition == TRUE) {
				//next level
				printf("you win");

				//todo: go next level when player is inbetween the box aka door
				//CP_Engine_SetNextGameState(Level1_Init, Level1_Update, Level1_Exit);

				//if (player->goPlayer->pos.x + player->goPlayer->size.x > endPoint->goEndPoint->pos.x + endPoint->goEndPoint->size.x/2) {

				//	CP_Engine_SetNextGameState(Level1_Init, Level1_Update, Level1_Exit);

				//}

			}
			break;

		}
		break;
	case Type_Proj:
		switch (go2->type) {
		case Type_Platform:
			//DespawnGameObject(go);
			projAlive = FALSE;
			break;
		case Type_Dummy:
			break;
		case Type_Enemy:
			player->markedObject = go2;
			projAlive = FALSE;
			break;
		}
		projectile->range = 0;
		break;
	case Type_Enemy:
		switch (go2->type) {
		case Type_Platform: { //enemy and platform collision
			Enemy* e = (Enemy*)go->childData;
			e->collidedWithPlatform = TRUE;
			e->vel.y = 0;
			if (go->pos.y < go2->pos.y) {
				float intheight = go->pos.y + go->size.y - go2->pos.y;
				go->pos.y -= intheight - 1;
			}
			break;
		}
		case 1:
			break;
		}
		break;
	}
}

CP_BOOL CheckCollision(GameObject* go, GameObject* go2) {
	if (go->type == go2->type)
		return FALSE;

	CP_BOOL collisionX = go->pos.x + go->size.x >= go2->pos.x &&
		go2->pos.x + go2->size.x >= go->pos.x;

	CP_BOOL collisionY = go->pos.y + go->size.y >= go2->pos.y &&
		go2->pos.y + go2->size.y >= go->pos.y;

	return collisionX && collisionY;
}

void SwapPositions() {
	CP_Vector tmp = player->markedObject->pos;
	player->markedObject->pos = player->goPlayer->pos;
	player->goPlayer->pos = tmp;
}
void SetProjSpawn(float x, float y) {
	projectile->goProj->pos.x = x;
	projectile->goProj->pos.y = y;
	projAlive = TRUE;
}

void CreateGameElement(CP_BOOL collider, enum GAMEOBJECT_TYPE type, CP_Vector pos, CP_Vector size, CP_Color color) {
	GameObject* go = GetGameObject();
	go->isActive = TRUE;
	go->hasCollider = collider;
	go->type = type;
	go->pos = pos;
	go->size = size;
	go->color = color;
	switch (type) {
	case Type_Enemy: {
		Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
		enemy->vel = CP_Vector_Set(0, 0);
		enemy->collidedWithPlatform = FALSE;
		enemy->goEnemy = go;
		go->childData = enemy;
	}
		break;
	case Type_Dummy:
		break;
	case Type_Barrel:
		break;
	case Type_Button: {
		Button* button = (Button*)malloc(sizeof(Button));
		button->isPushed = FALSE;
		go->childData = button;
		break;
	}
	case Type_Door:
		break;
	case Type_Platform: {
		Platform* platform = (Platform*)malloc(sizeof(Platform));
		go->childData = platform;
		break;
	}
	case Type_EndPoint:
		break;
	case Type_None:
		break;
	default:
		break;
	}
}


#ifndef CREATE_CODE

void CreatePlatform(float x, float y, float width, float height) {

	GameObject* goPlatform = GetGameObject();
	goPlatform->isActive = TRUE;
	goPlatform->hasCollider = TRUE;
	goPlatform->type = Type_Platform;
	goPlatform->pos = CP_Vector_Set(x, y);
	goPlatform->size = CP_Vector_Set(width, height);
	goPlatform->color = CP_Color_Create(0, 0, 0, 50);
	Platform* platform = (Platform*)malloc(sizeof(Platform));
	platform->vel = CP_Vector_Set(0, 0);

	goPlatform->childData = platform;
}

void CreateEnemy(float x, float y) {
	GameObject* goEnemy = GetGameObject();
	goEnemy->isActive = TRUE;
	goEnemy->hasCollider = TRUE;
	goEnemy->type = Type_Enemy;
	goEnemy->pos = CP_Vector_Set(x, y);
	goEnemy->size = CP_Vector_Set(50.f, 50.f);
	goEnemy->color = CP_Color_Create(100, 100, 100, 255);
	Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
	enemy->vel = CP_Vector_Set(0, 0);
	enemy->collidedWithPlatform = FALSE;
	enemy->goEnemy = goEnemy;
	goEnemy->childData = enemy;
}

void CreateButton(float x, float y) {
	GameObject* goButton = GetGameObject();
	goButton->isActive = TRUE;
	goButton->hasCollider = TRUE;
	goButton->type = Type_Enemy;
	goButton->pos = CP_Vector_Set(x, y);
	goButton->size = CP_Vector_Set(70.f, 20.f);
	goButton->color = CP_Color_Create(100, 100, 100, 255);
	Button* button = (Button*)malloc(sizeof(Button));
	button->isPushed = FALSE;
	goButton->childData = button;
}

#endif


void DrawGameElements(GameObject* self) {
	CP_Settings_Fill(self->color);
	if (self->type == Type_Proj) {
		CP_Settings_RectMode(CP_POSITION_CENTER);
	}
	else {
		CP_Settings_RectMode(CP_POSITION_CORNER);
	}
	CP_Graphics_DrawRect(self->pos.x, self->pos.y, self->size.x, self->size.y);
}

void UpdateProjectile(GameObject* self) {
	if (abs(projectile->range) >= projectile->maxRange) {
		projectile->range = 0.f;
		projAlive = FALSE;
	}

	self->pos.x += projectile->vel.x * CP_System_GetDt();
	projectile->range += projectile->vel.x * CP_System_GetDt();
}

void UpdateEnemy(GameObject* self) {
	Enemy* e = (Enemy*)self->childData;
	if (e->collidedWithPlatform == FALSE)
		e->vel.y += gravity * CP_System_GetDt();

	self->pos.y += e->vel.y * CP_System_GetDt();
	//self->pos.x += e->vel.x * CP_System_GetDt();
}

void Level_Init() {
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
	goPlayer->color = CP_Color_Create(255, 255, 255, 255);
	player = (Player*)malloc(sizeof(Player));
	player->speed = 7000.f;
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
	goEndPoint->pos = CP_Vector_Set(1500.f, 700.f);
	goEndPoint->size = CP_Vector_Set(60.f, 100.f);
	goEndPoint->color = CP_Color_Create(250, 60, 60, 255);
	endPoint = (EndPoint*)malloc(sizeof(EndPoint));
	endPoint->winCondition = TRUE;
	goEndPoint->childData = endPoint;

	CreateEnemy(1000.f, 300.f);
	CreateEnemy(700.f, 300.f);
	//CreateButton(600.f, windowHeight * 0.89);


	// Platforms
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(500.f, windowHeight * 0.9), CP_Vector_Set(5000.f, 200.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1000.f, windowHeight * 0.8), CP_Vector_Set(100.f, 100.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(200.f, windowHeight * 0.8), CP_Vector_Set(100.f, 100.f), PLATFORM_COLOR);

	// Enemies
	//CreateGameElement(TRUE, Type_Enemy, CP_Vector_Set(1000.f, 300.f), CP_Vector_Set(50.f, 50.f), ENEMY_COLOR);
	//CreateGameElement(TRUE, Type_Enemy, CP_Vector_Set(700.f, 300.f), CP_Vector_Set(50.f, 50.f), ENEMY_COLOR);

	CP_System_SetWindowSize(windowWidth, windowHeight);
}

void SideScrolling(GameObject* self) {
	if (player->goPlayer->pos.x >= 800 && rightPressed) {
		self->pos.x -= player->speed * CP_System_GetDt() * CP_System_GetDt();
		player->vel.x = 0;
	}
	else if (player->goPlayer->pos.x <= 400 && leftPressed) {
		self->pos.x += player->speed * CP_System_GetDt() * CP_System_GetDt();
		player->vel.x = 0;
	}
}

void RenderScene() {
	for (int i = 0; i < GOARRAY_SIZE; ++i) {
		if ((goPtr + i)->isActive) {
			if ((goPtr + i)->type == Type_Proj) {
				if (projAlive)
					DrawGameElements((goPtr + i));
			}
			else
				DrawGameElements((goPtr + i));
		}
		
	}
}


void Level_Update() {
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
				SideScrolling((goPtr + i));
			}
			else if ((goPtr + i)->type == Type_Enemy) {
				SideScrolling((goPtr + i));
				UpdateEnemy(goPtr + i);
			}
			else if ((goPtr + i)->type == Type_EndPoint) {
				SideScrolling((goPtr + i));
			}
			else if ((goPtr + i)->type == Type_Proj && projAlive) {
				UpdateProjectile(goPtr + i);
			}
		}
	}

	RenderScene();

	//simulate gravity
	player->goPlayer->pos.y += player->vel.y * CP_System_GetDt();
	player->goPlayer->pos.x += player->vel.x * CP_System_GetDt();


	if (player->goPlayer->size.y + player->goPlayer->pos.y <= windowHeight) {
		player->vel.y += gravity * CP_System_GetDt();
	}
	else {
		player->goPlayer->pos.y -= player->goPlayer->pos.y + player->goPlayer->size.y - windowHeight;
		player->vel.y = 0.f;
		isGrounded = TRUE;
	}

	PlayerMovement();

	if (CP_Input_KeyTriggered(KEY_X)) {
		shootPressed = TRUE;

	}
	if (CP_Input_KeyReleased(KEY_X)) {
		shootPressed = FALSE;
	}
	if (CP_Input_KeyTriggered(KEY_Z) && player->markedObject != NULL) {
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

	if (shootPressed && !projAlive) {
		projectile->vel.x = player->dir.x * projectile->speed;
		SetProjSpawn(player->goPlayer->pos.x + player->goPlayer->size.x, player->goPlayer->pos.y + player->goPlayer->size.y / 2);
	}

	if (CP_Input_KeyDown(KEY_Q)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}


void Level_Exit() {
	free(goPtr);
	free(player);
	free(projectile);
}

//void Level1_Init() {
//	goPtr = (GameObject*)malloc(GOARRAY_SIZE * sizeof(GameObject));
//	for (int i = 0; i < GOARRAY_SIZE; ++i) {
//		(goPtr + i)->isActive = FALSE;
//	}
//
//
//	GameObject* goProj = GetGameObject();
//	goProj->isActive = TRUE;
//	goProj->hasCollider = TRUE;
//	goProj->type = Type_Proj;
//	goProj->size = CP_Vector_Set(20.f, 20.f);
//	goProj->color = CP_Color_Create(128, 0, 0, 255);
//	projectile = (Projectile*)malloc(sizeof(Projectile));
//	projectile->maxRange = 1000.f;
//	projectile->range = 0.f;
//	projectile->speed = 1000.f;
//	projectile->goProj = goProj;
//	goProj->childData = projectile;
//
//	GameObject* goEndPoint = GetGameObject();
//	goEndPoint->isActive = TRUE;
//	goEndPoint->hasCollider = TRUE;
//	goEndPoint->type = Type_EndPoint;
//	goEndPoint->pos = CP_Vector_Set(1850.f, windowHeight * 0.55f);
//	goEndPoint->size = CP_Vector_Set(60.f, 100.f);
//	goEndPoint->color = CP_Color_Create(250, 60, 60, 255);
//	endPoint = (EndPoint*)malloc(sizeof(EndPoint));
//	endPoint->winCondition = TRUE;
//	goEndPoint->childData = endPoint;
//
//
//	GameObject* goPlayer = GetGameObject();
//	goPlayer->isActive = TRUE;
//	goPlayer->hasCollider = TRUE;
//	goPlayer->type = Type_Player;
//	goPlayer->pos = CP_Vector_Set(0.f, 100.f);
//	goPlayer->size = CP_Vector_Set(50.f, 50.f);
//	goPlayer->color = CP_Color_Create(255, 255, 255, 255);
//	player = (Player*)malloc(sizeof(Player));
//	player->speed = 7000.f;
//	player->vel.x = 0.f;
//	player->vel.y = 500.f;
//	player->dir.x = 1.f;
//	player->dir.y = 0.f;
//	player->goPlayer = goPlayer;
//	player->markedObject = NULL;
//	goPlayer->childData = player;
//
//	CreateEnemy(1850.f, windowHeight * 0.6f);
//
//	CreatePlatform(0.f, windowHeight * 0.9, 200, 100.f);
//	CreatePlatform(400.f, windowHeight * 0.9, 300.f, 200.f);
//	CreatePlatform(700.f, windowHeight * 0.8, 100, 250.f);
//	CreatePlatform(800.f, windowHeight * 0.7, 100, 350.f);
//	CreatePlatform(900.f, windowHeight * 0.6, 100, 450.f);
//
//	CreatePlatform(1100.f, windowHeight * 0.5, 100, 90.f);
//	CreatePlatform(1250.f, windowHeight * 0.4, 100, 90.f);
//	CreatePlatform(1400.f, windowHeight * 0.3, 100, 90.f);
//
//	CreatePlatform(1500.f, windowHeight * 0.65, 100, 90.f);
//	CreatePlatform(1850.f, windowHeight * 0.65, 300, 90.f);
//
//
//	CP_System_SetWindowSize(windowWidth, windowHeight);
//}
//
//
//void Level1_Update() {
//	CP_Graphics_ClearBackground(CP_Color_Create(240, 200, 200, 255));
//	for (int x = 0; x < GOARRAY_SIZE; ++x) {
//		if ((goPtr + x)->isActive && (goPtr + x)->hasCollider) {
//			for (int y = x + 1; y < GOARRAY_SIZE; ++y) {
//				if ((goPtr + y)->isActive && (goPtr + y)->hasCollider) {
//					if (CheckCollision((goPtr + x), (goPtr + y))) {
//						CollisionResponse((goPtr + x), (goPtr + y));
//					}
//				}
//			}
//		}
//	}
//
//	for (int i = 0; i < GOARRAY_SIZE; ++i) {
//		if ((goPtr + i)->isActive) {
//			if ((goPtr + i)->type == Type_Player)
//				DrawPlayer((goPtr + i));
//			else if ((goPtr + i)->type == Type_Platform) {
//				if (rightPressed && !isPlatformCollided) { //side scrolling
//					//(goPtr + i)->pos.x -= player->vel.x * CP_System_GetDt();
//				}
//				DrawPlatform((goPtr + i));
//			} else if ((goPtr + i)->type == Type_Enemy) {
//				DrawEnemy(goPtr + i);
//				//goPtr->pos.y += gravity * CP_System_GetDt();
//			} else if ((goPtr + i)->type == Type_EndPoint)
//				DrawEndPoint(goPtr + i);
//			else if ((goPtr + i)->type == Type_Proj && projAlive) {
//				DrawProjectile((goPtr + i));
//				UpdateProjectile((goPtr + i));
//				if (abs(projectile->range) >= projectile->maxRange) {
//					projectile->range = 0.f;
//					projAlive = FALSE;
//				}
//			}
//		}
//	}
//
//	//simulate gravity
//	player->goPlayer->pos.y += player->vel.y * CP_System_GetDt();
//	player->goPlayer->pos.x += player->vel.x * CP_System_GetDt();
//
//
//	if ((player->goPlayer->size.y + player->goPlayer->pos.y + player->vel.y * CP_System_GetDt()) <= windowHeight) {
//		player->vel.y += gravity * CP_System_GetDt();
//	} else {
//		player->vel.y = 0.f;
//		isGrounded = TRUE;
//	}
//
//	PlayerMovement();
//
//	if (CP_Input_KeyTriggered(KEY_X)) {
//		shootPressed = TRUE;
//
//	}
//	if (CP_Input_KeyReleased(KEY_X)) {
//		shootPressed = FALSE;
//	}
//	if (CP_Input_KeyTriggered(KEY_Z) && player->markedObject != NULL) {
//		SwapPositions();
//		player->markedObject = NULL;
//	}
//
//
//	if (rightPressed) {
//		player->dir.x = 1.f;
//		player->vel.x = player->speed * CP_System_GetDt();
//	} else if (leftPressed) {
//		player->dir.x = -1.f;
//		player->vel.x = -player->speed * CP_System_GetDt();
//	} else {
//		player->vel.x = 0.f;
//	}
//
//
//	//if (rightPressed && player->goPlayer->pos.x )
//
//	if (shootPressed && !projAlive) {
//		projectile->vel.x = player->dir.x * projectile->speed;
//		SetProjSpawn(player->goPlayer->pos.x + player->goPlayer->size.x, player->goPlayer->pos.y + player->goPlayer->size.y / 2);
//	}
//
//	if (CP_Input_KeyDown(KEY_Q)) {
//		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
//	}
//}
//
//void Level1_Exit() {
//	free(goPtr);
//	free(player);
//	free(projectile);
//}