//#pragma once

#ifndef SCENES_H
#define SCENES_H
typedef enum LEVELS {
	//Main_Menu,
	//Tutorial,
	Level1,
	Level2,
	Level3,
	Level4,
	Level5,
	Level6,
	Level7,
	level8,
	level9,
	level10,
	Num_Scenes
}LEVELS;

LEVELS nextLevel;

void TransitScene(enum LEVELS level);
#endif