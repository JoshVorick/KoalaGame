#pragma once

#include <allegro5\allegro_primitives.h>

enum KEYS{UP,DOWN,LEFT,RIGHT,SPACE,ESCAPE,ENTER,P,E,Q};
enum SELECTED{MENU, LEAF_PUNCH, HELP, EXIT, LEAF_PUZZLE, CAVE_GAME, NONE};

class GameState{
	protected:
		int state;
		int score;
		int mouseX;
		int mouseY;
		int width;		//initial width that the game is supposed to be played at
		int height;		//initial height ""
	public:
		void virtual Update(){}
		void virtual Render(){}
		void virtual Move(int dir){}
		void virtual Enter(){}
		void virtual Init(int w, int h, int curLevel, int curScore){}
		void SetMousePos(int x, int y){mouseX = x; mouseY = y;}
		int getState(){return state;}
		void setState(int newState){state = newState;}
		int getScore(){return score;}
		GameState(){state = MENU;}
		~GameState(){}
};