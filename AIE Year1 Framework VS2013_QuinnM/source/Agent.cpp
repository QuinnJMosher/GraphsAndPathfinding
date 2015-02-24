#include "Agent.h"

Agent::Agent(float in_startX, float in_startY, float in_maxSpeed) {
	posX = in_startX;
	posY = in_startY;

	maxSpeed = in_maxSpeed;

	textureId = CreateSprite("images/invaders/invaders_1_00", 40, 40, true);

	pathfindingNodes = nullptr;
	float targetX = 0;
	float targetY = 0;
	isMoving = false;
}
Agent::Agent() {
	posX = 0;
	posY = 0;
	
	maxSpeed = 10;

	textureId = CreateSprite("images/invaders/invaders_1_00", 40, 40, true);

	pathfindingNodes = nullptr;
	float targetX = 0;
	float targetY = 0;
	isMoving = false;
}

Agent::~Agent() { }

void Agent::SetGraph(Graph* in_graph) {
	pathfindingNodes = in_graph;
}

void Agent::GoTo(float in_x, float in_y) {
	if (pathfindingNodes != nullptr) {
		int startNode = pathfindingNodes->NearestNode(posX, posY);
		int endNode = pathfindingNodes->NearestNode(in_x, in_y);

		path = pathfindingNodes->FindPath(startNode, endNode);
	}
	targetX = in_x;
	targetY = in_y;
	isMoving = true;
}

void Agent::Update(float in_deltaTime) {
	if (isMoving) {
		float tarX, tarY;

		if (path.size() > 0) {
			pathfindingNodes->GetNodePos(path[0], tarX, tarY);
		} else {
			tarX = targetX;
			tarY = targetY;
		}

		float directionX = posX - tarX;
		float directionY = posY - tarY;

		float distance = sqrt((directionX * directionX) + (directionY * directionY));

		directionX = directionX / distance;
		directionY = directionY / distance;

		float currentSpeed;
		if (distance > maxSpeed) {
			currentSpeed = maxSpeed;
		} else {
			currentSpeed = maxSpeed - distance;
		}

		posX += directionX * currentSpeed;
		posY += directionY * currentSpeed;
	}
}
void Agent::draw() {
	MoveSprite(textureId, posX, posY);
	DrawSprite(textureId);
}