#include "Graph.h"

GrNode::GrNode(int in_name) {
	name = in_name;
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

std::vector<int> Graph::GetNames() {
	std::vector<int>out;
	for (int i = 0; i < nodes.size(); i++) {
		out.emplace_back(nodes[i]->name);
	}
	return out;
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