#pragma once

#include "LeafPunch.h"


LeafPunch::LeafPunch(){
	NUM_LEAVES = 100;
	srand(time(NULL));
	state = LEAF_PUNCH;
	treeX = 150;
	circleRadius = 50;
	timeWaited = 0;
	treeHealth = 500;
	for(int i=0;i<NUM_LEAVES;i++)
		isFalling[i] = false;
	
	font36 = al_load_font("Audio and Images/AAJAX.ttf",36,0);
	
	treeHit[0] = al_load_sample("Audio and Images/Ugh.wav");
	treeHit[1] = al_load_sample("Audio and Images/HitTheWood.wav");
	treeHit[2] = al_load_sample("Audio and Images/KnockOnWood.wav");
	treeHit[3] = al_load_sample("Audio and Images/Mmm.wav");
	treeHit[4] = al_load_sample("Audio and Images/MorningWood.wav");
	
	tree = al_load_bitmap("Audio and Images/Tree.bmp");
	al_convert_mask_to_alpha(tree, al_map_rgb(255,255,255));
	target = al_load_bitmap("Audio and Images/Target.bmp");
	al_convert_mask_to_alpha(target, al_map_rgb(255,255,255));
	background = al_load_bitmap("Audio and Images/TreePunchBackground.bmp");
	
	treeWidth = al_get_bitmap_width(tree);
	prevX = curX = rand() % (treeWidth - circleRadius) + treeX;
	prevY = curY = rand() % (treeWidth - circleRadius) + circleRadius;
}

void LeafPunch::Init(int w, int h){ //w = level, h = score
	score = h;
}

void LeafPunch::Update(int dir){}

void LeafPunch::Enter(){
	double dist = sqrt((mouseX-curX)*(mouseX-curX) + (mouseY-curY)*(mouseY-curY));
	al_play_sample(treeHit[rand() % 5], 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	al_play_sample(treeHit[1], 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	if(dist < circleRadius){
		score += abs(((circleRadius - (dist)) / (timeWaited + 20)) * ((curY - prevY) + (curX - prevX)));
		treeHealth -= abs((circleRadius - (dist)));
		timeWaited = 0;
		prevX = curX;
		prevY = curY;
		int n = 0;
		int end = (rand() % (circleRadius - (int)dist)) / 4;	//closer to the circle's radius means more leaves potentially.
		for(int i=0; i<NUM_LEAVES; i++){
			if(isFalling[i] && leaves[i]->getY() > 1000)
				isFalling[i] = false;
			if(!isFalling[i]){
				leaves[i] = new FallingLeaf();
				leaves[i]->Init(i);
				isFalling[i] = true;
				n++;
				if(n > end)
					break;
			}
		}
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
	al_draw_bitmap(background, 0, 0, 0);
	al_draw_bitmap(tree, treeX, 0, 0);
	al_draw_bitmap(target, curX - 50, curY - 50, 0);
	for(int i=0; i<NUM_LEAVES; i++)
		if(isFalling[i])
			leaves[i]->Render();
	double dist = sqrt((mouseX-curX)*(mouseX-curX) + (mouseY-curY)*(mouseY-curY));
	al_draw_textf(font36, al_map_rgb(255,0,255), 5, 5, 0, "Score: %i Time: %i", score, timeWaited);
	int scor = abs(((circleRadius - (dist)) / (timeWaited + 20)) * ((curY - prevY) + (curX - prevX)));
	int health = abs((circleRadius - (dist)));
	al_draw_textf(font36, al_map_rgb(255,0,255), 5, 70, 0, "Score for click: %i Tree health for hit: %i", scor, health);
	al_draw_rectangle(5, 50, 505, 70, al_map_rgb(100,100,100), 3);
	al_draw_filled_rectangle(5, 50, 505 - treeHealth, 70, al_map_rgb(0,255,0));
}