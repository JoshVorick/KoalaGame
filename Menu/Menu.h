#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string>
#include "math.h"
using namespace std;

class Menu : public GameState{
	private:
		//int width;
		//int height;
		int selected;
		int fontHeight;
		int options;
		int x;
		int y;
		
		ALLEGRO_FONT *font;
		ALLEGRO_SAMPLE *clicked;
		ALLEGRO_BITMAP *helpMenu, *background;
		
	public:
		Menu();
		void Update();
		void Enter();
		void Render();
		void Move(int dir);
		void Init(int w, int h, int curLevel, int curScore);	
};