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

void Cutscene7_Init() {
	CP_System_SetFrameRate(60);
	float time = 0;
}

void Cutscene7_Update() {
	CP_Settings_TextSize(400);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	time += CP_System_GetDt();
	if (time < .5)
		CP_Font_DrawText("NO", windowWidth / 2, windowHeight / 2);
	else if (time < 1)
		CP_Font_DrawText("SHAME", windowWidth / 2, windowHeight / 2);
	else if (time < 1.3)
		CP_Font_DrawText("IF", windowWidth / 2, windowHeight / 2);
	else if (time < 1.6) {
		CP_Font_DrawText("YOU", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 1.9)
		CP_Font_DrawText("CAN'T", windowWidth / 2, windowHeight / 2);
	else if (time < 2.5)
		CP_Font_DrawText("SOLVE", windowWidth / 2, windowHeight / 2);
	else if (time < 3)
		CP_Font_DrawText("THIS", windowWidth / 2, windowHeight / 2);
	else if (time < 4)
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	else if (time < 4.5)
		CP_Font_DrawText("YOU'RE", windowWidth / 2, windowHeight / 2);
	else if (time < 5) {
		CP_Font_DrawText("JUST", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 5.5) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("NOT", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 6) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("GOOD", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 7) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("ENOUGH", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 7.5)
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	else if (time > 7.5)
		TransitScene(Level7);
}


void Cutscene7_Exit() {
	time = 0;
}

		




