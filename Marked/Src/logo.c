#include "cprocessing.h"
#include "mainmenu.h"

int windowWidth, windowHeight;
CP_Image logo;
float alpha = 0;
float alphatime = 4;
void LogoInit(void)
{
    windowHeight = 900 ;
    windowWidth = 1920 ;
    logo = CP_Image_Load("Assets/DigiPen_BLACK.png");
    CP_Settings_ImageMode(CP_POSITION_CENTER);
    CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
    CP_System_SetWindowSize(windowWidth, windowHeight);
}
void LogoUpdate(void)
{
    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
    alpha += (255 / alphatime) * CP_System_GetDt();

    CP_Image_Draw(logo, (float)windowWidth / 2, (float)windowHeight / 2, (float)CP_Image_GetWidth(logo), (float)CP_Image_GetHeight(logo),(int) alpha);

    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_BASELINE);
    CP_Settings_TextSize(30.0f);
    CP_Font_DrawText("All content (C) 2022 DigiPen(SINGAPORE) Corporation, all rights reserved", (float)windowWidth / 2.0f, 850.f);

    if (alpha >= 255)
    {
        CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
    }
}
void LogoExit(void)
{
    CP_Image_Free(&logo);

}