#include "Menu.h"

Menu::Menu(){
	state = MENU;
	mouseX = 0;
	mouseY = 0;
	width = 1280;
	height = 720;
	score = 0;
	selected = LEAF_PUZZLE;
	fontHeight = 36;
	options = 3;
	y = fontHeight * options/2.0;
	x = width/2;
	helpMenu = al_load_bitmap("Audio and Images/HelpMenu.bmp");
	background = al_load_bitmap("Audio and Images/MenuBackground.bmp");
}

void Menu::Init(int w, int h){
	fontHeight = 36;
	options = 3;
	selected = LEAF_PUZZLE;
	y = fontHeight * options/2.0;
	x = width/2;
	font = al_load_font("Audio and Images/AAJAX.ttf", fontHeight, 0);
}

void Menu::Update(int dir){	//-1 for mouse movement
	if(dir == UP)	{
		if(selected > LEAF_PUNCH)
			selected--;
		else selected = EXIT;
	}
	else if(dir == DOWN)	{
		if(selected < EXIT)
			selected++;
		else selected = LEAF_PUNCH;
	}
	else if(mouseY < (height/2 + Menu::y) && mouseY > (height/2 - Menu::y)){	//*Mouse is below top option and above bottom option
		int tempY = mouseY;								//So we don't mess up mouseY
		tempY -= (height/2 - (Menu::y));					//Moves range of y-values so that lower bound is 0
		selected = ceil((tempY-5) / fontHeight) + 1;	//The -5 adjusts for slight offset of draw_text 
	}else
		selected = NONE;
} 

void Menu::Enter(){
	if(selected != HELP)
		state = selected;
}

void Menu::Render(){
	al_draw_bitmap(background, 0, 0, 0);
	if(selected == HELP)
		al_draw_bitmap(helpMenu, 0, 0, 0);
	int tempY = height/2 - y;
	if(selected == LEAF_PUNCH)
		al_draw_text(font, al_map_rgb(0,0,255), x, tempY, ALLEGRO_ALIGN_CENTRE, "Play Game");
	else 
		al_draw_text(font, al_map_rgb(255,0,255), x, tempY, ALLEGRO_ALIGN_CENTRE, "Play Game");
	tempY += fontHeight;
	
	if(selected == HELP)
		al_draw_text(font, al_map_rgb(0,0,255), x, tempY, ALLEGRO_ALIGN_CENTRE, "Help");
	else 
		al_draw_text(font, al_map_rgb(255,0,255), x, tempY, ALLEGRO_ALIGN_CENTRE, "Help");
	tempY += fontHeight;
	
	if(selected == EXIT)
		al_draw_text(font, al_map_rgb(0,0,255), x, tempY, ALLEGRO_ALIGN_CENTRE, "Exit");
	else 
		al_draw_text(font, al_map_rgb(255,0,255), x, tempY, ALLEGRO_ALIGN_CENTRE, "Exit");
}