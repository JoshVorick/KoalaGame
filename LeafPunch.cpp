#pragma once

#include "math.h"
#include "LeafPunch.h"


LeafPunch::LeafPunch(){
	srand(time(NULL));
	state = LEAF_PUNCH;
	treeX = 150;
	circleRadius = 50;
	timeWaited = 0;
	
	font36 = al_load_font("Audio and Images/AAJAX.ttf",36,0);
	
	tree = al_load_bitmap("Audio and Images/Tree.bmp");
	al_convert_mask_to_alpha(tree, al_map_rgb(255,255,255));
	target = al_load_bitmap("Audio and Images/Target.bmp");
	al_convert_mask_to_alpha(target, al_map_rgb(255,255,255));
	
	treeWidth = al_get_bitmap_width(tree);
	prevX = curX = rand() % (treeWidth - circleRadius) + treeX;
	prevY = curY = rand() % (treeWidth - circleRadius) + circleRadius;
}

void LeafPunch::Init(int w, int h){ //w = level, h = score
	levelScore = h;
}

void LeafPunch::Update(int dir){
}

void LeafPunch::Enter(){
	double dist = sqrt((mouseX-curX)*(mouseX-curX) + (mouseY-curY)*(mouseY-curY));
	if(dist < circleRadius){
		levelScore += abs(((circleRadius - (dist)) / (timeWaited + 20)) * ((curY - prevY) + (curX - prevX)));
		timeWaited = 0;
		prevX = curX;
		prevY = curY;
	}
	if(levelScore > 500)
		state = LEAF_PUZZLE;
	else{
		curX = rand() % (treeWidth - circleRadius) + treeX + circleRadius;
		curY = rand() % (treeWidth - circleRadius) + circleRadius;
	}
}

void LeafPunch::Render(){
	timeWaited++;
	al_draw_bitmap(tree, treeX, 0, 0);
	al_draw_bitmap(target, curX - 50, curY - 50, 0);
	al_draw_textf(font36, al_map_rgb(200,100,100), 5, 5, 0, "levelScore: %i Time: %i", levelScore, timeWaited);
}