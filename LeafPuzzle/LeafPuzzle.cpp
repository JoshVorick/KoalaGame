#pragma once

#include "LeafPuzzle.h"

LeafPuzzle::LeafPuzzle(){
	srand(time(NULL));
	state = LEAF_PUZZLE;
	theSelected = -1;
	flipped = 2;
	movesMade = 0;
	doesWork = false;
	isPaw = false;
	for(int i=0; i<6; i++) 
		selected[i] = -2;
	font36 = al_load_font("Audio and Images/AAJAX.ttf",36,0);
	leafDown = al_load_bitmap("Audio and Images/leafDown.bmp");
	leafUp = al_load_bitmap("Audio and Images/leafUp.bmp");
	rock = al_load_bitmap("Audio and Images/Rock.bmp");
	selector = al_load_bitmap("Audio and Images/Selector.bmp");
	paw = al_load_bitmap("Audio and Images/KoalaPaw.bmp");
	background = al_load_bitmap("Audio and Images/LeafPuzzleBackground.bmp");
	//omNomNom = al_load_bitmap("Audio and Images/omNomNom.bmp");
	al_convert_mask_to_alpha(leafDown, al_map_rgb(255,255,255));
	al_convert_mask_to_alpha(leafUp, al_map_rgb(255,255,255));
	al_convert_mask_to_alpha(rock, al_map_rgb(255,255,255));
	al_convert_mask_to_alpha(selector, al_map_rgb(255,255,255));
	al_convert_mask_to_alpha(paw, al_map_rgb(255,255,255));
	leafFlipSounds[0] = al_load_sample("Audio and Images/Flip.wav");
	leafFlipSounds[1] = al_load_sample("Audio and Images/Fwoo.wav");
	leafFlipSounds[2] = al_load_sample("Audio and Images/Swoosh.wav");
	leafFlipSounds[3] = al_load_sample("Audio and Images/Swooshhh.wav");
}

void LeafPuzzle::Init(int w, int h, int curLevel, int curScore){		//w is levelNumber, h is score
	string str;
	width = w;
	height = h;
	level = curLevel;
	score = curScore;
	ifstream openfile("Levels/AllLevels.txt");
	
	for(int i=0; i<level; i++)
		getline(openfile,str, 'x');
	
	getline(openfile,str, ' ');
	stringstream convert(str.c_str());
	convert >> type;
	getline(openfile,str, ' ');
	stringstream convert1(str.c_str());
	convert1 >> numRows;
	getline(openfile,str, ' ');
	stringstream convert2(str.c_str());
	convert2 >> numCol;
	numRows += 2;
	numCol += 2;
	
	arraySize = numRows*numCol;
	
	for(int i=0; i<numRows; i++)
		leafStates[i] = 3;
	for(int i=numRows; i<arraySize-numRows; i++){
		if(((i+1) % numRows) < 2)
			leafStates[i] = 3;
		else{
			getline(openfile,str, ' ');
			stringstream convert3(str.c_str());
			convert3 >> leafStates[i];
		}
	}
	for(int i=arraySize - numRows; i<arraySize; i++)
		leafStates[i] = 3;
	theSelected = numRows;
	openfile.close();
}

void LeafPuzzle::Update(){
	pawTime++;
	if(isPaw && pawTime == timeToCenter){
		for(int i=0; i<6; i++)
			if(selected[i] > -1 && selected[i] < arraySize)
				leafStates[selected[i]] = !leafStates[selected[i]];	
		if(hasWon() && state != MENU){
			state = LEAF_PUNCH;
			if(level == 14)
				state = CAVE_GAME;
			score += 100 * arraySize * type / (movesMade + 2);
		}
		al_play_sample(leafFlipSounds[rand() % 4], 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}

void LeafPuzzle::Move(int dir){
	if(!isPaw || pawTime > timeToCenter){
		if(dir == E)
			for(int i=0; i<5; i++)
				Move(Q);
		else if(dir > -1)	{
			doesWork = true;
			if(dir==Q){
				if(type != 5){
					flipped = 2 * (flipped % 3);
					if(flipped < 3) dir = UP;
					else dir = DOWN;
				}else{
					switch (flipped){
						case 2:{
							flipped = 7;
							if(theSelected + numRows + (int)floor(theSelected/numRows)%2 < numRows * numCol)
								theSelected += numRows + (int)floor(theSelected/numRows)%2 - 1;
							break;
						}
						case 7:{
							flipped = 4;
							break;
						}
						case 4:{
							flipped = 0;
							break;
						}
						case 0:{
							flipped = 1;
							break;
						}
						case 1:{
							flipped = 5;
							if(theSelected + numRows + (int)floor(theSelected/numRows)%2 < numRows * numCol - 1)
								theSelected += numRows + (int)floor(theSelected/numRows)%2;
							break;
						}
						case 5:{
							flipped = 2;
							if(theSelected >= 2*numRows)
								theSelected -= 2*numRows;
							break;
						}
					}
				}
			}
			switch(dir){
				case LEFT:{
					theSelected--;
					if(theSelected < 0)
						theSelected = arraySize - 1;
					break;
				}
				case DOWN:{
					theSelected += numRows;
					if(theSelected >= arraySize)
						theSelected = theSelected % numRows;
					break;
				}
				case UP:{
					theSelected -= numRows;
					if(theSelected < 0)
						theSelected += (numRows) * numCol;
					break;
				}
				case RIGHT:{
					theSelected++;
					if(theSelected >= arraySize)
						theSelected = 0;
					break;
				}
			}
			
			selected[0] = theSelected;
			
			if(type >= 3){
				if(flipped > 2){
					if(theSelected % (2*numRows) != 2*numRows - 1 && theSelected >= numRows)
						selected[1] = theSelected - numRows + (int)floor(theSelected/numRows)%2;
					else {
						selected[1] = -2; 
						doesWork = false;
					}
					if(theSelected % (2*numRows) != 0 && theSelected >= numRows)
						selected[2] = theSelected - numRows + (int)floor(theSelected/numRows)%2 - 1;
					else {
						selected[2] = -2; 
						doesWork = false;
					}
				}else{
					if(theSelected % (2*numRows) != 0 && (theSelected/numRows) < numCol - 1 )
						selected[1] = theSelected + numRows + (int)floor(theSelected/numRows)%2 - 1;
					else {
						selected[1] = -2; 
						doesWork = false;
					}
					if(theSelected % (2*numRows) != 2*numRows - 1 && (theSelected/numRows) < numCol - 1 )
						selected[2] = theSelected + numRows + (int)floor(theSelected/numRows)%2;
					else {
						selected[2] = -2; 
						doesWork = false;
					}
				}
			}
			if(type >= 4){
				if(flipped > 2){
					if(theSelected % numRows != 0)
						selected[3] = theSelected - 1;
					else {
						selected[3] = -2; 
						doesWork = false;
					}
				}else{
					if(theSelected % numRows != 0)
						selected[3] = theSelected - 1;
					else {
						selected[3] = -2; 
						doesWork = false;
					}
				}
			}
			if(type >= 5){
				switch (flipped){
					case 0:{
						if(theSelected >= numRows && theSelected % numRows != 0)
							selected[4] = theSelected - numRows + (int)floor(theSelected/numRows)%2 - 1;
						else {
							selected[4] = -2; 
							doesWork = false;
						}break;
					}
					case 1:{
						if(theSelected % numRows != numRows - 1)
							selected[4] = theSelected + 1;
						else {
							selected[4] = -2; 
							doesWork = false;
						}break;
					}
					case 2:{
						if(theSelected / numRows < numCol - 2)
							selected[4] = theSelected + 2 * numRows;
						else {
							selected[4] = -2; 
							doesWork = false;
						}break;
					}
					case 7:{
						if(theSelected % numRows != numRows - 1)
							selected[4] = theSelected + 1;
						else {
							selected[4] = -2; 
							doesWork = false;
						}break;
					}
					case 4:{
						if(theSelected < numRows * (numCol - 1) && theSelected % numRows != 0)
							selected[4] = theSelected + numRows - 1 + (int)floor(theSelected/numRows)%2;
						else {
							selected[4] = -2; 
							doesWork = false;
						}break;
					}
					case 5:{
						if(theSelected > 2*numRows -1)
							selected[4] = theSelected - 2 * numRows;
						else {
							selected[4] = -2; 
							doesWork = false;
						}break;
					}
				}
			}
		}
		for(int i=0; i<6; i++){
			if(leafStates[selected[i]] == 3){
				doesWork = false;
				break;
			}
		}
	}
}

void LeafPuzzle::Enter(){
	if(isPaw && pawTime > timeToCenter && 
		(pawYCenter + (pawVelY * (pawTime-timeToCenter)) < -75 + (25 * type)
		|| pawYCenter + (pawVelY * (pawTime-timeToCenter)) > 720 
		|| pawXCenter + (pawVelX * (pawTime-timeToCenter)) < -75 + (25 * type) 
		|| pawXCenter + (pawVelX * (pawTime-timeToCenter)) > 1280))
		isPaw = false;
	if(doesWork && !isPaw){
		isPaw = true;
		pawXCenter = 150 + 70*(theSelected%numRows) + 34*((int)(floor(theSelected/numRows))%2) - 5;
		pawYCenter = 50 + 85*((int)(floor(theSelected/numRows)) % numCol);
		if(type ==3)
			pawXCenter -= 25;
		if(type >= 4)
			pawXCenter -= 50;
		int angle = rand() % 360;
		pawVelX = 100 * cos(angle) * cos(angle);
		pawVelY = 100 * sin(angle) * sin(angle);
		if(rand() % 2)
			pawVelY *= -1;
		if(rand() % 2)
			pawVelX *= -1;
		pawTime = 0;
		timeToCenter = 15;
		movesMade++;
	}
}

bool LeafPuzzle::hasWon(){
	bool won = true;
	for(int i=0;i<arraySize;i++){
		if(leafStates[i] == 0){
			won = false;
			break;
		}
	}
	return won;
}

void LeafPuzzle::Render(){
	al_draw_bitmap(background,0,0,0);
	int xStart = 150;
	int yStart = 50;
	for(int i=0;i<arraySize;i++){
		if(leafStates[i] == 3)
			al_draw_bitmap(rock, xStart + 70*(i%numRows) + 34*((int)(floor(i/numRows))%2), yStart + 85*((int)(floor(i/numRows)) % numCol),0);
		else if(leafStates[i])
			al_draw_bitmap(leafUp, xStart + 70*(i%numRows) + 34*((int)(floor(i/numRows))%2), yStart + 85*((int)(floor(i/numRows)) % numCol),0);
		else
			al_draw_bitmap(leafDown, xStart + 70*(i%numRows) + 34*((int)(floor(i/numRows))%2), yStart + 85*((int)(floor(i/numRows)) % numCol),0);
	}
	for(int i=0;i<6;i++){
		if(selected[i] > -1 && selected[i] < arraySize){
			int xCorner = xStart + 10 + 70*(selected[i]%numRows) + 34*((int)(floor(selected[i]/numRows))%2);
			int yCorner = yStart + 30 + 85*((int)(floor(selected[i]/numRows)) % numCol);
			if (doesWork)
				al_draw_bitmap(selector, xCorner-10, yCorner-20, 0);
			else
				al_draw_rectangle(xCorner, yCorner, xCorner + 55, yCorner +77, al_map_rgb(255,0,0), 8);
			//if(selected[i] == theSelected)
			//	al_draw_rectangle(xCorner, yCorner, xCorner + 55, yCorner +77, al_map_rgb(255,0,0), 8);
		}
	}
	if(isPaw)
		al_draw_scaled_bitmap(paw, 0, 0, 100, 100, pawXCenter + (pawVelX * (pawTime-timeToCenter)), pawYCenter + (pawVelY * (pawTime-timeToCenter)), 75 + (25 * type), 75 + (25 * type), 0);
	al_draw_textf(font36, al_map_rgb(255,0,255), 15, 15, 0, "Score: %i", score);
	al_draw_textf(font36, al_map_rgb(255,0,255), 15, 50, 0, "Moves made: %i Level: %i", movesMade, level+1);
}

LeafPuzzle::~LeafPuzzle(){
	al_destroy_bitmap(paw);
	al_destroy_bitmap(selector);
	al_destroy_bitmap(rock);
	al_destroy_bitmap(omNomNom);
	al_destroy_bitmap(background);
	al_destroy_bitmap(leafUp);
	al_destroy_bitmap(leafDown);
	al_destroy_font(font36);
	for(int i=0;i<4;i++)
		al_destroy_sample(leafFlipSounds[i]);
}