#include "cprocessing.h"
#include <stdlib.h>
#include "game.h"
#include "player.h"

//Create Platform
void CreateGameElement(CP_BOOL collider, enum GAMEOBJECT_TYPE type, CP_Vector pos, CP_Vector size, CP_Color color) {
	GameObject* go = GetGameObject();
	go->hasCollider = collider;
	go->type = type;
	go->pos = pos;
	go->size = size;
	go->color = color;
	switch (type) {
	case Type_Platform: {
		Platform* platform = (Platform*)malloc(sizeof(Platform));
		go->childData = platform;
		CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(pos.x, pos.y + 10), CP_Vector_Set(size.x, size.y - 10), OBSTACLE_COLOR);
		break;
	}
	default:
		break;
	}
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
	if (door) {
		door->isOpened = FALSE;
		goDoor->childData = door;
	}
	
	GameObject* goButton = GetGameObject();
	goButton->hasCollider = TRUE;
	goButton->type = Type_Button;
	goButton->pos = buttonPos;
	goButton->size = CP_Vector_Set(70.f, 20.f);
	goButton->color = CP_Color_Create(100, 100, 100, 255);
	Button* button = (Button*)malloc(sizeof(Button));
	if (button) {
		goButton->childData = button;
		button->linkedDoor = (Door*)door;
	}
}

void UpdateDoor(GameObject* self) {
	Door* door = self->childData;
	if (door->isOpened) {
		self->hasCollider = FALSE;
		self->color = CP_Color_Create(50, 50, 50, 50);
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

void CreateDummy(float x, float y) {
	GameObject* goDummy = GetGameObject();
	goDummy->hasCollider = TRUE;
	goDummy->type = Type_Dummy;
	goDummy->pos = CP_Vector_Set(x, y);
	goDummy->size = CP_Vector_Set(50.f, 50.f);
	goDummy->color = CP_Color_Create(0, 0, 60, 0);
	Dummy* d = (Dummy*)malloc(sizeof(Dummy));
	if (d) {
		d->vel = CP_Vector_Set(0, 0);
		goDummy->childData = d;
	}
}

void UpdateDummy(GameObject* self) {
	Dummy* d = (Dummy*)self->childData;
	d->vel.y += gravity * CP_System_GetDt();
	self->pos.y += d->vel.y * CP_System_GetDt();
}

void InitEndPoint(float x, float y) {
	GameObject* goEndPoint = GetGameObject();
	goEndPoint->isActive = TRUE;
	goEndPoint->hasCollider = TRUE;
	goEndPoint->type = Type_EndPoint;
	goEndPoint->pos = CP_Vector_Set(x, y);
	goEndPoint->size = CP_Vector_Set(60.f, 100.f);
	goEndPoint->color = CP_Color_Create(128, 0, 0, 255);
	endPoint = (EndPoint*)malloc(sizeof(EndPoint));
	if (endPoint) {
		goEndPoint->childData = endPoint;
		endPoint->enemyCount = 0;
	}
}


void UpdateEndPoint(GameObject* self) {
	EndPoint* ep = (EndPoint*)self->childData;
	if (ep->enemyCount == 0) {
		self->color = CP_Color_Create(51, 165, 50, 255);
	}
}

void CreateLaser(float x, float y, float width, float height, float velx, float vely, float time) {
	GameObject* goLaser = GetGameObject();
	if (!goLaser) return;
	goLaser->hasCollider = TRUE;
	goLaser->type = Type_Laser;
	goLaser->pos = CP_Vector_Set(x, y);
	goLaser->size = CP_Vector_Set(width, height);
	goLaser->color = CP_Color_Create(200, 0, 0, 50);
	Laser* laser = (Laser*)malloc(sizeof(Laser));
	if (laser) {
		laser->vel = CP_Vector_Set(velx, vely);
		laser->dir = CP_Vector_Set(1, 1);
		laser->time = 0.f;
		laser->timeMax = time;
		goLaser->childData = laser;
	}
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
	}
	else if (player->goPlayer->pos.x <= 500 && leftPressed) {
		self->pos.x += player->speed * CP_System_GetDt() * CP_System_GetDt();
		player->vel.x = 0;
	}
}