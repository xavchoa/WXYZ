#include "cprocessing.h"
#include "mainmenu.h"
#include "level.h"
#include "scenes.h"

FunctionPtr levels[Num_Scenes][3] = {
	//{Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit},
	//{Level_Init, Level_Update, Level_Exit},
	{Level1_Init, Level1_Update, Level1_Exit},
	{Level2_Init, Level2_Update, Level2_Exit}
};

void TransitScene(enum SCENES level) {
	CP_Engine_SetNextGameState(levels[level][0], levels[level][1], levels[level][2]);
}