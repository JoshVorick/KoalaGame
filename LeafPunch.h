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

class LeafPunch : public GameState{
	private:
		int circleRadius, treeWidth, timeWaited, levelScore, curX, curY, prevX, prevY, treeX;			//treeY is always 0. tree X is its leftmost bound
		ALLEGRO_BITMAP *tree, *target;
		ALLEGRO_SAMPLE *treeHit[4];
		ALLEGRO_FONT *font36;
	public:
		LeafPunch();
		void Update(int dir);
		void Render();
		void Enter();
		void Init(int w, int h);
};