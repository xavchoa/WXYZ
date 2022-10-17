#include <cprocessing.h>
#include <stdio.h>
#include "utils.h"
#include "mainmenu.h"
//test
#define FALSE 0;
#define TRUE 1;

int windowWidth, windowHeight;
float const gravity = 750.f;
CP_BOOL isGrounded = FALSE;
CP_BOOL rightPressed = FALSE;
CP_BOOL leftPressed = FALSE;

typedef struct Velocity {
	float x;
	float y;
} Velocity;

typedef struct Position {
	float x;
	float y;
} Position;

typedef struct Player{
	float width;
	float height;
	Position pos;
	Velocity vel;
	CP_Color color;
} Player;

typedef struct Rect {
	float x;
	float y;
	float width;
	float height;
} Rect;

Player player;

CP_BOOL RectCollision(Rect *r1, Rect *r2) {
	if (r1->x + r1->width >= r2->x && r1->x <= r2->x + r2->width &&
		r1->y + r1->height >= r2->height && r1->y <= r2->y + r2->height) {
		return TRUE;
	}
	return FALSE;
}

void CreatePlatform(float x, float y, float width, float height) {
	CP_Settings_Fill(CP_Color_Create(0,0,0,255));
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(x, y, width, height);

	//platform collision detection
	if (player.pos.y + player.height <= y && player.pos.y + player.height + player.vel.y * CP_System_GetDt() >= y &&
		player.pos.x + player.width >= x && player.pos.x <= x+width) {
		player.vel.y = 0.f;
		isGrounded = TRUE;
	}
	if (player.pos.y <= y + height && player.pos.y - player.vel.y * CP_System_GetDt() >= y + height &&
		player.pos.x + player.width >= x && player.pos.x <= x + width) {
			player.vel.y = 0.f;
	}

	if (player.pos.x + player.width >= x && player.pos.x <= x+ width &&
		player.pos.y + player.height >= y && player.pos.y <= y + height &&
		player.pos.x + player.width + player.vel.x * CP_System_GetDt() >= x && player.pos.x + player.vel.x * CP_System_GetDt() <= x + width) {
			player.vel.x = 0.f;
	}
}

void DrawPlayer(Player *player) {
	CP_Settings_Fill(player->color);
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(player->pos.x, player->pos.y, player->width, player->height);
	CP_Settings_Fill(CP_Color_Create(255,255,255,255));

} 

void Level_Init()
{

	player.pos.x = 300.f;
	player.pos.y = 100.f;
	player.width = 50.f;
	player.height = 50.f;
	player.vel.x = 0.f;
	player.vel.y = 500.f;
	player.color = CP_Color_Create(255,255,255,255);
	CP_System_SetWindowSize(windowWidth, windowHeight);

}

void Level_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(240, 200, 200, 255));

	CreatePlatform(500.f, windowHeight * 0.9, 5000.f,200.f);
	CreatePlatform(1000.f, windowHeight * 0.8, 100, 100.f);
	CreatePlatform(200.f, windowHeight * 0.8, 100, 100.f);

	//simulate gravity
	player.pos.y += player.vel.y * CP_System_GetDt();
	player.pos.x += player.vel.x * CP_System_GetDt();

	if ((player.height + player.pos.y + player.vel.y * CP_System_GetDt())  <= windowHeight) {
		player.vel.y += gravity * CP_System_GetDt();
	}
	else {
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
	
	if (rightPressed) {
		if(5000.f * CP_System_GetDt())
		player.vel.x = 7000.f * CP_System_GetDt();
	}
	else if(leftPressed) {
		player.vel.x = -7000.f * CP_System_GetDt();
	}
	else {
		player.vel.x = 0.f;
	}
	
	DrawPlayer(&player);


	if (CP_Input_KeyDown(KEY_Q)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Level_Exit()
{

}