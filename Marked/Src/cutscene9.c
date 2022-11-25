#include <cprocessing.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "mainmenu.h"
#include "level.h"
#include "game.h"
#include "scenes.h"

float time;

void CutScene9Init() {
	CP_System_SetFrameRate(60);
	time = 0;
}

void CutScene9Update() {
	CP_Settings_TextSize(400);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	time += CP_System_GetDt();
	if (time < .5)
		CP_Font_DrawText("YOU", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 1)
		CP_Font_DrawText("THINK", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 1.5)
		CP_Font_DrawText("YOU'RE", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 2) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("FAST?", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 3)
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	else if (time < 3.5)
		CP_Font_DrawText("WELL...", (float)windowWidth / 2.f, (float)windowHeight/ 2.f);
	else if (time < 3.8)
		CP_Font_DrawText(".", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 4.2)
		CP_Font_DrawText("..", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 4.7)
		CP_Font_DrawText("...", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	else if (time < 5) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("THINK", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time < 5.3) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("FASTER", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	}
	else if (time > 5.3)
		TransitScene(Level9);
}


void CutScene9Exit() {
	time = 0;
}

		




