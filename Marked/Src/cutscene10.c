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

void Cutscene10_Init() {
	CP_System_SetFrameRate(60);
	float time = 0;
}

void Cutscene10_Update() {
	CP_Settings_TextSize(400);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	time += CP_System_GetDt();
	if (time < .3)
		CP_Font_DrawText("GIVE", windowWidth / 2, windowHeight / 2);
	else if (time < .6)
		CP_Font_DrawText("UP", windowWidth / 2, windowHeight / 2);
	else if (time < 1.6) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("MARKSMAN", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 2.6) 
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	else if (time < 3.6) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Font_DrawText("NO?", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 4.1)
		CP_Font_DrawText("I", windowWidth / 2, windowHeight / 2);
	else if (time < 4.8) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("WARNED", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 5.3) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Font_DrawText("YOU", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 6.3)
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	else if (time < 6.8)
		CP_Font_DrawText("HOPE", windowWidth / 2, windowHeight / 2);
	else if (time < 7.3) {
		CP_Font_DrawText("YOU", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 7.8)
		CP_Font_DrawText("LIKE", windowWidth / 2, windowHeight / 2);
	else if (time < 8.8) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("LASERS", windowWidth / 2, windowHeight / 2);
	}
	else if(time < 9.3)
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	else if (time > 9.3)
		TransitScene(Level10);
}


void Cutscene10_Exit() {
	time = 0;
}

		



