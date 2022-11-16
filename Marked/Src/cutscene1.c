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
CP_Image bg = NULL;

void Cutscene1_Init() {
	CP_System_SetFrameRate(60);
	float time = 0;
	bg = CP_Image_Load("./Assets/marked.png");
}

void Cutscene1_Update() {
	CP_Settings_TextSize(400);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	time += CP_System_GetDt();
	if (time < .5)
		CP_Font_DrawText("THAT", windowWidth / 2, windowHeight / 2);
	else if (time < 1)
		CP_Font_DrawText("WAS", windowWidth / 2, windowHeight / 2);
	else if (time < 1.5)
		CP_Font_DrawText("TOO", windowWidth / 2, windowHeight / 2);
	else if (time < 2.5) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("EASY", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 3)
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	else if (time < 3.5)
		CP_Font_DrawText("LET'S", windowWidth / 2, windowHeight / 2);
	else if (time < 3.8)
		CP_Font_DrawText("RAMP", windowWidth / 2, windowHeight / 2);
	else if (time < 4.2)
		CP_Font_DrawText("UP", windowWidth / 2, windowHeight / 2);
	else if (time < 4.7)
		CP_Font_DrawText("THE", windowWidth / 2, windowHeight / 2);
	else if (time < 6) {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawText("DIFFICULTY", windowWidth / 2, windowHeight / 2);
	}
	else if (time < 7)
		CP_Image_Draw(bg, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);
	else if (time > 7)
		TransitScene(Level4);
}


void Cutscene1_Exit() {
	time = 0;
}

		




