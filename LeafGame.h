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

class LeafGame : public GameState{
	private:
		//Leaf Puzzle variables
		int numRows, numCol, theSelected, selected[6], arraySize, type, flipped, doesWork;
		int leafStates[100];
		ALLEGRO_BITMAP *leafDown, *leafUp, *background, *omNomNom, *rock;
		bool hasWon();
		ALLEGRO_SAMPLE *leafFlipSounds[4];
		//Adventure/platformer variables
		//Tree Punching variables
		ALLEGRO_FONT *font36;
	public:
		LeafGame();
		void Update(int dir);
		void Render();
		void Enter();
		void Init(int w, int h);
};