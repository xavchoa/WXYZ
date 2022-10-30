#include <cprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "mainmenu.h"

#define FALSE 0
#define TRUE 1
#define GOARRAY_SIZE 20

int windowWidth, windowHeight;
float const gravity = 750.f;
CP_BOOL isGrounded = FALSE;
CP_BOOL rightPressed = FALSE;
CP_BOOL leftPressed = FALSE;
CP_BOOL shootPressed = FALSE;
CP_BOOL projAlive = FALSE;

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
			//case Type_Platform:	
			//	float intwidth = go->pos.x + go->size.x - go2->pos.x;
			//	float intheight = go->pos.y + go->size.y - go2->size.y;

			//	if (intwidth < intheight) {
			//		go->pos.x -= intwidth;
			//	} else {
			//		player->vel.y = 0.f;
			//		go->pos.y -= intheight;
			//	}
			//	break;
		case Type_EndPoint:
			endPoint = (EndPoint*)go2->childData;
			if (endPoint->winCondition == TRUE) {
				//next level
				printf("you win");
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
	case 2:
		switch (go2->type) {
		case 0:
			break;
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

	//if (collisionX && collisionY) {
	//	if (go->pos.x < go2->pos.x) {
	//		float dist = (go->pos.x + go->size.x) - go2->pos.x;
	//		go->pos.x -= dist;
	//	}
	//	else if (go->pos.x > go2->pos.x) {
	//		float dist = (go2->pos.x + go2->size.x) - go->pos.x;
	//		go->pos.x += dist;
	//	}
	//}



	//if (go->pos.x + go->size.x >= go2->pos.x &&
	//	go2->pos.x + go2->size.x >= go->pos.x && 
	//	go->pos.y + go->size.y >= go2->pos.y &&
	//	go2->pos.y + go2->size.y >= go->pos.y) {

	//	float intwidth = go->pos.x + go->size.x - go2->pos.x;
	//	float intheight = go->pos.y + go->size.y - go2->pos.y;

	//	if (intwidth < intheight) {
	//		go->pos.x -= intwidth;
	//	} else {
	//		player->vel.y = 0.f;
	//		go->pos.y -= intheight;
	//	}
	//}

	//
	//float intwidth = go->pos.x + go->size.x - go2->pos.x;
	//float intheight = go->pos.y + go->size.y - go2->pos.y;

	//if (go2->size.x < go2->size.y) {
	//	if (go->pos.x + go->size.x > go2->pos.x) {
	//		go->pos.x
	//	}
	//}


	//if () {
	//	if (go->pos.y > go2->pos.y) {
	//		go->pos.y = go2->pos.y - go->size.y;
	//		printf("%f", go->pos.x);
	//	}
	//}

	//if (player.pos.y + player.height <= y && player.pos.y + player.height + player.vel.y * CP_System_GetDt() >= y &&
	//	player.pos.x + player.width >= x && player.pos.x <= x+width) {
	//	player.vel.y = 0.f;
	//	isGrounded = TRUE;
	//}
	//if (player.pos.y <= y + height && player.pos.y - player.vel.y * CP_System_GetDt() >= y + height &&
	//	player.pos.x + player.width >= x && player.pos.x <= x + width) {
	//		player.vel.y = 0.f;
	//}

	//if (player.pos.x + player.width >= x && player.pos.x <= x+ width &&
	//	player.pos.y + player.height >= y && player.pos.y <= y + height &&
	//	player.pos.x + player.width + player.vel.x * CP_System_GetDt() >= x && player.pos.x + player.vel.x * CP_System_GetDt() <= x + width) {
	//		player.vel.x = 0.f;
	//}

	if (go->type == Type_Player && go2->type == Type_Platform) {
		if (go->pos.y + go->size.y <= go2->pos.y && go->pos.y + go->size.y + player->vel.y * CP_System_GetDt() >= go2->pos.y &&
			go->pos.x + go->size.x >= go2->pos.x && go->pos.x <= go2->pos.x + go2->size.x) {
			player->vel.y = 0.f;
			isGrounded = TRUE;
		}
		if (go->pos.y <= go2->pos.y + go2->size.y && go->pos.y - player->vel.y * CP_System_GetDt() >= go2->pos.y + go2->size.y &&
			go->pos.x + go->size.x >= go2->size.x && go->pos.x <= go2->pos.x + go2->size.x) {
			player->vel.y = 0.f;
		}

		if (go->pos.x + go->size.x >= go2->pos.x && go->pos.x <= go2->pos.x + go2->size.x &&
			go->pos.y + go->size.y >= go2->pos.y && go->pos.y <= go2->pos.y + go2->size.y &&
			go->pos.x + go->size.x + player->vel.x * CP_System_GetDt() >= go2->pos.x && go->pos.x + player->vel.x * CP_System_GetDt() <= go2->pos.x + go2->size.x) {

			player->vel.x = 0;
		}
		return;
	}



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

void CreatePlatform(float x, float y, float width, float height) {
	GameObject* goPlatform = GetGameObject();
	goPlatform->isActive = TRUE;
	goPlatform->hasCollider = TRUE;
	goPlatform->type = Type_Platform;
	goPlatform->pos = CP_Vector_Set(x, y);
	goPlatform->size = CP_Vector_Set(width, height);
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
	goEnemy->childData = enemy;
}

void DrawPlatform(GameObject* self) {
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(self->pos.x, self->pos.y, self->size.x, self->size.y);
}

void DrawProjectile(GameObject* self) {
	CP_Settings_Fill(CP_Color_Create(120, 0, 0, 255));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_DrawRect(self->pos.x, self->pos.y, self->size.x, self->size.y);
}

void DrawPlayer(GameObject* self) {
	CP_Settings_Fill(self->color);
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(self->pos.x, self->pos.y, self->size.x, self->size.y);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
}

void DrawEnemy(GameObject* self) {
	CP_Settings_Fill(self->color);
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(self->pos.x, self->pos.y, self->size.x, self->size.y);
	CP_Settings_Fill(CP_Color_Create(50, 50, 50, 255));
}

void DrawEndPoint(GameObject* self) {
	CP_Settings_Fill(self->color);
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(self->pos.x, self->pos.y, self->size.x, self->size.y);
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

	CreateEnemy(1000.f, 660.f);

	CreatePlatform(500.f, windowHeight * 0.9, 5000.f, 200.f);
	CreatePlatform(1000.f, windowHeight * 0.8, 100, 100.f);
	CreatePlatform(200.f, windowHeight * 0.8, 100, 100.f);

	CP_System_SetWindowSize(windowWidth, windowHeight);
}

void UpdateProjectile(GameObject* self) {
	self->pos.x += projectile->vel.x * CP_System_GetDt();
	projectile->range += projectile->vel.x * CP_System_GetDt();
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
			if ((goPtr + i)->type == Type_Player)
				DrawPlayer((goPtr + i));
			else if ((goPtr + i)->type == Type_Platform)
				DrawPlatform((goPtr + i));
			else if ((goPtr + i)->type == Type_Enemy)
				DrawEnemy(goPtr + i);
			else if ((goPtr + i)->type == Type_EndPoint)
				DrawEndPoint(goPtr + i);
			else if ((goPtr + i)->type == Type_Proj && projAlive) {
				DrawProjectile((goPtr + i));
				UpdateProjectile((goPtr + i));
				if (abs(projectile->range) >= projectile->maxRange) {
					projectile->range = 0.f;
					projAlive = FALSE;
				}
			}
		}
	}

	//simulate gravity
	player->goPlayer->pos.y += player->vel.y * CP_System_GetDt();
	player->goPlayer->pos.x += player->vel.x * CP_System_GetDt();


	if ((player->goPlayer->size.y + player->goPlayer->pos.y + player->vel.y * CP_System_GetDt()) <= windowHeight) {
		player->vel.y += gravity * CP_System_GetDt();
	}
	else {
		player->vel.y = 0.f;
		isGrounded = TRUE;
	}

	//player movement
	if (CP_Input_KeyTriggered(KEY_SPACE) && isGrounded) {
		player->vel.y -= 15000.f * CP_System_GetDt();
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

	if (CP_Input_KeyTriggered(KEY_X)) {
		shootPressed = TRUE;

	}
	if (CP_Input_KeyReleased(KEY_X)) {
		shootPressed = FALSE;
	}
	if (CP_Input_KeyTriggered(KEY_Z) && player->markedObject != NULL) {
		SwapPositions();
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

	//if (rightPressed && player->goPlayer->pos.x )

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