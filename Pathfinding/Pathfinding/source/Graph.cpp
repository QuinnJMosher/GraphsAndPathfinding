#include "Graph.h"

GrNode::GrNode(int in_name) {
	name = in_name;
	visited = false;
	posX = 0.0f;
	posY = 0.0f;
}

GrNode::GrNode(int in_name, float in_x, float in_y) {
	name = in_name;
	visited = false;
	posX = in_x;
	posY = in_y;
}

GrNode::~GrNode() { }

void GrNode::RemoveEdgesTo(int in_name) {
	for (int i = 0; i < edges.size(); i++) {
		if (edges[i].end->name == in_name) {
			edges.erase(edges.begin() + i);
			i--;
		}
	}
}

Graph::Graph() {
	nextNodeName = 1;
}

Graph::~Graph() {
	for (int i = 0; i < nodes.size(); i++) {
		delete nodes[i];
	}
}

int Graph::AddNode() {
	nodes.emplace_back(new GrNode(nextNodeName));
	nextNodeName++;
	return nodes[nodes.size() - 1]->name;
}

int Graph::AddNode(float in_x, float in_y) {
	nodes.emplace_back(new GrNode(nextNodeName));
	nodes.back()->posX = in_x;
	nodes.back()->posY = in_y;
	nextNodeName++;
	return nodes[nodes.size() - 1]->name;
}

void Graph::RemoveNode(int in_name) {
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i]->RemoveEdgesTo(in_name);
	}
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i]->name == in_name) {
			delete nodes[i];
			nodes.erase(nodes.begin() + i);
		}
	}
}

void Graph::SetNodePos(int in_name, float in_x, float in_y){
	GrNode* target = FindNodeByName(in_name);
	target->posX = in_x;
	target->posY = in_y;
}

void Graph::GetNodePos(int in_name, float& in_x, float& in_y) {
	GrNode* target = FindNodeByName(in_name);
	in_x = target->posX;
	in_y = target->posY;
}

void Graph::AddEdge(int in_name_from, int in_name_to, float in_cost) {
	GrNode* source = FindNodeByName(in_name_from);
	GrNode* target = FindNodeByName(in_name_to);

	if (source != nullptr && target != nullptr) {
		GrEdge newEdge;
		newEdge.end = target;
		newEdge.cost = in_cost;

		source->edges.emplace_back(newEdge);
	}
}

void Graph::AddConnections(int in_name_end1, int in_name_end2, float in_cost) {
	GrNode* end1 = FindNodeByName(in_name_end1);
	GrNode* end2 = FindNodeByName(in_name_end2);

	if (end1 != nullptr && end2 != nullptr) {
		GrEdge newEdge;
		newEdge.cost = in_cost;

		newEdge.end = end1;
		end2->edges.emplace_back(newEdge);

		newEdge.end = end2;
		end1->edges.emplace_back(newEdge);
	}
}

void Graph::RemoveEdge(int in_name_from, int in_name_to) {
	GrNode* source = FindNodeByName(in_name_from);

	if (source != nullptr) {
		source->RemoveEdgesTo(in_name_to);
	}
}
void Graph::RemoveConections(int in_name_end1, int in_name_end2) {
	GrNode* end1 = FindNodeByName(in_name_end1);
	GrNode* end2 = FindNodeByName(in_name_end2);

	if (end1 != nullptr) {
		end1->RemoveEdgesTo(in_name_end2);
	}
	if (end2 != nullptr) {
		end2->RemoveEdgesTo(in_name_end1);
	}
}
void Graph::ClearEdges(int in_name) {
	GrNode* target = FindNodeByName(in_name);

	if (target != nullptr) {
		target->edges.clear();
	}
}

GrNode* Graph::FindNodeByName(int in_name) {
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i]->name == in_name) {
			return nodes[i];
		}
	}
	return nullptr;
}

void Graph::ResetVisited() {
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i]->visited = false;
	}
}

std::vector<int> Graph::GetNames() {
	std::vector<int>out;
	for (int i = 0; i < nodes.size(); i++) {
		out.emplace_back(nodes[i]->name);
	}
	return out;
}

bool Graph::IsConnectedDFS(int in_name_start, int in_name_end) {
	ResetVisited();
	GrNode* start = FindNodeByName(in_name_start);
	GrNode* end = FindNodeByName(in_name_end);

	std::stack<GrNode*> nodeStack = std::stack<GrNode*>();
	nodeStack.push(start);

	while (!nodeStack.empty())
	{
		GrNode* current = nodeStack.top();
		nodeStack.pop();

		if (current->visited == true)
		{
			continue;
		}

		current->visited = true;

		if (current == end)
		{
			return true;
		}

		for (int i = 0; i < current->edges.size(); ++i) {
			nodeStack.push(current->edges[i].end);
		}
	}

	return false;
}

int Graph::NodeDistanceDFS(int in_name_start, int in_name_end) {
	ResetVisited();
	GrNode* end = FindNodeByName(in_name_end);

	std::stack<GrNode*> nodeStack = std::stack<GrNode*>();
	nodeStack.push(FindNodeByName(in_name_start));

	std::vector<GrNode*> path = std::vector<GrNode*>();

	while (!nodeStack.empty())
	{
		GrNode* current = nodeStack.top();
		path.emplace_back(current);
		nodeStack.pop();

		if (current->visited == true)
		{
			continue;
		}

		current->visited = true;

		if (current == end)
		{
			return path.size() - 1;
		}

		if (current->edges.size() > 0) {
			for (int i = 0; i < current->edges.size(); ++i) {
				nodeStack.push(current->edges[i].end);
			}
		} else {
			path.erase(path.end());
		}

		for (int i = path.size() - 1; i >= 0; i--) {
			bool UnvisitedNodes = false;
			for (int j = 0; j < path[i]->edges.size(); j++) {
				if (path[i]->edges[j].end->visited == false) {
					UnvisitedNodes = true;
				}
			}
			if (!UnvisitedNodes) {
				path.erase(path.begin() + i);
			}
		}
	}

	return -1;
}
int Graph::TraverseCostDFS(int in_name_start, int in_name_end) {
	ResetVisited();
	GrNode* end = FindNodeByName(in_name_end);

	std::stack<GrNode*> nodeStack = std::stack<GrNode*>();
	nodeStack.push(FindNodeByName(in_name_start));

	std::vector<GrNode*> path = std::vector<GrNode*>();

	while (!nodeStack.empty())
	{
		GrNode* current = nodeStack.top();
		path.emplace_back(current);
		nodeStack.pop();

		if (current->visited == true)
		{
			continue;
		}

		current->visited = true;

		if (current == end)
		{
			int cost = 0;
			for (int i = 0; i < path.size() - 1; i++) {
				int nextEdgeCost;
				for (int j = 0; j < path[i]->edges.size(); j++) {
					if (path[i]->edges[j].end == path[i + 1]) {
						nextEdgeCost = path[i]->edges[j].cost;
					}
				}

				cost += 1 + nextEdgeCost;
			}
			return cost;
		}

		if (current->edges.size() > 0) {
			for (int i = 0; i < current->edges.size(); ++i) {
				nodeStack.push(current->edges[i].end);
			}
		}
		else {
			path.erase(path.end());
		}

		for (int i = path.size() - 1; i >= 0; i--) {
			bool UnvisitedNodes = false;
			for (int j = 0; j < path[i]->edges.size(); j++) {
				if (path[i]->edges[j].end->visited == false) {
					UnvisitedNodes = true;
				}
			}
			if (!UnvisitedNodes) {
				path.erase(path.begin() + i);
			}
		}
	}

	return -1;
}


std::ostream& operator<<(std::ostream& stream, Graph& graph) {
	//post graph
	stream << "Graph: {\n";
	//post all nodes
	for (int i = 0; i < graph.nodes.size(); i++) {
		//post node name
		stream << (*graph.nodes[i]);

		//check if there are any edges
		if (graph.nodes[i]->edges.size() > 0) {
			//post list of edges
			stream << "-> ";

			//post all edges
			for (int j = 0; j < graph.nodes[i]->edges.size(); j++) {
				//post edge
				stream << " " << graph.nodes[i]->edges[j] << " |";
			}

		} else {
			//show there are no edges
			stream << ";";
		}
		//end line for node
		stream << std::endl;
	}
	//close graph
	stream << "}\n";
	//return
	return stream;
}

std::ostream& operator<<(std::ostream& stream, GrNode& grNode) {
	stream << grNode.name;
	return stream;
}
std::ostream& operator<<(std::ostream& stream, GrEdge& grEdge) {
	stream << "T:" << grEdge.end->name << " C:" << grEdge.cost;
	return stream;
}