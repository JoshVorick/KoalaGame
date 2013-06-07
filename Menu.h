#pragma once

enum KEYS{UP,DOWN,LEFT,RIGHT,SPACE,ESCAPE,ENTER,P,E};
enum SELECTED{MENU, LEAF_PUNCH, HELP, EXIT, LEAF_PUZZLE, NONE};

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string>
#include "math.h"
#include "GameState.h"
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
		void Enter();
		void Render();
		void Update(int dir);
		void Init(int w, int h);
		//void Destroy(){}
	
};