#include <cprocessing.h>
#include <stdio.h>
#include "utils.h"
#include "mainmenu.h"

#define FALSE 0
#define TRUE 1

int windowWidth, windowHeight;
float const gravity = 750.f;
CP_BOOL isGrounded = FALSE;
CP_BOOL rightPressed = FALSE;
CP_BOOL leftPressed = FALSE;
CP_BOOL throwPressed = FALSE;
CP_BOOL isThrowing = FALSE;

typedef struct GameObject {
	float width;
	float height;
	CP_Vector pos;
	CP_BOOL hasCollider;
	CP_BOOL isMarkable;
	void* extData;
} GameObject;

typedef struct Player {
	float width;
	float height;
	CP_Vector pos;
	CP_Vector vel;
	CP_Color color;
} Player;

typedef struct Projectile {
	float width;
	float height;
	float range;
	CP_Vector pos;
	CP_Vector vel;
} Projectile;

typedef struct Rect {
	float width;
	float height;
	CP_Vector pos;
} Rect;


Player player;
Projectile projectile;

CP_BOOL RectCollision(Rect* r1, Rect* r2) {
	if (r1->pos.x + r1->width >= r2->pos.x && r1->pos.x <= r2->pos.x + r2->width &&
		r1->pos.y + r1->height >= r2->height && r1->pos.y <= r2->pos.y + r2->height) {
		return TRUE;
	}
	return FALSE;
}

void PlayerInit(Player *player, CP_Vector p, CP_Vector v, float w, float h) {
	player->pos.x = p.x;
	player->pos.y = p.y;
	player->width = w;
	player->height = h;
	player->vel.x = v.x;
	player->vel.y = v.y;
	player->color = CP_Color_Create(255, 255, 255, 255);
}

void ProjectileInit(Projectile *projectile, CP_Vector p, CP_Vector v, float w, float h, float r) {
	projectile->pos.x = p.x;
	projectile->pos.y = p.y;
	projectile->width = w;
	projectile->height = h;
	projectile->vel.x = v.x;
	projectile->range = r;
}
void DrawProjectile(Projectile* proj) {
	CP_Settings_Fill(CP_Color_Create(120, 0, 0, 255));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_DrawRect(proj->pos.x, proj->pos.y, proj->width, proj->height);
}

void CreatePlatform(float x, float y, float width, float height) {
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(x, y, width, height);

	//platform collision detection
	if (player.pos.y + player.height <= y && player.pos.y + player.height + player.vel.y * CP_System_GetDt() >= y &&
		player.pos.x + player.width >= x && player.pos.x <= x + width) {
		player.vel.y = 0.f;
		isGrounded = TRUE;
	}
	if (player.pos.y <= y + height && player.pos.y - player.vel.y * CP_System_GetDt() >= y + height &&
		player.pos.x + player.width >= x && player.pos.x <= x + width) {
		player.vel.y = 0.f;
	}

	if (player.pos.x + player.width >= x && player.pos.x <= x + width &&
		player.pos.y + player.height >= y && player.pos.y <= y + height &&
		player.pos.x + player.width + player.vel.x * CP_System_GetDt() >= x && player.pos.x + player.vel.x * CP_System_GetDt() <= x + width) {
		player.vel.x = 0.f;
	}
}


void SetProjectileSpawn(float x, float y) {
	if (isThrowing == 0) {
		projectile.pos.x = x;
		projectile.pos.y = y;
		isThrowing = TRUE;
	}
}


void DrawPlayer(Player* player) {
	CP_Settings_Fill(player->color);
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(player->pos.x, player->pos.y, player->width, player->height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

}



void Level_Init()
{
	PlayerInit(&player, CP_Vector_Set(300,100), CP_Vector_Set(0,500), 50, 50);
	ProjectileInit(&projectile, CP_Vector_Set(-100,-100), CP_Vector_Set(7000,1000), 20, 20, 1000);

	CP_System_SetWindowSize(windowWidth, windowHeight);

}

void Level_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(240, 200, 200, 255));

	CreatePlatform(500.f, windowHeight * 0.9, 5000.f, 200.f);
	CreatePlatform(1000.f, windowHeight * 0.8, 100, 100.f);
	CreatePlatform(200.f, windowHeight * 0.8, 100, 100.f);

	player.pos.y += player.vel.y * CP_System_GetDt(); 	//simulate gravity
	player.pos.x += player.vel.x * CP_System_GetDt();

	if ((player.height + player.pos.y + player.vel.y * CP_System_GetDt()) <= windowHeight+ player.height+50) {
		player.vel.y += gravity * CP_System_GetDt();
	}
	else {
		//GAMEOVER
		player.vel.y = 0.f;
		isGrounded = TRUE;
	}

	//player movement
	if (CP_Input_KeyTriggered(KEY_W) && isGrounded) {
		player.vel.y -= 15000.f * CP_System_GetDt();
		isGrounded = FALSE;
	}
	if (CP_Input_KeyDown(KEY_A)) {
		leftPressed = TRUE;
	}
	if (CP_Input_KeyReleased(KEY_A)) {
		leftPressed = FALSE;
	}

	if (CP_Input_KeyDown(KEY_D)) {
		rightPressed = TRUE;
	}
	if (CP_Input_KeyReleased(KEY_D)) {
		rightPressed = FALSE;
	}
	//player throwing
	if (CP_Input_KeyTriggered(KEY_X)) {
		throwPressed = TRUE;
	}
	if (CP_Input_KeyReleased(KEY_X)) {
		throwPressed = FALSE;
	}

	if (rightPressed) {
		if (5000.f * CP_System_GetDt())
			player.vel.x = 7000.f * CP_System_GetDt();
	}
	else if (leftPressed) {
		player.vel.x = -7000.f * CP_System_GetDt();
	}
	else {
		player.vel.x = 0.f;
	}

	DrawPlayer(&player);

	if (isThrowing == TRUE) {
		projectile.pos.x += 1000 * CP_System_GetDt();

		if (projectile.pos.x > player.pos.x + projectile.range) {
			isThrowing = FALSE;
			projectile.pos.y = 1000; //makes projectile go offscreen

		}
	}
	if (throwPressed) {
		SetProjectileSpawn(player.pos.x + player.width, player.pos.y + player.height / 2);
	}
	DrawProjectile(&projectile);

	if (CP_Input_KeyDown(KEY_Q)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}

}

void Level_Exit()
{

}