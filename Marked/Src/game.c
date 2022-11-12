#include <cprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "mainmenu.h"
#include "level.h"
#include "game.h"
#include "scenes.h"

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
				printf("Level: %d\n", level);
				//next level
				TransitScene(level);
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

