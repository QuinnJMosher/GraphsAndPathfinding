#include <stdio.h>
#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
	Graph graph = Graph();
	for (int i = 0; i < 8; i++) {
		graph.AddNode();
	}
	vector<int>names = graph.GetNames();
	graph.AddEdge(names[0], names[1], 1);
	graph.AddEdge(names[0], names[2], 1);
	graph.AddEdge(names[1], names[2], 1);
	graph.AddEdge(names[1], names[3], 1);
	graph.AddEdge(names[1], names[4], 2);
	graph.AddEdge(names[2], names[4], 1);
	graph.AddEdge(names[2], names[5], 3);
	graph.AddEdge(names[2], names[6], 3);
	graph.AddEdge(names[3], names[4], 1);
	graph.AddEdge(names[4], names[5], 1);
	graph.AddEdge(names[4], names[6], 1);
	graph.AddEdge(names[5], names[3], 3);
	graph.AddEdge(names[5], names[7], 1);
	graph.AddEdge(names[6], names[5], 1);
	graph.AddEdge(names[6], names[7], 0);

	cout << graph.IsConnectedDFS(names[0], names[7]) << endl;
	cout << graph.NodeDistanceDFS(names[0], names[7]) << endl;
	cout << graph.TraverseCostDFS(names[0], names[7]) << endl;

	cout << graph;
	cout << endl;
	system("pause");
	return 0;
}