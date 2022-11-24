//---------------------------------------------------------
// file:	main.c
// author:	[Xavier Choa]
// email:	[k.choa@digipen.edu]
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "mainmenu.h"

int main(void)
{
	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
	CP_Engine_Run();
	return 0;
}
