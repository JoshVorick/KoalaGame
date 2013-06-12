#pragma once
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
#include "CaveObject.h"

class CaveGame : public GameState{
	private:
		int intoxication, koalaX, floorY, ceilY, koalaHeight, koalaWidth, time, timeDone, caveSpeed,
			objTime[10][50], numObj[10], objY[10], objV[10], objFrames[10][3]; //10 types of obj, max of 50 per level
		float koalaV, koalaY, gravity;
		bool isObj[10][8];	//10 object types, 8 on screen at a time
		ALLEGRO_BITMAP *koala, *objImage[10][3];	//10 images for the 10 different objects
		CaveObject *obstacles[10][8]; // maximum of 8 objects per type
		//0 is for stalactite. 1 is for stalagmite. 2 is bat.
	public:
		CaveGame();
		void Update();
		void Move(int dir);
		void Enter();
		void Render();
		void Init(int w, int h, int curLevel, int curScore);
		~CaveGame();
};