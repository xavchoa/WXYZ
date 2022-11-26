//---------------------------------------------------------
// file:	winscreen.c
// author:	[CHOA KAI RONG, XAVIER]
// email:	[k.choa@digipen.edu]
//
// brief:	Code containing cutscene after player beats the
// final level
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <stdlib.h>
#include "cprocessing.h"
#include "mainmenu.h"
#include "level.h"
#include "game.h"
#include "scenes.h"

float time;

void WinsceneInit() {
	CP_System_SetFrameRate(60);
	time = 0;
}

void WinsceneUpdate() {
	CP_Settings_TextSize(400);
	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	time += CP_System_GetDt();
	if (time < .5)
		CP_Font_DrawText("CONGRATS", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 1)
		CP_Font_DrawText("MARKSMAN!", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 1.5)
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	else if (time < 2)
		CP_Font_DrawText("YOU", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 2.5) {
		CP_Font_DrawText("MADE", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 3)
		CP_Font_DrawText("IT", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 4)
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	else if (time < 4.5)
		CP_Font_DrawText("NOW", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 5)
		CP_Font_DrawText("WHAT?", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 5.5)
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	else if (time < 6.5) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("THERE", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 7.5) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("IS", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 8.5) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("NO", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 9.5) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("END.", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 10.5)
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	else if (time > 10.5)
		TransitScene(Level10);
}

void WinsceneExit() {
	shootPressed = FALSE;
	rightPressed = FALSE;
	leftPressed = FALSE;
	time = 0;
}