#include "AIE.h"
#include <iostream>
#include "Graph.h"
#include "Agent.h"

//constant vars
static int SCREEN_MAX_X = 900, SCREEN_MAX_Y = 600;

int main( int argc, char* argv[] )
{	
	Initialise(SCREEN_MAX_X, SCREEN_MAX_Y, false, "My Awesome Game");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));

	unsigned int GraphPointSpriteId = CreateSprite("images/invaders/invaders_7_01.png", 30, 30, true, SColour(255, 0, 0, 255));
	Agent agent = Agent(100, 100, 200);

	Graph graph = Graph();
	graph.AddNode(450, 500);
	graph.AddNode(800, 300);
	graph.AddNode(450, 100);
	graph.AddNode(100, 300);

	std::vector<int>names = graph.GetNames();

	graph.AddConnections(names[0], names[1]);
	graph.AddConnections(names[1], names[2]);
	graph.AddConnections(names[2], names[3]);
	graph.AddConnections(names[3], names[0]);

	graph.AddConnections(names[0], names[2]);
	graph.AddConnections(names[1], names[3]);

	agent.SetGraph(&graph);

    //Game Loop
    do
	{
        ClearScreen();

		//draw all nodes in graph and their connections
		for (int i = 0; i < names.size(); i++) {
			float x, y;//get position
			graph.GetNodePos(names[i], x, y);

			MoveSprite(GraphPointSpriteId, x, y);//draw node
			DrawSprite(GraphPointSpriteId);

			std::vector<int> edges = graph.GetNodesConectedTo(names[i]);//get edges

			for (int j = 0; j < edges.size(); j++) {
				float edgeX, edgeY;
				graph.GetNodePos(edges[j], edgeX, edgeY);//get edge end
				
				DrawLine(x, y, edgeX, edgeY, SColour(0, 0, 255, 255));//draw edge
			}

		}

		if (IsKeyDown('1')) {
			agent.GoTo(800, 500);
		}

		if (IsKeyDown('2')) {
			agent.GoTo(800, 100);
		}

		if (IsKeyDown('3')) {
			agent.GoTo(100, 100);
		}

		//update agent
		agent.Update(GetDeltaTime());
		//draw Agent
		agent.draw();

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}
