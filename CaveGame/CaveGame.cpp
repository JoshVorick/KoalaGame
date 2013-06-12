# pragma once

#include "CaveGame.h"

CaveGame::CaveGame(){
	koalaY = 100;
	koalaV = 0;
	ceilY = 100;
	state = CAVE_GAME;
	gravity = 75;
	intoxication = 0;
	time = 0;
	koalaX = 100;
	floorY = 800;
	caveSpeed = -10;
	koala = al_load_bitmap("Audio and Images/Koala.bmp");
	al_convert_mask_to_alpha(koala, al_map_rgb(255,255,255));
	objImage[0][0] = al_load_bitmap("Audio and Images/Stalactite.bmp");
	al_convert_mask_to_alpha(objImage[0][0], al_map_rgb(255,255,255));
	objY[0] = ceilY;
	objV[0] = caveSpeed;
	objFrames[0][0] = 1;
	objImage[1][0] = al_load_bitmap("Audio and Images/Stalagmite.bmp");
	al_convert_mask_to_alpha(objImage[1][0], al_map_rgb(255,255,255));
	objY[1] = floorY - al_get_bitmap_height(objImage[1][0]);
	objV[1] = caveSpeed;
	objFrames[1][0] = 1;
	objImage[2][0] = al_load_bitmap("Audio and Images/Bat.bmp");
	al_convert_mask_to_alpha(objImage[2][0], al_map_rgb(255,255,255));
	objY[2] = ceilY + 300;
	objV[2] = caveSpeed - 5;
	objFrames[2][0] = 1;
	objImage[3][0] = al_load_bitmap("Audio and Images/Mushroom.bmp");
	al_convert_mask_to_alpha(objImage[3][0], al_map_rgb(255,255,255));
	objY[3] = floorY - al_get_bitmap_height(objImage[3][0]);
	objV[3] = caveSpeed;
	objFrames[3][0] = 1;
	koala = al_load_bitmap("Audio and Images/Koala.bmp");
	al_convert_mask_to_alpha(koala, al_map_rgb(255,255,255));
	objImage[0][1] = al_load_bitmap("Audio and Images/Stalactite1.bmp");
	al_convert_mask_to_alpha(objImage[0][1], al_map_rgb(255,255,255));
	objFrames[0][1] = 20;
	objImage[1][1] = al_load_bitmap("Audio and Images/Stalagmite.bmp");
	al_convert_mask_to_alpha(objImage[1][1], al_map_rgb(255,255,255));
	objFrames[1][1] = 1;
	objImage[2][1] = al_load_bitmap("Audio and Images/Bat.bmp");
	al_convert_mask_to_alpha(objImage[2][1], al_map_rgb(255,255,255));
	objFrames[2][1] = 1;
	objImage[3][1] = al_load_bitmap("Audio and Images/Mushroom.bmp");
	al_convert_mask_to_alpha(objImage[3][1], al_map_rgb(255,255,255));
	objFrames[3][1] = 1;
	for(int i=0;i<10;i++)
		for(int k=0;k<8;k++)
			obstacles[i][k] = new CaveObject();
	for(int i=0; i<10;i++)
		for(int k=0;k<8;k++)
			isObj[i][k] = false;
}

void CaveGame::Init(int w, int h, int curLevel, int curSccore){
	string str;
	width = w;
	height = h;
	koalaHeight = al_get_bitmap_height(koala);
	koalaWidth = al_get_bitmap_width(koala);
	
	ifstream openfile("Levels/CaveLevel.txt");
	getline(openfile,str,' ');
	stringstream convert(str.c_str());
	convert >> timeDone;
	int total;
	for(int i=0;i<10;i++){
		getline(openfile,str,'~');
		getline(openfile,str,' ');
		stringstream convert1(str.c_str());
		convert1 >> total;
		for(int k=0; k<total; k++){
			getline(openfile,str,' ');
			stringstream convert2(str.c_str());
			convert2 >> objTime[i][k];
		}
		numObj[i] = 0;
	}
	openfile.close();
}

void CaveGame::Update(){
	if(intoxication > 0)
		intoxication -= 1;
	if(koalaY >= (floorY - koalaHeight) && koalaV > 0){
		koalaV = 0;
		koalaY = floorY - koalaHeight;
	}
	if(koalaY < floorY - koalaHeight)
		koalaV += gravity/60;
	koalaY += koalaV;
	time++;
	for(int i=0;i<10;i++){
		if(time == objTime[i][numObj[i]] && time < timeDone){
			for(int k=0; k<8;k++){
				if(!isObj[i][k]){
					obstacles[i][k]->Init(width, objY[i], objV[i], 0, al_get_bitmap_height(objImage[i][0]), al_get_bitmap_width(objImage[i][0]));
					isObj[i][k] = true;
					numObj[i]++;
					break;
				}
			}
		}
		for(int k=0; k<8;k++){
			if(isObj[i][k]){
				obstacles[i][k]->Update();
				if(obstacles[i][k]->Collides(koalaX+50, koalaX + koalaWidth-30, koalaY+5, koalaY + koalaHeight)){
					if(i == 3){
						intoxication += 300;
						isObj[3][k] = false;
						if(intoxication > 600)
							intoxication = 599;
					}else{
						state = MENU;
					}
				}
				if(obstacles[i][k]->getRightBound() < 0)
					isObj[i][k] = false;
			}
		}
	}
}

void CaveGame::Enter(){
	if(koalaY >= floorY - koalaHeight)
		koalaV -= 30;
}

void CaveGame::Move(int dir){

}

void CaveGame::Render(){
	al_draw_bitmap(koala, koalaX, koalaY, 0);
	for(int i=0; i<10;i++)
		for(int k=0;k<8;k++)
			if(isObj[i][k])
				obstacles[i][k]->Render(objImage[i][(int)(intoxication/300) % 2], (time/3) % objFrames[i][(int)(intoxication/300) % 2]);

	al_draw_filled_rectangle(0,0,width,ceilY,al_map_rgb(64,64,64));
	al_draw_filled_rectangle(0,floorY,width,height,al_map_rgb(64,64,64));
	al_draw_filled_rectangle(0,0, intoxication, 10, al_map_rgb(200,50,200));
}

CaveGame::~CaveGame(){
	al_destroy_bitmap(koala);
	for(int i=0;i<10;i++)
		al_destroy_bitmap(objImage[i][0]);
	al_destroy_bitmap(koala);
	delete obstacles;
}