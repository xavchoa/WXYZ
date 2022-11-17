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

void Cutscene9_Init() {
	CP_System_SetFrameRate(60);
	float time = 0;
}

void Cutscene9_Update() {
	CP_Settings_TextSize(400);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	time += CP_System_GetDt();
	if (time < .5)
		CP_Font_DrawText("YOU", windowWidth / 2, windowHeight / 2);
	else if (time < 1)
		CP_Font_DrawText("THINK", windowWidth / 2, windowHeight / 2);
	else if (time < 1.5)
		CP_Font_DrawText("YOU'RE", windowWidth / 2, windowHeight / 2);
	else if (time < 2) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("FAST?", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 3)
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	else if (time < 3.5)
		CP_Font_DrawText("WELL...", windowWidth / 2, windowHeight / 2);
	else if (time < 3.8)
		CP_Font_DrawText(".", windowWidth / 2, windowHeight / 2);
	else if (time < 4.2)
		CP_Font_DrawText("..", windowWidth / 2, windowHeight / 2);
	else if (time < 4.7)
		CP_Font_DrawText("...", windowWidth / 2, windowHeight / 2);
	else if (time < 5) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("THINK", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 5.3) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("FASTER", windowWidth / 2, windowHeight / 2);
	}
	else if (time > 5.3)
		TransitScene(Level9);
}


void Cutscene9_Exit() {
	time = 0;
}

		




