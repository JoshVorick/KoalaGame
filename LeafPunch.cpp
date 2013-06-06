#pragma once

#include "math.h"
#include "LeafPunch.h"


LeafPunch::LeafPunch(){
	srand(time(NULL));
	state = LEAF_PUNCH;
	treeX = 150;
	circleRadius = 50;
	timeWaited = 0;
	treeHealth = 500;
	
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
	score = h;
}

void LeafPunch::Update(int dir){
}

void LeafPunch::Enter(){
	double dist = sqrt((mouseX-curX)*(mouseX-curX) + (mouseY-curY)*(mouseY-curY));
	if(dist < circleRadius){
		score += abs(((circleRadius - (dist)) / (timeWaited + 20)) * ((curY - prevY) + (curX - prevX)));
		treeHealth -= abs((circleRadius - (dist)));
		timeWaited = 0;
		prevX = curX;
		prevY = curY;
	}
	if(treeHealth <= 0)
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
	double dist = sqrt((mouseX-curX)*(mouseX-curX) + (mouseY-curY)*(mouseY-curY));
	al_draw_textf(font36, al_map_rgb(255,0,255), 5, 5, 0, "Score: %i Time: %i", score, timeWaited);
	int scor = abs(((circleRadius - (dist)) / (timeWaited + 20)) * ((curY - prevY) + (curX - prevX)));
	int health = abs((circleRadius - (dist)));
	al_draw_textf(font36, al_map_rgb(255,0,255), 5, 70, 0, "Score for click: %i Tree health for hit: %i", scor, health);
	al_draw_rectangle(5, 50, 505, 70, al_map_rgb(100,100,100), 3);
	al_draw_filled_rectangle(5, 50, 5 + treeHealth, 70, al_map_rgb(90,90,90));
}