//#pragma once

#ifndef SCENES_H
#define SCENES_H
typedef enum LEVELS {
	//Main_Menu,
	Level0,
	Level1,
	Level2,
	Level3,
	Level4,
	Level5,
	Level6,
	Level7,
	//Level8,
	//Level9,
	Level10,
	Cutscene1,
	Num_Scenes
}LEVELS;

LEVELS nextLevel;

void TransitScene(enum LEVELS level);
#endif