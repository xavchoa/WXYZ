#include <cprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "mainmenu.h"
#include "level.h"

#define FALSE 0
#define TRUE 1
#define GOARRAY_SIZE 500
#define PLATFORM_COLOR CP_Color_Create(0, 0, 0, 50)
#define OBSTACLE_COLOR CP_Color_Create(128, 0, 0, 50)
#define ENEMY_COLOR CP_Color_Create(100, 100, 100, 255)

int windowWidth, windowHeight;
float const gravity = 980.f;
CP_BOOL isGrounded = FALSE;
CP_BOOL rightPressed = FALSE;
CP_BOOL leftPressed = FALSE;
CP_BOOL shootPressed = FALSE;
CP_BOOL isPlatformCollided = FALSE;
CP_BOOL isGameOver = FALSE;

enum GAMEOBJECT_TYPE {
	Type_Player,
	Type_Proj,
	Type_Enemy,
	Type_EnemyProj,
	Type_Dummy,
	Type_Barrel,
	Type_Explosion,
	Type_Button,
	Type_Door,
	Type_Platform,
	Type_Obstacle,
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

	float bt; //time between bullets
} Enemy;

typedef struct Dummy {
	
	CP_Vector vel;
} Dummy;
typedef struct Projectile {
	CP_Vector vel;
	CP_Vector dir;
	float maxRange;
	float range;
	float speed;
	GameObject* goProj;
	CP_BOOL projAlive;

} Projectile;

typedef struct EndPoint {
	int enemyCount;
} EndPoint;

typedef struct Platform {
	CP_Vector vel;
	float speed;
} Platform;

typedef struct Barrel {
	CP_BOOL isExploded;

} Barrel;

typedef struct Door {
	CP_BOOL isOpened;

} Door;

typedef struct Button {
	//CP_BOOL isPushed;
	Door* linkedDoor;

} Button;

GameObject* goPtr;

Player* player;
Projectile* projectile;
EndPoint* endPoint;

GameObject* GetGameObject() {
	for (int i = 0; i < GOARRAY_SIZE; ++i) {
		if (!(goPtr + i)->isActive) {
			(goPtr + i)->isActive = TRUE;
			return (goPtr + i);
		}
	}
	return;
}

void PlayerMovement() {
	//player movement
	if (CP_Input_KeyDown(KEY_SPACE) && isGrounded) {
		player->vel.y -= 500.f;
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
		case Type_Platform: {
			if (go->pos.x + go->size.x <= go2->pos.x + go2->size.x) {
				float intWidth = go->pos.x + go->size.x - go2->pos.x;

				if (go->pos.y > go2->pos.y) {
					float intHeight = go2->pos.y + go2->size.y - go->pos.y;

					if (intWidth < intHeight) {
						go->pos.x -= intWidth;
					}
					else {
						player->vel.y = 0.f;
						go->pos.y += intHeight + 0.1f;
					}
				}
				else {
					float intHeight = go->pos.y + go->size.y - go2->pos.y;

					if (intWidth < intHeight) {
						go->pos.x -= intWidth;
					}
					else {
						player->vel.y = 0.f;
						go->pos.y -= intHeight + 0.1f;
						isGrounded = TRUE;
					}
				}
			}
			else {
				float intWidth = go2->pos.x + go2->size.x - go->pos.x;

				if (go->pos.y > go2->pos.y) {
					float intHeight = go2->pos.y + go2->size.y - go->pos.y;

					if (intWidth < intHeight) {
						go->pos.x += intWidth;
					}
					else {
						player->vel.y = 0.f;
						go->pos.y += intHeight + 0.1f;
					}
				}
				else {
					float intHeight = go->pos.y + go->size.y - go2->pos.y;

					if (intWidth < intHeight) {
						go->pos.x += intWidth;
					}
					else {
						player->vel.y = 0.f;
						go->pos.y -= intHeight + 0.1f;
						isGrounded = TRUE;
					}
				}
			}
			break;
		}
		case Type_EndPoint: {
			endPoint = (EndPoint*)go2->childData;
			if (endPoint->enemyCount == 0) {
				printf("you win");
				//next level

				//todo: go next level when player is inbetween the box aka door
				CP_Engine_SetNextGameState(Level1_Init, Level1_Update, Level1_Exit);

				//if (player->goPlayer->pos.x + player->goPlayer->size.x > endPoint->goEndPoint->pos.x + endPoint->goEndPoint->size.x/2) {

				//	CP_Engine_SetNextGameState(Level1_Init, Level1_Update, Level1_Exit);

				//}

				break;
			}
		}
						  break;
		case Type_Button: { //player-button collision
			Button* b = (Button*)go2->childData;
			Door* door = b->linkedDoor;
			door->isOpened = TRUE;
			break;
		}
		case Type_EnemyProj: {
			isGameOver = TRUE;
			break;
		}
		case Type_Door: {
			if (go->pos.x + go->size.x <= go2->pos.x + go2->size.x) {
				float intWidth = go->pos.x + go->size.x - go2->pos.x;

				if (go->pos.y > go2->pos.y) {
					float intHeight = go2->pos.y + go2->size.y - go->pos.y;

					if (intWidth < intHeight) {
						go->pos.x -= intWidth;
					}
					else {
						player->vel.y = 0.f;
						go->pos.y += intHeight + 0.1f;
					}
				}
				else {
					float intHeight = go->pos.y + go->size.y - go2->pos.y;

					if (intWidth < intHeight) {
						go->pos.x -= intWidth;
					}
					else {
						player->vel.y = 0.f;
						go->pos.y -= intHeight + 0.1f;
						isGrounded = TRUE;
					}
				}
			}
			else {
				float intWidth = go2->pos.x + go2->size.x - go->pos.x;

				if (go->pos.y > go2->pos.y) {
					float intHeight = go2->pos.y + go2->size.y - go->pos.y;

					if (intWidth < intHeight) {
						go->pos.x += intWidth;
					}
					else {
						player->vel.y = 0.f;
						go->pos.y += intHeight + 0.1f;
					}
				}
				else {
					float intHeight = go->pos.y + go->size.y - go2->pos.y;

					if (intWidth < intHeight) {
						go->pos.x += intWidth;
					}
					else {
						player->vel.y = 0.f;
						go->pos.y -= intHeight + 0.1f;
						isGrounded = TRUE;
					}
				}
			}
			break;
		}
		}
		break;
	case Type_Platform:
		switch (go2->type) {
		case Type_EnemyProj: //enemy proj-platform collision
			DespawnGameObject(go2);
			break;
		}
		break;
		
	
	case Type_Proj:
		switch (go2->type) {
		case Type_Platform: //player proj-platform collision
			projectile->projAlive = FALSE;
			break;
		case Type_Dummy:
			player->markedObject = go2;
			projectile->projAlive = FALSE;
			break;
		case Type_Enemy:	//player proj - enemy collision
			player->markedObject = go2;
			projectile->projAlive = FALSE;
			break;
		case Type_Door:
			projectile->projAlive = FALSE;
			break;
		}
		projectile->range = 0;
		break;
	case Type_Enemy:
		switch (go2->type) {
			case Type_Platform: { //enemy - platform collision
			Enemy* e = (Enemy*)go->childData;
			//e->collidedWithPlatform = TRUE;
			e->vel.y = 0;
			if (go->pos.x + go->size.x <= go2->pos.x + go2->size.x) {
				float intWidth = go->pos.x + go->size.x - go2->pos.x; //intersecting width

				if (go->pos.y > go2->pos.y) {
					float intHeight = go2->pos.y + go2->size.y - go->pos.y; //intersecting height

					if (intWidth < intHeight)
						go->pos.x -= intWidth;
					else {
						e->vel.y = 0.f;
						go->pos.y += intHeight;
					}
				}
				else {
					float intHeight = go->pos.y + go->size.y - go2->pos.y;

					if (intWidth < intHeight)
						go->pos.x -= intWidth;
					else
						go->pos.y -= intHeight;
				}
			}
			else {
				float intWidth = go2->pos.x + go2->size.x - go->pos.x;

				if (go->pos.y > go2->pos.y) {
					float intHeight = go2->pos.y + go2->size.y - go->pos.y;

					if (intWidth < intHeight) {
						go->pos.x += intWidth;
					}
					else {
						e->vel.y = 0.f;
						go->pos.y += intHeight;
					}
				}
				else {
					float intHeight = go->pos.y + go->size.y - go2->pos.y;

					if (intWidth < intHeight) {
						go->pos.x += intWidth;
					}
					else {
						e->vel.y = 0.f;
						go->pos.y -= intHeight;
					}
				}
			}
			break;
		}
			case Type_Obstacle: {
			Enemy* e = (Enemy*)go->childData;
			e->dir.x = -e->dir.x;
			break;
		}		  
			case Type_EnemyProj:{
			DespawnGameObject(go);
			--endPoint->enemyCount;
			break;
			}
			case Type_Door: {
				Enemy* e = (Enemy*)go->childData;
				//e->collidedWithPlatform = TRUE;
				e->vel.y = 0;
				if (go->pos.x + go->size.x <= go2->pos.x + go2->size.x) {
					float intWidth = go->pos.x + go->size.x - go2->pos.x; //intersecting width

					if (go->pos.y > go2->pos.y) {
						float intHeight = go2->pos.y + go2->size.y - go->pos.y; //intersecting height

						if (intWidth < intHeight)
							go->pos.x -= intWidth;
						else {
							e->vel.y = 0.f;
							go->pos.y += intHeight;
						}
					}
					else {
						float intHeight = go->pos.y + go->size.y - go2->pos.y;

						if (intWidth < intHeight)
							go->pos.x -= intWidth;
						else
							go->pos.y -= intHeight;
					}
				}
				else {
					float intWidth = go2->pos.x + go2->size.x - go->pos.x;

					if (go->pos.y > go2->pos.y) {
						float intHeight = go2->pos.y + go2->size.y - go->pos.y;

						if (intWidth < intHeight) {
							go->pos.x += intWidth;
						}
						else {
							e->vel.y = 0.f;
							go->pos.y += intHeight;
						}
					}
					else {
						float intHeight = go->pos.y + go->size.y - go2->pos.y;

						if (intWidth < intHeight) {
							go->pos.x += intWidth;
						}
						else {
							e->vel.y = 0.f;
							go->pos.y -= intHeight;
						}
					}
				}
			}
			break;
		}
		break;
	case Type_Dummy: {
		switch (go2->type) {
			case Type_Platform: { // dummy - platform collision
				Dummy* d = (Dummy*)go->childData;
				d->vel.y = 0;
				if (go->pos.x + go->size.x <= go2->pos.x + go2->size.x) {
					float intWidth = go->pos.x + go->size.x - go2->pos.x; //intersecting width

					if (go->pos.y > go2->pos.y) {
						float intHeight = go2->pos.y + go2->size.y - go->pos.y; //intersecting height

						if (intWidth < intHeight)
							go->pos.x -= intWidth;
						else {
							d->vel.y = 0.f;
							go->pos.y += intHeight;
						}
					}
					else {
						float intHeight = go->pos.y + go->size.y - go2->pos.y;

						if (intWidth < intHeight)
							go->pos.x -= intWidth;
						else
							go->pos.y -= intHeight;
					}
				}
				else {
					float intWidth = go2->pos.x + go2->size.x - go->pos.x;

					if (go->pos.y > go2->pos.y) {
						float intHeight = go2->pos.y + go2->size.y - go->pos.y;

						if (intWidth < intHeight) {
							go->pos.x += intWidth;
						}
						else {
							d->vel.y = 0.f;
							go->pos.y += intHeight;
						}
					}
					else {
						float intHeight = go->pos.y + go->size.y - go2->pos.y;

						if (intWidth < intHeight) {
							go->pos.x += intWidth;
						}
						else {
							d->vel.y = 0.f;
							go->pos.y -= intHeight;
						}
					}
				}
				break;
			}
			case Type_Button:{ //player-button collision
				Button* b = (Button*)go2->childData;
				Door* door = b->linkedDoor;
				door->isOpened = TRUE;
				break;
			}

		}
	}
		break;
	case Type_Door: {
		switch(go2->type) {
		case Type_EnemyProj:
			DespawnGameObject(go2);
			break;
		}
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
	projectile->projAlive = TRUE;
}

void UpdateDoor(GameObject* self) {
	Door* door = self->childData;
	if (door->isOpened) {
		self->hasCollider = FALSE;
		self->color = CP_Color_Create(50,50,50,50);

		float count = 0;
		if (count >= .5f) {
			count = 0.f;
		}
		count += CP_System_GetDt();
		door->isOpened = FALSE;
	}
	else {
		self->hasCollider = TRUE;
		self->color = CP_Color_Create(50, 50, 50, 255);
	}
}
	//else if (!door->isOpened && !self->hasCollider) {
	//	self->hasCollider = TRUE;
	//	self->color = CP_Color_Create(50, 50, 50, 255);
	//}

void UpdateEnemyProj(GameObject* self) {
	float speedScale = 2.f;
	Projectile* proj = self->childData;
	self->pos.x += proj->dir.x * proj->speed * speedScale * CP_System_GetDt();
	proj->range += proj->dir.x * proj->speed * speedScale * CP_System_GetDt();

	if (abs(proj->range) >= proj->maxRange) {
		proj->range = 0.f;
		DespawnGameObject(self);
	}
}

void EnemyShoot(GameObject* _enemy) {
	Enemy* enemy = (Enemy*)_enemy->childData;
	GameObject* enemyProj = GetGameObject();
	enemyProj->hasCollider = TRUE;
	enemyProj->size = CP_Vector_Set(20.f, 20.f);
	enemyProj->color = ENEMY_COLOR;
	enemyProj->type = Type_EnemyProj;
	Projectile* proj = (Projectile*)malloc(sizeof(Projectile));
	proj->maxRange = 600.f;
	proj->range = 0.f;
	proj->speed = 500.f;
	proj->goProj = enemyProj;
	proj->dir = enemy->dir;
	if (enemy->dir.x > 0)
		enemyProj->pos = CP_Vector_Add(_enemy->pos, CP_Vector_Set(_enemy->size.x + 10.f, 10.f));
	else
		enemyProj->pos = CP_Vector_Add(_enemy->pos, CP_Vector_Set(-10.f, 10.f));
	enemyProj->childData = proj;
}

//	CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(1000.f, windowHeight * 0.8 + 10), CP_Vector_Set(100.f, 100.f), OBSTACLE_COLOR);
void CreateGameElement(CP_BOOL collider, enum GAMEOBJECT_TYPE type, CP_Vector pos, CP_Vector size, CP_Color color) {
	GameObject* go = GetGameObject();
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
		go->childData = button;
		break;
	}
	case Type_Door:
		break;
	case Type_Platform: {
		Platform* platform = (Platform*)malloc(sizeof(Platform));
		go->childData = platform;
		CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(pos.x, pos.y +10), CP_Vector_Set(size.x, size.y-10), OBSTACLE_COLOR);
		CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(pos.x, pos.y - 1), CP_Vector_Set(1.f, 1.f), OBSTACLE_COLOR);
		CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(pos.x + size.x - 1, pos.y - 1), CP_Vector_Set(1.f, 1.f), OBSTACLE_COLOR);
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
	endPoint->enemyCount++;
	GameObject* goEnemy = GetGameObject();
	goEnemy->hasCollider = TRUE;
	goEnemy->type = Type_Enemy;
	goEnemy->pos = CP_Vector_Set(x, y);
	goEnemy->size = CP_Vector_Set(50.f, 50.f);
	goEnemy->color = CP_Color_Create(100, 100, 100, 255);
	Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
	enemy->vel = CP_Vector_Set(100, 0);
	enemy->dir = CP_Vector_Set(1, 0);
	enemy->collidedWithPlatform = FALSE;
	enemy->bt = 0.f;
	goEnemy->childData = enemy;
}

void CreateDummy(float x, float y) {
	//CreateGameElement(TRUE, Type_Dummy, CP_Vector_Set(800.f, windowHeight * 0.8), CP_Vector_Set(50.f, 50.f), CP_Color_Create(0, 0, 60, 255));
	GameObject* goDummy = GetGameObject();
	goDummy->hasCollider = TRUE;
	goDummy->type = Type_Dummy;
	goDummy->pos = CP_Vector_Set(x, y);
	goDummy->size = CP_Vector_Set(50.f, 50.f);
	goDummy->color = CP_Color_Create(0, 0, 60, 255);
	Dummy* d = (Dummy*)malloc(sizeof(Dummy));
	d->vel = CP_Vector_Set(0, 0);
	goDummy->childData = d;
}

void CreateButtonDoorLink(CP_Vector buttonPos, CP_Vector doorPos) {
	GameObject* goDoor = GetGameObject();
	goDoor->hasCollider = TRUE;
	goDoor->type = Type_Door;
	goDoor->pos = doorPos;
	goDoor->size = CP_Vector_Set(50.f, 100.f);
	goDoor->color = CP_Color_Create(100, 100, 100, 255);
	Door* door = (Door*)malloc(sizeof(Door));
	door->isOpened = FALSE;
	goDoor->childData = door;
	CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(doorPos.x, doorPos.y + 10), CP_Vector_Set(50.f, 90.f ), OBSTACLE_COLOR);

	GameObject* goButton = GetGameObject();
	goButton->hasCollider = TRUE;
	goButton->type = Type_Button;
	goButton->pos = buttonPos;
	goButton->size = CP_Vector_Set(70.f, 20.f);
	goButton->color = CP_Color_Create(100, 100, 100, 255);
	Button* button = (Button*)malloc(sizeof(Button));
	goButton->childData = button;
	button->linkedDoor = (Door*)door;

}

#endif

void DrawGameElements(GameObject* self) {
	CP_Settings_Fill(self->color);
	if (self->type == Type_Proj) {
		CP_Settings_RectMode(CP_POSITION_CENTER);
	} else {
		CP_Settings_RectMode(CP_POSITION_CORNER);
	}
	CP_Graphics_DrawRect(self->pos.x, self->pos.y, self->size.x, self->size.y);
}

void UpdateProjectile(GameObject* self) {
	if (abs(projectile->range) >= projectile->maxRange) {
		projectile->range = 0.f;
		projectile->projAlive = FALSE;
	}

	self->pos.x += projectile->vel.x * CP_System_GetDt();
	projectile->range += projectile->vel.x * CP_System_GetDt();
}

void UpdateDummy(GameObject* self) {
	Dummy* d = (Dummy*)self->childData;
	//if (d->collidedWithPlatform == FALSE)
		d->vel.y += gravity * CP_System_GetDt();

	self->pos.y += d->vel.y * CP_System_GetDt();
}
void UpdateEnemy(GameObject* self) {
	Enemy* e = (Enemy*)self->childData;
	if (e->collidedWithPlatform == FALSE)
		e->vel.y += gravity * CP_System_GetDt();

	self->pos.y += e->vel.y * CP_System_GetDt();
	self->pos.x += e->dir.x * e->vel.x * CP_System_GetDt();


	// Shooting
	if (e->bt >= .5f) {
		e->bt = 0.f;
		EnemyShoot(self);
	}
	e->bt += CP_System_GetDt();
}

void SideScrolling(GameObject* self) {
	if (player->goPlayer->pos.x >= 1200 && rightPressed) {
		self->pos.x -= player->speed * CP_System_GetDt() * CP_System_GetDt();
		player->vel.x = 0;
	} else if (player->goPlayer->pos.x <= 400 && leftPressed) {
		self->pos.x += player->speed * CP_System_GetDt() * CP_System_GetDt();
		player->vel.x = 0;
	}
}

void RenderScene() {
	for (int i = 0; i < GOARRAY_SIZE; ++i) {
		if ((goPtr + i)->isActive) {
			if ((goPtr + i)->type == Type_Proj) {
				if (projectile->projAlive)
					DrawGameElements((goPtr + i));
			} else
				DrawGameElements((goPtr + i));
		}

	}
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
	goEndPoint->pos = CP_Vector_Set(1500.f, 700.f);
	goEndPoint->size = CP_Vector_Set(60.f, 100.f);
	goEndPoint->color = CP_Color_Create(75, 0, 130, 255);
	endPoint = (EndPoint*)malloc(sizeof(EndPoint));
	goEndPoint->childData = endPoint;
	endPoint->enemyCount = 0;

	CreateEnemy(1000.f, 300.f);
	CreateEnemy(700.f, 300.f);
	CreateDummy(800.f, windowHeight * 0.8);
	//CreateButton(600.f, windowHeight * 0.89);

	// Platforms
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(500.f, windowHeight * 0.9), CP_Vector_Set(2000.f, 200.f), PLATFORM_COLOR);
	//CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(480.f, windowHeight * 0.8 + 10), CP_Vector_Set(20.f, 100.f), OBSTACLE_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1000.f, windowHeight * 0.8), CP_Vector_Set(100.f, 100.f), PLATFORM_COLOR);
	//CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(1000.f, windowHeight * 0.8 + 10), CP_Vector_Set(100.f, 100.f), OBSTACLE_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(200.f, windowHeight * 0.8), CP_Vector_Set(200.f, 100.f), PLATFORM_COLOR);

	CreateButtonDoorLink(CP_Vector_Set(500, 800), CP_Vector_Set(700, 710));


	

	// Enemies
	//CreateGameElement(TRUE, Type_Enemy, CP_Vector_Set(1000.f, 300.f), CP_Vector_Set(50.f, 50.f), ENEMY_COLOR);
	//CreateGameElement(TRUE, Type_Enemy, CP_Vector_Set(700.f, 300.f), CP_Vector_Set(50.f, 50.f), ENEMY_COLOR);

	CP_System_SetWindowSize(windowWidth, windowHeight);
}


void Level_Update() {
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
				} else if ((goPtr + i)->type == Type_Enemy) {
					SideScrolling(goPtr + i);
					UpdateEnemy(goPtr + i);
					if ((goPtr + i)->pos.y > windowHeight) {
						DespawnGameObject(goPtr + i);
						endPoint->enemyCount--;
					}
				} else if ((goPtr + i)->type == Type_EndPoint){
					SideScrolling(goPtr + i);
				} else if ((goPtr + i)->type == Type_Obstacle) {
					SideScrolling(goPtr + i);
				} else if ((goPtr + i)->type == Type_Proj && projectile->projAlive) {
					UpdateProjectile(goPtr + i);
				} else if ((goPtr + i)->type == Type_EnemyProj) {
					UpdateEnemyProj(goPtr + i);
				} else if ((goPtr + i)->type == Type_Door) {
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
		} else {
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
		} else if (leftPressed) {
			player->dir.x = -1.f;
			player->vel.x = -player->speed * CP_System_GetDt();
		} else {
			player->vel.x = 0.f;
		}

		if (shootPressed && !projectile->projAlive) {
			projectile->vel.x = player->dir.x * projectile->speed;
			SetProjSpawn(player->goPlayer->pos.x + player->goPlayer->size.x, player->goPlayer->pos.y + player->goPlayer->size.y / 2);
		}



	} else {
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
}


void Level_Exit() {
	free(goPtr);
	free(player);
	free(projectile);
}

void Level1_Init() {
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
	goEndPoint->pos = CP_Vector_Set(2200.f, windowHeight * 0.55f);
	goEndPoint->size = CP_Vector_Set(55.f, 100.f);
	goEndPoint->color = CP_Color_Create(250, 60, 60, 255);
	endPoint = (EndPoint*)malloc(sizeof(EndPoint));
	goEndPoint->childData = endPoint;
	endPoint->enemyCount = 0;

	//CreateEnemy(1000.f, 300.f);
	//CreateEnemy(700.f, 300.f);

	CreateEnemy(1850.f, windowHeight * 0.6f);
	//CreateButton(600.f, windowHeight * 0.89);

	// Platforms
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(0.f, windowHeight * 0.9), CP_Vector_Set(200, 100.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(400.f, windowHeight * 0.9), CP_Vector_Set(300.f, 200.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(700.f, windowHeight * 0.8), CP_Vector_Set(100.f, 250.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(800.f, windowHeight * 0.7), CP_Vector_Set(100.f, 350.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(900.f, windowHeight * 0.6), CP_Vector_Set(100.f, 450.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1100.f, windowHeight * 0.5), CP_Vector_Set(100.f, 90.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1250.f, windowHeight * 0.4), CP_Vector_Set(100.f, 90.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1400.f, windowHeight * 0.3), CP_Vector_Set(100.f, 90.f), PLATFORM_COLOR);
	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1400.f, windowHeight * 0.65), CP_Vector_Set(200.f, 90.f), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(1380.f, windowHeight * 0.6), CP_Vector_Set(20.f, 60.f), OBSTACLE_COLOR);
	CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(1600.f, windowHeight * 0.6), CP_Vector_Set(20.f, 60.f), OBSTACLE_COLOR);


	CreateGameElement(TRUE, Type_Platform, CP_Vector_Set(1850.f, windowHeight * 0.65), CP_Vector_Set(400.f, 90.f), PLATFORM_COLOR);

	CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(1820.f, windowHeight * 0.6), CP_Vector_Set(20.f, 60.f), OBSTACLE_COLOR);
	CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(2200.f, windowHeight * 0.6), CP_Vector_Set(20.f, 60.f), OBSTACLE_COLOR);



	CP_System_SetWindowSize(windowWidth, windowHeight);
}



void Level1_Update() {
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
					SideScrolling((goPtr + i));
				}
				else if ((goPtr + i)->type == Type_Enemy) {
					SideScrolling((goPtr + i));
					UpdateEnemy(goPtr + i);
					if ((goPtr + i)->pos.y > windowHeight) {
						DespawnGameObject(goPtr + i);
						endPoint->enemyCount--;
					}
				}
				else if ((goPtr + i)->type == Type_EndPoint) {
					SideScrolling((goPtr + i));
				}
				else if ((goPtr + i)->type == Type_Obstacle) {
					SideScrolling((goPtr + i));
				}
				else if ((goPtr + i)->type == Type_Proj && projectile->projAlive) {
					UpdateProjectile(goPtr + i);
				}
				else if ((goPtr + i)->type == Type_EnemyProj)
					UpdateEnemyProj((goPtr + i));
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
}


void Level1_Exit() {
	free(goPtr);
	free(player);
	free(projectile);
}
