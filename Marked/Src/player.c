//---------------------------------------------------------
// file:	player.c
// author:	[CHOA KAI RONG, XAVIER]
// email:	[k.choa@digipen.edu]
// 
// co-author:	[TAN ZHI XIN DARIEN]
// email:		[t.zhixindarien@digipen.edu]
// -Responsible for the function SwapPositions
// 
// brief:	Functions which initialize the player, projectile,
// set projectile spawn, the projectile's update, player movement,
// press keys and swap positions.
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <stdlib.h>
#include "cprocessing.h"
#include "game.h"

void InitPlayer(float x, float y) {
	GameObject* goPlayer = GetGameObject();
	goPlayer->isActive = TRUE;
	goPlayer->hasCollider = TRUE;
	goPlayer->type = Type_Player;
	goPlayer->pos = CP_Vector_Set(x, y);
	goPlayer->size = CP_Vector_Set(50, 50);
	goPlayer->color = CP_Color_Create(255, 255, 255, 0);
	player = (Player*)malloc(sizeof(Player));
	if (player) {
		player->speed = 10000.f;
		player->vel.x = 0.f;
		player->vel.y = 500.f;
		player->dir.x = 1.f;
		player->dir.y = 0.f;
		player->goPlayer = goPlayer;
		player->markedObject = NULL;
		goPlayer->childData = player;
	}
}

void InitPlayerProjectile() {
	GameObject* goProj = GetGameObject();
	goProj->isActive = TRUE;
	goProj->hasCollider = TRUE;
	goProj->type = Type_Proj;
	goProj->size = CP_Vector_Set(20.f, 20.f);
	goProj->color = CP_Color_Create(128, 0, 0, 255);
	projectile = (Projectile*)malloc(sizeof(Projectile));
	if (projectile) {
		projectile->projAlive = FALSE;
		projectile->maxRange = 1000.f;
		projectile->range = 0.f;
		projectile->speed = 1000.f;
		projectile->goProj = goProj;
		goProj->childData = projectile;
	}
}

void SetProjSpawn(float x, float y) {
	projectile->goProj->pos.x = x;
	projectile->goProj->pos.y = y;
	projectile->projAlive = TRUE;
}

void PlayerMovement() {
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

void SwapPositions() {
	CP_Vector tmp = player->markedObject->pos;
	player->markedObject->pos = player->goPlayer->pos;
	player->goPlayer->pos = tmp;
	player->markedObject->color = CP_Color_Create(0, 0, 0, 0);
}

void UpdateProjectile(GameObject* self) {
	if (fabs(projectile->range) >= projectile->maxRange) {
		projectile->range = 0.f;
		projectile->projAlive = FALSE;
	}

	self->pos.x += projectile->vel.x * CP_System_GetDt();
	projectile->range += projectile->vel.x * CP_System_GetDt();
}