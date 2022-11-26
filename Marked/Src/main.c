//---------------------------------------------------------
// file:	main.c
// author:	[CHOA KAI RONG, XAVIER]
// email:	[k.choa@digipen.edu]
//
// brief:	Main entry point for the Marked game utilizing the
//			CProcessing library
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
	CP_Engine_Run();
	return 0;
}