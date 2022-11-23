#include <stdio.h>
#include "cprocessing.h"
#include "utils.h"
#include "level.h"
#include "scenes.h"

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
float rect3_x = 0.f;
float rect3_y = 0.f;
float rect3_width = 0.f;
float rect3_height = 0.f;
float rect4_x = 0.f;
float rect4_y = 0.f;
float rect4_width = 0.f;
float rect4_height = 0.f;
float rect5_x = 0.f;
float rect5_y = 0.f;
float rect5_width = 0.f;
float rect5_height = 0.f;
float text_size = 50.f;
CP_BOOL is_rect1_clicked = 0;
CP_BOOL is_rect2_clicked = 0;
CP_BOOL is_rect3_clicked = 0;
CP_BOOL is_rect4_clicked = 0;
CP_BOOL is_rect5_clicked = 0;
CP_Color rect_color;
CP_Image background = NULL;

void Main_Menu_Init()
{
	background = CP_Image_Load("./Assets/marked.png");

	windowWidth = CP_System_GetDisplayWidth();
	windowHeight = CP_System_GetDisplayHeight();
	windowWidth = 1920;
	windowHeight = 900;
	CP_System_SetWindowSize(windowWidth, windowHeight);
	//START
	rect1_x = windowWidth / 2.f;
	rect1_y = windowHeight / 2.5f + 190.f;
	rect1_width = windowWidth / 13.f;
	rect1_height = windowHeight / 14.f;
	// EXIT
	rect2_x = windowWidth / 2.f;
	rect2_y = windowHeight / 2.5f + 510.f;
	rect2_width = windowWidth / 13.f;
	rect2_height = windowHeight / 14.f;
	// SELECT LEVEL
	rect4_x = windowWidth / 2.f;
	rect4_y = windowHeight / 2.5f + 270.f;
	rect4_width = windowWidth / 7.f;
	rect4_height = windowHeight / 14.f;
	// HOW TO PLAY
	rect3_x = windowWidth / 2.f;
	rect3_y = windowHeight / 2.5f + 350.f;
	rect3_width = windowWidth / 7.f;
	rect3_height = windowHeight / 14.f;
	//CREDITS
	rect5_x = windowWidth / 2.f;
	rect5_y = windowHeight / 2.5f + 430.f;
	rect5_width = windowWidth / 12.f;
	rect5_height = windowHeight / 14.f;
	rect_color = CP_Color_Create(250, 160, 160, 0);
	printf("init complete\n");
}

void Main_Menu_Update()
{
	int width = CP_Image_GetWidth(background);
	int height = CP_Image_GetHeight(background);
	int windowWidth = CP_System_GetWindowWidth();
	int windowHeight = CP_System_GetWindowHeight();

	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));
	CP_Image_Draw(background, (float)windowWidth / 2.f, (float)windowHeight / 2.f, (float)windowWidth, (float)windowHeight, 255);

	CP_Graphics_ClearBackground(CP_Color_Create(128, 0, 0, 255));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_TextSize(text_size);

	CP_Settings_Fill(rect_color);
	CP_Graphics_DrawRect(rect1_x, rect1_y, rect1_width, rect1_height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("START", rect1_x - rect1_width / 2.f, rect1_y, rect1_width);

	CP_Settings_Fill(rect_color);
	CP_Graphics_DrawRect(rect4_x, rect4_y, rect4_width, rect4_height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("LEVEL SELECT", rect4_x - rect4_width / 2.f, rect4_y, rect4_width);

	CP_Settings_Fill(rect_color);
	CP_Graphics_DrawRect(rect3_x, rect3_y, rect3_width, rect3_height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("HOW TO PLAY", rect3_x - rect3_width / 2.f, rect3_y, rect3_width);

	CP_Settings_Fill(rect_color);
	CP_Graphics_DrawRect(rect5_x, rect5_y, rect5_width, rect5_height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("CREDITS", rect5_x - rect5_width / 2.f, rect5_y, rect5_width);

	CP_Settings_Fill(rect_color);
	CP_Graphics_DrawRect(rect2_x, rect2_y, rect2_width, rect2_height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("EXIT", rect2_x - rect2_width / 2.f, rect2_y, rect2_width);

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	is_rect1_clicked = IsAreaClicked(rect1_x, rect1_y, rect1_width, rect1_height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	is_rect2_clicked = IsAreaClicked(rect2_x, rect2_y, rect2_width, rect2_height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	is_rect3_clicked = IsAreaClicked(rect3_x, rect3_y, rect3_width, rect3_height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	is_rect4_clicked = IsAreaClicked(rect4_x, rect4_y, rect4_width, rect4_height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	is_rect5_clicked = IsAreaClicked(rect5_x, rect5_y, rect5_width, rect5_height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	if (is_rect1_clicked) {
		TransitScene(Level1);
	}
	if (is_rect2_clicked) {
		CP_Engine_Terminate();
	}
	if (is_rect3_clicked) {
		TransitScene(Level0);
	}
	if (is_rect4_clicked) {
		CP_Engine_SetNextGameState(StageSelect_Init, StageSelect_Update, StageSelect_Exit);
	}
	if (is_rect5_clicked) {
		CP_Engine_SetNextGameState(CreditsInit, CreditsUpdate, CreditsExit);
	}
}

void Main_Menu_Exit()
{
	CP_Image_Free(&background);
}