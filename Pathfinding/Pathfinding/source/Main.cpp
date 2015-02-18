#include <stdio.h>
#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
	Graph graph = Graph();
	for (int i = 0; i < 5; i++) {
		graph.AddNode();
	}
	vector<int>names = graph.GetNames();
	graph.RemoveNode(names[2]);
	names = graph.GetNames();

	graph.AddEdge(names[0], names[2]);
	graph.AddEdge(names[3], names[1]);
	graph.AddEdge(names[0], names[1], 3);

	graph.AddConnections(names[1], names[0]);
	graph.AddConnections(names[3], names[2], 5);

	graph.RemoveNode(names[0]);
	names = graph.GetNames();

	cout << graph;
	cout << endl;
	system("pause");
	return 0;
}