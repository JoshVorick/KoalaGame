#pragma once

#include <allegro5/allegro_image.h>
#include "math.h"

class FallingLeaf{
	private:
		int startX, startY, t;
		double velocity;
		ALLEGRO_BITMAP *leaf;
	public:
		FallingLeaf();
		void Init(int seed);
		void Render();
		int getY();
};