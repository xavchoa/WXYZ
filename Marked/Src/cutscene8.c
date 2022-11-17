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

void Cutscene8_Init() {
	CP_System_SetFrameRate(60);
	float time = 0;
}

void Cutscene8_Update() {
	CP_Settings_TextSize(400);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	time += CP_System_GetDt();
	if (time < .5)
		CP_Font_DrawText("I", windowWidth / 2, windowHeight / 2);
	else if (time < 1)
		CP_Font_DrawText("NAMED", windowWidth / 2, windowHeight / 2);
	else if (time < 1.3)
		CP_Font_DrawText("THE", windowWidth / 2, windowHeight / 2);
	else if (time < 1.6) {
		CP_Font_DrawText("NEXT", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 2)
		CP_Font_DrawText("LEVEL", windowWidth / 2, windowHeight / 2);
	else if (time < 2.5)
		CP_Font_DrawText("AFTER", windowWidth / 2, windowHeight / 2);
	else if (time < 3) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("YOU", windowWidth / 2, windowHeight / 2);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	}
	else if (time < 4)
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	else if (time < 5)
		CP_Font_DrawText("DOORS", windowWidth / 2, windowHeight / 2);
	else if (time < 5.5) {
		CP_Font_DrawText("AND", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 6.5) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("DUMMIES", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 7.5)
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	else if (time < 8.5) {
		CP_Font_DrawText("YOU", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 9.5) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("DUMMY.", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 9.8) {
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	}
	else if (time > 9.8)
		TransitScene(Level8);
}


void Cutscene8_Exit() {
	time = 0;
}

		




