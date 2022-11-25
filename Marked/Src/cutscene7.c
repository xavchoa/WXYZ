//---------------------------------------------------------
// file:	cutscene7.c
// author:	[Xavier Choa]
// email:	[k.choa@digipen.edu]
//
// brief:	Code for cutscene for level 7
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <stdlib.h>
#include <math.h>
#include "cprocessing.h"
#include "level.h"
#include "game.h"
#include "scenes.h"

float time;

void CutScene7Init() {
	CP_System_SetFrameRate(60);
	time = 0;
}

void CutScene7Update() {
	CP_Settings_TextSize(400);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	time += CP_System_GetDt();
	if (time < .5)
		CP_Font_DrawText("NO", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 1)
		CP_Font_DrawText("SHAME", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 1.3)
		CP_Font_DrawText("IF", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 1.6) {
		CP_Font_DrawText("YOU", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 1.9)
		CP_Font_DrawText("CAN'T", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 2.5)
		CP_Font_DrawText("SOLVE", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 3)
		CP_Font_DrawText("THIS", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 4)
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	else if (time < 4.5)
		CP_Font_DrawText("YOU'RE", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 5) {
		CP_Font_DrawText("JUST", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 5.5) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("NOT", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 6) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("GOOD", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 7) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("ENOUGH", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 7.5)
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	else if (time > 7.5)
		TransitScene(Level7);
}


void CutScene7Exit() {
	time = 0;
}