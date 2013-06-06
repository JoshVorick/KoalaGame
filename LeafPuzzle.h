#pragma once

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
#include "math.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class LeafPuzzle : public GameState{
	private:
		bool hasWon();
		//Leaf Puzzle variables
		int numRows, numCol, theSelected, selected[6], arraySize, type, flipped, doesWork, leafStates[200], movesMade;
		ALLEGRO_BITMAP *leafDown, *leafUp, *background, *omNomNom, *rock;
		ALLEGRO_SAMPLE *leafFlipSounds[4];
		//Adventure/platformer variables
		//Tree Punching variables
		ALLEGRO_FONT *font36;
	public:
		LeafPuzzle();
		void Update(int dir);
		void Render();
		void Enter();
		void Init(int w, int h);
};