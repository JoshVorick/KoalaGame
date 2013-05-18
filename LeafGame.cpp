#pragma once

#include <allegro5/allegro_primitives.h>

#include "math.h"
#include "LeafGame.h"

LeafGame::LeafGame()
{
	srand(time(NULL));
	state = LEAF_PUZZLE;
	theSelected = -1;
	flipped = 2;
	doesWork = false;
	for(int i=0; i<6; i++) selected[i] = -2;
	leafDown = al_load_bitmap("leafDown.bmp");
	al_convert_mask_to_alpha(leafDown, al_map_rgb(255,255,255));
	leafUp = al_load_bitmap("leafUp.bmp");
	al_convert_mask_to_alpha(leafUp, al_map_rgb(255,255,255));
	background = al_load_bitmap("background.bmp");
	omNomNom = al_load_bitmap("omNomNom.bmp");
	leafFlipSounds[0] = al_load_sample("Audio/Flip.wav");
	leafFlipSounds[1] = al_load_sample("Audio/Fwoo.wav");
	leafFlipSounds[2] = al_load_sample("Audio/Swoosh.wav");
	leafFlipSounds[3] = al_load_sample("Audio/Swooshhh.wav");
	font36 = al_load_font("AAJAX.ttf",36,0);
}

void LeafGame::Init(int w, int h)
{
	string str;
	/*
	ifstream openlevels("Levels.txt");
	for(int i=0; i<=w+1; i++)
	{
		getline(openlevels, str);
	}
	
	ifstream openfile(str.c_str());
	*/
	ifstream openfile("level3.txt");
	switch(w)
	{
		openfile.close();
		openfile.open("level1.txt");
		case(1):
		{
			openfile.close();
			openfile.open("level2.txt");
			break;
		}
		case(2):
		{
			openfile.close();
			openfile.open("level3.txt");
			break;
		}
		case(3):
		{
			openfile.close();
			openfile.open("level4.txt");
			break;
		}
		/*
		case(4):
		{
			openfile.close();
			openfile.open("level5.txt");
			break;
		}
		case(5):
		{
			openfile.close();
			openfile.open("level6.txt");
			break;
		}
		case(6):
		{
			openfile.close();
			openfile.open("level7.txt");
			break;
		}
		case(7):
		{
			openfile.close();
			openfile.open("level8.txt");
			break;
		}
		case(8):
		{
			openfile.close();
			openfile.open("level9.txt");
			break;
		}
		*/
	}
	
	getline(openfile,str, ' ');
	stringstream convert(str.c_str());
	convert >> type;
	
	getline(openfile,str, ' ');
	stringstream convert1(str.c_str());
	convert1 >> numRows;
	
	getline(openfile,str, ' ');
	stringstream convert2(str.c_str());
	convert2 >> numCol;
	
	arraySize = numRows*numCol;
	
	for(int i=0; i<arraySize; i++)
	{
		getline(openfile,str, ' ');
		stringstream convert3(str.c_str());
		convert3 >> leafStates[i];
	}
}

void LeafGame::Update(int dir)
{
	if(dir > -1)
	{
		doesWork = true;
		if(dir==SPACE)
		{
			if(type != 5)
			{
				flipped = 2 * (flipped % 3);
				if(flipped < 3) dir = UP;
				else dir = DOWN;
			}else
			{
				switch (flipped)
				{
					case 2:
					{
						flipped = 3;
						if(theSelected + numRows + (int)floor(theSelected/numRows)%2 < numRows * numCol)
							theSelected += numRows + (int)floor(theSelected/numRows)%2 - 1;
						break;
					}
					case 3:
					{
						flipped = 4;
						break;
					}
					case 4:
					{
						flipped = 0;
						break;
					}
					case 0:
					{
						flipped = 1;
						break;
					}
					case 1:
					{
						flipped = 5;
						if(theSelected + numRows + (int)floor(theSelected/numRows)%2 < numRows * numCol - 1)
							theSelected += numRows + (int)floor(theSelected/numRows)%2;
						break;
					}
					case 5:
					{
						flipped = 2;
						if(theSelected >= 2*numRows)
							theSelected -= 2*numRows;
						break;
					}
				}
			}
		}
		switch(dir)
		{
			case LEFT:
			{
				theSelected--;
				if(theSelected < 0)
					theSelected = arraySize - 1;
				break;
			}
			case DOWN:
			{
				theSelected += numRows;
				if(theSelected >= arraySize)
					theSelected = theSelected % numRows;
				break;
			}
			case UP:
			{
				theSelected -= numRows;
				if(theSelected < 0)
					theSelected += (numRows) * numCol;
				break;
			}
			case RIGHT:
			{
				theSelected++;
				if(theSelected >= arraySize)
					theSelected = 0;
				break;
			}
		}
		
		selected[0] = theSelected;
		
		if(type >= 3)
		{
			if(flipped > 2)
			{
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
			}
			else
			{
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
		if(type >= 4)
		{
			if(flipped > 2)
			{
				if(theSelected % numRows != 0)
					selected[3] = theSelected - 1;
				else {
					selected[3] = -2; 
					doesWork = false;
				}
			}
			else
			{
				if(theSelected % numRows != 0)
					selected[3] = theSelected - 1;
				else {
					selected[3] = -2; 
					doesWork = false;
				}
			}
		}
		if(type >= 5)
		{
			switch (flipped)
			{
				case 0:
				{
					if(theSelected >= numRows && theSelected % numRows != 0)
						selected[4] = theSelected - numRows + (int)floor(theSelected/numRows)%2 - 1;
					else {
						selected[4] = -2; 
						doesWork = false;
					}
					break;
				}
				case 1:
				{
					if(theSelected % numRows != numRows - 1)
						selected[4] = theSelected + 1;
					else {
						selected[4] = -2; 
						doesWork = false;
					}
					break;
				}
				case 2:
				{
					if(theSelected / numRows < numCol - 2)
						selected[4] = theSelected + 2 * numRows;
					else {
						selected[4] = -2; 
						doesWork = false;
					}
					break;
				}
				case 3:
				{
					if(theSelected % numRows != numRows - 1)
						selected[4] = theSelected + 1;
					else {
						selected[4] = -2; 
						doesWork = false;
					}
					break;
				}
				case 4:
				{
					if(theSelected < numRows * (numCol - 1) && theSelected % numRows != 0)
						selected[4] = theSelected + numRows - 1 + (int)floor(theSelected/numRows)%2;
					else {
						selected[4] = -2; 
						doesWork = false;
					}
					break;
				}
				case 5:
				{
					if(theSelected > 2*numRows -1)
						selected[4] = theSelected - 2 * numRows;
					else {
						selected[4] = -2; 
						doesWork = false;
					}
					break;
				}
			}
		}
	}
}

void LeafGame::Enter()
{
	if(doesWork)
	{
		for(int i=0; i<6; i++)
		{
			if(selected[i] > -1 && selected[i] < arraySize)
				leafStates[selected[i]] = !leafStates[selected[i]];
		}
		al_play_sample(leafFlipSounds[rand() % 3], 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		if(hasWon())
		{
			state = MENU;
		}
	}
}

bool LeafGame::hasWon()
{
	bool won = true;
	
	for(int i=0;i<arraySize;i++)
	{
		if(!leafStates[i])
		{
			won = false;
			break;
		}
	}
	return won;
}

void LeafGame::Render()
{
	al_draw_bitmap(background,0,0,0);
	
	for(int i=0;i<arraySize;i++)
	{
		if(leafStates[i])
			al_draw_bitmap(leafUp, 300 + 70*(i%numRows) + 34*((int)(floor(i/numRows))%2),100 + 85*((int)(floor(i/numRows)) % numCol),0);
		else
			al_draw_bitmap(leafDown, 300 + 70*(i%numRows) + 34*((int)(floor(i/numRows))%2),100 + 85*((int)(floor(i/numRows)) % numCol),0);
	}
	for(int i=0;i<6;i++)
	{
		if(selected[i] > -1 && selected[i] < arraySize)
		{
			int xCorner = 310 + 70*(selected[i]%numRows) + 34*((int)(floor(selected[i]/numRows))%2);
			int yCorner = 130 + 85*((int)(floor(selected[i]/numRows)) % numCol);
			if(i>0 && doesWork)
				al_draw_rectangle(xCorner, yCorner, xCorner + 55, yCorner+ 77, al_map_rgb(0,255,0),8);
			else if (doesWork)
				al_draw_rectangle(xCorner, yCorner, xCorner + 55, yCorner+ 77, al_map_rgb(0,0,255),8);
			else
				al_draw_rectangle(xCorner, yCorner, xCorner + 55, yCorner +77, al_map_rgb(255,0,0), 8);
		}
	}
	
	al_draw_textf(font36, al_map_rgb(255,0,255), 15, 15, 0, "Flipped: %i", flipped);
	
	//al_draw_bitmap(foreground,0,0,0);
}