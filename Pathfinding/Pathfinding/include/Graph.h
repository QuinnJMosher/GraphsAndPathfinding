#ifndef _Graph_h_
#define _Graph_h_

#include <iostream>
#include <vector>

class GrNode;

struct GrEdge {
	GrNode* end;

	float cost;
};

class GrNode {
public:
	GrNode(int in_name);
	~GrNode();

	void RemoveEdgesTo(int in_name);

	int name;

	std::vector<GrEdge>edges;
};

class Graph {
public:
	Graph();
	~Graph();

	int AddNode();//returns node name;
	void RemoveNode(int in_name);

	void AddEdge(int in_name_from, int in_name_to, float in_cost = 0);
	void AddConnections(int in_name_end1, int in_name_end2, float in_cost = 0);

	void RemoveEdge(int in_name_from, int in_name_to);
	void RemoveConections(int in_name_end1, int in_name_end2);
	void ClearEdges(int in_name);

	std::vector<int> GetNames();

	friend std::ostream& operator<<(std::ostream& stream, Graph& graph);

private:
	GrNode* FindNodeByName(int in_name);

	int nextNodeName;
	std::vector<GrNode*>nodes;
};

std::ostream& operator<<(std::ostream& stream, GrNode& grNode);
std::ostream& operator<<(std::ostream& stream, GrEdge& grEdge);

#endif