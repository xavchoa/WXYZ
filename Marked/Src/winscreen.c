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

void Winscene_Init() {
	CP_System_SetFrameRate(60);
	float time = 0;
}

void Winscene_Update() {
	CP_Settings_TextSize(400);
	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	time += CP_System_GetDt();
	if (time < .5)
		CP_Font_DrawText("CONGRATS", windowWidth / 2, windowHeight / 2);
	else if (time < 1)
		CP_Font_DrawText("MARKSMAN!", windowWidth / 2, windowHeight / 2);
	else if (time < 1.5)
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	else if (time < 2)
		CP_Font_DrawText("YOU", windowWidth / 2, windowHeight / 2);
	else if (time < 2.5) {
		CP_Font_DrawText("MADE", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 3)
		CP_Font_DrawText("IT", windowWidth / 2, windowHeight / 2);
	else if (time < 4)
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	else if (time < 4.5)
		CP_Font_DrawText("NOW", windowWidth / 2, windowHeight / 2);
	else if (time < 5)
		CP_Font_DrawText("WHAT?", windowWidth / 2, windowHeight / 2);
	else if (time < 5.5)
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	else if (time < 6.5) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("THERE", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 7.5) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("IS", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 8.5) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("NO", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 9.5) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("END.", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 10.5)
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	else if (time > 10.5)
		TransitScene(Level10);
}


void Winscene_Exit() {
	time = 0;
}

		




