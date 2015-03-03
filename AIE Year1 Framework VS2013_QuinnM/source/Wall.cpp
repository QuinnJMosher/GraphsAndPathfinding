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

bool Wall::IntersectsWith(float end1_x, float end1_y, float end2_x, float end2_y) {
	//get points
	float boxMin_x, boxMin_y;
	GetTopLeft(boxMin_x, boxMin_y);
	float boxMax_x, boxMax_y;
	GetBottomRight(boxMax_x, boxMax_y);

	//setup bools
	bool topLeft_above, bottomRight_above, topRight_above, bottomLeft_above;

	//topLeft
	if (boxMin_x > std::max(end1_x, end2_x)) {//greater than both
		topLeft_above = true;
	}
	else if (boxMin_x > std::min(end1_x, end2_x)) { //in between the two
		//find what percwntage we are between the points vertically
		float lerpT = (boxMin_y - std::min(end1_y, end2_y)) / (std::max(end1_y, end2_y) - std::min(end1_y, end2_y));
		//find the point the line crosses at our height
		float linePos;
		linePos = lerp(end1_x, end2_x, lerpT);

		//compare
		if (linePos < boxMin_x) {// / < . 
			topLeft_above = true;
		}
		else if (linePos > boxMin_x) {// . < /
			topLeft_above = false;
		}
		else { //they are equal
			return true;
		}
	}
	else if (boxMin_x < std::min(end1_x, end2_x)) {//less than both
		topLeft_above = true;
	}

	//bottom right
	if (boxMax_x > std::max(end1_x, end2_x)) {//greater than both
		bottomRight_above = true;
	}
	else if (boxMax_x > std::min(end1_x, end2_x)) { //in between the two
		//find what percwntage we are between the points vertically
		float lerpT = (boxMax_y - std::min(end1_y, end2_y)) / (std::max(end1_y, end2_y) - std::min(end1_y, end2_y));
		//find the point the line crosses at our height
		float linePos;
		linePos = lerp(end1_x, end2_x, lerpT);

		//compare
		if (linePos < boxMax_x) {// / < . 
			bottomRight_above = true;
		}
		else if (linePos > boxMax_x) {// . < /
			bottomRight_above = false;
		}
		else { //they are equal
			return true;
		}
	}
	else if (boxMax_x < std::min(end1_x, end2_x)) {//less than both
		bottomRight_above = true;
	}

	//topRight
	if (boxMax_x > std::max(end1_x, end2_x)) {//greater than both
		topRight_above = true;
	}
	else if (boxMax_x > std::min(end1_x, end2_x)) { //in between the two
		//find what percwntage we are between the points vertically
		float lerpT = (boxMin_y - std::min(end1_y, end2_y)) / (std::max(end1_y, end2_y) - std::min(end1_y, end2_y));
		//find the point the line crosses at our height
		float linePos;
		linePos = lerp(end1_x, end2_x, lerpT);

		//compare
		if (linePos < boxMax_x) {// / < . 
			topRight_above = true;
		}
		else if (linePos > boxMax_x) {// . < /
			topRight_above = false;
		}
		else { //they are equal
			return true;
		}
	}
	else if (boxMax_x < std::min(end1_x, end2_x)) {//less than both
		topRight_above = true;
	}

	//bottomLeft
	if (boxMin_x > std::max(end1_x, end2_x)) {//greater than both
		bottomLeft_above = true;
	}
	else if (boxMin_x > std::min(end1_x, end2_x)) { //in between the two
		//find what percwntage we are between the points vertically
		float lerpT = (boxMax_y - std::min(end1_y, end2_y)) / (std::max(end1_y, end2_y) - std::min(end1_y, end2_y));
		//find the point the line crosses at our height
		float linePos;
		linePos = lerp(end1_x, end2_x, lerpT);

		//compare
		if (linePos < boxMin_x) {// / < . 
			bottomLeft_above = true;
		}
		else if (linePos > boxMin_x) {// . < /
			bottomLeft_above = false;
		}
		else { //they are equal
			return true;
		}
	}
	else if (boxMin_x < std::min(end1_x, end2_x)) {//less than both
		bottomLeft_above = true;
	}

	//if all of the bools are the same then the line hasen't touched us, otherwise it has
	if (bottomLeft_above && bottomRight_above && topLeft_above && topRight_above) {
		return false;
	} else if (!bottomLeft_above && !bottomRight_above && !topLeft_above && !topRight_above) {
		return false;
	} else {
		return true;
	}

}

float Wall::lerp(float v0, float v1, float t) {
	return v0 + t*(v1 - v0);
}