#include <stdio.h>
#include "cprocessing.h"
#include "utils.h"
#include "level.h"
#include "mainmenu.h"
#include "scenes.h"


int windowWidth;
int windowHeight;

float rect1X ;
float rect1Y ;
float rect1Width ;
float rect1Height;

float rect2X ;
float rect2Y ;
float rect2Width ;
float rect2Height ;

float rect3X ;
float rect3Y ;
float rect3Width;
float rect3Height;

float rect4X;
float rect4Y ;
float rect4Width;
float rect4Height;

float rect5X ;
float rect5Y ;
float rect5Width ;
float rect5Height;

float rect6X ;
float rect6Y ;
float rect6Width ;
float rect6Height ;

float rect7X ;
float rect7Y ;
float rect7Width;
float rect7Height;

float rect8X;
float rect8Y;
float rect8Width;
float rect8Height;

float rect9X;
float rect9Y;
float rect9Width;
float rect9Height;

float rect10X;
float rect10Y;
float rect10Width;
float rect10Height;

float rectHeaderX;
float rectHeaderY;
float rectHeaderWidth;
float rectHeaderHeight;

float rectBackX;
float rectBackY;
float rectBackWidth ;
float rectBackHeight;

float textSize;

CP_BOOL isRect1Clicked ;
CP_BOOL isRect2Clicked ;
CP_BOOL isRect3Clicked ;
CP_BOOL isRect4Clicked ;
CP_BOOL isRect5Clicked ;
CP_BOOL isRect6Clicked = 0;
CP_BOOL isRect7Clicked = 0;
CP_BOOL isRect8Clicked = 0;
CP_BOOL isRect9Clicked = 0;
CP_BOOL isRect10Clicked = 0;
CP_BOOL isRectBackClicked;

CP_Color rectColor;
CP_Color rectColorHeader;
CP_Image background;

void StageSelectInit()
{

	windowWidth = CP_System_GetDisplayWidth();
	windowHeight = CP_System_GetDisplayHeight();
	windowWidth = 1920;
	windowHeight = 900;
	CP_System_SetWindowSize(windowWidth, windowHeight);
	rectColorHeader = CP_Color_Create(0, 0, 0, 0);
	rectColor = CP_Color_Create(128, 0, 0, 255);

	// BACK + HEADER
	rectBackX = windowWidth / 2.f - 840.f;
	rectBackY = windowHeight / 2.f - 395.f;
	rectBackWidth = windowWidth / 15.f;
	rectBackHeight = windowHeight / 16.f;

	rectHeaderX = windowWidth / 2.f;
	rectHeaderY = windowHeight / 2.f - 400.f;
	rectHeaderWidth = windowWidth / 2.f;
	rectHeaderHeight = windowHeight / 7.f;
	
	// row 1
	rect1X = windowWidth / 3.f;
	rect1Y = windowHeight / 2.f - 275.f;
	rect1Width = windowWidth / 4.f;
	rect1Height = windowHeight / 7.f;

	rect2X = windowWidth / 1.5f;
	rect2Y = windowHeight / 2.f - 275.f;
	rect2Width = windowWidth / 4.f;
	rect2Height = windowHeight / 7.f;

	// row 2
	rect3X = windowWidth / 3.f;
	rect3Y = windowHeight / 2.f - 125.f;
	rect3Width = windowWidth / 4.f;
	rect3Height = windowHeight / 7.f;
	
	rect4X = windowWidth / 1.5f;
	rect4Y = windowHeight / 2.f - 125.f;
	rect4Width = windowWidth / 4.f;
	rect4Height = windowHeight / 7.f;

	// row 3
	rect5X = windowWidth / 3.f;
	rect5Y = windowHeight / 2.f + 25.f;
	rect5Width = windowWidth / 4.f;
	rect5Height = windowHeight / 7.f;

	rect6X = windowWidth / 1.5f;
	rect6Y = windowHeight / 2.f + 25.f;
	rect6Width = windowWidth / 4.f;
	rect6Height = windowHeight / 7.f;

	// row 4
	rect7X = windowWidth / 3.f;
	rect7Y = windowHeight / 2.f + 175.f;
	rect7Width = windowWidth / 4.f;
	rect7Height = windowHeight / 7.f;

	rect8X = windowWidth / 1.5f;
	rect8Y = windowHeight / 2.f + 175.f;
	rect8Width = windowWidth / 4.f;
	rect8Height = windowHeight / 7.f;

	// row 5
	rect9X = windowWidth / 3.f;
	rect9Y = windowHeight / 2.f + 325.f;
	rect9Width = windowWidth / 4.f;
	rect9Height = windowHeight / 7.f;

	rect10X = windowWidth / 1.5f;
	rect10Y = windowHeight / 2.f + 325.f;
	rect10Width = windowWidth / 4.f;
	rect10Height = windowHeight / 7.f;

	textSize = 70.f;
}

void StageSelectUpdate()
{
	int width_SS = CP_Image_GetWidth(background);
	int height_SS = CP_Image_GetHeight(background);
	int windowWidth_SS = CP_System_GetWindowWidth();
	int windowHeight_SS = CP_System_GetWindowHeight();
	CP_Settings_NoStroke();

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(background, (float)windowWidth_SS / 2.f, (float)windowHeight_SS / 2.f, (float)windowWidth_SS, (float)windowHeight_SS, 255);

	// BACK + HEADER
	CP_Settings_Fill(rectColorHeader);
	CP_Graphics_DrawRect(rectBackX, rectBackY, rectBackWidth, rectBackHeight);
	CP_Settings_Fill(CP_Color_Create(160, 0, 0, 255));
	CP_Graphics_DrawTriangleAdvanced(80.0f, 34.5f, 105.0f, 64.5f, 55.0f, 64.5f, 270.0f);
	CP_Graphics_DrawQuadAdvanced(130.0f, 10.0f, 140.0f, 10.0f, 140.0f, 100.0f, 130.0f, 100.0f, 90.0f);
	CP_Graphics_DrawQuadAdvanced(170.0f, 30.0f, 180.0f, 30.0f, 180.0f, 60.0f, 170.0f, 60.0f, 0.0f);

	CP_Settings_Fill(rectColorHeader);
	CP_Graphics_DrawRect(rectHeaderX, rectHeaderY, rectHeaderWidth, rectHeaderHeight);
	CP_Settings_Fill(CP_Color_Create(160, 0, 0, 255));
	CP_Font_DrawTextBox("CHOOSE YOUR POISON!", rectHeaderX - rectHeaderWidth / 2.f, rectHeaderY, rectHeaderWidth);

	// row 1
	CP_Settings_Fill(rectColor);
	CP_Graphics_DrawRect(rect1X, rect1Y, rect1Width, rect1Height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 1", rect1X - rect1Width / 2.f, rect1Y, rect1Width);

	CP_Settings_Fill(rectColor);
	CP_Graphics_DrawRect(rect2X, rect2Y, rect2Width, rect2Height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 2", rect2X - rect2Width / 2.f, rect2Y, rect2Width);

	// row 2
	CP_Settings_Fill(rectColor);
	CP_Graphics_DrawRect(rect3X, rect3Y, rect3Width, rect3Height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 3", rect3X - rect3Width / 2.f, rect3Y, rect3Width);

	CP_Settings_Fill(rectColor);
	CP_Graphics_DrawRect(rect4X, rect4Y, rect4Width, rect4Height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 4", rect4X - rect4Width / 2.f, rect4Y, rect4Width);

	// row 3
	CP_Settings_Fill(rectColor);
	CP_Graphics_DrawRect(rect5X, rect5Y, rect5Width, rect5Height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 5", rect5X - rect5Width / 2.f, rect5Y, rect5Width);

	CP_Settings_Fill(rectColor);
	CP_Graphics_DrawRect(rect6X, rect6Y, rect6Width, rect6Height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 6", rect6X - rect6Width / 2.f, rect6Y, rect6Width);

	// row 4
	CP_Settings_Fill(rectColor);
	CP_Graphics_DrawRect(rect7X, rect7Y, rect7Width, rect7Height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 7", rect7X - rect7Width / 2.f, rect7Y, rect7Width);

	CP_Settings_Fill(rectColor);
	CP_Graphics_DrawRect(rect8X, rect8Y, rect8Width, rect8Height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 8", rect8X - rect8Width / 2.f, rect8Y, rect8Width);

	// row 5
	CP_Settings_Fill(rectColor);
	CP_Graphics_DrawRect(rect3X, rect9Y, rect9Width, rect9Height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 9", rect9X - rect9Width / 2.f, rect9Y, rect9Width);

	CP_Settings_Fill(rectColor);
	CP_Graphics_DrawRect(rect10X, rect10Y, rect10Width, rect10Height);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 10", rect10X - rect10Width / 2.f, rect10Y, rect10Width);


	isRect1Clicked = IsAreaClicked(rect1X, rect1Y, rect1Width, rect1Height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	isRect2Clicked = IsAreaClicked(rect2X, rect2Y, rect2Width, rect2Height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	isRect3Clicked = IsAreaClicked(rect3X, rect3Y, rect3Width, rect3Height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	isRect4Clicked = IsAreaClicked(rect4X, rect4Y, rect4Width, rect4Height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	isRect5Clicked = IsAreaClicked(rect5X, rect5Y, rect5Width, rect5Height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	isRect6Clicked = IsAreaClicked(rect6X, rect6Y, rect6Width, rect6Height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	isRect7Clicked = IsAreaClicked(rect7X, rect7Y, rect7Width, rect7Height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	isRect8Clicked = IsAreaClicked(rect8X, rect8Y, rect8Width, rect8Height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	isRect9Clicked = IsAreaClicked(rect9X, rect9Y, rect9Width, rect9Height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	isRect10Clicked = IsAreaClicked(rect10X, rect10Y, rect10Width, rect10Height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	isRectBackClicked = IsAreaClicked(rectBackX, rectBackY, rectBackWidth, rectBackHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	if (isRect1Clicked) {
		TransitScene(Level1);
	}
	if (isRect2Clicked) {
		TransitScene(Level2);
	}
	if (isRect3Clicked) {
		TransitScene(Level3);
	}
	if (isRect4Clicked) {
		TransitScene(Cutscene1);
	}
	if (isRect5Clicked) {
		TransitScene(Level5);
	}
	if (isRect6Clicked) {
		TransitScene(Level6);
	}
	if (isRect7Clicked) {
		TransitScene(Cutscene7);
	}
	if (isRect8Clicked) {
		TransitScene(Cutscene8);
	}
	if (isRect9Clicked) {
		TransitScene(Cutscene9);
	}
	if (isRect10Clicked) {
		TransitScene(Cutscene10);
	}
	if (isRectBackClicked) {
		TransitScene(Main_Menu);
	}

}

void StageSelectExit()
{
	CP_Image_Free(&background);
}