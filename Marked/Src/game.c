#pragma optimize off
#include <cprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "mainmenu.h"
#include "level.h"
#include "game.h"
#include "scenes.h"
#include <string.h>

GameObject* GetGameObject() {
	for (int i = 0; i < GOARRAY_SIZE; ++i) {
		if (!(goPtr + i)->isActive) {
			(goPtr + i)->isActive = TRUE;
			return (goPtr + i);
		}
	}
	return NULL;
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

void KeysPressed() {
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
		SetProjSpawn(player->goPlayer->pos.x + player->goPlayer->size.x / 2, player->goPlayer->pos.y + player->goPlayer->size.y / 2);
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
		case Type_Enemy: {
			isGameOver = TRUE;
			break;
		}
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
				//next level
				TransitScene(nextLevel);
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
		case Type_Laser: {
			isGameOver = TRUE;
			break;
		}
		case Type_Dummy: {
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
		if (projectile->projAlive) {
			switch (go2->type) {
			case Type_Platform: //player proj-platform collision
				projectile->projAlive = FALSE;
				break;
			case Type_Dummy:
				player->markedObject = go2;
				player->markedObject->color = CP_Color_Create(128, 0, 0, 100);
				projectile->projAlive = FALSE;
				break;
			case Type_Enemy:    //player proj - enemy collision
				player->markedObject = go2;
				player->markedObject->color = CP_Color_Create(128, 0, 0, 100);
				projectile->projAlive = FALSE;
				break;
			case Type_Door:
				projectile->projAlive = FALSE;
				break;
			}
		}
		projectile->range = 0;
		break;
	case Type_Enemy:
		switch (go2->type) {
		case Type_Platform: { //enemy - platform collision
			Enemy* e = (Enemy*)go->childData;
			//e->goPlatform = go2;
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

			if (go->pos.x <= go2->pos.x) {
				e->dir.x = 1;
			}else if(go->pos.x + go->size.x >= go2->pos.x + go2->size.x) {
				e->dir.x = -1;
			}
			break;
		}
			case Type_Dummy: {
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
				e->dir.x = -e->dir.x;
				break;
			}
			case Type_Obstacle: {
				/*if (go2->pos.x > go->pos.x-1 && go2->pos.x + go2->size.x < go->pos.x + 1 + go->size.x) {
					return;
			}*/
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
				e->dir.x = -e->dir.x;
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
			case Type_Button: { //player-button collision
				Button* b = (Button*)go2->childData;
				Door* door = b->linkedDoor;
				door->isOpened = TRUE;
				break;
			}
		}
		break;
	case Type_Dummy: {
		switch (go2->type) {
			case Type_EnemyProj: {
				DespawnGameObject(go2);
				break;
			}
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
			case Type_Door: {
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
	case Type_EnemyProj: {
		switch (go2->type) {
		case Type_Platform:
			DespawnGameObject(go);
			break;
		case Type_Door:
			DespawnGameObject(go);
			break;
		case Type_Dummy:
			DespawnGameObject(go);
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
	player->markedObject->color = CP_Color_Create(0, 0, 0, 0);
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

void InitPlayerProjectile() {
	GameObject* goProj = GetGameObject();
	goProj->isActive = TRUE;
	goProj->hasCollider = TRUE;
	goProj->type = Type_Proj;
	goProj->size = CP_Vector_Set(20.f, 20.f);
	goProj->color = CP_Color_Create(128, 0, 0, 255);
	projectile = (Projectile*)malloc(sizeof(Projectile));
	projectile->projAlive = FALSE;
	projectile->maxRange = 1000.f;
	projectile->range = 0.f;
	projectile->speed = 1000.f;
	projectile->goProj = goProj;
	goProj->childData = projectile;
}
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
		//enemy->collidedWithPlatform = FALSE;
		enemy->goEnemy = go;
		go->childData = enemy;
	}
				   break;
	case Type_Dummy:
		break;
	case Type_Laser:
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
		//CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(pos.x, pos.y - 1), CP_Vector_Set(3.f, 1.f), OBSTACLE_COLOR);
		//CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(pos.x + size.x - 1, pos.y - 1), CP_Vector_Set(3.f, 1.f), OBSTACLE_COLOR);
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

void CreateLaser(float x, float y, float width, float height, float velx, float vely, float time) {
	GameObject* goLaser = GetGameObject();
	goLaser->hasCollider = TRUE;
	goLaser->type = Type_Laser;
	goLaser->pos = CP_Vector_Set(x, y);
	goLaser->size = CP_Vector_Set(width, height);
	goLaser->color = CP_Color_Create(200, 0, 0, 50);
	Laser* laser = (Laser*)malloc(sizeof(Laser));
	laser->vel = CP_Vector_Set(velx, vely);
	laser->dir = CP_Vector_Set(1, 1);
	laser->time = 0.f;
	laser->timeMax = time;
	goLaser->childData = laser;
}

void CreateEnemy(float x, float y) {
	endPoint->enemyCount++;
	GameObject* goEnemy = GetGameObject();
	goEnemy->hasCollider = TRUE;
	goEnemy->type = Type_Enemy;
	goEnemy->pos = CP_Vector_Set(x, y);
	goEnemy->size = CP_Vector_Set(50.f, 50.f);
	goEnemy->color = CP_Color_Create(100, 100, 100, 0);
	Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
	enemy->vel = CP_Vector_Set(100, 0);
	enemy->dir = CP_Vector_Set(1, 0);
	//enemy->collidedWithPlatform = FALSE;
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
	goDummy->color = CP_Color_Create(0, 0, 60, 0);
	Dummy* d = (Dummy*)malloc(sizeof(Dummy));
	d->vel = CP_Vector_Set(0, 0);
	goDummy->childData = d;
}

void CreateButtonDoorLink(CP_Vector buttonPos, CP_Vector doorPos, int type) {
	GameObject* goDoor = GetGameObject();
	goDoor->hasCollider = TRUE;
	goDoor->type = Type_Door;
	goDoor->pos = doorPos;
	if (type == 1) {
		goDoor->size = CP_Vector_Set(50.f, 100.f);
	}
	else if (type == 2) {
		goDoor->size = CP_Vector_Set(100.f, 50.f);
	}
	goDoor->color = CP_Color_Create(100, 100, 100, 255);
	Door* door = (Door*)malloc(sizeof(Door));
	door->isOpened = FALSE;
	goDoor->childData = door;
	//CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(doorPos.x, doorPos.y + 10), CP_Vector_Set(50.f, 90.f ), OBSTACLE_COLOR);

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
	switch (self->type) {
		case Type_Door: {
			//door
			if (self->hasCollider && self->size.x == 50) {
				CP_Settings_Fill(CP_Color_Create(192, 192, 192, 255));
				CP_Graphics_DrawRectAdvanced(self->pos.x, self->pos.y, 50.f, 100.f, 0, 0);
				CP_Settings_Fill(CP_Color_Create(140, 140, 140, 255));
				CP_Graphics_DrawTriangle(self->pos.x + 5, self->pos.y + 5, self->pos.x + 5, self->pos.y + 40, self->pos.x + 45, self->pos.y + 5);
				CP_Graphics_DrawTriangle(self->pos.x + 5, self->pos.y + 50, self->pos.x + 45, self->pos.y + 15, self->pos.x + 45, self->pos.y + 85);
				CP_Graphics_DrawTriangle(self->pos.x + 5, self->pos.y + 60, self->pos.x + 5, self->pos.y + 95, self->pos.x + 45, self->pos.y + 95);
				return;
			}
			else if(self->hasCollider) {
				CP_Settings_Fill(CP_Color_Create(192, 192, 192, 255));
				CP_Graphics_DrawRectAdvanced(self->pos.x, self->pos.y+50, 50.f, 100.f, -90, 0);
				CP_Settings_Fill(CP_Color_Create(140, 140, 140, 255));
				CP_Graphics_DrawTriangleAdvanced(self->pos.x + 3, self->pos.y + 20, self->pos.x + 3, self->pos.y + 55, self->pos.x + 43, self->pos.y + 20, -90);
				CP_Graphics_DrawTriangleAdvanced(self->pos.x + 23, self->pos.y + 19, self->pos.x + 63, self->pos.y + -16, self->pos.x + 63, self->pos.y + 54, -90);
				CP_Graphics_DrawTriangleAdvanced(self->pos.x + 70, self->pos.y + 8, self->pos.x + 70, self->pos.y + 43, self->pos.x + 110, self->pos.y + 43, -90);
				return;
			}
			CP_Graphics_DrawRect(self->pos.x, self->pos.y, self->size.x, self->size.y);
		}
		case Type_Obstacle: {
			return;
		}
		break;
		case Type_Player: {
			//player face
			CP_Color player_color = CP_Color_Create(255, 255, 255, 255);
			CP_Settings_Fill(player_color);
			CP_Graphics_DrawRect(self->pos.x, self->pos.y, self->size.x, self->size.y);
			CP_Settings_Stroke(CP_Color_Create(128, 0, 0, 255));
			CP_Graphics_DrawLine(self->pos.x, self->pos.y + self->size.x, self->pos.x + self->size.x, self->pos.y);
			CP_Graphics_DrawLine(self->pos.x + 10.0, self->pos.y + 6.0, self->pos.x + 40.0, self->pos.y + 35.0);
			CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));

			//player eyes
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			CP_Graphics_DrawRect(self->pos.x + 5.0, self->pos.y + 10.0, 15, 15);
			CP_Graphics_DrawRect(self->pos.x + 30.0, self->pos.y + 10.0, 15, 15);
			CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
			CP_Graphics_DrawCircle(self->pos.x + 12.5, self->pos.y + 17.5, 8);
			CP_Graphics_DrawCircle(self->pos.x + 37.5, self->pos.y + 17.5, 8);

			//player mouth
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			CP_Graphics_DrawRect(self->pos.x, self->pos.y + 40.0, 10, 10);
			CP_Graphics_DrawRect(self->pos.x + 40.0, self->pos.y + 40.0, 10, 10);
			CP_Graphics_DrawRect(self->pos.x + 16.0, self->pos.y + 40.0, 1, 10);
			CP_Graphics_DrawRect(self->pos.x + 24.0, self->pos.y + 40.0, 1, 10);
			CP_Graphics_DrawRect(self->pos.x + 32.0, self->pos.y + 40.0, 1, 10);
			
		}
		break;
		case Type_Enemy: {
			CP_Color enermy_color = CP_Color_Create(255, 255, 255, 255);
			//enermy face

			CP_Settings_Fill(enermy_color);
			CP_Graphics_DrawRect(self->pos.x, self->pos.y, self->size.x, self->size.y);
			CP_Settings_Fill(CP_Color_Create(0, 128, 255, 255));
			CP_Graphics_DrawRect(self->pos.x, self->pos.y + 5.0, 15.0, 5.0);
			CP_Graphics_DrawRect(self->pos.x + 35.0, self->pos.y + 5.0, 15.0, 5.0);
			CP_Settings_Fill(CP_Color_Create(255, 255, 153, 255));
			CP_Graphics_DrawRect(self->pos.x + 15.0, self->pos.y + 4.0, 20.0, 8.0);


			//enermy eyes
			CP_Settings_Fill(CP_Color_Create(0, 128, 255, 255));
			CP_Graphics_DrawRect(self->pos.x + 5.0, self->pos.y + 18.0, 15, 15);
			CP_Graphics_DrawRect(self->pos.x + 30.0, self->pos.y + 18.0, 15, 15);
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Graphics_DrawRect(self->pos.x + 10, self->pos.y + 25.0, 10, 7);
			CP_Graphics_DrawRect(self->pos.x + 31, self->pos.y + 25.0, 10, 7);

			//enermy mouth
			CP_Settings_Fill(CP_Color_Create(0, 128, 255, 255));
			CP_Graphics_DrawRect(self->pos.x, self->pos.y + 40.0, 50, 10);
			
		}
		break;
		case Type_Dummy: {
			//dummy face
			CP_Settings_Fill(CP_Color_Create(128, 128, 128, 255));
			CP_Graphics_DrawRect(self->pos.x, self->pos.y, self->size.x, self->size.y);
			CP_Settings_Stroke(CP_Color_Create(96, 96, 96, 255));
			CP_Graphics_DrawLine(self->pos.x, self->pos.y + self->size.y, self->pos.x + self->size.x, self->pos.y);
			CP_Graphics_DrawLine(self->pos.x + 10.0, self->pos.y + 6.0, self->pos.x + 40.0, self->pos.y + 35.0);
			CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			CP_Graphics_DrawRect(self->pos.x, self->pos.y + 40.0, 10, 10);
			CP_Graphics_DrawRect(self->pos.x + 40.0, self->pos.y + 40.0, 10, 10);
			CP_Graphics_DrawRect(self->pos.x + 16.0, self->pos.y + 40.0, 1, 10);
			CP_Graphics_DrawRect(self->pos.x + 24.0, self->pos.y + 40.0, 1, 10);
			CP_Graphics_DrawRect(self->pos.x + 32.0, self->pos.y + 40.0, 1, 10);


			//dummy eyes
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			CP_Graphics_DrawRect(self->pos.x + 5.0, self->pos.y + 10.0, 15, 15);
			CP_Graphics_DrawRect(self->pos.x + 30.0, self->pos.y + 10.0, 15, 15);
			CP_Settings_Stroke(CP_Color_Create(192, 192, 192, 255));
			CP_Graphics_DrawLine(self->pos.x + 5.0, self->pos.y + 25.0, self->pos.x + 20.0, self->pos.y + 10.0);
			CP_Graphics_DrawLine(self->pos.x + 5.0, self->pos.y + 10.0, self->pos.x + 20.0, self->pos.y + 25.0);
			CP_Graphics_DrawLine(self->pos.x + 30.0, self->pos.y + 25.0, self->pos.x + 45.0, self->pos.y + 10.0);
			CP_Graphics_DrawLine(self->pos.x + 30.0, self->pos.y + 10.0, self->pos.x + 45.0, self->pos.y + 25.0);
			CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));

		}
		break;
		case Type_Button: {
			//button
			CP_Settings_Fill(CP_Color_Create(155, 0, 0, 255));
			CP_Graphics_DrawRectAdvanced(self->pos.x + 10.0, self->pos.y - 8.0, 50.0, 10.f, 0, 5);
			CP_Settings_Fill(CP_Color_Create(192, 192, 192, 255));
			CP_Graphics_DrawRect(self->pos.x, self->pos.y, 70.f, 10.f);
			
			return;
		}
		case Type_Proj: {
			//CP_Settings_RectMode(CP_POSITION_CENTER); 
			CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
			CP_Graphics_DrawRectAdvanced(self->pos.x, self->pos.y, 7.f, 7.f, 0.0, 0);
			CP_Graphics_DrawTriangleAdvanced(self->pos.x, self->pos.y, self->pos.x, self->pos.y + 7.f, self->pos.x - 15.f, self->pos.y + 3.5f, 0.0);
			CP_Graphics_DrawTriangleAdvanced(self->pos.x, self->pos.y + 7.f, self->pos.x + 7.f, self->pos.y + 7.f, self->pos.x + 3.5f, self->pos.y + 22.f, 0.0);
			CP_Graphics_DrawTriangleAdvanced(self->pos.x, self->pos.y, self->pos.x + 7.f, self->pos.y, self->pos.x + 3.5f, self->pos.y - 15.f, 0.0);
			CP_Graphics_DrawTriangleAdvanced(self->pos.x + 7.f, self->pos.y, self->pos.x + 7.f, self->pos.y + 7.f, self->pos.x + 22.f, self->pos.y + 3.5f, 0.0);
			CP_Settings_Stroke(CP_Color_Create(128, 0, 0, 255));
			CP_Graphics_DrawCircle(self->pos.x + 3.5, self->pos.y + 3.5f, 5.f);
			CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
			return;
		}
		break;
		case Type_EnemyProj: {
			//enermy projectile
			CP_Settings_Fill(CP_Color_Create(30, 144, 255, 255));
			CP_Graphics_DrawRect(self->pos.x, self->pos.y, 7.f, 7.f);
			CP_Graphics_DrawTriangleAdvanced(self->pos.x, self->pos.y, self->pos.x, self->pos.y + 7.f, self->pos.x - 15.f, self->pos.y + 3.5f, 90.0);
			CP_Graphics_DrawTriangleAdvanced(self->pos.x, self->pos.y + 7.f, self->pos.x + 7.f, self->pos.y + 7.f, self->pos.x + 3.5f, self->pos.y + 22.f, 90.0);
			CP_Graphics_DrawTriangleAdvanced(self->pos.x, self->pos.y, self->pos.x + 7.f, self->pos.y, self->pos.x + 3.5f, self->pos.y - 15.f, 90.0);
			CP_Graphics_DrawTriangleAdvanced(self->pos.x + 7.f, self->pos.y, self->pos.x + 7.f, self->pos.y + 7.f, self->pos.x + 22.f, self->pos.y + 3.5f, 90.0);
			CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));
			CP_Graphics_DrawCircle(self->pos.x + 3.5, self->pos.y + 3.5f, 5.f);
			CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
			return;
		}
		case Type_Info: {
			CP_Settings_TextSize(50);
			CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
			CP_Font_DrawTextBox("REMEMBER: All enemies need to be eliminated to proceed. Press \"R\" if you get stuck.", self->pos.x, self->pos.y, self->size.x);
			return;
		}
		case Type_Info2: {
			CP_Settings_TextSize(50);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			CP_Font_DrawTextBox("You cannot kill enemies directly.", self->pos.x, self->pos.y - 100, self->size.x);
			CP_Font_DrawTextBox("Think of ways to take them out by swapping positions.", self->pos.x, self->pos.y, self->size.x);
			return;
		}
		default:
			CP_Settings_RectMode(CP_POSITION_CORNER);
		break;
	}
	CP_Settings_Fill(self->color);
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
	//if (e->collidedWithPlatform == FALSE)
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

void UpdateLaser(GameObject* self) {
	Laser* l = (Laser*)self->childData;
	self->pos.x += l->dir.x * l->vel.x * CP_System_GetDt();
	self->pos.y += l->dir.y * l->vel.y * CP_System_GetDt();

	if (l->time >= l->timeMax && l->timeMax) {
		l->time = 0.f;
		l->dir.x = -l->dir.x;
		l->dir.y = -l->dir.y;
	}
	l->time += CP_System_GetDt();
}
void SideScrolling(GameObject* self) {
	if (player->goPlayer->pos.x >= 800 && rightPressed) {
		self->pos.x -= player->speed * CP_System_GetDt() * CP_System_GetDt();
		player->vel.x = 0;
	} else if (player->goPlayer->pos.x <= 500 && leftPressed) {
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

void DisplayGameOver() {
	CP_Graphics_ClearBackground(CP_Color_Create(128, 0, 0, 120));
	RenderScene();
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(100);
	CP_Font_DrawText("YOU DIED...", windowWidth / 2, windowHeight / 2);
	CP_Settings_TextSize(50);
	CP_Font_DrawText("Press \"R\" to restart level", windowWidth / 2, windowHeight / 2 + 60);
}
