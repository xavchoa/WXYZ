//---------------------------------------------------------
// file:	credits.c
// author:	[CHEONG YU QING]
// email:	[c.yuqing@digipen.edu]
//
// brief:	credits
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
//---------------------------------------------------------



#include <stdio.h>
#include "cprocessing.h"
#include "utils.h"
#include "level.h"
#include "mainmenu.h"
#include "scenes.h"

float windowW = 0.f;
float windowH = 0.f;

float RectBackX = 0.f;
float RectBackY= 0.f;
float RectBackWidth = 0.f;
float RectBackHeight = 0.f;

float TextSizeHeader = 80.f;
float TextSizeSubHeader = 60.f;
float TextSize = 40.f;
float TextSizeCopy = 30.f;

CP_BOOL isRectBackClicked = 0;
CP_Color RectColor;


void CreditsInit()
{

	windowW = (float)CP_System_GetDisplayWidth();
	windowH = (float)CP_System_GetDisplayHeight();
	windowW = 1920.f;
	windowH = 900.f;
	CP_System_SetWindowSize((int)windowW, (int)windowH);

	RectBackX = windowW / 2.f - 840.f;
	RectBackY = windowH / 2.f - 395.f;
	RectBackWidth = windowW / 15.f;
	RectBackHeight = windowH / 16.f;
	RectColor = CP_Color_Create(0, 0, 0, 0);
}

void CreditsUpdate()
{


	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_NoStroke();
	CP_Settings_RectMode(CP_POSITION_CENTER);



	//// BACK 
	CP_Settings_Fill(RectColor);
	CP_Graphics_DrawRect(RectBackX, RectBackY, RectBackWidth, RectBackHeight);
	CP_Settings_Fill(CP_Color_Create(160, 0, 0, 255));
	CP_Graphics_DrawTriangleAdvanced(80.0f, 34.5f, 105.0f, 64.5f, 55.0f, 64.5f, 270.0f);
	CP_Graphics_DrawQuadAdvanced(130.0f, 10.0f, 140.0f, 10.0f, 140.0f, 100.0f, 130.0f, 100.0f, 90.0f);
	CP_Graphics_DrawQuadAdvanced(170.0f, 30.0f, 180.0f, 30.0f, 180.0f, 60.0f, 170.0f, 60.0f, 0.0f);

	CP_Settings_TextSize(TextSizeHeader);
	CP_Font_DrawText("TEAM: WXYZ", windowW / 2.f, windowH * 0.05f );

	CP_Settings_TextSize(TextSizeSubHeader);
	CP_Font_DrawText("MEMBERS", windowW / 3.f, windowH * 0.15f);
	CP_Font_DrawText("INSTRUCTORS", windowW / 1.5f, windowH * 0.15f);
	CP_Font_DrawText("PRESIDENT", windowW / 2.f, windowH * 0.55f);
	CP_Font_DrawText("EXECUTIVES", windowW / 2.f, windowH * 0.7f);


	CP_Settings_TextSize(TextSize);
	CP_Settings_Fill(CP_Color_Create(255,255, 255, 255));
	//members
	CP_Font_DrawText("Choa Kai Rong, Xavier", windowW / 3.f, windowH * 0.2f);
	CP_Font_DrawText("Cheong Yu Qing", windowW / 3.f, windowH * 0.25f);
	CP_Font_DrawText("Liu WanTing", windowW / 3.f, windowH * 0.3f);
	CP_Font_DrawText("Tan Zhi Xin, Darien", windowW / 3.f, windowH * 0.35f);

	// instructor
	CP_Font_DrawText("Gerald Wong", windowW / 1.5f, windowH * 0.2f);
	CP_Font_DrawText("Ding Xiang Cheng", windowW / 1.5f, windowH * 0.25f);

	CP_Font_DrawText("Created at DigiPen Institute of Technology Singapore", windowW / 2.f, windowH * 0.45f);

	//President
	CP_Font_DrawText("Claude Comair", windowW / 2.f, windowH * 0.6f);

	//EXECUTIVES
	CP_Font_DrawTextBox("John Bauer     Samir Abou Samra     Christopher Comair     Michele Comair\nMelvin Gonsalvez     Dr. Charles Duba     Johnny Deek"
					"Michael Gats\nJason Chu     Ben Ellinger     Prasanna Ghali\nRaymond Yan     Dr. Erik Mohrmann     Angela Kugler", windowW / 22.f, windowH * 0.75f, 1800);



	CP_Settings_TextSize(TextSizeCopy);

	CP_Font_DrawText("All content (C) 2022 DigiPen Institute of Technology Singapore. All Rights Reserved", windowW / 2.f, windowH * 0.98f);





	isRectBackClicked = IsAreaClicked(RectBackX, RectBackY, RectBackWidth, RectBackHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY());

	if (isRectBackClicked) {
		TransitScene(Main_Menu);
	}

}

void CreditsExit()
{

}