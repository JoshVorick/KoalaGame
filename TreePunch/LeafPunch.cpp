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
	curCombo = 0;
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

void LeafPunch::Update(){
	timeWaited++;
	if(timeWaited > circleRadius * 25 / (curCombo+1)){
		curCombo = 0;
		timeWaited = 0;
		circleRadius = 50 - (2*curCombo);
		curX = rand() % (treeWidth - (2*circleRadius)) + treeX + circleRadius;
		curY = rand() % (height - (2*circleRadius)) + circleRadius;
		circleRadius = 50 - (2*curCombo);
	}

}

void LeafPunch::Init(int w, int h, int curLevel, int curScore){ //w = level, h = score
	width = w;
	height = h;
	score = curScore;
}

void LeafPunch::Move(int dir){}

void LeafPunch::Enter(){
	double dist = sqrt((mouseX-curX)*(mouseX-curX) + (mouseY-curY)*(mouseY-curY));
	al_play_sample(treeHit[rand() % 5], 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	al_play_sample(treeHit[1], 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	if(dist < circleRadius){
		curCombo++;
		score += ((curCombo)/2) * abs(((50 - (dist)) / (timeWaited + 10)) * ((curY - prevY) + (curX - prevX)));
		treeHealth -= abs((50 - (dist))) / 2;
		prevX = curX;
		prevY = curY;
		int n = 0;
		int end = (rand() % (circleRadius - (int)dist)) / 4;	//closer to the circle's radius means more leaves potentially.
		for(int i=0; i<NUM_LEAVES; i++){
			if(isFalling[i] && leaves[i]->getY() > 720)
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
		if(curCombo < 20)
			circleRadius = 50 - (2*curCombo);
	}
	else
		curCombo = 0;
	if(treeHealth <= 0)
		state = LEAF_PUZZLE;
	else if(dist < circleRadius){
		curX = rand() % (treeWidth - (2*circleRadius)) + treeX + circleRadius;
		curY = rand() % (height - (2*circleRadius)) + circleRadius;
		timeWaited = 0;
	}
}

void LeafPunch::Render(){
	int timeLeft = circleRadius * 25 / (curCombo+1) - timeWaited;
	al_draw_bitmap(background, 0, 0, 0);
	al_draw_bitmap(tree, treeX, 0, 0);
	float percentDone =  timeLeft / (timeLeft + timeWaited + .1);
	al_draw_tinted_scaled_bitmap(target, al_map_rgba_f(percentDone,percentDone,percentDone,percentDone), 0, 0, 100, 100, curX - circleRadius, curY - circleRadius, 2*circleRadius, 2*circleRadius, 0);
	//al_draw_ellipse(curX, curY, circleRadius * (timeLeft / (timeLeft + timeWaited + 1.0)), 
	//		circleRadius * (timeLeft / (timeLeft + timeWaited + 1.0)), al_map_rgb(0,0,0), 3); //draws circle based on percent of time remaining.
	for(int i=0; i<NUM_LEAVES; i++)
		if(isFalling[i])
			leaves[i]->Render();
	double dist = sqrt((mouseX-curX)*(mouseX-curX) + (mouseY-curY)*(mouseY-curY));
	al_draw_textf(font36, al_map_rgb(255,0,255), 5, 5, 0, "Score: %i", score);
	int scor = abs(((50 - (dist)) / (timeWaited + 20)) * ((curY - prevY) + (curX - prevX)));
	int health = abs((50 - (dist)));
	//al_draw_textf(font36, al_map_rgb(255,0,255), 5, 70, 0, "Score for click: %i Tree health for hit: %i", scor, health);
	al_draw_textf(font36, al_map_rgb(255,0,255), 5, 70, 0, "COMBO: %i", curCombo);
	//al_draw_textf(font36, al_map_rgb(255,0,255), 5, 150, 0, "ComboTime left: %i", timeLeft);
	al_draw_rectangle(5, 50, 505, 70, al_map_rgb(100,100,100), 3);
	al_draw_filled_rectangle(5, 50, 505 - treeHealth, 70, al_map_rgb(0,255,0));
}

LeafPunch::~LeafPunch(){
	al_destroy_bitmap(tree);
	al_destroy_bitmap(target);
	al_destroy_bitmap(fallingLeaf[0]);
	al_destroy_bitmap(fallingLeaf[1]);
	al_destroy_bitmap(background);
	al_destroy_font(font36);
	delete[] fallingLeaf;
}