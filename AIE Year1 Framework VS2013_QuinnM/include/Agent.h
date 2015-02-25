#ifndef _Agent_h_
#define _Agent_h_
#include "AIE.h"
#include "Graph.h"

class Agent {
public:
	Agent(float in_startX, float in_startY, float in_maxSpeed);
	Agent();
	~Agent();

	void SetGraph(Graph* in_graph);
	void GoTo(float in_x, float in_y);
	void SmoothPath();

	void Update(float in_deltaTime);
	void Draw();

private:
	//position
	float posX;
	float posY;
	float maxSpeed;

	//pathfinding
	Graph* pathfindingNodes;
	std::vector<int>path;
	float targetX;
	float targetY;
	bool isMoving;

	//drawing
	unsigned int textureId;


};

#endif