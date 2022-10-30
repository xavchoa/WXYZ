#include <stdio.h>
#include "cprocessing.h"
#include "utils.h"
#include "level.h"

int windowWidth = 0;
int windowHeight = 0;

float rect1_x = 0.f;
float rect1_y = 0.f;
float rect1_width = 0.f;
float rect1_height = 0.f;
float rect2_x = 0.f;
float rect2_y = 0.f;
float rect2_width = 0.f;
float rect2_height = 0.f;
float text_size = 70.f;
CP_BOOL is_rect1_clicked = 0;
CP_BOOL is_rect2_clicked = 0;
CP_Color rect_color;


void Main_Menu_Init()
{
	windowWidth = CP_System_GetDisplayWidth();
	windowHeight = CP_System_GetDisplayHeight();
	windowWidth = 1920;
	windowHeight = 900;
	CP_System_SetWindowSize(windowWidth, windowHeight);
	rect1_x = windowWidth / 2.f;
	rect1_y = windowHeight / 2.f - 150.f;
	rect1_width = windowWidth / 6.f;
	rect1_height = windowHeight/ 6.f;
	rect2_x = windowWidth / 2.f;
	rect2_y = windowHeight / 2.f + 150.f;
	rect2_width = windowWidth / 6.f;
	rect2_height = windowHeight / 6.f;
	rect_color = CP_Color_Create(250,160,160,255);
	printf("init complete\n");
}

void Main_Menu_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(128,0,0,255));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_TextSize(text_size);

	CP_Settings_Fill(rect_color);
	CP_Graphics_DrawRect(rect1_x, rect1_y, rect1_width, rect1_height);
	CP_Settings_Fill(CP_Color_Create(0,0,0,255));
	CP_Font_DrawTextBox("START", rect1_x - rect1_width /2.f, rect1_y, rect1_width);

	CP_Settings_Fill(rect_color);
	CP_Graphics_DrawRect(rect2_x, rect2_y, rect2_width, rect2_height);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawTextBox("EXIT", rect2_x - rect2_width /2.f, rect2_y, rect2_width);
	
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	is_rect1_clicked = IsAreaClicked(rect1_x, rect1_y, rect1_width, rect1_height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	is_rect2_clicked = IsAreaClicked(rect2_x, rect2_y, rect2_width, rect2_height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	if (is_rect1_clicked) {
		CP_Engine_SetNextGameState(Level_Init, Level_Update, Level_Exit);
	}
	if (is_rect2_clicked) {
		CP_Engine_Terminate();
	}
	
	
	
}

void Main_Menu_Exit()
{

}