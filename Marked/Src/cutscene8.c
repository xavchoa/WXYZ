//---------------------------------------------------------
// file:	cutscene8.c
// author:	[CHOA KAI RONG, XAVIER]
// email:	[k.choa@digipen.edu]
//
// brief:	Code for cutscene for level 8
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright ? 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <stdlib.h>
#include "cprocessing.h"
#include "level.h"
#include "game.h"
#include "scenes.h"

float time;

void CutScene8Init() {
	CP_System_SetFrameRate(60);
	time = 0;
}

void CutScene8Update() {
	CP_Settings_TextSize(400);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	time += CP_System_GetDt();
	if (time < .5)
		CP_Font_DrawText("I", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 1)
		CP_Font_DrawText("NAMED", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 1.3)
		CP_Font_DrawText("THE", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 1.6) {
		CP_Font_DrawText("NEXT", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 2)
		CP_Font_DrawText("LEVEL", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 2.5)
		CP_Font_DrawText("AFTER", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 3) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("YOU", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	}
	else if (time < 4)
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	else if (time < 5)
		CP_Font_DrawText("BUTTONS", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 5.5) {
		CP_Font_DrawText("AND", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 6.5) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("DUMMIES", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 7.5)
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	else if (time < 8.2) {
		CP_Font_DrawText("I'M", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 8.6) {
		CP_Font_DrawText("PUSHING", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 9) {
		CP_Font_DrawText("YOUR", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 9.4) {
		CP_Font_DrawText("BUTTONS", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 9.7) {
		CP_Font_DrawText("AND", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 10) {
		CP_Font_DrawText("YOU'RE", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 10.4) {
		CP_Font_DrawText("THE", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 11.5) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("DUMMY.", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 11.5) {
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	}
	else if (time > 11.4)
		TransitScene(Level8);
}


void CutScene8Exit() {
	shootPressed = FALSE;
	rightPressed = FALSE;
	leftPressed = FALSE;
	time = 0;
}