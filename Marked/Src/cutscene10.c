//---------------------------------------------------------
// file:	cutscene10.c
// author:	[CHOA KAI RONG, XAVIER]
// email:	[k.choa@digipen.edu]
//
// brief:	Code for cutscene for level 10
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <stdlib.h>
#include "cprocessing.h"
#include "level.h"
#include "game.h"
#include "scenes.h"

float time;

void CutScene10Init() {
	CP_System_SetFrameRate(60);
	time = 0;
}

void CutScene10Update() {
	CP_Settings_TextSize(400);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	time += CP_System_GetDt();
	if (time < .3)
		CP_Font_DrawText("GIVE", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < .6)
		CP_Font_DrawText("UP", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 1.6) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("MARKSMAN", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 2.6) 
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	else if (time < 3.6) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Font_DrawText("NO?", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 4.1)
		CP_Font_DrawText("I", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 4.8) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("WARNED", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 5.3) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Font_DrawText("YOU", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 6.3)
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	else if (time < 6.8)
		CP_Font_DrawText("HOPE", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 7.3) {
		CP_Font_DrawText("YOU", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 7.8)
		CP_Font_DrawText("LIKE", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 8.8) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("LASERS", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if(time < 9.3)
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	else if (time > 9.3)
		TransitScene(Level10);
}


void CutScene10Exit() {
	shootPressed = FALSE;
	rightPressed = FALSE;
	leftPressed = FALSE;
	time = 0;
}