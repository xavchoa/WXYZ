//---------------------------------------------------------
// file:	cutscene4.c
// author:	[CHOA KAI RONG, XAVIER]
// email:	[k.choa@digipen.edu]
//
// brief:	Code for cutscene for level 4
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

void CutScene4Init() {
	CP_System_SetFrameRate(60);
	time = 0;
}

void CutScene4Update() {
	CP_Settings_TextSize(400);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	time += CP_System_GetDt();
	if (time < .5)
		CP_Font_DrawText("THAT", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 1)
		CP_Font_DrawText("WAS", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 1.5)
		CP_Font_DrawText("TOO", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 2.5) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("EASY", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 3)
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	else if (time < 3.5)
		CP_Font_DrawText("LET'S", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 3.8)
		CP_Font_DrawText("RAMP", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 4.2)
		CP_Font_DrawText("UP", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 4.7)
		CP_Font_DrawText("THE", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 6) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("DIFFICULTY", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 6.5)
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	else if (time > 6.5)
		TransitScene(Level4);
}


void CutScene4Exit() {
	shootPressed = FALSE;
	rightPressed = FALSE;
	leftPressed = FALSE;
	time = 0;
}