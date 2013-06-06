#pragma once
#include <allegro5\allegro_primitives.h>
#include "Menu.h"

class GameState{
	protected:
		int state;
		int score;
		int mouseX;
		int mouseY;
		int width;		//initial width that the game is supposed to be played at
		int height;		//initial height ""
	public:
		void virtual Enter(){}
		void virtual Render(){}
		void virtual Update(int dir){}
		void virtual Init(int w, int h){}
		void SetMousePos(int x, int y){mouseX = x; mouseY = y;}
		//void virtual Destroy();
		int getState(){return state;}
		void setState(int newState){state = newState;}
		int getScore(){return score;}
		GameState(){state = MENU;}
};