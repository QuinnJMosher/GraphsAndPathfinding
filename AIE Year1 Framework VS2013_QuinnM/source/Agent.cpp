#include "Agent.h"

Agent::Agent(float in_startX, float in_startY, float in_maxSpeed) {
	posX = in_startX;
	posY = in_startY;

	maxSpeed = in_maxSpeed;

	textureId = CreateSprite("images/invaders/invaders_1_00.png", 40, 40, true);

	pathfindingNodes = nullptr;
	float targetX = 0;
	float targetY = 0;
	isMoving = false;
}
Agent::Agent() {
	posX = 0;
	posY = 0;
	
	maxSpeed = 10;

	textureId = CreateSprite("images/invaders/invaders_1_00.png", 40, 40, true);

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
	//smooth path

	isMoving = true;
}

void Agent::SmoothPath() {
	for (int i = 0; i < path.size() - 2; i++) {
		//get position of the start of the line
		float end1_x, end1_y;
		pathfindingNodes->GetNodePos(path[i], end1_x, end1_y);

		//check for unnessesary nodes after current node
		for (int j = i + 2; j < path.size(); j++) {//change to while loop (we will only need to access i and i + 2)
			float end2_x, end2_y;
			pathfindingNodes->GetNodePos(path[j], end2_x, end2_y);

			//get box points
			//find where min point is (above/below) (right/left)
			//find where max point is
			//compare the point's relitive positions
			//if they aren't coliding, remove the extra point and suptract j by one
			//break loop it they are coliding
		}

	}

	//if(while?) path.size() > 2 run comparison between current pos and path[1]
	
	//if path.size() == 1 run comparison between current pos and target pos
}

void Agent::Update(float in_deltaTime) {
	
	//if we are moving
	if (isMoving) {
		float tarX, tarY;//create variables for current targets

		if (path.size() > 0) {//if there are any more nodes to hit on the way to our target

			//get the next node's position
			pathfindingNodes->GetNodePos(path[0], tarX, tarY);

			//see if we're allredy at the node
			if ((posX < tarX + 20 && posX > tarX - 20)
			&& (posY < tarY + 20 && posY > tarY - 20)) {

				//if we are then we will move on instead
				path.erase(path.begin());//erase the last node

				//check for more nodes
				if (path.size() > 0) {

					//if we still have node to go to then we'll head there
					pathfindingNodes->GetNodePos(path[0], tarX, tarY);

				} else {

					//if there arn't any then we need to head to our final target
					tarX = targetX;
					tarY = targetY;
				}
			}
		} else {//if we're headed to our final target

			//check if we've arrived at out goal
			if ((posX < targetX + 20 && posX > targetX - 20)
			&& (posY < targetY + 20 && posY > targetY - 20)) {
				//if we have then we are done moving
				isMoving = false;
				//also we arn't headed anywhere so we'll try to move to where we already are
				tarX = targetX;
				tarY = targetY;
			} else {
				//if where arn't at our target yet then we'll keep heading there
				tarX = targetX;
				tarY = targetY;
			}
		}

		//find our direction by calculating the diference between where we are and our goal
		float directionX = posX - tarX;
		float directionY = posY - tarY;

		//find the magnitude of the direction to find the distance
		float distance = sqrt((directionX * directionX) + (directionY * directionY));

		//normalize the direction
		directionX = directionX / distance;
		directionY = directionY / distance;

		//if we are more than one steap away from the goal then move less than one steap
		float currentSpeed;
		if (distance > maxSpeed * in_deltaTime) {
			currentSpeed = maxSpeed * in_deltaTime;
		} else {
			currentSpeed = (maxSpeed * in_deltaTime) - distance;
		}

		//move our position
		posX -= directionX * currentSpeed;
		posY -= directionY * currentSpeed;
	}
}

void Agent::Draw() {
	MoveSprite(textureId, posX, posY);
	DrawSprite(textureId);
}