//---------------------------------------------------------
// file:	render.c
// author:	[Liu Wan Ting]
// email:	[wanting.liu@digipen.edu]
//
// brief:	Contains render code which displays the graphics
// using various graphical functions in the CProcessing lib.
// Contains the code for displaying the game over screen as
// well.
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cprocessing.h"
#include "game.h"
void DrawGameElements(GameObject* self) {
	CP_Settings_Fill(self->color);
	switch (self->type) {
	case Type_EndPoint: {
		CP_Settings_Fill(CP_Color_Create(170, 169, 173, 255));
		CP_Graphics_BeginShape();
		CP_Graphics_AddVertex(self->pos.x, self->pos.y);
		CP_Graphics_AddVertex(self->pos.x - 20.f, self->pos.y + 20.f);
		CP_Graphics_AddVertex(self->pos.x, self->pos.y + 20.f);
		CP_Graphics_EndShape();
		CP_Settings_Fill(CP_Color_Create(170, 169, 173, 255));
		CP_Graphics_BeginShape();
		CP_Graphics_AddVertex(self->pos.x + 60.f, self->pos.y);
		CP_Graphics_AddVertex(self->pos.x + 60.f, self->pos.y + 20.f);
		CP_Graphics_AddVertex(self->pos.x + 80.f, self->pos.y + 20.f);
		CP_Graphics_EndShape();
		CP_Settings_Fill(CP_Color_Create(170, 169, 173, 255));
		CP_Graphics_DrawRect(self->pos.x, self->pos.y, 60.f, 20.f);
		CP_Settings_Fill(CP_Color_Create(68, 80, 85, 255));
		CP_Graphics_DrawRect(self->pos.x - 20, self->pos.y + 20.f, 100.f, 80.f);
		CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Graphics_DrawLine(self->pos.x - 10.f, self->pos.y + 20.f, self->pos.x - 10.f, self->pos.y + 90.f);
		CP_Graphics_DrawLine(self->pos.x - 10.f, self->pos.y + 90.f, self->pos.x + 70.f, self->pos.y + 90.f);
		CP_Graphics_DrawLine(self->pos.x + 70.f, self->pos.y + 90.f, self->pos.x + 70.f, self->pos.y + 20.f);
		CP_Graphics_DrawLine(self->pos.x + 30.f, self->pos.y + 10.f, self->pos.x + 30.f, self->pos.y + 90.f);

		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 0));
		CP_Graphics_DrawRect(self->pos.x + 12.f, self->pos.y + 40.f, 10.f, 20.f);
		CP_Graphics_DrawRect(self->pos.x + 38.f, self->pos.y + 40.f, 10.f, 20.f);
		CP_Settings_Fill(self->color);
		CP_Graphics_DrawCircle(self->pos.x + 30.f, self->pos.y + 10.f, 15.f);
		return;
	}
	case Type_Door: {
		//door
		if (self->hasCollider && self->size.x == 50) {
			CP_Settings_Fill(CP_Color_Create(192, 192, 192, 255));
			CP_Graphics_DrawRectAdvanced(self->pos.x, self->pos.y, 50.f, 100.f, 0, 0);
			CP_Settings_Fill(CP_Color_Create(140, 140, 140, 255));
			CP_Graphics_DrawTriangle(self->pos.x + 5.f, self->pos.y + 5.f, self->pos.x + 5.f, self->pos.y + 40.f, self->pos.x + 45.f, self->pos.y + 5.f);
			CP_Graphics_DrawTriangle(self->pos.x + 5.f, self->pos.y + 50.f, self->pos.x + 45.f, self->pos.y + 15.f, self->pos.x + 45.f, self->pos.y + 85.f);
			CP_Graphics_DrawTriangle(self->pos.x + 5.f, self->pos.y + 60.f, self->pos.x + 5.f, self->pos.y + 95.f, self->pos.x + 45.f, self->pos.y + 95.f);
			return;
		}
		else if (self->hasCollider) {
			CP_Settings_Fill(CP_Color_Create(192, 192, 192, 255));
			CP_Graphics_DrawRectAdvanced(self->pos.x, self->pos.y + 50.f, 50.f, 100.f, -90.f, 0);
			CP_Settings_Fill(CP_Color_Create(140, 140, 140, 255));
			CP_Graphics_DrawTriangleAdvanced(self->pos.x + 3.f, self->pos.y + 20.f, self->pos.x + 3.f, self->pos.y + 55.f, self->pos.x + 43.f, self->pos.y + 20.f, -90.f);
			CP_Graphics_DrawTriangleAdvanced(self->pos.x + 23.f, self->pos.y + 19.f, self->pos.x + 63.f, self->pos.y + -16.f, self->pos.x + 63.f, self->pos.y + 54.f, -90.f);
			CP_Graphics_DrawTriangleAdvanced(self->pos.x + 70.f, self->pos.y + 8.f, self->pos.x + 70.f, self->pos.y + 43.f, self->pos.x + 110.f, self->pos.y + 43.f, -90.f);
			return;
		}
		CP_Graphics_DrawRect(self->pos.x, self->pos.y, self->size.x, self->size.y);
	}
	case Type_Obstacle: {
		return;
	}
					  break;
	case Type_Player: {
		//player face
		CP_Color player_color = CP_Color_Create(255, 255, 255, 255);
		CP_Settings_Fill(player_color);
		CP_Graphics_DrawRect(self->pos.x, self->pos.y, self->size.x, self->size.y);
		CP_Settings_Stroke(CP_Color_Create(128, 0, 0, 255));
		CP_Graphics_DrawLine(self->pos.x, self->pos.y + self->size.x, self->pos.x + self->size.x, self->pos.y);
		CP_Graphics_DrawLine(self->pos.x + 10.f, self->pos.y + 6.f, self->pos.x + 40.f, self->pos.y + 35.f);
		CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));

		//player eyes
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Graphics_DrawRect(self->pos.x + 5.f, self->pos.y + 10.f, 15.f, 15.f);
		CP_Graphics_DrawRect(self->pos.x + 30.f, self->pos.y + 10.f, 15.f, 15.f);
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Graphics_DrawCircle(self->pos.x + 12.5f, self->pos.y + 17.5f, 8.f);
		CP_Graphics_DrawCircle(self->pos.x + 37.5f, self->pos.y + 17.5f, 8.f);

		//player mouth
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Graphics_DrawRect(self->pos.x, self->pos.y + 40.f, 10.f, 10.f);
		CP_Graphics_DrawRect(self->pos.x + 40.f, self->pos.y + 40.f, 10.f, 10.f);
		CP_Graphics_DrawRect(self->pos.x + 16.f, self->pos.y + 40.f, 1.f, 10.f);
		CP_Graphics_DrawRect(self->pos.x + 24.f, self->pos.y + 40.f, 1.f, 10.f);
		CP_Graphics_DrawRect(self->pos.x + 32.f, self->pos.y + 40.f, 1.f, 10.f);

	}
					break;
	case Type_Enemy: {
		CP_Color enermy_color = CP_Color_Create(255, 255, 255, 255);
		//enermy face

		CP_Settings_Fill(enermy_color);
		CP_Graphics_DrawRect(self->pos.x, self->pos.y, self->size.x, self->size.y);
		CP_Settings_Fill(CP_Color_Create(0, 128, 255, 255));
		CP_Graphics_DrawRect(self->pos.x, self->pos.y + 5.f, 15.f, 5.f);
		CP_Graphics_DrawRect(self->pos.x + 35.f, self->pos.y + 5.f, 15.f, 5.f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 153, 255));
		CP_Graphics_DrawRect(self->pos.x + 15.f, self->pos.y + 4.f, 20.f, 8.f);


		//enermy eyes
		CP_Settings_Fill(CP_Color_Create(0, 128, 255, 255));
		CP_Graphics_DrawRect(self->pos.x + 5.f, self->pos.y + 18.f, 15.f, 15.f);
		CP_Graphics_DrawRect(self->pos.x + 30.f, self->pos.y + 18.f, 15.f, 15.f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(self->pos.x + 10.f, self->pos.y + 25.f, 10.f, 7.f);
		CP_Graphics_DrawRect(self->pos.x + 31.f, self->pos.y + 25.f, 10.f, 7.f);

		//enermy mouth
		CP_Settings_Fill(CP_Color_Create(0, 128, 255, 255));
		CP_Graphics_DrawRect(self->pos.x, self->pos.y + 40.f, 50.f, 10.f);

	}
				   break;
	case Type_Dummy: {
		//dummy face
		CP_Settings_Fill(CP_Color_Create(128, 128, 128, 255));
		CP_Graphics_DrawRect(self->pos.x, self->pos.y, self->size.x, self->size.y);
		CP_Settings_Stroke(CP_Color_Create(96, 96, 96, 255));
		CP_Graphics_DrawLine(self->pos.x, self->pos.y + self->size.y, self->pos.x + self->size.x, self->pos.y);
		CP_Graphics_DrawLine(self->pos.x + 10.f, self->pos.y + 6.f, self->pos.x + 40.f, self->pos.y + 35.f);
		CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Graphics_DrawRect(self->pos.x, self->pos.y + 40.f, 10.f, 10.f);
		CP_Graphics_DrawRect(self->pos.x + 40.f, self->pos.y + 40.f, 10.f, 10.f);
		CP_Graphics_DrawRect(self->pos.x + 16.f, self->pos.y + 40.f, 1.f, 10.f);
		CP_Graphics_DrawRect(self->pos.x + 24.f, self->pos.y + 40.f, 1.f, 10.f);
		CP_Graphics_DrawRect(self->pos.x + 32.f, self->pos.y + 40.f, 1.f, 10.f);


		//dummy eyes
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Graphics_DrawRect(self->pos.x + 5.f, self->pos.y + 10.f, 15.f, 15.f);
		CP_Graphics_DrawRect(self->pos.x + 30.f, self->pos.y + 10.f, 15.f, 15.f);
		CP_Settings_Stroke(CP_Color_Create(192, 192, 192, 255));
		CP_Graphics_DrawLine(self->pos.x + 5.f, self->pos.y + 25.f, self->pos.x + 20.f, self->pos.y + 10.f);
		CP_Graphics_DrawLine(self->pos.x + 5.f, self->pos.y + 10.f, self->pos.x + 20.f, self->pos.y + 25.f);
		CP_Graphics_DrawLine(self->pos.x + 30.f, self->pos.y + 25.f, self->pos.x + 45.f, self->pos.y + 10.f);
		CP_Graphics_DrawLine(self->pos.x + 30.f, self->pos.y + 10.f, self->pos.x + 45.f, self->pos.y + 25.f);
		CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));

	}
				   break;
	case Type_Button: {
		//button
		CP_Settings_Fill(CP_Color_Create(155, 0, 0, 255));
		CP_Graphics_DrawRectAdvanced(self->pos.x + 10.f, self->pos.y - 8.f, 50.f, 10.f, 0.f, 5.f);
		CP_Settings_Fill(CP_Color_Create(192, 192, 192, 255));
		CP_Graphics_DrawRect(self->pos.x, self->pos.y, 70.f, 10.f);

		return;
	}
	case Type_Proj: {
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Graphics_DrawRectAdvanced(self->pos.x, self->pos.y, 7.f, 7.f, 0.f, 0.f);
		CP_Graphics_DrawTriangleAdvanced(self->pos.x, self->pos.y, self->pos.x, self->pos.y + 7.f, self->pos.x - 15.f, self->pos.y + 3.5f, 0.f);
		CP_Graphics_DrawTriangleAdvanced(self->pos.x, self->pos.y + 7.f, self->pos.x + 7.f, self->pos.y + 7.f, self->pos.x + 3.5f, self->pos.y + 22.f, 0.f);
		CP_Graphics_DrawTriangleAdvanced(self->pos.x, self->pos.y, self->pos.x + 7.f, self->pos.y, self->pos.x + 3.5f, self->pos.y - 15.f, 0.f);
		CP_Graphics_DrawTriangleAdvanced(self->pos.x + 7.f, self->pos.y, self->pos.x + 7.f, self->pos.y + 7.f, self->pos.x + 22.f, self->pos.y + 3.5f, 0.f);
		CP_Settings_Stroke(CP_Color_Create(128, 0, 0, 255));
		CP_Graphics_DrawCircle(self->pos.x + 3.5f, self->pos.y + 3.5f, 5.f);
		CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
		return;
	}
				  break;
	case Type_EnemyProj: {
		//enermy projectile
		CP_Settings_Fill(CP_Color_Create(30, 144, 255, 255));
		CP_Graphics_DrawRect(self->pos.x, self->pos.y, 7.f, 7.f);
		CP_Graphics_DrawTriangleAdvanced(self->pos.x, self->pos.y, self->pos.x, self->pos.y + 7.f, self->pos.x - 15.f, self->pos.y + 3.5f, 90.0);
		CP_Graphics_DrawTriangleAdvanced(self->pos.x, self->pos.y + 7.f, self->pos.x + 7.f, self->pos.y + 7.f, self->pos.x + 3.5f, self->pos.y + 22.f, 90.0);
		CP_Graphics_DrawTriangleAdvanced(self->pos.x, self->pos.y, self->pos.x + 7.f, self->pos.y, self->pos.x + 3.5f, self->pos.y - 15.f, 90.0);
		CP_Graphics_DrawTriangleAdvanced(self->pos.x + 7.f, self->pos.y, self->pos.x + 7.f, self->pos.y + 7.f, self->pos.x + 22.f, self->pos.y + 3.5f, 90.0);
		CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawCircle(self->pos.x + 3.5f, self->pos.y + 3.5f, 5.f);
		CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
		return;
	}
	case Type_Info: {
		CP_Settings_TextSize(50);
		CP_Settings_Fill(CP_Color_Create(128, 0, 0, 255));
		CP_Font_DrawTextBox("REMEMBER: All enemies need to be eliminated to proceed. Press \"R\" if you get stuck.", self->pos.x, self->pos.y, self->size.x);
		return;
	}
	case Type_Info2: {
		CP_Settings_TextSize(50);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawTextBox("You cannot kill enemies directly.", self->pos.x, self->pos.y - 100, self->size.x);
		CP_Font_DrawTextBox("Think of ways to take them out by swapping positions.", self->pos.x, self->pos.y, self->size.x);
		return;
	}
	default:
		CP_Settings_RectMode(CP_POSITION_CORNER);
		break;
	}
	CP_Settings_Fill(self->color);
	CP_Graphics_DrawRect(self->pos.x, self->pos.y, self->size.x, self->size.y);
}

void RenderScene() {
	for (int i = 0; i < GOARRAY_SIZE; ++i) {
		if ((goPtr + i)->isActive) {
			if ((goPtr + i)->type == Type_Proj) {
				if (projectile->projAlive)
					DrawGameElements((goPtr + i));
			}
			else
				DrawGameElements((goPtr + i));
		}

	}
}

void DisplayGameOver() {
	CP_Graphics_ClearBackground(CP_Color_Create(128, 0, 0, 120));
	RenderScene();
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(100);
	CP_Font_DrawText("YOU DIED...", (float)windowWidth / 2.f, (float)windowHeight / 2.f);
	CP_Settings_TextSize(50);
	CP_Font_DrawText("Press \"R\" to restart level", (float)windowWidth / 2.f, (float)windowHeight / 2.f + 60.f);
}