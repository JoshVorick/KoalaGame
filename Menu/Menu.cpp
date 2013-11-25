#pragma once

#include "Menu.h"

Menu::Menu(){
	state = MENU;
	mouseX = 0;
	mouseY = 0;
	score = 0;
	selected = LEAF_PUZZLE;
	fontHeight = 36;
	options = 3;
	y = fontHeight * options/2.0;
	x = width/2;
	helpMenu = al_load_bitmap("Audio and Images/HelpMenu.bmp");
	background = al_load_bitmap("Audio and Images/MenuBackground.bmp");
	font36 = al_load_font("Audio and Images/AAJAX.ttf", fontHeight, 0);
	selected = LEAF_PUZZLE;
	options = 3;
}

void Menu::Init(int w, int h, int curLevel, int curScore){
	width = w;
	height = h;
	y = fontHeight * options/2.0;
	x = width/2;
}

void Menu::Update(){	
	if(mouseY < (height/2 + Menu::y) && mouseY > (height/2 - Menu::y)){	//*Mouse is below top option and above bottom option
		int tempY = mouseY;								//So we don't mess up mouseY
		tempY -= (height/2 - (Menu::y));					//Moves range of y-values so that lower bound is 0
		selected = ceil((float)(tempY-5) / fontHeight) + 1;	//The -5 adjusts for slight offset of draw_text 
	}else
		selected = NONE;
} 

void Menu::Move(int dir){
	if(dir == UP)	{
		if(selected > LEAF_PUNCH)
			selected--;
		else 
			selected = EXIT;
	}
	else if(dir == DOWN){
		if(selected < EXIT)
			selected++;
		else 
			selected = LEAF_PUNCH;
	}
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
		al_draw_text(font36, al_map_rgb(0,0,255), x, tempY, ALLEGRO_ALIGN_CENTRE, "Play Game");
	else 
		al_draw_text(font36, al_map_rgb(255,0,255), x, tempY, ALLEGRO_ALIGN_CENTRE, "Play Game");
	tempY += fontHeight;
	
	if(selected == HELP)
		al_draw_text(font36, al_map_rgb(0,0,255), x, tempY, ALLEGRO_ALIGN_CENTRE, "Help");
	else 
		al_draw_text(font36, al_map_rgb(255,0,255), x, tempY, ALLEGRO_ALIGN_CENTRE, "Help");
	tempY += fontHeight;
	
	if(selected == EXIT)
		al_draw_text(font36, al_map_rgb(0,0,255), x, tempY, ALLEGRO_ALIGN_CENTRE, "Exit");
	else 
		al_draw_text(font36, al_map_rgb(255,0,255), x, tempY, ALLEGRO_ALIGN_CENTRE, "Exit");
	al_draw_textf(font36, al_map_rgb(100,100,100), 5, 5, 0, "X: %i Y: %i", mouseX, mouseY);
}

Menu::~Menu(){
	al_destroy_bitmap(helpMenu);
	al_destroy_bitmap(background);
	al_destroy_font(font36);
	al_destroy_sample(clicked);
}