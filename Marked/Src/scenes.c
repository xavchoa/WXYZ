//---------------------------------------------------------
// file:	scenes.c
// author:	[CHOA KAI RONG, XAVIER]
// email:	[k.choa@digipen.edu]
//
// brief:	Functions that manage scenes and levels,
// restart level and transit to next level. Contains array
// of function pointers to be used by TransitScene function.
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "mainmenu.h"
#include "level.h"
#include "scenes.h"

FunctionPtr levels[Num_Scenes][3] = {
	{MainMenuInit, MainMenuUpdate, MainMenuExit},
	{LevelInit, LevelUpdate, LevelExit},
	{Level1Init, Level1Update, Level1Exit},
	{Level2Init, Level2Update, Level2Exit},
	{Level3Init, Level3Update, Level3Exit},
	{Level4Init, Level4Update, Level4Exit},
	{Level5Init, Level5Update, Level5Exit},
	{Level6Init, Level6Update, Level6Exit},
	{Level7Init, Level7Update, Level7Exit},
	{Level8Init, Level8Update, Level8Exit},
	{Level9Init, Level9Update, Level9Exit},
	{Level10Init, Level10Update, Level10Exit},
	{CutScene4Init, CutScene4Update, CutScene4Exit},
	{CutScene7Init, CutScene7Update, CutScene7Exit},
	{CutScene8Init, CutScene8Update, CutScene8Exit},
	{CutScene9Init, CutScene9Update, CutScene9Exit},
	{CutScene10Init, CutScene10Update, CutScene10Exit},
	{WinsceneInit, WinsceneUpdate, WinsceneExit}

};

void TransitScene(enum SCENES level) {
	CP_Engine_SetNextGameState(levels[level][0], levels[level][1], levels[level][2]);
}

void RestartLevel(enum SCENES level) {
	CP_Engine_SetNextGameStateForced(levels[level][0], levels[level][1], levels[level][2]);
}