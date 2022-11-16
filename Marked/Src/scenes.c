#include "cprocessing.h"
#include "mainmenu.h"
#include "level.h"
#include "scenes.h"

FunctionPtr levels[Num_Scenes][3] = {
	//{Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit},
	{Level_Init, Level_Update, Level_Exit},
	{Level1_Init, Level1_Update, Level1_Exit},
	{Level2_Init, Level2_Update, Level2_Exit},
	{Level3_Init, Level3_Update, Level3_Exit},
	{Level4_Init, Level4_Update, Level4_Exit},
	{Level5_Init, Level5_Update, Level5_Exit},
	{Level6_Init, Level6_Update, Level6_Exit},
	{Level7_Init, Level7_Update, Level7_Exit},
	
	//{Level8_Init, Level8_Update, Level8_Exit},
	//{Level9_Init, Level9_Update, Level9_Exit},
	{Level10_Init, Level10_Update, Level10_Exit},
	{Cutscene1_Init, Cutscene1_Update, Cutscene1_Exit}

};

void TransitScene(enum SCENES level) {
	CP_Engine_SetNextGameState(levels[level][0], levels[level][1], levels[level][2]);
}