#include <stdio.h>
#include "cprocessing.h"
#include "utils.h"
#include "level.h"
#include "scenes.h"
#include "logo.h"

int windowWidth = 0;
int windowHeight = 0;

float rect1X = 0.f;
float rect1Y = 0.f;
float rect1Width = 0.f;
float rect1Height = 0.f;
float rect2X = 0.f;
float rect2Y = 0.f;
float rect2Width = 0.f;
float rect2Height = 0.f;
float rect3X = 0.f;
float rect3Y = 0.f;
float rect3Width = 0.f;
float rect3Height = 0.f;
float rect4X = 0.f;
float rect4Y = 0.f;
float rect4Width = 0.f;
float rect4Height = 0.f;
float rect5X = 0.f;
float rect5Y = 0.f;
float rect5Width = 0.f;
float rect5Height = 0.f;
float textSize = 50.f;
CP_BOOL isRect1Clicked = 0;
CP_BOOL isRect2Clicked = 0;
CP_BOOL isRect3Clicked = 0;
CP_BOOL isRect4Clicked = 0;
CP_BOOL isRect5Clicked = 0;
CP_Color rectColor;
CP_Image background = NULL;

void MainMenuInit()
{
	background = CP_Image_Load("./Assets/marked.png");

	windowWidth = CP_System_GetDisplayWidth();
	windowHeight = CP_System_GetDisplayHeight();
	windowWidth = 1920;
	windowHeight = 900;
	CP_System_SetWindowSize(windowWidth, windowHeight);
	//START
	rect1X = windowWidth / 2.f;
	rect1Y = windowHeight / 2.5f + 190.f;
	rect1Width = windowWidth / 13.f;
	rect1Height = windowHeight / 14.f;
	// EXIT
	rect2X = windowWidth / 2.f;
	rect2Y = windowHeight / 2.5f + 510.f;
	rect2Width = windowWidth / 13.f;
	rect2Height = windowHeight / 14.f;
	// SELECT LEVEL
	rect4X = windowWidth / 2.f;
	rect4Y = windowHeight / 2.5f + 270.f;
	rect4Width = windowWidth / 7.f;
	rect4Height = windowHeight / 14.f;
	// HOW TO PLAY
	rect3X = windowWidth / 2.f;
	rect3Y = windowHeight / 2.5f + 350.f;
	rect3Width = windowWidth / 7.f;
	rect3Height = windowHeight / 14.f;
	//CREDITS
	rect5X = windowWidth / 2.f;
	rect5Y = windowHeight / 2.5f + 430.f;
	rect5Width = windowWidth / 12.f;
	rect5Height = windowHeight / 14.f;
	rectColor = CP_Color_Create(250, 160, 160, 0);
	printf("init complete\n");
}

void MainMenuUpdate()
{
	int Width = CP_Image_GetWidth(background);
	int Height = CP_Image_GetHeight(background);
	int WindowWidth = CP_System_GetWindowWidth();
	int WindowHeight = CP_System_GetWindowHeight();

	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));
	CP_Image_Draw(background, (float)WindowWidth / 2.f, (float)WindowHeight / 2.f, (float)WindowWidth, (float)WindowHeight, 255);

	CP_Graphics_ClearBackground(CP_Color_Create(128, 0, 0, 255));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_TextSize(textSize);

	CP_Settings_Fill(rectColor);
	CP_Graphics_DrawRect(rect1X, rect1Y, rect1Width, rect1Height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("START", rect1X - rect1Width / 2.f, rect1Y, rect1Width);

	CP_Settings_Fill(rectColor);
	CP_Graphics_DrawRect(rect4X, rect4Y, rect4Width, rect4Height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("LEVEL SELECT", rect4X - rect4Width / 2.f, rect4Y, rect4Width);

	CP_Settings_Fill(rectColor);
	CP_Graphics_DrawRect(rect3X, rect3Y, rect3Width, rect3Height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("HOW TO PLAY", rect3X - rect3Width / 2.f, rect3Y, rect3Width);

	CP_Settings_Fill(rectColor);
	CP_Graphics_DrawRect(rect5X, rect5Y, rect5Width, rect5Height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("CREDITS", rect5X - rect5Width / 2.f, rect5Y, rect5Width);

	CP_Settings_Fill(rectColor);
	CP_Graphics_DrawRect(rect2X, rect2Y, rect2Width, rect2Height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("EXIT", rect2X - rect2Width / 2.f, rect2Y, rect2Width);

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	isRect1Clicked = IsAreaClicked(rect1X, rect1Y, rect1Width, rect1Height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	isRect2Clicked = IsAreaClicked(rect2X, rect2Y, rect2Width, rect2Height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	isRect3Clicked = IsAreaClicked(rect3X, rect3Y, rect3Width, rect3Height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	isRect4Clicked = IsAreaClicked(rect4X, rect4Y, rect4Width, rect4Height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	isRect5Clicked = IsAreaClicked(rect5X, rect5Y, rect5Width, rect5Height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	if (isRect1Clicked) {
		TransitScene(Level1);
	}
	if (isRect2Clicked) {
		CP_Engine_Terminate();
	}
	if (isRect3Clicked) {
		TransitScene(Level0);
	}
	if (isRect4Clicked) {
		CP_Engine_SetNextGameState(StageSelectInit, StageSelectUpdate, StageSelectExit);
	}
	if (isRect5Clicked) {
		CP_Engine_SetNextGameState(CreditsInit, CreditsUpdate, CreditsExit);
	}
}

void MainMenuExit()
{
	CP_Image_Free(&background);
}