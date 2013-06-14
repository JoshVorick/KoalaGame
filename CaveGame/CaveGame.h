#pragma once
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class CaveGame : public GameState{
	private:
		int intoxication, health, koalaX, floorY, ceilY, koalaHeight, koalaWidth, t, caveSpeed, objW[10][3], objH[10][3], 
			objFreq[10], objFrames[10][3]; //10 types of obj, max of 50 per level
		float koalaVx, koalaVy, koalaY, objX[10][8], objY[10][8], objVx[10], objVy[10];
		bool isObj[10][8];	//10 object types, 8 on screen at a time
		ALLEGRO_BITMAP *caveBackground, *koala, *objImage[10][3];	//10 images for the 10 different objects
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