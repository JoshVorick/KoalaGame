#pragma once

#include "fallingLeaf.h"

FallingLeaf::FallingLeaf(){
}		

void FallingLeaf::Init(int seed){
	srand(seed);
	t = 0;
	if(rand() % 2)
		leaf = al_load_bitmap("Audio and Images/LeafUp.bmp");
	else
		leaf = al_load_bitmap("Audio and Images/LeafDown.bmp");
	al_convert_mask_to_alpha(leaf, al_map_rgb(255,255,255));
	startX = rand() % 1100 + 160;
	startY = rand() % 100 - 200;
	velocity = (rand() % 200) / 100.0 + 3;
}

int FallingLeaf::getY(){
	return t*velocity + startY;
}

void FallingLeaf::Render(){
	al_draw_bitmap(leaf, startX, t*velocity + startY, 0);
	t++;
}