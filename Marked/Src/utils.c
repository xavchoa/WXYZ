//---------------------------------------------------------
// file:	render.c
// author:	[LIU WAN TING]
// email:	[wanting.liu@digipen.edu]
//
// brief:	Contains utility code which allows rectangular
// area to be clicked
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <stdio.h>
#include <math.h>
#include "cprocessing.h"

int IsAreaClicked(float areaCenterX, float areaCenterY, float areaWidth, float areaHeight, float clickX, float clickY)
{
	float xLeftCoords = areaCenterX - areaWidth / 2.0f;
	float xRightCoords = areaCenterX + areaWidth / 2.0f;
	float yTopCoords = areaCenterY - areaHeight / 2.0f;
	float yBottomCoords = areaCenterY + areaHeight / 2.0f;

	CP_BOOL withinRangeX = 0;
	CP_BOOL withinRangeY = 0;

	// if x coordinates of mouse within range of area
	if (clickX > xLeftCoords && clickX < xRightCoords) {
		withinRangeX = 1;
	} //else within_x_range is false
	// if y coordinates of mouse within range of area
	if (clickY > yTopCoords && clickY < yBottomCoords) {
		withinRangeY = 1;

	} //else within_y_range is false
	//when mouse cursor within rectangle, and mouse is clicked
	if (withinRangeX && withinRangeY && CP_Input_MouseClicked()) {
		return 1;
	}
	return 0;
}