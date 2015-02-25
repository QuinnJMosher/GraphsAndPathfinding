#ifndef _Wall_h_
#define _Wall_h_

#include "AIE.h"

class Wall {
public:
	Wall(float in_posX, float in_posY, float in_width, float in_height);
	Wall();
	~Wall();

	void Draw();
	
	void GetTopLeft(float& ref_x, float& ref_y);
	void GetBottomRight(float& ref_x, float& ref_y);

private:
	float posX;
	float posY;
	float width;
	float height;

	unsigned int spriteId;
};

#endif