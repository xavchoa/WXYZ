#include <stdio.h>
#include "cprocessing.h"
#include "utils.h"
#include "level.h"
#include "mainmenu.h"
#include "scenes.h"


int windowWidth_SS = 0;
int windowHeight_SS = 0;

float rect1_x_SS = 0.f;
float rect1_y_SS = 0.f;
float rect1_width_SS = 0.f;
float rect1_height_SS = 0.f;

float rect2_x_SS = 0.f;
float rect2_y_SS = 0.f;
float rect2_width_SS = 0.f;
float rect2_height_SS = 0.f;

float rect3_x_SS = 0.f;
float rect3_y_SS = 0.f;
float rect3_width_SS = 0.f;
float rect3_height_SS = 0.f;

float rect4_x_SS = 0.f;
float rect4_y_SS = 0.f;
float rect4_width_SS = 0.f;
float rect4_height_SS = 0.f;

float rect5_x_SS = 0.f;
float rect5_y_SS = 0.f;
float rect5_width_SS = 0.f;
float rect5_height_SS = 0.f;

float rect6_x_SS = 0.f;
float rect6_y_SS = 0.f;
float rect6_width_SS = 0.f;
float rect6_height_SS = 0.f;

float rect7_x_SS = 0.f;
float rect7_y_SS = 0.f;
float rect7_width_SS = 0.f;
float rect7_height_SS = 0.f;

float rect8_x_SS = 0.f;
float rect8_y_SS = 0.f;
float rect8_width_SS = 0.f;
float rect8_height_SS = 0.f;

float rect9_x_SS = 0.f;
float rect9_y_SS = 0.f;
float rect9_width_SS = 0.f;
float rect9_height_SS = 0.f;

float rect10_x_SS = 0.f;
float rect10_y_SS = 0.f;
float rect10_width_SS = 0.f;
float rect10_height_SS = 0.f;

float rectHEADER_x_SS = 0.f;
float rectHEADER_y_SS = 0.f;
float rectHEADER_width_SS = 0.f;
float rectHEADER_height_SS = 0.f;

float rectBACK_x_SS = 0.f;
float rectBACK_y_SS = 0.f;
float rectBACK_width_SS = 0.f;
float rectBACK_height_SS = 0.f;

float text_size_SS = 70.f;

CP_BOOL is_rect1_clicked_SS = 0;
CP_BOOL is_rect2_clicked_SS = 0;
CP_BOOL is_rect3_clicked_SS = 0;
CP_BOOL is_rect4_clicked_SS = 0;
CP_BOOL is_rect5_clicked_SS = 0;
CP_BOOL is_rect6_clicked_SS = 0;
CP_BOOL is_rect7_clicked_SS = 0;
CP_BOOL is_rect8_clicked_SS = 0;
CP_BOOL is_rect9_clicked_SS = 0;
CP_BOOL is_rect10_clicked_SS = 0;
CP_BOOL is_rectBACK_clicked_SS = 0;

CP_Color rect_color_SS;
CP_Color rect_color_HEADER;
CP_Image background_SS = NULL;

void StageSelectInit()
{
	//background2 = CP_Image_Load("./Assets/marked.png");

	windowWidth_SS = CP_System_GetDisplayWidth();
	windowHeight_SS = CP_System_GetDisplayHeight();
	windowWidth_SS = 1920;
	windowHeight_SS = 900;
	CP_System_SetWindowSize(windowWidth_SS, windowHeight_SS);
	rect_color_HEADER = CP_Color_Create(0, 0, 0, 0);
	rect_color_SS = CP_Color_Create(128, 0, 0, 255);

	// BACK + HEADER
	rectBACK_x_SS = windowWidth_SS / 2.f - 840.f;
	rectBACK_y_SS = windowHeight_SS / 2.f - 395.f;
	rectBACK_width_SS = windowWidth_SS / 15.f;
	rectBACK_height_SS = windowHeight_SS / 16.f;

	rectHEADER_x_SS = windowWidth_SS / 2.f;
	rectHEADER_y_SS = windowHeight_SS / 2.f - 400.f;
	rectHEADER_width_SS = windowWidth_SS / 2.f;
	rectHEADER_height_SS = windowHeight_SS / 7.f;
	
	// row 1
	rect1_x_SS = windowWidth_SS / 3.f;
	rect1_y_SS = windowHeight_SS / 2.f - 275.f;
	rect1_width_SS = windowWidth_SS / 4.f;
	rect1_height_SS = windowHeight_SS / 7.f;

	rect2_x_SS = windowWidth_SS / 1.5f;
	rect2_y_SS = windowHeight_SS / 2.f - 275.f;
	rect2_width_SS = windowWidth_SS / 4.f;
	rect2_height_SS = windowHeight_SS / 7.f;

	// row 2
	rect3_x_SS = windowWidth_SS / 3.f;
	rect3_y_SS = windowHeight_SS / 2.f - 125.f;
	rect3_width_SS = windowWidth_SS / 4.f;
	rect3_height_SS = windowHeight_SS / 7.f;
	
	rect4_x_SS = windowWidth_SS / 1.5f;
	rect4_y_SS = windowHeight_SS / 2.f - 125.f;
	rect4_width_SS = windowWidth_SS / 4.f;
	rect4_height_SS = windowHeight_SS / 7.f;

	// row 3
	rect5_x_SS = windowWidth_SS / 3.f;
	rect5_y_SS = windowHeight_SS / 2.f + 25.f;
	rect5_width_SS = windowWidth_SS / 4.f;
	rect5_height_SS = windowHeight_SS / 7.f;

	rect6_x_SS = windowWidth_SS / 1.5f;
	rect6_y_SS = windowHeight_SS / 2.f + 25.f;
	rect6_width_SS = windowWidth_SS / 4.f;
	rect6_height_SS = windowHeight_SS / 7.f;

	// row 4
	rect7_x_SS = windowWidth_SS / 3.f;
	rect7_y_SS = windowHeight_SS / 2.f + 175.f;
	rect7_width_SS = windowWidth_SS / 4.f;
	rect7_height_SS = windowHeight_SS / 7.f;

	rect8_x_SS = windowWidth_SS / 1.5f;
	rect8_y_SS = windowHeight_SS / 2.f + 175.f;
	rect8_width_SS = windowWidth_SS / 4.f;
	rect8_height_SS = windowHeight_SS / 7.f;

	// row 5
	rect9_x_SS = windowWidth_SS / 3.f;
	rect9_y_SS = windowHeight_SS / 2.f + 325.f;
	rect9_width_SS = windowWidth_SS / 4.f;
	rect9_height_SS = windowHeight_SS / 7.f;

	rect10_x_SS = windowWidth_SS / 1.5f;
	rect10_y_SS = windowHeight_SS / 2.f + 325.f;
	rect10_width_SS = windowWidth_SS / 4.f;
	rect10_height_SS = windowHeight_SS / 7.f;
}

void StageSelectUpdate()
{
	int width_SS = CP_Image_GetWidth(background_SS);
	int height_SS = CP_Image_GetHeight(background_SS);
	int windowWidth_SS = CP_System_GetWindowWidth();
	int windowHeight_SS = CP_System_GetWindowHeight();
	CP_Settings_NoStroke();

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(background_SS, (float)windowWidth_SS / 2.f, (float)windowHeight_SS / 2.f, (float)windowWidth_SS, (float)windowHeight_SS, 255);

	// BACK + HEADER
	CP_Settings_Fill(rect_color_HEADER);
	CP_Graphics_DrawRect(rectBACK_x_SS, rectBACK_y_SS, rectBACK_width_SS, rectBACK_height_SS);
	CP_Settings_Fill(CP_Color_Create(160, 0, 0, 255));
	CP_Graphics_DrawTriangleAdvanced(80.0f, 34.5f, 105.0f, 64.5f, 55.0f, 64.5f, 270.0f);
	CP_Graphics_DrawQuadAdvanced(130.0f, 10.0f, 140.0f, 10.0f, 140.0f, 100.0f, 130.0f, 100.0f, 90.0f);
	CP_Graphics_DrawQuadAdvanced(170.0f, 30.0f, 180.0f, 30.0f, 180.0f, 60.0f, 170.0f, 60.0f, 0.0f);

	CP_Settings_Fill(rect_color_HEADER);
	CP_Graphics_DrawRect(rectHEADER_x_SS, rectHEADER_y_SS, rectHEADER_width_SS, rectHEADER_height_SS);
	CP_Settings_Fill(CP_Color_Create(160, 0, 0, 255));
	CP_Font_DrawTextBox("CHOOSE YOUR POISON!", rectHEADER_x_SS - rectHEADER_width_SS / 2.f, rectHEADER_y_SS, rectHEADER_width_SS);

	// row 1
	CP_Settings_Fill(rect_color_SS);
	CP_Graphics_DrawRect(rect1_x_SS, rect1_y_SS, rect1_width_SS, rect1_height_SS);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 1", rect1_x_SS - rect1_width_SS / 2.f, rect1_y_SS, rect1_width_SS);

	CP_Settings_Fill(rect_color_SS);
	CP_Graphics_DrawRect(rect2_x_SS, rect2_y_SS, rect2_width_SS, rect2_height_SS);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 2", rect2_x_SS - rect2_width_SS / 2.f, rect2_y_SS, rect2_width_SS);

	// row 2
	CP_Settings_Fill(rect_color_SS);
	CP_Graphics_DrawRect(rect3_x_SS, rect3_y_SS, rect3_width_SS, rect3_height_SS);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 3", rect3_x_SS - rect3_width_SS / 2.f, rect3_y_SS, rect3_width_SS);

	CP_Settings_Fill(rect_color_SS);
	CP_Graphics_DrawRect(rect4_x_SS, rect4_y_SS, rect4_width_SS, rect4_height_SS);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 4", rect4_x_SS - rect4_width_SS / 2.f, rect4_y_SS, rect4_width_SS);

	// row 3
	CP_Settings_Fill(rect_color_SS);
	CP_Graphics_DrawRect(rect5_x_SS, rect5_y_SS, rect5_width_SS, rect5_height_SS);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 5", rect5_x_SS - rect5_width_SS / 2.f, rect5_y_SS, rect5_width_SS);

	CP_Settings_Fill(rect_color_SS);
	CP_Graphics_DrawRect(rect6_x_SS, rect6_y_SS, rect6_width_SS, rect6_height_SS);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 6", rect6_x_SS - rect6_width_SS / 2.f, rect6_y_SS, rect6_width_SS);

	// row 4
	CP_Settings_Fill(rect_color_SS);
	CP_Graphics_DrawRect(rect7_x_SS, rect7_y_SS, rect7_width_SS, rect7_height_SS);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 7", rect7_x_SS - rect7_width_SS / 2.f, rect7_y_SS, rect7_width_SS);

	CP_Settings_Fill(rect_color_SS);
	CP_Graphics_DrawRect(rect8_x_SS, rect8_y_SS, rect8_width_SS, rect8_height_SS);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 8", rect8_x_SS - rect8_width_SS / 2.f, rect8_y_SS, rect8_width_SS);

	// row 5
	CP_Settings_Fill(rect_color_SS);
	CP_Graphics_DrawRect(rect3_x_SS, rect9_y_SS, rect9_width_SS, rect9_height_SS);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 9", rect9_x_SS - rect9_width_SS / 2.f, rect9_y_SS, rect9_width_SS);

	CP_Settings_Fill(rect_color_SS);
	CP_Graphics_DrawRect(rect10_x_SS, rect10_y_SS, rect10_width_SS, rect10_height_SS);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Level 10", rect10_x_SS - rect10_width_SS / 2.f, rect10_y_SS, rect10_width_SS);


	//CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	is_rect1_clicked_SS = IsAreaClicked(rect1_x_SS, rect1_y_SS, rect1_width_SS, rect1_height_SS, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	is_rect2_clicked_SS = IsAreaClicked(rect2_x_SS, rect2_y_SS, rect2_width_SS, rect2_height_SS, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	is_rect3_clicked_SS = IsAreaClicked(rect3_x_SS, rect3_y_SS, rect3_width_SS, rect3_height_SS, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	is_rect4_clicked_SS = IsAreaClicked(rect4_x_SS, rect4_y_SS, rect4_width_SS, rect4_height_SS, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	is_rect5_clicked_SS = IsAreaClicked(rect5_x_SS, rect5_y_SS, rect5_width_SS, rect5_height_SS, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	is_rect6_clicked_SS = IsAreaClicked(rect6_x_SS, rect6_y_SS, rect6_width_SS, rect6_height_SS, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	is_rect7_clicked_SS = IsAreaClicked(rect7_x_SS, rect7_y_SS, rect7_width_SS, rect7_height_SS, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	is_rect8_clicked_SS = IsAreaClicked(rect8_x_SS, rect8_y_SS, rect8_width_SS, rect8_height_SS, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	is_rect9_clicked_SS = IsAreaClicked(rect9_x_SS, rect9_y_SS, rect9_width_SS, rect9_height_SS, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	is_rect10_clicked_SS = IsAreaClicked(rect10_x_SS, rect10_y_SS, rect10_width_SS, rect10_height_SS, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	is_rectBACK_clicked_SS = IsAreaClicked(rectBACK_x_SS, rectBACK_y_SS, rectBACK_width_SS, rectBACK_height_SS, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	if (is_rect1_clicked_SS) {
		TransitScene(Level1);
	}
	if (is_rect2_clicked_SS) {
		TransitScene(Level2);
	}
	if (is_rect3_clicked_SS) {
		TransitScene(Level3);
	}
	if (is_rect4_clicked_SS) {
		TransitScene(Cutscene1);
	}
	if (is_rect5_clicked_SS) {
		TransitScene(Level5);
	}
	if (is_rect6_clicked_SS) {
		TransitScene(Level6);
	}
	if (is_rect7_clicked_SS) {
		TransitScene(Cutscene7);
	}
	if (is_rect8_clicked_SS) {
		TransitScene(Cutscene8);
	}
	if (is_rect9_clicked_SS) {
		TransitScene(Cutscene9);
	}
	if (is_rect10_clicked_SS) {
		TransitScene(Cutscene10);
	}
	if (is_rectBACK_clicked_SS) {
		TransitScene(Main_Menu);
	}

	//CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	//CP_Settings_RectMode(CP_POSITION_CENTER);
	//CP_Settings_TextSize(text_size2);
}

void StageSelectExit()
{
	CP_Image_Free(&background_SS);
}