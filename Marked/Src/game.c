//---------------------------------------------------------
// file:	game.c
// author:	[CHOA KAI RONG, XAVIER]
// email:	[k.choa@digipen.edu]
//
// brief:	Functions for the game that handles game objects,
// checks for AABB collision, and manages what game objects do
// after colliding. Contains functions that restarts the level
// and exits back to main menu when the respective buttons are
// pressed. Contains functions that handle the game obejects
// such as allocating memory as well as freeing them.
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright ? 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

//#include <stdio.h>

#include <stdlib.h>
#include "cprocessing.h"
#include "game.h"
#include "scenes.h"
#include <string.h>
#include "gameelements.h"
#include "level.h"

GameObject* GetGameObject() {
	for (int i = 0; i < GOARRAY_SIZE; ++i) {
		if (!(goPtr + i)->isActive) {
			(goPtr + i)->isActive = TRUE;
			return (goPtr + i);
		}
	}
	return NULL;
}

GameObject* InitGoPtr() {
	GameObject* goPtr = (GameObject*)malloc(GOARRAY_SIZE * sizeof(GameObject));
	if (goPtr) {
		for (int i = 0; i < GOARRAY_SIZE; ++i) {
			(goPtr + i)->isActive = FALSE;
			(goPtr + i)->childData = NULL;
		}
	}
	return goPtr;
}

void FreeGoPtr(GameObject* goPtr) {
	for (int i = 0; i < GOARRAY_SIZE; ++i) {
		if ((goPtr + i)->childData != NULL)
			free((goPtr + i)->childData);
	}
}

void DespawnGameObject(GameObject* go) {
	go->isActive = FALSE;
	go->hasCollider = FALSE;
	go->type = Type_None;
	go->pos = CP_Vector_Set(0, 0);
	go->size = CP_Vector_Set(0, 0);
	if (go->childData != NULL) {
		free(go->childData);
		go->childData = NULL;
	}
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
	case Type_EndPoint: {
		switch (go2->type) {
		case Type_Player: {
			endPoint = (EndPoint*)go->childData;
			if (endPoint->enemyCount == 0)
				TransitScene(nextLevel);
			break;
		}
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

void ManageCollision() {
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
}


//causes screen to move with plyaer
void SideScrolling(GameObject* self) {
	if (player->goPlayer->pos.x >= 800 && rightPressed) {
		self->pos.x -= player->speed * CP_System_GetDt() * CP_System_GetDt();
		player->vel.x = 0;
	}
	else if (player->goPlayer->pos.x <= 500 && leftPressed) {
		self->pos.x += player->speed * CP_System_GetDt() * CP_System_GetDt();
		player->vel.x = 0;
	}
}

//when escape key is pressed, go back to main menu when in game

void QuitPressed() {
	if (CP_Input_KeyDown(KEY_ESCAPE)) {
		shootPressed = FALSE;
		rightPressed = FALSE;
		leftPressed = FALSE;
		isGameOver = FALSE;
		TransitScene(Main_Menu);
	}
}

void RestartPressed() {
	if (CP_Input_KeyTriggered(KEY_R)) {
		projectile->projAlive = FALSE;
		shootPressed = FALSE;
		rightPressed = FALSE;
		leftPressed = FALSE;
		isGameOver = FALSE;
		RestartLevel(currentLevel);
	}
}