#pragma once
#include <allegro5\allegro_primitives.h>

class GameState
{
protected:
	int state;
	int mouseX;
	int mouseY;
	int width;
	int height;
public:
	void virtual Enter(){}
	void virtual Render(){}
	void virtual Update(int dir){}
	void virtual Init(int w, int h){}
	void SetMousePos(int x, int y){mouseX = x; mouseY = y;}
	//void virtual Destroy();
	int getState(){return state;}
	GameState(){state = MENU;}
};