# pragma once

#include "CaveGame.h"

CaveGame::CaveGame(){
	koalaY = 100;
	koalaVx = 0;
	koalaVy = 0;
	ceilY = 100;
	state = CAVE_GAME;
	intoxication = 0;
	health = 450;
	time = 0;
	koalaX = 100;
	floorY = 800;
	caveSpeed = -10;
	for(int i=0;i<10;i++)
		objVy[i] = 0;
	caveBackground = al_load_bitmap("Audio and Images/CaveBackground.bmp");
	koala = al_load_bitmap("Audio and Images/Koala.bmp");
	al_convert_mask_to_alpha(koala, al_map_rgb(255,255,255));
	objImage[0][0] = al_load_bitmap("Audio and Images/GoodMushroom.bmp");
	objVx[0] = caveSpeed;
	objFrames[0][0] = 1;
	objFreq[0] = 150;
	objImage[0][1] = al_load_bitmap("Audio and Images/GoodMushroom1.bmp");
	objFrames[0][1] = 20;
	objImage[1][0] = al_load_bitmap("Audio and Images/BadMushroom.bmp");
	objVx[1] = caveSpeed;
	objFrames[1][0] = 1;
	objFreq[1] = 150;
	objImage[1][1] = al_load_bitmap("Audio and Images/BadMushroom1.bmp");
	objFrames[1][1] = 20;
	objImage[2][0] = al_load_bitmap("Audio and Images/IntoxMushroom.bmp");
	objVx[2] = caveSpeed;
	objFrames[2][0] = 1;
	objFreq[2] = 150;
	objImage[2][1] = al_load_bitmap("Audio and Images/IntoxMushroom1.bmp");
	objFrames[2][1] = 20;
	objImage[3][0] = al_load_bitmap("Audio and Images/Bat.bmp");
	objVx[3] = caveSpeed - 5;
	objFrames[3][0] = 1;
	objFreq[3] = 120;
	objImage[3][1] = al_load_bitmap("Audio and Images/Bat1.bmp");
	objFrames[3][1] = 3;
	objImage[4][0] = al_load_bitmap("Audio and Images/Stalagmite.bmp");
	objVx[4] = caveSpeed;
	objFrames[4][0] = 1;
	objFreq[4] = 180;
	objImage[4][1] = al_load_bitmap("Audio and Images/Stalagmite1.bmp");
	objFrames[4][1] = 20;
	
	for(int i=0;i<5;i++){
		for(int k=0;k<2;k++){
			al_convert_mask_to_alpha(objImage[i][k], al_map_rgb(255,255,255));			
			objW[i][k] = al_get_bitmap_width(objImage[i][k]) / objFrames[i][k];
			objH[i][k] = al_get_bitmap_height(objImage[i][k]);
		}
	}
	for(int i=0; i<10;i++)
		for(int k=0;k<8;k++)
			isObj[i][k] = false;
}

void CaveGame::Init(int w, int h, int curLevel, int curScore){
	string str;
	width = w;
	height = h;
	koalaHeight = al_get_bitmap_height(koala);
	koalaWidth = al_get_bitmap_width(koala);
	
}

void CaveGame::Update(){
	time++;
	if(intoxication > 0)
		intoxication -= 1;
	koalaX += koalaVx;
	koalaY += koalaVy;
	if(koalaY < 0)
		koalaY=0;
	if(koalaY > height - koalaHeight)
		koalaY = height - koalaHeight;
	if(koalaX < 0)
		koalaX = 0;
	koalaVy /= 1.2;
	koalaVx /= 1.2;
	if(health < 1)
		state = MENU;
	for(int i=0;i<5;i++){
		if(rand() % objFreq[i] == 0){
			objFreq[i] += 100;
			health-=3;
			for(int k=0; k<8;k++){
				if(!isObj[i][k]){
					objX[i][k] = width;
					objY[i][k] = rand() % (height - objH[i][0]);
					isObj[i][k] = true;
					break;
				}
			}
		}
		else
			objFreq[i]--;
		for(int k=0; k<8;k++){
			if(isObj[i][k]){
				objX[i][k] += objVx[i];
				objY[i][k] += objVy[i];
				if(objX[i][k] < koalaX + koalaWidth - 40 && objX[i][k] + objW[i][0] > koalaX + 50 && objY[i][k] < koalaY + koalaHeight && objY[i][k] + objH[i][0] > koalaY + 5){
					if(i > 2){
						state = MENU;
					}else if(i==0){
						health += 300;
					}else if(i==1){
						health -= 200;
						intoxication += 50;
					}else if(i==2){
						intoxication += 250;
					}
					if(intoxication > 600)
						intoxication = 599;
					if(health > 600)
						health = 600;
					isObj[i][k] = false;
				}
				if(objX[i][k] + objW[i][0] < 0)
					isObj[i][k] = false;
			}
		}
	}
}

void CaveGame::Enter(){
}

void CaveGame::Move(int dir){
	if(dir == UP){
		koalaVy = -14;
	}else if(dir == DOWN){
		koalaVy = 14;
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
				int numImage = (int)(intoxication/300) % 2;
				al_draw_bitmap_region(objImage[i][numImage], objW[i][numImage] * ((time/3) % objFrames[i][numImage]), 0, objW[i][numImage], objH[i][numImage], objX[i][k], objY[i][k], 0);
			}
	al_draw_rectangle(1,1,600,49,al_map_rgb(10,200,10),2);
	al_draw_filled_rectangle(2,2,health-2, 50, al_map_rgb(0,220,0));
	if(intoxication <= 300)
		al_draw_filled_rectangle(2,54, intoxication, 98, al_map_rgb(200,50,200));
	else{
		al_draw_rectangle(1,53,299,69,al_map_rgb(180,70,180),2);
		al_draw_rectangle(1,73,299,109,al_map_rgb(180,70,180),2);
		al_draw_filled_rectangle(2,54, 298, 68, al_map_rgb(200,50,200));
		al_draw_filled_rectangle(2,74, intoxication-300 - 2, 110, al_map_rgb(200,50,200));
	}
}

CaveGame::~CaveGame(){
	al_destroy_bitmap(koala);
	for(int i=0;i<10;i++)
		al_destroy_bitmap(objImage[i][0]);
	al_destroy_bitmap(koala);
}