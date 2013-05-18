#include "Menu.h"

Menu::Menu()
{
	state = MENU;
	mouseX = 0;
	mouseY = 0;
	width = 1280;
	height = 720;
	selected = LEAF_PUZZLE;
	fontHeight = 36;
	options = 3;
	y = fontHeight * options/2.0;
	x = width/2;
}

void Menu::Init(int w, int h)
{
	width = w;
	height = h;
	fontHeight = 36;
	options = 3;
	selected = NONE;
	y = fontHeight * options/2.0;
	x = width/2;
	font36 = al_load_font("AAJAX.ttf",36,0);
}

void Menu::Update(int dir)	//-1 for mouse movement
{
	if(dir == UP)
	{
		if(selected > LEAF_PUZZLE)
			selected--;
		else selected = EXIT;
	}
	else if(dir == DOWN)
	{
		if(selected < EXIT)
			selected++;
		else selected = LEAF_PUZZLE;
	}
	else if(mouseY < (height/2 + Menu::y) && mouseY > (height/2 - Menu::y))	//Mouse is below top option and above bottom option
	{
		int tempY = mouseY;								//So we don't mess up mouseY
		tempY -= height/2 - (Menu::y);					//Moves range of y-values so that lower bound is 0
		selected = ceil ((tempY-5) / fontHeight) + 1;	//The -5 adjusts for slight offset of draw_text
	}else
		selected = NONE;
} 

void Menu::Render()
{
	int tempY = height/2 - y;
	if(selected == LEAF_PUZZLE)al_draw_text(font36, al_map_rgb(0,0,255), x, tempY, ALLEGRO_ALIGN_CENTRE, "Play Leaf Puzzle");
		else al_draw_text(font36, al_map_rgb(255,0,255), x, tempY, ALLEGRO_ALIGN_CENTRE, "Play Leaf Puzzle");
	tempY += fontHeight;
	
	if(selected == HELP)al_draw_text(font36, al_map_rgb(0,0,255), x, tempY, ALLEGRO_ALIGN_CENTRE, "Help");
		else al_draw_text(font36, al_map_rgb(255,0,255), x, tempY, ALLEGRO_ALIGN_CENTRE, "Help");
	tempY += fontHeight;
	
	if(selected == EXIT)al_draw_text(font36, al_map_rgb(0,0,255), x, tempY, ALLEGRO_ALIGN_CENTRE, "Exit");
		else al_draw_text(font36, al_map_rgb(255,0,255), x, tempY, ALLEGRO_ALIGN_CENTRE, "Exit");
	
	al_draw_text(font36, al_map_rgb(0,0,255), 15, 60, 0, "WASD to move selector, E to flip leaves, Q to rotate selector");
	al_draw_textf(font36, al_map_rgb(100,10,100), 15, 15, 0, "h: %i w: %i", height, width);
}
