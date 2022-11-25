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
#include "logo.h"

int main(void)
{
	CP_Engine_SetNextGameState(LogoInit, LogoUpdate, LogoExit);

	//CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
	CP_Engine_Run();
	return 0;
}
