#pragma once

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "FallingLeaf.cpp"
#include "math.h"
#include <allegro5/allegro_primitives.h>

class LeafPunch : public GameState{
	private:
		int NUM_LEAVES;
		int circleRadius, treeWidth, timeWaited, curX, curY, prevX, prevY, treeX, treeHealth, curCombo;			//treeY is always 0. tree X is its leftmost bound
		ALLEGRO_BITMAP *tree, *target, *fallingLeaf[2], *background;
		ALLEGRO_SAMPLE *treeHit[5];
		ALLEGRO_FONT *font36;
		FallingLeaf *leaves[100];// = new fallingLeaf()[20];
		bool isFalling[100];
	public:
		LeafPunch();
		void Update();
		void Move(int dir);
		void Render();
		void Enter();
		void Init(int w, int h, int curLevel, int curScore);
		~LeafPunch();
};