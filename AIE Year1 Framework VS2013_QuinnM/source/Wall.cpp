#include "Wall.h"

Wall::Wall(float in_posX, float in_posY, float in_width, float in_height) {
	posX = in_posX;
	posY = in_posY;
	width = in_width;
	height = in_height;

	spriteId = CreateSprite("images/crate_sideup.png", width, height, true);
}
Wall::Wall() {
	posX = 0;
	posY = 0;
	width = 10;
	height = 10;

	spriteId = CreateSprite("images/crate_sideup.png", width, height, true);
}

Wall::~Wall() { }

void Wall::Draw() {
	MoveSprite(spriteId, posX, posY);
	DrawSprite(spriteId);
}

void Wall::GetTopLeft(float& ref_x, float& ref_y) {
	ref_x = posX - (width / 2);
	ref_y = posY + (height / 2);
}
void Wall::GetBottomRight(float& ref_x, float& ref_y) {
	ref_x = posX + (width / 2);
	ref_y = posY - (height / 2);
}