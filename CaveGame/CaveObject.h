#pragma once

#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>

class CaveObject{
	protected:
		int objHeight, objWidth; //state is based on mushroom consumption can be 0, 1 or 2
		double objX, objY, objVx, objVy;
	public:
		CaveObject(){}
		void virtual Update(){
			objX += objVx;
			objY += objVy;
		}
		void Render(ALLEGRO_BITMAP *objImage, int curFrame){
			al_draw_bitmap_region(objImage, curFrame*objWidth, 0, objWidth, al_get_bitmap_height(objImage), objX,objY, 0);
		}
		void Init(int x, int y, double vx, double vy, int h, int w){
			objX = x;
			objY = y;
			objVx = vx;
			objVy = vy;
			objHeight = h;
			objWidth = w;
		}
		int getRightBound(){return objX+objWidth;}
		bool Collides(int left, int right, int top, int bottom){
			if(objX < right && objX + objWidth > left && objY < bottom && objY + objHeight > top)
				return true;
			return false;
		}
};