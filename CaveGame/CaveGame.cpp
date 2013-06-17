# pragma once

#include "CaveGame.h"

CaveGame::CaveGame(){
	srand(time(NULL));
	koalaY = 100;
	koalaVx = 0;
	koalaVy = 0;
	ceilY = 100;
	state = CAVE_GAME;
	intoxication = 0;
	timeAtIntox = 0;
	health = 450;
	t = 0;
	koalaX = 100;
	floorY = 800;
	caveSpeed = -10;		
	font36 = al_load_font("Audio and Images/AAJAX.ttf",36,0);

	for(int i=0;i<10;i++)
		objVy[i] = 0;
	caveBackground = al_load_bitmap("Audio and Images/CaveBackground.bmp");
	koala = al_load_bitmap("Audio and Images/KoalaCave.bmp");
	al_convert_mask_to_alpha(koala, al_map_rgb(255,255,255));
	objImage[0][0] = al_load_bitmap("Audio and Images/GoodMushroom.bmp");
	objVx[0] = 0;
	objFrames[0][0] = 1;
	objFreq[0] = 100;
	objImage[0][1] = al_load_bitmap("Audio and Images/GoodMushroom1.bmp");
	objFrames[0][1] = 20;
	objImage[0][2] = al_load_bitmap("Audio and Images/GoodMushroom1.bmp");
	objFrames[0][2] = 21;
	objImage[1][0] = al_load_bitmap("Audio and Images/BadMushroom.bmp");
	objVx[1] = 0;
	objFrames[1][0] = 1;
	objFreq[1] = 50;
	objImage[1][1] = al_load_bitmap("Audio and Images/BadMushroom1.bmp");
	objFrames[1][1] = 20;
	objImage[1][2] = al_load_bitmap("Audio and Images/BadMushroom1.bmp");
	objFrames[1][2] = 21;
	objImage[2][0] = al_load_bitmap("Audio and Images/IntoxMushroom.bmp");
	objVx[2] = 0;
	objFrames[2][0] = 1;
	objFreq[2] = 20;
	objImage[2][1] = al_load_bitmap("Audio and Images/IntoxMushroom1.bmp");
	objFrames[2][1] = 20;
	objImage[2][2] = al_load_bitmap("Audio and Images/IntoxMushroom1.bmp");
	objFrames[2][2] = 21;
	objImage[3][0] = al_load_bitmap("Audio and Images/Bat.bmp");
	objVx[3] = -5;
	objFrames[3][0] = 1;
	objFreq[3] = 40;
	objImage[3][1] = al_load_bitmap("Audio and Images/Bat1.bmp");
	objFrames[3][1] = 20;
	objImage[3][2] = al_load_bitmap("Audio and Images/Bat1.bmp");
	objFrames[3][2] = 21;
	objImage[4][0] = al_load_bitmap("Audio and Images/Stalagmite.bmp");
	objVx[4] = 0;
	objFrames[4][0] = 1;
	objFreq[4] = 60;
	objImage[4][1] = al_load_bitmap("Audio and Images/Stalagmite1.bmp");
	objFrames[4][1] = 20;
	objImage[4][2] = al_load_bitmap("Audio and Images/Stalagmite1.bmp");
	objFrames[4][2] = 21;
	
	string str;
	ifstream openfile("Levels/CaveFrequencies.txt");
	for(int i=0;i<5;i++){
		getline(openfile, str, ' ');
		stringstream convert(str.c_str());
		convert >> objFreq[i];
	}
	
	for(int i=0;i<5;i++){
		numOnScreen[i] = 0;
		for(int k=0;k<3;k++){
			al_convert_mask_to_alpha(objImage[i][k], al_map_rgb(255,255,255));			
			objW[i][k] = al_get_bitmap_width(objImage[i][k]) / objFrames[i][k];
			objH[i][k] = al_get_bitmap_height(objImage[i][k]);
		}
	}
	for(int i=0; i<10;i++){
		for(int k=0;k<8;k++)
			isObj[i][k] = false;
	}
}

void CaveGame::Init(int w, int h, int curLevel, int curScore){
	string str;
	width = w;
	height = h;
	score = curScore;
	koalaHeight = al_get_bitmap_height(koala);
	koalaWidth = al_get_bitmap_width(koala);
	
}

void CaveGame::Update(){
	t++;
	timeAtIntox++;
	caveSpeed -= 0.002;
	if(intoxication > 0){
		intoxication -= 1;
		if(intoxication > 299)
			score += timeAtIntox/10;
	}
	
	koalaX += koalaVx;
	koalaY += koalaVy;
	if(koalaY < 0)
		koalaY=0;
	if(koalaY > height - koalaHeight)
		koalaY = height - koalaHeight;
	if(koalaX < 0)
		koalaX = 0;
	koalaVy *= 0.8;
	koalaVx *= 0.8;
	if(health < 1)
		state = MENU;
	for(int i=0;i<5;i++){
		if(rand() % (objFreq[i] * (numOnScreen[i]+1)) == 0){
			health-=3;
			for(int k=0; k<8;k++){
				if(!isObj[i][k]){
					objX[i][k] = width;
					objY[i][k] = rand() % (height - objH[i][0]);
					isObj[i][k] = true;
					numOnScreen[i]++;
					break;
				}
			}
		}
		for(int k=0; k<8;k++){
			if(isObj[i][k]){
				objX[i][k] += objVx[i]+ caveSpeed;
				objY[i][k] += objVy[i];
				if(objX[i][k] < koalaX + koalaWidth - 20 && objX[i][k] + objW[i][0] > koalaX  + 20 && objY[i][k] < koalaY + koalaHeight -20 && objY[i][k] + objH[i][0] > koalaY + 20){
					isObj[i][k] = false;
					numOnScreen[i]--;
					if(i > 2){
						state = MENU;
						isObj[i][k] = true;
					}else if(i==0){
						health += 300;
					}else if(i==1){
						if(intoxication > 249 && intoxication < 300)
							timeAtIntox = 0;
						health -= 200;
						intoxication += 50;
					}else if(i==2){
						intoxication += 175;
					}
					if(intoxication >= 900)
						intoxication = 899;
					if(health > 600)
						health = 600;
				}
				if(objX[i][k] + objW[i][0] < 0){
					isObj[i][k] = false;
					numOnScreen[i]--;
				}
			}
		}
	}
}

void CaveGame::Enter(){
}

void CaveGame::Move(int dir){
	if(dir == UP){
		koalaVy = -8;
	}else if(dir == DOWN){
		koalaVy = 8;
	}else if(dir == LEFT){
		koalaVx = -14;
	}else if(dir == RIGHT){
		koalaVx = 7;
	}
}

void CaveGame::Render(){
	al_draw_bitmap(caveBackground,0,0,0);
	al_draw_bitmap(koala, koalaX, koalaY, 0);
	for(int i=0; i<10;i++)
		for(int k=0;k<8;k++)
			if(isObj[i][k]){
				int numImage = (int)(intoxication/300) % 3;
				al_draw_bitmap_region(objImage[i][numImage], objW[i][numImage] * ((t/2) % objFrames[i][numImage]), 0, objW[i][numImage], objH[i][numImage], objX[i][k], objY[i][k], 0);
			}
	al_draw_rectangle(1,1,600,49,al_map_rgb(10,200,10),2);
	al_draw_filled_rectangle(2,2,health-2, 50, al_map_rgb(0,220,0));
	if(intoxication <= 300){
		al_draw_rectangle(1,53,299,99,al_map_rgb(180,70,180),2);
		al_draw_filled_rectangle(2,54, intoxication, 98, al_map_rgb(200,50,200));
	}else if(intoxication <= 600){
		al_draw_rectangle(1,53,299,69,al_map_rgb(180,70,180),2);
		al_draw_rectangle(1,73,299,109,al_map_rgb(180,70,180),2);
		al_draw_filled_rectangle(2,54, 298, 68, al_map_rgb(200,50,200));
		al_draw_filled_rectangle(2,74, intoxication-302, 108, al_map_rgb(200,50,200));
		al_draw_textf(font36, al_map_rgb(0,100,200), width, 40, ALLEGRO_ALIGN_RIGHT, "Score per second: %i", timeAtIntox*6);
	}else{
		al_draw_rectangle(1,53,299,69,al_map_rgb(180,70,180),2);
		al_draw_rectangle(1,73,299,89,al_map_rgb(180,70,180),2);
		al_draw_rectangle(1,93,299,129,al_map_rgb(180,70,180),2);
		al_draw_filled_rectangle(2,54, 298, 68, al_map_rgb(200,50,200));
		al_draw_filled_rectangle(2,74, 298, 88, al_map_rgb(200,50,200));
		al_draw_filled_rectangle(2,94, intoxication-602, 128, al_map_rgb(200,50,200));
		al_draw_textf(font36, al_map_rgb(0,100,200), width, 40, ALLEGRO_ALIGN_RIGHT, "Score per second: %i", timeAtIntox*6);
	}
	al_draw_text(font36, al_map_rgb(10,200,10),5,5,0,"Health");
	al_draw_textf(font36, al_map_rgb(0,100,200), width, 0, ALLEGRO_ALIGN_RIGHT, "Score: %i", score);
}

CaveGame::~CaveGame(){
	al_destroy_bitmap(koala);
	for(int i=0;i<10;i++)
		for(int k=0;k<3;k++)
			al_destroy_bitmap(objImage[i][k]);
	al_destroy_bitmap(caveBackground);
	al_destroy_font(font36);
}